// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>
#include <errno.h>
#include <sys/stat.h>

#if defined(_WIN32)
  struct w32_stat;
  typedef struct stat Stat_t;
#else
  typedef struct stat Stat_t;
#endif

static const char* FILE_NAME = "Sys/IO/Stat.c";

int32_t SPVM__Sys__IO__Stat__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  Stat_t* st_stat = env->new_memory_block(env, stack, sizeof(Stat_t));
  
  void* obj_stat = env->new_pointer_object_by_name(env, stack, "Sys::IO::Stat", st_stat, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_stat;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  assert(st_stat);
  
  env->free_memory_block(env, stack, st_stat);

  env->set_pointer(env, stack, obj_stat, NULL);
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__stat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  void* obj_stat = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat object $stat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  Stat_t* stat_buf = env->get_pointer(env, stack, obj_stat);
  
  int32_t status = stat(path, stat_buf);
  
  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]stat() failed:%s. $path is \"%s\".", path, env->strerror_nolen(env, stack, errno), __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__lstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
#if defined(_WIN32)
  return env->die(env, stack, "Sys::IO::Stat#lstat method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
#else

  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  void* obj_lstat = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  if (!obj_lstat) {
    return env->die(env, stack, "The stat object $lstat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  Stat_t* stat_buf = env->get_pointer(env, stack, obj_lstat);
  
  int32_t status = lstat(path, stat_buf);
  
  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]lstat() failed:%s. $path is \"%s\".", env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif

  return 0;
}

int32_t SPVM__Sys__IO__Stat__fstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t fd = stack[0].ival;
  
  void* obj_stat = stack[1].oval;
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat object $stat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  Stat_t* stat_buf = env->get_pointer(env, stack, obj_stat);
  
  int32_t status = fstat(fd, stat_buf);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]fstat() failed:%s.", env->strerror_nolen(env, stack, errno), __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_dev(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_dev;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_ino(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_ino;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_mode;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_nlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_nlink;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_size(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_size;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_blksize(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_blksize method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_blksize;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_blocks method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_blocks;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_uid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_uid;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_gid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_gid;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_rdev(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_rdev;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_atime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_atimespec.tv_sec;
#else
  stack[0].lval = st_stat->st_atime;
#endif

  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_mtimespec.tv_sec;
#else
  stack[0].lval = st_stat->st_mtime;
#endif
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_ctime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_ctimespec.tv_sec;
#else
  stack[0].lval = st_stat->st_ctime;
#endif
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_atim_tv_nsec(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_atim_tv_nsec method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#elif defined(__solaris) || defined(__sun)
  env->die(env, stack, "Sys::IO::Stat#st_atim_tv_nsec method is not supported in this system(__solaris or __sun).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);

#ifdef __APPLE__
  stack[0].lval = st_stat->st_atimespec.tv_nsec;
#else
  stack[0].lval = st_stat->st_atim.tv_nsec;
#endif

  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_mtim_tv_nsec(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#The st_mtim_tv_nsec method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#elif defined(__solaris) || defined(__sun)
  env->die(env, stack, "Sys::IO::Stat#st_mtim_tv_nsec method is not supported in this system(__solaris or __sun).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_mtimespec.tv_nsec;
#else
  stack[0].lval = st_stat->st_mtim.tv_nsec;
#endif
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_ctim_tv_nsec(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_ctim_tv_nsec method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#elif defined(__solaris) || defined(__sun)
  env->die(env, stack, "Sys::IO::Stat#st_ctim_tv_nsec method is not supported in this system(__solaris or __sun).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_stat = stack[0].oval;
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_ctimespec.tv_nsec;
#else
  stack[0].lval = st_stat->st_ctim.tv_nsec;
#endif
  
  return 0;
#endif
}

#if defined(_WIN32)
  #include <windows.h>
  #include <time.h>
  
// These are different from Perl's ones, but they must be defined well
typedef BOOL bool;
typedef uint32_t STRLEN;
#define PerlDir_mapA(dir) dir
#define dTHX 
#define aTHX_ 
#define MKTIME_LOCK 
#define MKTIME_UNLOCK
#define Zero(ptr, size, type) memset(ptr, 0, size * sizeof(type));
typedef uint64_t Off_t;

// Exactly same as Perl's one in Win32.h
#define _S_IFLNK ((unsigned)(_S_IFDIR | _S_IFCHR))

// Exactly same as Perl's one in Win32.h
#define _S_IFSOCK ((unsigned)(_S_IFDIR | _S_IFIFO))

// Exactly same as Perl's one in Win32.h
typedef DWORD Dev_t;

// Exactly same as Perl's one in Win32.h
typedef unsigned __int64 Ino_t;

// Exactly same as Perl's one in Win32.h
struct w32_stat {
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
};

// Exactly same as Perl's one in sys/errno2.h
#ifndef EDQUOT			/* Not in errno.h but wanted by POSIX.pm */
#  define EDQUOT		WSAEDQUOT
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
typedef DWORD (__stdcall *pGetFinalPathNameByHandleA_t)(HANDLE, LPSTR, DWORD, DWORD);

// Exactly same as Perl's one in Win32.c
typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    ULONG  Flags;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_SYMLINK_REPARSE_BUFFER, *PMY_SYMLINK_REPARSE_BUFFER;

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
} MY_REPARSE_DATA_BUFFER, *PMY_REPARSE_DATA_BUFFER;

static HANDLE
S_follow_symlinks_to(const char *pathname, DWORD *reparse_type) {
  
  // TODO
  assert(0);
}

// Exactly same as Perl's one in Win32.c
static int
do_readlink_handle(HANDLE hlink, char *buf, size_t bufsiz, bool *is_symlink) {
    MY_REPARSE_DATA_BUFFER linkdata;
    DWORD linkdata_returned;

    if (is_symlink)
        *is_symlink = FALSE;

    if (!DeviceIoControl(hlink, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
        translate_to_errno();
        return -1;
    }

    int bytes_out;
    BOOL used_default;
    switch (linkdata.ReparseTag) {
    case IO_REPARSE_TAG_SYMLINK:
        {
            const MY_SYMLINK_REPARSE_BUFFER * const sd =
                &linkdata.Data.SymbolicLinkReparseBuffer;
            if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)) {
                errno = EINVAL;
                return -1;
            }
            bytes_out =
                WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS,
                                    sd->PathBuffer + sd->PrintNameOffset/2,
                                    sd->PrintNameLength/2,
                                    buf, (int)bufsiz, NULL, &used_default);
            if (is_symlink)
                *is_symlink = TRUE;
        }
        break;
    case IO_REPARSE_TAG_MOUNT_POINT:
        {
            const MY_MOUNT_POINT_REPARSE_BUFFER * const rd =
                &linkdata.Data.MountPointReparseBuffer;
            if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.MountPointReparseBuffer.PathBuffer)) {
                errno = EINVAL;
                return -1;
            }
            bytes_out =
                WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS,
                                    rd->PathBuffer + rd->PrintNameOffset/2,
                                    rd->PrintNameLength/2,
                                    buf, (int)bufsiz, NULL, &used_default);
            if (is_symlink)
                *is_symlink = TRUE;
        }
        break;

    default:
        errno = EINVAL;
        return -1;
    }

    if (bytes_out == 0 || used_default) {
        /* failed conversion from unicode to ANSI or otherwise failed */
        errno = EINVAL;
        return -1;
    }

    return bytes_out;
}

// Exactly same as Perl's one in Win32.c
time_t
translate_ft_to_time_t(FILETIME ft) {
    SYSTEMTIME st;
    struct tm pt;
    time_t retval;
    dTHX;

    if (!FileTimeToSystemTime(&ft, &st))
        return -1;

    Zero(&pt, 1, struct tm);
    pt.tm_year = st.wYear - 1900;
    pt.tm_mon = st.wMonth - 1;
    pt.tm_mday = st.wDay;
    pt.tm_hour = st.wHour;
    pt.tm_min = st.wMinute;
    pt.tm_sec = st.wSecond;

    MKTIME_LOCK;
    retval = _mkgmtime(&pt);
    MKTIME_UNLOCK;

    return retval;
}

// Exactly same as Perl's one in Win32.c
static int
win32_stat_low(HANDLE handle, const char *path, STRLEN len, Stat_t *sbuf,
               DWORD reparse_type) {
    DWORD type = GetFileType(handle);
    BY_HANDLE_FILE_INFORMATION bhi;

    Zero(sbuf, 1, Stat_t);

    if (reparse_type) {
        /* Lie to get to the right place */
        type = FILE_TYPE_DISK;
    }

    type &= ~FILE_TYPE_REMOTE;

    switch (type) {
    case FILE_TYPE_DISK:
        if (GetFileInformationByHandle(handle, &bhi)) {
            sbuf->st_dev = bhi.dwVolumeSerialNumber;
            sbuf->st_ino = bhi.nFileIndexHigh;
            sbuf->st_ino <<= 32;
            sbuf->st_ino |= bhi.nFileIndexLow;
            sbuf->st_nlink = bhi.nNumberOfLinks;
            sbuf->st_uid = 0;
            sbuf->st_gid = 0;
            /* ucrt sets this to the drive letter for
               stat(), lets not reproduce that mistake */
            sbuf->st_rdev = 0;
            sbuf->st_size = bhi.nFileSizeHigh;
            sbuf->st_size <<= 32;
            sbuf->st_size |= bhi.nFileSizeLow;

            sbuf->st_atime = translate_ft_to_time_t(bhi.ftLastAccessTime);
            sbuf->st_mtime = translate_ft_to_time_t(bhi.ftLastWriteTime);
            sbuf->st_ctime = translate_ft_to_time_t(bhi.ftCreationTime);

            if (reparse_type) {
                /* https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-fscc/c8e77b37-3909-4fe6-a4ea-2b9d423b1ee4
                   describes all of these as WSL only, but the AF_UNIX tag
                   is known to be used for AF_UNIX sockets without WSL.
                */
                switch (reparse_type) {
                case IO_REPARSE_TAG_AF_UNIX:
                    sbuf->st_mode = _S_IFSOCK;
                    break;

                case IO_REPARSE_TAG_LX_FIFO:
                    sbuf->st_mode = _S_IFIFO;
                    break;

                case IO_REPARSE_TAG_LX_CHR:
                    sbuf->st_mode = _S_IFCHR;
                    break;

                case IO_REPARSE_TAG_LX_BLK:
                    sbuf->st_mode = _S_IFBLK;
                    break;

                default:
                    /* Is there anything else we can do here? */
                    errno = EINVAL;
                    return -1;
                }
            }
            else if (bhi.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                sbuf->st_mode = _S_IFDIR | _S_IREAD | _S_IEXEC;
                /* duplicate the logic from the end of the old win32_stat() */
                if (!(bhi.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
                    sbuf->st_mode |= S_IWRITE;
                }
            }
            else {
                char path_buf[MAX_PATH+1];
                sbuf->st_mode = _S_IFREG;

                if (!path) {
                    pGetFinalPathNameByHandleA_t pGetFinalPathNameByHandleA =
                        (pGetFinalPathNameByHandleA_t)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetFinalPathNameByHandleA");
                    if (pGetFinalPathNameByHandleA) {
                        len = pGetFinalPathNameByHandleA(handle, path_buf, sizeof(path_buf), 0);
                    }
                    else {
                        len = 0;
                    }

                    /* < to ensure there's space for the \0 */
                    if (len && len < sizeof(path_buf)) {
                        path = path_buf;
                    }
                }

                if (path && len > 4 &&
                    (_stricmp(path + len - 4, ".exe") == 0 ||
                     _stricmp(path + len - 4, ".bat") == 0 ||
                     _stricmp(path + len - 4, ".cmd") == 0 ||
                     _stricmp(path + len - 4, ".com") == 0)) {
                    sbuf->st_mode |= _S_IEXEC;
                }
                if (!(bhi.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
                    sbuf->st_mode |= _S_IWRITE;
                }
                sbuf->st_mode |= _S_IREAD;
            }
        }
        else {
            translate_to_errno();
            return -1;
        }
        break;

    case FILE_TYPE_CHAR:
    case FILE_TYPE_PIPE:
        sbuf->st_mode = (type == FILE_TYPE_CHAR) ? _S_IFCHR : _S_IFIFO;
        if (handle == GetStdHandle(STD_INPUT_HANDLE) ||
            handle == GetStdHandle(STD_OUTPUT_HANDLE) ||
            handle == GetStdHandle(STD_ERROR_HANDLE)) {
            sbuf->st_mode |= _S_IWRITE | _S_IREAD;
        }
        break;

    default:
        return -1;
    }

    /* owner == user == group */
    sbuf->st_mode |= (sbuf->st_mode & 0700) >> 3;
    sbuf->st_mode |= (sbuf->st_mode & 0700) >> 6;

    return 0;
}

// Exactly same as Perl's one in Win32.c
int
win32_stat(const char *path, Stat_t *sbuf)
{
    int result;
    HANDLE handle;
    DWORD reparse_type = 0;

    path = PerlDir_mapA(path);

    handle =
        CreateFileA(path, FILE_READ_ATTRIBUTES,
                    FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
        /* AF_UNIX sockets need to be opened as a reparse point, but
           that will also open symlinks rather than following them.

           There may be other reparse points that need similar
           treatment.
        */
        handle = S_follow_symlinks_to(aTHX_ path, &reparse_type);
        if (handle == INVALID_HANDLE_VALUE) {
            /* S_follow_symlinks_to() will set errno */
            return -1;
        }
    }
    if (handle != INVALID_HANDLE_VALUE) {
        result = win32_stat_low(handle, path, strlen(path), sbuf, reparse_type);
        CloseHandle(handle);
    }
    else {
        translate_to_errno();
        result = -1;
    }

    return result;
}

// Exactly same as Perl's one in Win32.c
static int
win32_lstat(const char *path, Stat_t *sbuf)
{
    HANDLE f;
    int result;
    DWORD attr = GetFileAttributes(path); /* doesn't follow symlinks */

    if (attr == INVALID_FILE_ATTRIBUTES) {
        translate_to_errno();
        return -1;
    }

    if (!(attr & FILE_ATTRIBUTE_REPARSE_POINT)) {
        return win32_stat(path, sbuf);
    }

    f = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                           FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    if (f == INVALID_HANDLE_VALUE) {
        translate_to_errno();
        return -1;
    }
    bool is_symlink;
    int size = do_readlink_handle(f, NULL, 0, &is_symlink);
    if (!is_symlink) {
        /* it isn't a symlink, fallback to normal stat */
        CloseHandle(f);
        return win32_stat(path, sbuf);
    }
    else if (size < 0) {
        /* some other error, errno already set */
        CloseHandle(f);
        return -1;
    }
    result = win32_stat_low(f, NULL, 0, sbuf, 0);

    if (result != -1){
        sbuf->st_mode = (sbuf->st_mode & ~_S_IFMT) | _S_IFLNK;
        sbuf->st_size = size;
    }
    CloseHandle(f);

    return result;
}

#endif

