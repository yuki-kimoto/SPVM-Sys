#ifndef SPVM__SYS__WINDOWS__H
#define SPVM__SYS__WINDOWS__H

#if defined(_WIN32)

// For SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
#define MY_TARGET_WIN_VERSION 0x0A00 // Windows 10 (10.0)
#ifndef _WIN32_WINNT
  #define _WIN32_WINNT MY_TARGET_WIN_VERSION
#else
  #if _WIN32_WINNT < MY_TARGET_WIN_VERSION
    #undef _WIN32_WINNT
    #define _WIN32_WINNT MY_TARGET_WIN_VERSION
  #endif
#endif

#include <windows.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>
#include <errno.h>
#include <winbase.h>
#include <fcntl.h>
#include <direct.h>
#include <time.h>
#include <assert.h>


// Exactly same as Perl's one in Win32.c
typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    ULONG  Flags;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_SYMLINK_REPARSE_BUFFER;

// Exactly same as Perl's one in Win32.c
typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_MOUNT_POINT_REPARSE_BUFFER;

// These are different from Perl's ones, but they must be defined well
typedef BOOL bool;
typedef uint32_t STRLEN;
#define dTHX 
#define MKTIME_LOCK 
#define MKTIME_UNLOCK
#define Zero(ptr, size, type) memset(ptr, 0, size * sizeof(type));
typedef uint64_t Off_t;

#define isSLASHW(c) ((c) == L'/' || (c) == L'\\')
#define strEQW(string1, string2) (wcscmp(string1, string2) == 0)

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_SYMLINK
#  define IO_REPARSE_TAG_SYMLINK                  (0xA000000CL)
#endif

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_AF_UNIX
#  define IO_REPARSE_TAG_AF_UNIX 0x80000023
#endif

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_LX_FIFO
#  define IO_REPARSE_TAG_LX_FIFO 0x80000024
#endif

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_LX_CHR
#  define IO_REPARSE_TAG_LX_CHR  0x80000025
#endif

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_LX_BLK
#  define IO_REPARSE_TAG_LX_BLK  0x80000026
#endif

// Exactly same as Perl's one in Win32.c
static void
translate_to_errno(void)
{
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
      errno = ENOENT;
      break;
    case ERROR_ALREADY_EXISTS:
      errno = EEXIST;
      break;
    case ERROR_ACCESS_DENIED:
      errno = EACCES;
      break;
    case ERROR_PRIVILEGE_NOT_HELD:
      errno = EPERM;
      break;
    case ERROR_NOT_SAME_DEVICE:
      errno = EXDEV;
      break;
    case ERROR_DISK_FULL:
      errno = ENOSPC;
      break;
    case ERROR_NOT_ENOUGH_QUOTA:
      errno = EDQUOT;
      break;
    default:
      /* ERROR_INVALID_FUNCTION - eg. symlink on a FAT volume */
      errno = EINVAL;
      break;
    }
}

static void* utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
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
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  void* obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
  wchar_t* utf16le_string = env->get_elems_short(env, stack, obj_utf16le_string);
  
  utf16le_string_length = MultiByteToWideChar(
    CP_UTF8,
    0,
    utf8_string,
    -1,
    utf16le_string,
    utf16le_string_length
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error converting UTF-8 to UTF-16LE: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf16le_string;
}

static const char* win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, wchar_t* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
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
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
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
    *error_id = env->die(env, stack,  "win_wchar_to_utf8 failed:Error converting UTF-16LE to UTF-8: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf8_string;
}

static HANDLE CreateFileW_for_read(wchar_t* path_w) {
  
  return CreateFileW_for_read_common(path_w, 0);
}

static HANDLE CreateFileW_reparse_point_for_read(wchar_t* path_w) {

  return CreateFileW_for_read_common(path_w, FILE_FLAG_OPEN_REPARSE_POINT);
}

static HANDLE CreateFileW_for_read_common(wchar_t* path_w, int32_t file_flag) {

  HANDLE handle = CreateFileW(path_w, GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
    file_flag|FILE_FLAG_BACKUP_SEMANTICS, 0
  );
  
  return handle;
}

static BOOL
is_symlink(HANDLE h) {
    REPARSE_DATA_BUFFER linkdata;
    const MY_SYMLINK_REPARSE_BUFFER * const sd =
        &linkdata.Data.SymbolicLinkReparseBuffer;
    DWORD linkdata_returned;
    
    if (!DeviceIoControl(h, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
        return FALSE;
    }
    
    if (linkdata_returned < offsetof(REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)
        || (linkdata.ReparseTag != IO_REPARSE_TAG_SYMLINK
            && linkdata.ReparseTag != IO_REPARSE_TAG_MOUNT_POINT)) {
        /* some other type of reparse point */
        return FALSE;
    }
    
    return TRUE;
}

static int32_t is_symlink_name(const wchar_t* path_w) {
  
  HANDLE handle = CreateFileW_reparse_point_for_read(path_w);
  
  if (handle == INVALID_HANDLE_VALUE) {
    translate_to_errno();
    return 0;
  }
  
  int32_t is_symlink = is_symlink(handle);
  
  CloseHandle(handle);
  
  return is_symlink;
}

#endif // defined(_WIN32)

#endif // SPVM__SYS__WINDOWS__H
