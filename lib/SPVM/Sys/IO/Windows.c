// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Sys/IO/Windows.c";

#if defined(_WIN32)

// These implementations are originally copied form Perl win32/win32.c and win32/win32.h

#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>
#include <errno.h>
#include <winbase.h>
#include <fcntl.h>
#include <direct.h>

#include "Sys-Windows.h"

#endif // _WIN32

int32_t SPVM__Sys__IO__Windows__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#unlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  void* obj_pathname = stack[0].oval;
  if (!obj_pathname) {
    return env->die(env, stack, "The path $pathname must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* pathname = env->get_chars(env, stack, obj_pathname);
  
  wchar_t* pathname_w = utf8_to_win_wchar(env, stack, pathname, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  int32_t status = win32_unlink(pathname_w);
  
  stack[0].ival = status;
  if (status == -1) {
    env->die(env, stack, "[System Error]unlink() failed:%s. $pathname is \"%s\".", env->strerror_nolen(env, stack, errno), pathname, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Windows__rename(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#rename method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  void* obj_oldpath = stack[0].oval;
  if (!obj_oldpath) {
    return env->die(env, stack, "The old path $oldpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* oldpath = env->get_chars(env, stack, obj_oldpath);
  
  void* obj_newpath = stack[1].oval;
  if (!obj_newpath) {
    return env->die(env, stack, "The new path $newpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* newpath = env->get_chars(env, stack, obj_newpath);
  
  wchar_t* oldpath_w = utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  wchar_t* newpath_w = utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  int32_t status = win32_rename(oldpath_w, newpath_w);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]rename() failed:%s. $oldpath is \"%s\". $newpath is \"%s\".", env->strerror_nolen(env, stack, errno), oldpath, newpath, __func__, FILE_NAME, __LINE__);
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
  
  void* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  wchar_t* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  
  DWORD fileattr = GetFileAttributesW(path_w);
  if (fileattr == INVALID_FILE_ATTRIBUTES) {
    translate_to_errno();
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  if (!(fileattr & FILE_ATTRIBUTE_REPARSE_POINT)) {
    /* not a symbolic link */
    errno = EINVAL;
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  HANDLE hlink =
    CreateFileW(path_w, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
  if (hlink == INVALID_HANDLE_VALUE) {
    translate_to_errno();
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  MY_REPARSE_DATA_BUFFER linkdata;
  DWORD linkdata_returned;
  
  if (!DeviceIoControl(hlink, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
    translate_to_errno();
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  const wchar_t* PathBuffer = NULL;
  int32_t PrintNameOffset = -1;
  int32_t PrintNameLength = -1;
  switch (linkdata.ReparseTag) {
    case IO_REPARSE_TAG_SYMLINK: {
      const MY_SYMLINK_REPARSE_BUFFER * const sd =
        &linkdata.Data.SymbolicLinkReparseBuffer;
      if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)) {
        errno = EINVAL;
        error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
        goto END_OF_FUNC;
      }
      
      PathBuffer = sd->PathBuffer;
      PrintNameOffset = sd->PrintNameOffset;
      PrintNameLength = sd->PrintNameLength;
      
      break;
    }
    case IO_REPARSE_TAG_MOUNT_POINT: {
      const MY_MOUNT_POINT_REPARSE_BUFFER * const rd =
        &linkdata.Data.MountPointReparseBuffer;
      if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.MountPointReparseBuffer.PathBuffer)) {
        errno = EINVAL;
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
    /*() failed.conversion from unicode to ANSI or otherwise() failed.*/
    errno = EINVAL;
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  void* obj_link_text = env->new_string(env, stack, NULL, bytes_out);
  char* link_text = (char*)env->get_chars(env, stack, obj_link_text);
  
  bytes_out =
    WideCharToMultiByte(CP_UTF8, 0,
                        PathBuffer + PrintNameOffset/2,
                        PrintNameLength/2,
                        link_text, bytes_out, NULL, NULL);
  if (bytes_out == 0) {
    /*() failed.conversion from unicode to ANSI or otherwise() failed.*/
    errno = EINVAL;
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (!(hlink == INVALID_HANDLE_VALUE)) {
    CloseHandle(hlink);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]win_readlink() failed:%s. $path is \"%s\".", env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    }
    
    return error_id;
  }
  
  stack[0].oval = obj_link_text;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Windows__symlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#symlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  int32_t error_id = 0;
  
  void* obj_oldpath = stack[0].oval;
  
  void* obj_newpath = stack[1].oval;
  
  if (!obj_oldpath) {
    return env->die(env, stack, "The old path $oldpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* oldpath = env->get_chars(env, stack, obj_oldpath);
  
  if (!obj_newpath) {
    return env->die(env, stack, "The new path $newpath must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* newpath = env->get_chars(env, stack, obj_newpath);
  
  wchar_t* oldpath_w = utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  wchar_t* newpath_w = utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  errno = 0;
  int32_t status = win32_symlink(env, stack, oldpath_w, newpath_w);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]win32_symlink() failed:%s. $oldpath is \"%s\". $newpath is \"%s\".", env->strerror_nolen(env, stack, errno), oldpath, newpath, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Windows__realpath(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  return env->die(env, stack, "Sys::IO::Windows#realpath method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
#else
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  void* obj_resolved_path = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (obj_resolved_path) {
    return env->die(env, stack, "The resolved path $resolved_path must not be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  wchar_t* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  int32_t len = win32_realpath(path_w, NULL, 0);
  
  if (len == -1) {
    env->die(env, stack, "[System Error]CreateFile() failed:the symbolic link is not permitted, broken or not found. $path:\"%s\".", path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  else if (!(len > 0)) {
    env->die(env, stack, "[System Error]win32_realpath() failed:GetLastError() %d. $path:\"%s\".", GetLastError(), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  void* obj_resolved_path_w = env->new_short_array(env, stack, len + 1);
  wchar_t* resolved_path_w = (wchar_t*)env->get_elems_short(env, stack, obj_resolved_path_w);
  
  len = win32_realpath(path_w, resolved_path_w, len);
  
  if (!(len > 0)) {
    env->die(env, stack, "[System Error]win32_realpath() failed:GetLastError() %d. $path:\"%s\".", GetLastError(), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  const char* resolved_path_tmp = win_wchar_to_utf8(env, stack, resolved_path_w, &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    return error_id;
  }
  obj_resolved_path = env->new_string(env, stack, resolved_path_tmp, strlen(resolved_path_tmp));
  char* resolved_path = (char*)env->get_chars(env, stack, obj_resolved_path);
  int32_t resolved_path_length = env->length(env, stack, obj_resolved_path);
  
  if (strncmp(resolved_path, "\\\\?\\", 4) == 0) {
    for (int32_t i = 0; i < resolved_path_length - 4; i++) {
      resolved_path[i] = resolved_path[i + 4];
    }
    env->shorten(env, stack, obj_resolved_path, resolved_path_length - 4);
  }
  else if (strncmp(resolved_path, "\\\\?\\UNC\\", 8) == 0) {
    for (int32_t i = 2; i < resolved_path_length - 6; i++) {
      resolved_path[i] = resolved_path[i + 6];
    }
    env->shorten(env, stack, obj_resolved_path, resolved_path_length - 8);
  }
  
  for (int32_t i = 0; i < resolved_path_length; i++) {
    if (resolved_path[i] == '\\') {
      resolved_path[i] = '/';
    }
  }
  
  stack[0].oval = obj_resolved_path;
  
  return 0;
#endif
}
