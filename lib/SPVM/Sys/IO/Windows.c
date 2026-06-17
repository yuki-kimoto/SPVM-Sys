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

// This logic is the same as Perl's win32_rename in win32.c, and UTF-8 arguments are supported.
int32_t SPVM__Sys__IO__Windows__rename(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#rename method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_oldpath = stack[0].oval;
  if (!obj_oldpath) {
    return env->die(env, stack, "The old path $oldpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* oldpath = env->get_chars(env, stack, obj_oldpath);
  
  SPVM_OBJ* obj_newpath = stack[1].oval;
  if (!obj_newpath) {
    return env->die(env, stack, "The new path $newpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* newpath = env->get_chars(env, stack, obj_newpath);
  
  WCHAR* oldpath_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  WCHAR* newpath_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  DWORD flags = MOVEFILE_COPY_ALLOWED;
  if (!(_wcsicmp(newpath_w, oldpath_w) == 0)) {
    flags |= MOVEFILE_REPLACE_EXISTING;
  }
  
  int32_t success = MoveFileExW(oldpath_w, newpath_w, flags);
  
  int32_t status = success ? 0 : -1;
  
  if (status == -1) {
    spvm_sys_windows_util_win_last_error_to_errno(EACCES);
    env->die(env, stack, "[System Error]MoveFileExW() for renaming failed(%d: %s). $oldpath='%s', $newpath='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), oldpath, newpath);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

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

// The logic is the same as Perl's win32_symlink in win32.c
int32_t SPVM__Sys__IO__Windows__symlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#symlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_oldpath = stack[0].oval;
  
  SPVM_OBJ* obj_newpath = stack[1].oval;
  
  if (!obj_oldpath) {
    return env->die(env, stack, "The old path $oldpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* oldpath = env->get_chars(env, stack, obj_oldpath);
  
  if (!obj_newpath) {
    return env->die(env, stack, "The new path $newpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* newpath = env->get_chars(env, stack, obj_newpath);
  
  WCHAR* oldpath_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  WCHAR* newpath_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  // Win32 (or perhaps NTFS) won't follow symlinks containing /, so replace any with \\.
  int32_t oldpath_w_length = wcslen(oldpath_w);
  for (int32_t i = 0; i < oldpath_w_length; i++) {
    if (oldpath_w[i] == L'/') {
      oldpath_w[i] = L'\\';
    }
  }
  
  DWORD create_flags = SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
  /* are we linking to a directory?
     CreateSymlinkW() needs to know if the target is a directory,
     If it looks like a directory name:
      - ends in slash
      - is just . or ..
      - ends in /. or /.. (with either slash)
      - is a simple drive letter
     assume it's a directory.
     Otherwise if the oldpath_w is relative we need to make a relative path
     based on the newpath_w to check if the target is a directory.
  */
  int32_t oldpath_is_dir = 0;
  if (oldpath_w_length >= 1 && is_path_separator(oldpath_w[oldpath_w_length - 1])) {
    oldpath_is_dir = 1;
  }
  else if (wcscmp(oldpath_w, L"..") == 0) {
    oldpath_is_dir = 1;
  }
  else if (wcscmp(oldpath_w, L".") == 0) {
    oldpath_is_dir = 1;
  }
  else if (oldpath_w_length >= 2 && is_path_separator(oldpath_w[oldpath_w_length - 2]) && oldpath_w[oldpath_w_length - 1] == L'.') {
    oldpath_is_dir = 1;
  }
  else if (oldpath_w_length >= 3 && wcscmp(oldpath_w+oldpath_w_length - 3, L"\\..") == 0) {
    oldpath_is_dir = 1;
  }
  else if (oldpath_w_length == 2 && oldpath_w[1] == L':') {
    oldpath_is_dir = 1;
  }
  
  if (oldpath_is_dir) {
    create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
  }
  else {
    const WCHAR *resolved_path_w = NULL;
    WCHAR *resolved_path_w_tmp = NULL;
    
    int32_t oldpath_is_abs = 0;
    if (oldpath_w_length >= 3 && oldpath_w[1] == L':') {
      /* relative to current directory on a drive, or absolute */
      oldpath_is_abs = 1;
    }
    else if (oldpath_w[0] == L'\\') {
      oldpath_is_abs = 1;
    }
    
    if (oldpath_is_abs) {
      resolved_path_w = oldpath_w;
    }
    else {
      int32_t last_sep_index = -1;
      size_t newpath_w_length = wcslen(newpath_w);
      for (int32_t i = newpath_w_length - 1; i >= 0; i--) {
        char ch = newpath_w[i];
        if (ch == '\\' || ch == '/') {
          last_sep_index = i;
          break;
        }
      }
      
      if (last_sep_index >= 0) {
        resolved_path_w_tmp = env->new_memory_block(env, stack, (last_sep_index + 1 + oldpath_w_length + 1) * sizeof(WCHAR));
        memcpy(resolved_path_w_tmp, newpath_w, sizeof(WCHAR) * (last_sep_index + 1));
        memcpy(resolved_path_w_tmp + (last_sep_index + 1), oldpath_w, oldpath_w_length);
        resolved_path_w = resolved_path_w_tmp;
      }
      else {
        /* newpath_w is just a filename */
        resolved_path_w = oldpath_w;
      }
    }
    
    DWORD dest_attr = GetFileAttributesW(resolved_path_w);
    if (dest_attr != (DWORD)-1 && (dest_attr & FILE_ATTRIBUTE_DIRECTORY)) {
      create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
    }
    
    if (resolved_path_w_tmp) {
      env->free_memory_block(env, stack, resolved_path_w_tmp);
    }
  }
  
  int32_t success = CreateSymbolicLinkW(newpath_w, oldpath_w, create_flags);
  int32_t status = success ? 0 : -1;
  if (status == -1) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
  }
  
  if (status == -1) {
    env->die(env, stack, "[System Error]CreateSymbolicLinkW() failed(%d: %s). $oldpath='%s', $newpath='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), oldpath, newpath);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}
