#if defined(_WIN32)

#include "spvm_sys_windows.h"

void* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  if (utf8_string == NULL) {
    return NULL;
  }
  
  int32_t utf16le_string_length = MultiByteToWideChar(
      CP_UTF8,
      0,
      utf8_string,
      -1,
      NULL,
      0
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die_v2(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  void* obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
  WCHAR* utf16le_string = env->get_elems_short(env, stack, obj_utf16le_string);
  
  utf16le_string_length = MultiByteToWideChar(
    CP_UTF8,
    0,
    utf8_string,
    -1,
    utf16le_string,
    utf16le_string_length
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die_v2(env, stack,  "utf8_to_win_wchar failed:Error converting UTF-8 to UTF-16LE: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf16le_string;
}

const char* spvm_sys_windows_win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, WCHAR* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  if (utf16le_string == NULL) {
    return NULL;
  }
  
  int32_t utf8_string_length = WideCharToMultiByte(
    CP_UTF8,
    0,
    utf16le_string,
    -1,
    NULL,
    0,
    NULL,
    NULL
  );
  
  if (utf8_string_length == 0) {
    *error_id = env->die_v2(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  void* obj_utf8_string = env->new_string(env, stack, NULL, utf8_string_length);
  
  char* utf8_string = (char*)env->get_chars(env, stack, obj_utf8_string);
  
  utf8_string_length = WideCharToMultiByte(
    CP_UTF8,
    0,
    utf16le_string,
    -1,
    utf8_string,
    utf8_string_length,
    NULL,
    NULL
  );
  
  if (utf8_string_length == 0) {
    *error_id = env->die_v2(env, stack,  "win_wchar_to_utf8 failed:Error converting UTF-16LE to UTF-8: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf8_string;
}

void spvm_sys_windows_win_last_error_to_errno(int32_t default_errno) {
  /* This isn't perfect, eg. Win32 returns ERROR_ACCESS_DENIED for
     both permissions errors and if the source is a directory, while
     POSIX wants EACCES and EPERM respectively.
  */
  switch (GetLastError()) {
    case ERROR_BAD_NET_NAME:
    case ERROR_BAD_NETPATH:
    case ERROR_BAD_PATHNAME:
    case ERROR_FILE_NOT_FOUND:
    case ERROR_FILENAME_EXCED_RANGE:
    case ERROR_INVALID_DRIVE:
    case ERROR_PATH_NOT_FOUND:
    {
      errno = ENOENT;
      break;
    }
    case ERROR_ALREADY_EXISTS: {
      errno = EEXIST;
      break;
    }
    case ERROR_ACCESS_DENIED: {
      errno = EACCES;
      break;
    }
    case ERROR_PRIVILEGE_NOT_HELD: {
      errno = EPERM;
      break;
    }
    case ERROR_NOT_SAME_DEVICE: {
      errno = EXDEV;
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
      errno = default_errno;
    }
  }
}

static HANDLE spvm_sys_windows_CreateFileW_for_read_common(const WCHAR* path_w, int32_t file_flag) {

  HANDLE handle = CreateFileW(path_w, GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
    file_flag|FILE_FLAG_BACKUP_SEMANTICS, 0
  );
  
  return handle;
}

HANDLE spvm_sys_windows_CreateFileW_for_read(const WCHAR* path_w) {
  
  return spvm_sys_windows_CreateFileW_for_read_common(path_w, 0);
}

HANDLE spvm_sys_windows_CreateFileW_reparse_point_for_read(const WCHAR* path_w) {

  return spvm_sys_windows_CreateFileW_for_read_common(path_w, FILE_FLAG_OPEN_REPARSE_POINT);
}

int32_t spvm_sys_windows_is_symlink_by_handle(HANDLE handle) {
  
  int32_t is_sym = 0;
  
  SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER linkdata = {0};
  if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), NULL, NULL)) {
    if (GetLastError() == ERROR_NOT_A_REPARSE_POINT) {
      goto END_OF_FUNC;
    }
    else {
      spvm_sys_windows_win_last_error_to_errno(EINVAL);
      goto END_OF_FUNC;
    }
  }
  
  if (linkdata.ReparseTag == IO_REPARSE_TAG_SYMLINK || linkdata.ReparseTag == IO_REPARSE_TAG_MOUNT_POINT) {
    is_sym = 1;
  }
  
  END_OF_FUNC:
  
  return is_sym;
}

int32_t spvm_sys_windows_is_symlink(const WCHAR* path_w) {
  
  int32_t is_sym = 0;
  
  HANDLE handle = spvm_sys_windows_CreateFileW_reparse_point_for_read(path_w);
  
  if (handle == INVALID_HANDLE_VALUE) {
    spvm_sys_windows_win_last_error_to_errno(EINVAL);
    goto END_OF_FUNC;
  }
  
  is_sym = spvm_sys_windows_is_symlink_by_handle(handle);
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  return is_sym;
}

#endif // defined(_WIN32)
