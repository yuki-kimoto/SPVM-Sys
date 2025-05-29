#ifndef SPVM__SYS__WINDOWS__H
#define SPVM__SYS__WINDOWS__H

#if defined(_WIN32)

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

#define _S_IFLNK ((unsigned)(_S_IFDIR | _S_IFCHR))

#ifndef EDQUOT			/* Not in errno.h but wanted by POSIX.pm */
#  define EDQUOT		WSAEDQUOT
#endif

#ifndef SYMBOLIC_LINK_FLAG_DIRECTORY
#  define SYMBOLIC_LINK_FLAG_DIRECTORY 0x1
#endif

#ifndef SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
#  define SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE 0x2
#endif

// These are different from Perl's ones, but they must be defined well
typedef BOOL bool;
typedef uint32_t STRLEN;
#define dTHX 
#define MKTIME_LOCK 
#define MKTIME_UNLOCK
#define Zero(ptr, size, type) memset(ptr, 0, size * sizeof(type));
typedef uint64_t Off_t;
#define PERL_ARGS_ASSERT_MY_MEMRCHR

#define isSLASHW(c) ((c) == L'/' || (c) == L'\\')
#define strEQW(string1, string2) (wcscmp(string1, string2) == 0)

// Exactly same as Perl's one in inline.h
static void *
S_my_memrchr(const char * s, const char c, const STRLEN len)
{
    /* memrchr(), since many platforms lack it */

    const char * t = s + len - 1;

    PERL_ARGS_ASSERT_MY_MEMRCHR;

    while (t >= s) {
        if (*t == c) {
            return (void *) t;
        }
        t--;
    }

    return NULL;
}

// Exactly same as Perl's one in embed.h
#define my_memrchr S_my_memrchr

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

typedef struct w32_stat Stat_t;

// Exactly same as Perl's one in sys/errno2.h
#ifndef EDQUOT			/* Not in errno.h but wanted by POSIX.pm */
#  define EDQUOT		WSAEDQUOT
#endif

// Exactly same as Perl's one in Win32.c
#define SYMLINK_FOLLOW_LIMIT 63

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

__thread SPVM_ENV* thread_env;

// Exactly same as Perl's one in Win32.c
static
intptr_t
win32_get_osfhandle(int fd)
{
    return (intptr_t)_get_osfhandle(fd);
}

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

// Exactly same as Perl's one in Win32.c, bytes_out is UTF-8
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
                WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS,
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
                WideCharToMultiByte(CP_UTF8, WC_NO_BEST_FIT_CHARS,
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

static BOOL
is_symlink(HANDLE h) {
    MY_REPARSE_DATA_BUFFER linkdata;
    const MY_SYMLINK_REPARSE_BUFFER * const sd =
        &linkdata.Data.SymbolicLinkReparseBuffer;
    DWORD linkdata_returned;
    
    if (!DeviceIoControl(h, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), &linkdata_returned, NULL)) {
        return FALSE;
    }
    
    if (linkdata_returned < offsetof(MY_REPARSE_DATA_BUFFER, Data.SymbolicLinkReparseBuffer.PathBuffer)
        || (linkdata.ReparseTag != IO_REPARSE_TAG_SYMLINK
            && linkdata.ReparseTag != IO_REPARSE_TAG_MOUNT_POINT)) {
        /* some other type of reparse point */
        return FALSE;
    }
    
    return TRUE;
}

// Same as Perl's is_symlink_name in Win32.c, but call APIs for wide characters(W instead of A).
static BOOL
is_symlink_name(const wchar_t *name) {
    HANDLE f = CreateFileW(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
                           FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    BOOL result;

    if (f == INVALID_HANDLE_VALUE) {
      translate_to_errno();
      return FALSE;
    }
    result = is_symlink(f);
    CloseHandle(f);

    return result;
}

// Exactly same as Perl's one in Win32.c
static
int
win32_readlink(const char *pathname, char *buf, size_t bufsiz) {
    if (pathname == NULL || buf == NULL) {
        errno = EFAULT;
        return -1;
    }
    if (bufsiz <= 0) {
        errno = EINVAL;
        return -1;
    }

    DWORD fileattr = GetFileAttributes(pathname);
    if (fileattr == INVALID_FILE_ATTRIBUTES) {
        translate_to_errno();
        return -1;
    }

    if (!(fileattr & FILE_ATTRIBUTE_REPARSE_POINT)) {
        /* not a symbolic link */
        errno = EINVAL;
        return -1;
    }

    HANDLE hlink =
        CreateFileA(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                    FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    if (hlink == INVALID_HANDLE_VALUE) {
        translate_to_errno();
        return -1;
    }
    int bytes_out = do_readlink_handle(hlink, buf, bufsiz, NULL);
    CloseHandle(hlink);
    if (bytes_out < 0) {
        /* errno already set */
        return -1;
    }

    if ((size_t)bytes_out > bufsiz) {
        errno = EINVAL;
        return -1;
    }

    return bytes_out;
}

// The logic is the same as Perl's one in Win32.c, but this function use Perl data structure SV. I replace it with SPVM data structure.
static HANDLE
S_follow_symlinks_to(const char *pathname, DWORD *reparse_type) {
    
    SPVM_ENV* env = thread_env;
    
    SPVM_VALUE* stack = env->new_stack(env);
    
    int32_t scope_id = env->enter_scope(env, stack);
    
    char link_target[MAX_PATH];
    void* work_path = env->new_string(env, stack, pathname, strlen(pathname));
    int link_count = 0;
    int link_len;
    HANDLE handle;
    
    *reparse_type = 0;
    
    while ((link_len = win32_readlink(env->get_chars(env, stack, work_path), link_target,
                                      sizeof(link_target))) > 0) {
        if (link_count++ >= SYMLINK_FOLLOW_LIMIT) {
            /* Windows doesn't appear to ever return ELOOP,
               let's do better ourselves
            */
            errno = ELOOP;
            handle = INVALID_HANDLE_VALUE;
            goto END_OF_FUNC;
        }
        /* Adjust the linktarget based on the link source or current
           directory as needed.
        */
        if (link_target[0] == '\\'
            || link_target[0] == '/'
            || (link_len >=2 && link_target[1] == ':')) {
            /* link is absolute */
            work_path = env->new_string(env, stack, link_target, link_len);
        }
        else {
            STRLEN work_len;
            const char *workp = env->get_chars(env, stack, work_path);
            const char *final_bslash =
                (const char *)my_memrchr(workp, '\\', work_len);
            const char *final_slash =
                (const char *)my_memrchr(workp, '/', work_len);
            const char *path_sep = NULL;
            if (final_bslash && final_slash)
                path_sep = final_bslash > final_slash ? final_bslash : final_slash;
            else if (final_bslash)
                path_sep = final_bslash;
            else if (final_slash)
                path_sep = final_slash;

            if (path_sep) {
                void* new_path = env->new_string(env, stack, workp, path_sep - workp + 1);
                env->concat(env, stack, new_path, env->new_string(env, stack, link_target, link_len));
                work_path = new_path;
            }
            else {
                /* should only get here the first time around */
                assert(link_count == 1);
                char path_temp[MAX_PATH];
                DWORD path_len = GetCurrentDirectoryA(sizeof(path_temp), path_temp);
                if (!path_len || path_len > sizeof(path_temp)) {
                    errno = EINVAL;
                    handle = INVALID_HANDLE_VALUE;
                    goto END_OF_FUNC;
                }

                void* new_path = env->new_string(env, stack, path_temp, path_len);
                if (path_temp[path_len-1] != '\\') {
                    new_path = env->concat(env, stack, new_path, env->new_string_nolen(env, stack, "\\"));
                }
                new_path = env->concat(env, stack, new_path, env->new_string(env, stack, link_target, link_len));
                work_path = new_path;
            }
        }
    }

    handle =
        CreateFileA(env->get_chars(env, stack, work_path), GENERIC_READ, 0, NULL, OPEN_EXISTING,
                    FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    if (handle != INVALID_HANDLE_VALUE) {
        MY_REPARSE_DATA_BUFFER linkdata;
        DWORD linkdata_returned;

        if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0,
                             &linkdata, sizeof(linkdata),
                             &linkdata_returned, NULL)) {
            translate_to_errno();
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
            goto END_OF_FUNC;
        }
        *reparse_type = linkdata.ReparseTag;
        goto END_OF_FUNC;
    }
    else {
        translate_to_errno();
    }
    
    END_OF_FUNC:
    
    env->leave_scope(env, stack, scope_id);
    
    env->free_stack(env, stack);
    
    return handle;
}

// Exactly same as Perl's one in Win32.c
static
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

static HANDLE CreateFileW_for_read_common(wchar_t* path_w, int32_t file_flag) {

  HANDLE handle = CreateFileW(path_w, GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
    file_flag|FILE_FLAG_BACKUP_SEMANTICS, 0
  );
  
  return handle;
}
static HANDLE CreateFileW_for_read(wchar_t* path_w) {
  
  return CreateFileW_for_read_common(path_w, 0);
}

static HANDLE CreateFileW_reparse_point_for_read(wchar_t* path_w) {

  return CreateFileW_for_read_common(path_w, FILE_FLAG_OPEN_REPARSE_POINT);
}

#endif // defined(_WIN32)

#endif // SPVM__SYS__WINDOWS__H
