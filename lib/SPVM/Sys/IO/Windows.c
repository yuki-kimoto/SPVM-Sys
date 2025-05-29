// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Sys/IO/Windows.c";

#if defined(_WIN32)

#include "Sys-Windows.h"

#define isSLASHW(c) ((c) == L'/' || (c) == L'\\')
#define strEQW(string1, string2) (wcscmp(string1, string2) == 0)

// The logic is the same as Perl's win32_symlink in Win32.c, and supports UTF-8 arugments.
static int win32_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const WCHAR *oldpath_w, const WCHAR *newpath_w) {
  DWORD create_flags = SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
  size_t oldpath_w_len = wcslen(oldpath_w);
  
  if (wcschr(oldpath_w, L'/')) {
    /* Win32 (or perhaps NTFS) won't follow symlinks containing
       /, so replace any with \\
    */
    WCHAR *temp = (WCHAR*)env->new_memory_block(env, stack, (wcslen(oldpath_w) + 1) * sizeof(WCHAR));
    memcpy(temp, oldpath_w, (wcslen(oldpath_w) + 1) * sizeof(WCHAR));
    WCHAR *p = temp;
    while (*p) {
      if (*p == L'/') {
        *p = L'\\';
      }
      ++p;
    }
    *p = 0;
    oldpath_w = temp;
    oldpath_w_len = p - temp;
    env->free_memory_block(env, stack, temp);
  }
  
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
  if ((oldpath_w_len >= 1 && isSLASHW(oldpath_w[oldpath_w_len - 1])) ||
    strEQW(oldpath_w, L"..") ||
    strEQW(oldpath_w, L".") ||
    (isSLASHW(oldpath_w[oldpath_w_len-2]) && oldpath_w[oldpath_w_len - 1] == L'.') ||
    strEQW(oldpath_w+oldpath_w_len-3, L"\\..") ||
    (oldpath_w_len == 2 && oldpath_w[1] == L':')) {
    create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
  }
  else {
    DWORD dest_attr;
    const WCHAR *dest_path_w = oldpath_w;
    WCHAR target_name_w[MAX_PATH+1];
    
    if (oldpath_w_len >= 3 && oldpath_w[1] == L':') {
      /* relative to current directory on a drive, or absolute */
      /* dest_path_w = oldpath_w; already done */
    }
    else if (oldpath_w[0] != L'\\') {
      size_t newpath_w_len = wcslen(newpath_w);
      WCHAR *last_slash_w = wcsrchr(newpath_w, L'/');
      WCHAR *last_bslash_w = wcsrchr(newpath_w, L'\\');
      WCHAR *end_dir_w = last_slash_w && last_bslash_w
        ? ( last_slash_w > last_bslash_w ? last_slash_w : last_bslash_w)
        : last_slash_w ? last_slash_w : last_bslash_w ? last_bslash_w : NULL;
      
      if (end_dir_w) {
        if ((end_dir_w - newpath_w + 1) + oldpath_w_len > MAX_PATH) {
          /* too long */
          errno = EINVAL;
          return -1;
        }
        
        memcpy(target_name_w, newpath_w, (end_dir_w - newpath_w + 1) * sizeof(WCHAR));
        wcscpy(target_name_w + (end_dir_w - newpath_w + 1), oldpath_w);
        dest_path_w = target_name_w;
      }
      else {
        /* newpath_w is just a filename */
        /* dest_path_w = oldpath_w; */
      }
    }
    
    dest_attr = GetFileAttributesW(dest_path_w);
    if (dest_attr != (DWORD)-1 && (dest_attr & FILE_ATTRIBUTE_DIRECTORY)) {
      create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
    }
  }
  
  if (!CreateSymbolicLinkW(newpath_w, oldpath_w, create_flags)) {
    win_last_error_to_errno();
    return -1;
  }
  
  return 0;
}

#endif // _WIN32

// This logic is the same as Perl's win32_unlink in Win32.c, and UTF-8 arguments are supported.
int32_t SPVM__Sys__IO__Windows__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#unlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  WCHAR* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  int32_t status = -1;
  
  DWORD attrs = GetFileAttributesW(path_w);
  
  if (attrs == 0xFFFFFFFF) {
    errno = ENOENT;
    status = -1;
    goto END_OF_FUNC;
  }
  
  if (attrs & FILE_ATTRIBUTE_READONLY) {
    SetFileAttributesW(path_w, attrs & ~FILE_ATTRIBUTE_READONLY);
    status = _wunlink(path_w);
    if (status == -1) {
      SetFileAttributesW(path_w, attrs);
    }
  }
  else if ((attrs & (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY))
    == (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY)
         && is_symlink(path_w))
  {
    status = _wrmdir(path_w);
  }
  else {
    status = _wunlink(path_w);
  }
  
  END_OF_FUNC:
  
  if (status == -1) {
    env->die(env, stack, "[System Error]unlink() failed(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

// This logic is the same as Perl's win32_rename in Win32.c, and UTF-8 arguments are supported.
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
  
  WCHAR* oldpath_w = utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  WCHAR* newpath_w = utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  DWORD flags = MOVEFILE_COPY_ALLOWED;
  if (!(_wcsicmp(newpath_w, oldpath_w) == 0)) {
    flags |= MOVEFILE_REPLACE_EXISTING;
  }
  
  int32_t success = MoveFileExW(oldpath_w, newpath_w, flags);
  
  int32_t status = -1;
  if (success) {
    status = 0;
  }
  else {
    DWORD last_error = GetLastError();
    switch (last_error) {
      case ERROR_BAD_NET_NAME:
      case ERROR_BAD_NETPATH:
      case ERROR_BAD_PATHNAME:
      case ERROR_FILE_NOT_FOUND:
      case ERROR_FILENAME_EXCED_RANGE:
      case ERROR_INVALID_DRIVE:
      case ERROR_NO_MORE_FILES:
      case ERROR_PATH_NOT_FOUND:
      {
        errno = ENOENT;
        break;
      }
      case ERROR_DISK_FULL: {
        errno = ENOSPC;
        break;
      }
      case ERROR_NOT_ENOUGH_QUOTA: {
        errno = EDQUOT;
        break;
      }
      default: {
        errno = EACCES;
        break;
      }
    }
  }
  
  if (status == -1) {
    env->die(env, stack, "[System Error]MoveFileExW() for renaming failed(%d: %s). $oldpath=\"%s\", $newpath=\"%s\".", errno, env->strerror_nolen(env, stack, errno), oldpath, newpath, __func__, FILE_NAME, __LINE__);
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
  
  WCHAR* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  DWORD fileattr = GetFileAttributesW(path_w);
  if (fileattr == INVALID_FILE_ATTRIBUTES) {
    win_last_error_to_errno();
    env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);    
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  MY_REPARSE_DATA_BUFFER linkdata;
  DWORD linkdata_returned;
  HANDLE handle = NULL;
  if (fileattr & FILE_ATTRIBUTE_REPARSE_POINT) {
    handle = CreateFileW_reparse_point_for_read(path_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      win_last_error_to_errno();
      env->die(env, stack, "[System Error]CreateFileW() failed when opening a file(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
    
    if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
      win_last_error_to_errno();
      env->die(env, stack, "[System Error]DeviceIoControl() failed(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  else {
    handle = CreateFileW_for_read(path_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      win_last_error_to_errno();
      env->die(env, stack, "[System Error]CreateFileW() failed when opening a file(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
    else {
      errno = EINVAL;
      env->die(env, stack, "[System Error]This file is not a reparse point. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  const WCHAR* PathBuffer = NULL;
  int32_t PrintNameOffset = -1;
  int32_t PrintNameLength = -1;
  switch (linkdata.ReparseTag) {
    case IO_REPARSE_TAG_SYMLINK: {
      const MY_SYMLINK_REPARSE_BUFFER * const sd =
        &linkdata.Data.SymbolicLinkReparseBuffer;
      if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)) {
        errno = ENOMEM;
        env->die(env, stack, "[System Error]The data DeviceIoControl() retruned is invalid. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
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
        errno = ENOMEM;
        env->die(env, stack, "[System Error]The data DeviceIoControl() retruned is invalid. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
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
      env->die(env, stack, "[System Error]The type of the reparse point must be IO_REPARSE_TAG_SYMLINK or IO_REPARSE_TAG_MOUNT_POINT. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
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
    env->die(env, stack, "[System Error]WideCharToMultiByte() failed. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
    errno = EILSEQ;
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
    env->die(env, stack, "[System Error]WideCharToMultiByte() failed. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
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
  
  WCHAR* oldpath_w = utf8_to_win_wchar(env, stack, oldpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  WCHAR* newpath_w = utf8_to_win_wchar(env, stack, newpath, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  errno = 0;
  int32_t status = win32_symlink(env, stack, oldpath_w, newpath_w);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]win32_symlink() failed(%d: %s). $oldpath=\"%s\", $newpath=\"%s\".", errno, env->strerror_nolen(env, stack, errno), oldpath, newpath, __func__, FILE_NAME, __LINE__);
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
  
  void* obj_resolved_path_tmp = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  if (obj_resolved_path_tmp) {
    return env->die(env, stack, "The resolved path $resolved_path must not be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_resolved_link_text = NULL;
  {
    void* obj_link_text = NULL;
    stack[0].oval = obj_path;
    env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "_follow_symlinks_to", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      goto END_OF_FUNC;
    }
    obj_resolved_link_text = stack[0].oval;
  }
  const char* resolved_link_text = env->get_chars(env, stack, obj_resolved_link_text);
  
  WCHAR* resolved_link_text_w = utf8_to_win_wchar(env, stack, resolved_link_text, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  HANDLE handle = CreateFileW_reparse_point_for_read(resolved_link_text_w);
  
  if (handle == INVALID_HANDLE_VALUE) {
    win_last_error_to_errno();
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  int32_t needed_len = GetFinalPathNameByHandleW(handle, NULL, 0, 0);
  
  if (needed_len == 0) {
    env->die(env, stack, "[System Error]GetFinalPathNameByHandleW() failed. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  void* obj_resolved_path_w = env->new_short_array(env, stack, needed_len);
  WCHAR* resolved_path_w = (WCHAR*)env->get_elems_short(env, stack, obj_resolved_path_w);
  
  int32_t len = GetFinalPathNameByHandleW(handle, resolved_path_w, needed_len, 0);
  
  if (len == 0) {
    env->die(env, stack, "[System Error]GetFinalPathNameByHandleW() failed. $path=\"%s\".", path, __func__, FILE_NAME, __LINE__);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  char* resolved_path_tmp = (char*)win_wchar_to_utf8(env, stack, resolved_path_w, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  void* obj_resolved_path = env->new_string(env, stack, resolved_path_tmp, strlen(resolved_path_tmp));
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
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]win_realpath() failed(%d: %s). $path=\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    }
    
    return error_id;
  }
  
  stack[0].oval = obj_resolved_path;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Windows__is_symlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#is_symlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  WCHAR* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  int32_t ret = is_symlink(path_w);
  
  stack[0].ival = ret;
  
  return 0;
#endif
}
