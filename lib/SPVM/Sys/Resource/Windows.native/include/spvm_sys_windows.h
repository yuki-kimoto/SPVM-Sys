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

#include "spvm_native.h"

// Exactly same as Perl's one in sys/errno2.h
#ifndef EDQUOT
#  define EDQUOT WSAEDQUOT
#endif

// Exactly same as Perl's one in Win32.c
#ifndef IO_REPARSE_TAG_SYMLINK
#  define IO_REPARSE_TAG_SYMLINK (0xA000000CL)
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

// Exactly same as Perl's one in Win32.c
typedef struct {
  ULONG  ReparseTag;
  USHORT ReparseDataLength;
  USHORT Reserved;
  union {
    MY_SYMLINK_REPARSE_BUFFER SymbolicLinkReparseBuffer;
    MY_MOUNT_POINT_REPARSE_BUFFER MountPointReparseBuffer;
    struct {
      UCHAR DataBuffer[1];
    } GenericReparseBuffer;
  } Data;
} MY_REPARSE_DATA_BUFFER;

void* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

const char* spvm_sys_windows_win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, WCHAR* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

void spvm_sys_windows_win_last_error_to_errno(void);

HANDLE spvm_sys_windows_CreateFileW_for_read_common(const WCHAR* path_w, int32_t file_flag);

HANDLE spvm_sys_windows_CreateFileW_for_read(const WCHAR* path_w);

HANDLE spvm_sys_windows_CreateFileW_reparse_point_for_read(const WCHAR* path_w);

int32_t spvm_sys_windows_is_symlink_by_handle(HANDLE handle);

int32_t spvm_sys_windows_is_symlink(const WCHAR* path_w);

#endif // defined(_WIN32)

#endif // SPVM__SYS__WINDOWS__H
