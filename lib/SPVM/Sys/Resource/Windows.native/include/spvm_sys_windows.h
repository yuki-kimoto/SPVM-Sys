#ifndef SPVM_SYS_WINDOWS_H
#define SPVM_SYS_WINDOWS_H

#if defined(_WIN32)

// For SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
#define SPVM_SYS_WINDOWS_TARGET_WIN_VERSION 0x0A00 // Windows 10 (10.0)
#if !defined(_WIN32_WINNT) || _WIN32_WINNT < SPVM_SYS_WINDOWS_TARGET_WIN_VERSION
  #undef _WIN32_WINNT
  #define _WIN32_WINNT SPVM_SYS_WINDOWS_TARGET_WIN_VERSION
#endif

/*
 * Minimize macro pollution from windows.h
 * 
 * NOMINMAX:
 *   Prevent defining min/max macros to avoid conflicts with 
 *   variable names or standard libraries.
 * 
 * WIN32_LEAN_AND_MEAN:
 *   Exclude rarely-used APIs to speed up build time 
 *   and keep the namespace clean.
 */
#ifndef NOMINMAX
  #define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
#endif

// Core Windows API
#include <windows.h>

/*
 * Explicitly include winioctl.h for reparse point constants 
 * (e.g., FSCTL_GET_REPARSE_POINT) which are excluded by WIN32_LEAN_AND_MEAN.
 */
#include <winioctl.h>

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
} SPVM_SYS_WINDOWS_SYMLINK_REPARSE_BUFFER;

// Exactly same as Perl's one in Win32.c
typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    WCHAR  PathBuffer[MAX_PATH*3];
} SPVM_SYS_WINDOWS_MOUNT_POINT_REPARSE_BUFFER;

// Exactly same as Perl's one in Win32.c
typedef struct {
  ULONG  ReparseTag;
  USHORT ReparseDataLength;
  USHORT Reserved;
  union {
    SPVM_SYS_WINDOWS_SYMLINK_REPARSE_BUFFER SymbolicLinkReparseBuffer;
    SPVM_SYS_WINDOWS_MOUNT_POINT_REPARSE_BUFFER MountPointReparseBuffer;
    struct {
      UCHAR DataBuffer[1];
    } GenericReparseBuffer;
  } Data;
} SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER;

WCHAR* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

const char* spvm_sys_windows_win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, WCHAR* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

void spvm_sys_windows_win_last_error_to_errno(int32_t default_errno);

HANDLE spvm_sys_windows_CreateFileW_for_read(const WCHAR* path_w);

HANDLE spvm_sys_windows_CreateFileW_reparse_point_for_read(const WCHAR* path_w);

int32_t spvm_sys_windows_is_symlink_by_handle(HANDLE handle);

int32_t spvm_sys_windows_is_symlink(const WCHAR* path_w);

// Originally copied from struct direct in Perl's win32/include/dirent.h
typedef struct
{
  int64_t d_ino;
  int32_t d_namlen;
  WCHAR d_name[257];
} SPVM_SYS_WINDOWS_WDIRENT;

// Originally copied from struct _dir_struc in Perl's win32/include/dirent.h
typedef struct
{
  HANDLE handle;
  WCHAR* start;
  WCHAR* end;
  WCHAR* curr;
  int64_t size;
  SPVM_SYS_WINDOWS_WDIRENT dirstr;
  int64_t nfiles;
} SPVM_SYS_WINDOWS_DIR;

#endif // defined(_WIN32)

#endif // SPVM_SYS_WINDOWS_H
