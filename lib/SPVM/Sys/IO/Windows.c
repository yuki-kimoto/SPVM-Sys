#if defined(_WIN32)

#include "spvm_sys_windows.h"

#include <direct.h>

#endif // _WIN32

#include "spvm_native.h"

#if defined(_WIN32)

static inline int32_t is_path_separator(WCHAR ch_w) {
  return (ch_w == L'/' || ch_w == L'\\');
};

#endif // _WIN32

static const char* FILE_NAME = "Sys/IO/Windows.c";

int32_t SPVM__Sys__IO__Windows__win_readlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#win_readlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else

  int32_t error_id = 0;
  SPVM_OBJ* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER linkdata;
  DWORD linkdata_returned;
  HANDLE handle = NULL;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  DWORD fileattr = GetFileAttributesW(path_w);
  if (fileattr == INVALID_FILE_ATTRIBUTES) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);    
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  if (fileattr & FILE_ATTRIBUTE_REPARSE_POINT) {
    handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(path_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      env->die(env, stack, "[System Error]CreateFileW() failed when opening a file(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
    
    if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      env->die(env, stack, "[System Error]DeviceIoControl() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  else {
    handle = spvm_sys_windows_util_CreateFileW_for_read(path_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      env->die(env, stack, "[System Error]CreateFileW() failed when opening a file(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
    else {
      errno = EINVAL;
      env->die(env, stack, "[System Error]This file is not a reparse point. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  const WCHAR* PathBuffer = NULL;
  int32_t PrintNameOffset = -1;
  int32_t PrintNameLength = -1;
  switch (linkdata.ReparseTag) {
    case IO_REPARSE_TAG_SYMLINK: {
      const SPVM_SYS_WINDOWS_SYMLINK_REPARSE_BUFFER * const sd =
        &linkdata.Data.SymbolicLinkReparseBuffer;
      if (linkdata_returned < offsetof(SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)) {
        errno = ENOMEM;
        env->die(env, stack, "[System Error]The data DeviceIoControl() retruned is invalid. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
        error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
        goto END_OF_FUNC;
      }
      
      PathBuffer = sd->PathBuffer;
      PrintNameOffset = sd->PrintNameOffset;
      PrintNameLength = sd->PrintNameLength;
      
      break;
    }
    case IO_REPARSE_TAG_MOUNT_POINT: {
      const SPVM_SYS_WINDOWS_MOUNT_POINT_REPARSE_BUFFER * const rd =
        &linkdata.Data.MountPointReparseBuffer;
      if (linkdata_returned < offsetof(SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER, Data.MountPointReparseBuffer.PathBuffer)) {
        errno = ENOMEM;
        env->die(env, stack, "[System Error]The data DeviceIoControl() retruned is invalid. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
        error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
        goto END_OF_FUNC;
      }
      
      PathBuffer = rd->PathBuffer;
      PrintNameOffset = rd->PrintNameOffset;
      PrintNameLength = rd->PrintNameLength;
      break;
    }
    default: {
      errno = EINVAL;
      env->die(env, stack, "[System Error]The type of the reparse point must be IO_REPARSE_TAG_SYMLINK or IO_REPARSE_TAG_MOUNT_POINT. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  int32_t bytes_out =
    WideCharToMultiByte(CP_UTF8, 0,
                        PathBuffer + PrintNameOffset/2,
                        PrintNameLength/2,
                        NULL, 0, NULL, NULL);
                        
  if (bytes_out == 0) {
    env->die(env, stack, "[System Error]WideCharToMultiByte() failed. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
    errno = EILSEQ;
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  SPVM_OBJ* obj_link_text = env->new_string(env, stack, NULL, bytes_out);
  char* link_text = (char*)env->get_chars(env, stack, obj_link_text);
  
  bytes_out =
    WideCharToMultiByte(CP_UTF8, 0,
                        PathBuffer + PrintNameOffset/2,
                        PrintNameLength/2,
                        link_text, bytes_out, NULL, NULL);
  if (bytes_out == 0) {
    env->die(env, stack, "[System Error]WideCharToMultiByte() failed. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
    errno = EILSEQ;
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    return error_id;
  }
  
  stack[0].oval = obj_link_text;
  
  return 0;
#endif
}

