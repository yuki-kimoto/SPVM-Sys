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
#include <io.h>
#include <direct.h>
#include <process.h>
#include <sys/utime.h>
#include <errno.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/stat.h>

#include <time.h>
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif

#include "spvm_native.h"

/* File type mask */
#ifndef S_IFMT
  #define S_IFMT 0170000
#endif

/* Directory */
#ifndef S_IFDIR
  #define S_IFDIR 0040000
#endif

/* Character device */
#ifndef S_IFCHR
  #define S_IFCHR 0020000
#endif

/* Block device (Windows doesn't have, but for portability) */
#ifndef S_IFBLK
  #define S_IFBLK 0060000
#endif

/* Regular file */
#ifndef S_IFREG
  #define S_IFREG 0100000
#endif

/* FIFO */
#ifndef S_IFIFO
  #define S_IFIFO 0010000
#endif

/* Symbolic link (Manually defined for Windows) */
#ifndef S_IFLNK
  #define S_IFLNK 0120000
#endif

/* Socket (Manually defined for Windows) */
#ifndef S_IFSOCK
  #define S_IFSOCK 0140000
#endif

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

// Copied from https://github.com/msys2-contrib/mingw-w64/blob/master/mingw-w64-headers/crt/dirent.h
typedef struct {
  long    d_ino;    /* Always zero. */
  unsigned short  d_reclen; /* Always zero. */
  unsigned short  d_namlen; /* Length of name in d_name. */
  WCHAR   d_name[260]; /* [FILENAME_MAX] */ /* File name. */
} SPVM_SYS_WINDOWS_WDIRENT;

// Copied from https://github.com/msys2-contrib/mingw-w64/blob/master/mingw-w64-headers/crt/dirent.h
typedef struct {
  /* disk transfer area for this dir */
  struct _wfinddata64_t dd_dta;

  /* dirent struct to return from dir (NOTE: this makes this thread
   * safe as long as only one thread uses a particular DIR struct at
   * a time) */
  SPVM_SYS_WINDOWS_WDIRENT   dd_dir;

  /* _findnext handle */
  intptr_t    dd_handle;

  /*
   * Status of search:
   *   0 = not started yet (next entry to read is first entry)
   *  -1 = off the end
   *   positive = 0 based index of next entry
   */
  int     dd_stat;

  /* given path for dir with search pattern (struct is extended) */
  WCHAR     dd_name[1];
} SPVM_SYS_WINDOWS_DIR;

typedef struct {
  int tz_minuteswest; /* minutes west of Greenwich */
  int tz_dsttime;      /* type of dst correction */
} SPVM_SYS_WINDOWS_TIMEZONE;

// Exactly same as Perl's one in Win32.h
typedef DWORD Dev_t;

// Exactly same as Perl's one in Win32.h
typedef unsigned __int64 Ino_t;

// This is different from Perl's ones, but it must be defined well
typedef uint64_t Off_t;

// Exactly same as Perl's one in Win32.h
typedef struct {
  Dev_t st_dev;
  Ino_t st_ino;
  unsigned short st_mode;
  DWORD st_nlink;
  short st_uid;
  short st_gid;
  Dev_t st_rdev;
  Off_t st_size;
  time_t st_atime;
  time_t st_mtime;
  time_t st_ctime;
} SPVM_SYS_WINDOWS_STAT;

#ifdef __cplusplus
extern "C" {
#endif

WCHAR* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

const char* spvm_sys_windows_win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, WCHAR* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line);

int32_t spvm_sys_windows_is_symlink_by_handle(SPVM_ENV* env, SPVM_VALUE* stack, HANDLE handle);

int spvm_sys_windows_is_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* path);

SPVM_SYS_WINDOWS_DIR* spvm_sys_windows_opendir(SPVM_ENV* env, SPVM_VALUE* stack, const char* szPath);

SPVM_SYS_WINDOWS_WDIRENT* spvm_sys_windows_readdir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp);

int spvm_sys_windows_closedir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp);

void spvm_sys_windows_rewinddir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp);

long spvm_sys_windows_telldir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp);

void spvm_sys_windows_seekdir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp, long lPos);

int spvm_sys_windows_ftruncate(SPVM_ENV* env, SPVM_VALUE* stack, int fd, int64_t length);

unsigned int spvm_sys_windows_sleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int seconds);

int spvm_sys_windows_usleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int usec);

int spvm_sys_windows_gettimeofday(SPVM_ENV* env, SPVM_VALUE* stack, struct timeval *p, SPVM_SYS_WINDOWS_TIMEZONE *z);

int spvm_sys_windows_clock_gettime(SPVM_ENV* env, SPVM_VALUE* stack, int clk_id, struct timespec *ts);

int32_t spvm_sys_windows_fstat_by_handle(SPVM_ENV* env, SPVM_VALUE* stack, HANDLE handle, SPVM_SYS_WINDOWS_STAT *st_stat);

int32_t spvm_sys_windows_stat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat);

int32_t spvm_sys_windows_lstat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat);

// Utilitiies
HANDLE spvm_sys_windows_util_CreateFileW_for_read_common(const WCHAR* path_w, int32_t file_flag);

HANDLE spvm_sys_windows_util_CreateFileW_for_read(const WCHAR* path_w);

HANDLE spvm_sys_windows_util_CreateFileW_reparse_point_for_read(const WCHAR* path_w);

void spvm_sys_windows_util_win_last_error_to_errno(int32_t default_errno);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // defined(_WIN32)

#endif // SPVM_SYS_WINDOWS_H
