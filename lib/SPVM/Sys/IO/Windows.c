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

static OSVERSIONINFO g_osver = {0, 0, 0, 0, 0, ""};

typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    ULONG  Flags;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_SYMLINK_REPARSE_BUFFER;

typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_MOUNT_POINT_REPARSE_BUFFER;

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

#define strEQ(string1, string2) (strcmp(string1, string2) == 0)
#define isSLASH(c) ((c) == '/' || (c) == '\\')

#ifndef SYMBOLIC_LINK_FLAG_DIRECTORY
#  define SYMBOLIC_LINK_FLAG_DIRECTORY 0x1
#endif

#ifndef SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
#  define SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE 0x2
#endif

// These are different from Perl's ones, but they must be defined well
#define PerlDir_mapA(dir) dir
#define dTHX 

typedef BOOLEAN (__stdcall *pCreateSymbolicLinkA_t)(LPCSTR, LPCSTR, DWORD);
typedef BOOLEAN (__stdcall *pCreateSymbolicLinkW_t)(LPCWSTR, LPCWSTR, DWORD);

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
    HANDLE f = CreateFileW(name, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                           FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    BOOL result;

    if (f == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    result = is_symlink(f);
    CloseHandle(f);

    return result;
}

// Same as Perl's win32_unlink in Win32.c, but call APIs for wide characters(W instead of A and _w prefixed).
static int
win32_unlink(const wchar_t *filename)
{
  int ret;
  DWORD attrs;
  
  attrs = GetFileAttributesW(filename);
  if (attrs == 0xFFFFFFFF) {
    errno = ENOENT;
    return -1;
  }
  
  if (attrs & FILE_ATTRIBUTE_READONLY) {
    (void)SetFileAttributesW(filename, attrs & ~FILE_ATTRIBUTE_READONLY);
    ret = _wunlink(filename);
    if (ret == -1)
        (void)SetFileAttributesW(filename, attrs);
  }
  else if ((attrs & (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY))
    == (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY)
         && is_symlink_name(filename)) {
    ret = _wrmdir(filename);
  }
  else {
    ret = _wunlink(filename);
  }
  
  return ret;
}

// Same as Perl's win32_rename in Win32.c, but call APIs for wide characters(W instead of A and _w prefixed).
static int
win32_rename(const wchar_t *oname, const wchar_t *newname)
{
    wchar_t szOldName[MAX_PATH+1];
    BOOL bResult;
    DWORD dwFlags = MOVEFILE_COPY_ALLOWED;
    dTHX;

    if (_wcsicmp(newname, oname))
        dwFlags |= MOVEFILE_REPLACE_EXISTING;
    wcscpy(szOldName, oname);
    
    bResult = MoveFileExW(szOldName,newname, dwFlags);
    
    if (!bResult) {
        DWORD err = GetLastError();
        switch (err) {
        case ERROR_BAD_NET_NAME:
        case ERROR_BAD_NETPATH:
        case ERROR_BAD_PATHNAME:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_FILENAME_EXCED_RANGE:
        case ERROR_INVALID_DRIVE:
        case ERROR_NO_MORE_FILES:
        case ERROR_PATH_NOT_FOUND:
            errno = ENOENT;
            break;
        case ERROR_DISK_FULL:
            errno = ENOSPC;
            break;
        case ERROR_NOT_ENOUGH_QUOTA:
            errno = EDQUOT;
            break;
        default:
            errno = EACCES;
            break;
        }
        return -1;
    }
    return 0;
}

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

static int
do_readlink_handle(HANDLE hlink, char *buf, size_t bufsiz, BOOL *is_symlink) {
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
        /*() failed.conversion from unicode to ANSI or otherwise() failed.*/
        errno = EINVAL;
        return -1;
    }

    return bytes_out;
}

static int
win32_readlink(const wchar_t *pathname, char *buf, size_t bufsiz) {
    if (pathname == NULL || buf == NULL) {
        errno = EFAULT;
        return -1;
    }
    if (bufsiz <= 0) {
        errno = EINVAL;
        return -1;
    }

    DWORD fileattr = GetFileAttributesW(pathname);
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
        CreateFileW(pathname, GENERIC_READ, 0, NULL, OPEN_EXISTING,
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

#define isSLASHW(c) ((c) == L'/' || (c) == L'\\')
#define strEQW(string1, string2) (wcscmp(string1, string2) == 0)

static int
win32_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const wchar_t *oldfile, const wchar_t *newfile)
{
    size_t oldfile_len = wcslen(oldfile);
    pCreateSymbolicLinkW_t pCreateSymbolicLinkW =
        (pCreateSymbolicLinkW_t)GetProcAddress(GetModuleHandle("kernel32.dll"), "CreateSymbolicLinkW");
    DWORD create_flags = 0;

    /* this flag can be used only on Windows 10 1703 or newer */
    if (g_osver.dwMajorVersion > 10 ||
        (g_osver.dwMajorVersion == 10 &&
         (g_osver.dwMinorVersion > 0 || g_osver.dwBuildNumber > 15063)))
    {
        create_flags |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
    }

    if (!pCreateSymbolicLinkW) {
        errno = ENOSYS;
        return -1;
    }

    if (wcschr(oldfile, L'/')) {
        /* Win32 (or perhaps NTFS) won't follow symlinks containing
           /, so replace any with \\
        */
        wchar_t *temp = (wchar_t*)env->new_memory_block(env, stack, (wcslen(oldfile) + 1) * sizeof(wchar_t));
        memcpy(temp, oldfile, (wcslen(oldfile) + 1) * sizeof(wchar_t));
        wchar_t *p = temp;
        while (*p) {
            if (*p == L'/') {
                *p = '\\';
            }
            ++p;
        }
        *p = 0;
        oldfile = temp;
        oldfile_len = p - temp;
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
       Otherwise if the oldfile is relative we need to make a relative path
       based on the newfile to check if the target is a directory.
    */
    if ((oldfile_len >= 1 && isSLASHW(oldfile[oldfile_len-1])) ||
        strEQW(oldfile, L"..") ||
        strEQW(oldfile, L".") ||
        (isSLASH(oldfile[oldfile_len-2]) && oldfile[oldfile_len-1] == '.') ||
        strEQW(oldfile+oldfile_len-3, L"\\..") ||
        (oldfile_len == 2 && oldfile[1] == L':')) {
        create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
    }
    else {
        DWORD dest_attr;
        const wchar_t *dest_path = oldfile;
        wchar_t szTargetName[MAX_PATH+1];

        if (oldfile_len >= 3 && oldfile[1] == ':') {
            /* relative to current directory on a drive, or absolute */
            /* dest_path = oldfile; already done */
        }
        else if (oldfile[0] != L'\\') {
            size_t newfile_len = wcslen(newfile);
            wchar_t *last_slash = wcsrchr(newfile, L'/');
            wchar_t *last_bslash = wcsrchr(newfile, L'\\');
            wchar_t *end_dir = last_slash && last_bslash
                ? ( last_slash > last_bslash ? last_slash : last_bslash)
                : last_slash ? last_slash : last_bslash ? last_bslash : NULL;

            if (end_dir) {
                if ((end_dir - newfile + 1) + oldfile_len > MAX_PATH) {
                    /* too long */
                    errno = EINVAL;
                    return -1;
                }

                memcpy(szTargetName, newfile, (end_dir - newfile + 1) * sizeof(wchar_t));
                wcscpy(szTargetName + (end_dir - newfile + 1), oldfile);
                dest_path = szTargetName;
            }
            else {
                /* newpath is just a filename */
                /* dest_path = oldfile; */
            }
        }

        dest_attr = GetFileAttributesW(dest_path);
        if (dest_attr != (DWORD)-1 && (dest_attr & FILE_ATTRIBUTE_DIRECTORY)) {
            create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
        }
    }

    if (!pCreateSymbolicLinkW(newfile, oldfile, create_flags)) {
        translate_to_errno();
        return -1;
    }

    return 0;
}

// Original implementation
static int win32_realpath(const wchar_t* path, wchar_t* out_path, int32_t out_path_length) {
  
  int32_t len = 0; // 0 indicates an error
  HANDLE hFile = CreateFileW(path, FILE_READ_ATTRIBUTES,
                    FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  
  if (hFile == INVALID_HANDLE_VALUE) {
    len = -1;
    goto END_OF_FUNC;
  }
  
  len = GetFinalPathNameByHandleW(hFile, out_path, out_path_length, 0);
  
  END_OF_FUNC:
  
  CloseHandle(hFile);
  
  return len;
}

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

int32_t SPVM__Sys__IO__Windows__readlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::IO::Windows#readlink method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_buf = stack[1].oval;
  if (!obj_buf) {
    return env->die(env, stack, "The buffer $buf must be defined.", __func__, FILE_NAME, __LINE__);
  }
  char* buf = (char*)env->get_chars(env, stack, obj_buf);
  int32_t buf_length = env->length(env, stack, obj_buf);
  
  int32_t bufsiz = stack[2].ival;
  if (!(bufsiz >= 0)) {
    return env->die(env, stack, "The buffer size $bufsiz must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  if (!(bufsiz <= buf_length)) {
    return env->die(env, stack, "The buffer size $bufsiz must be less than or equal to the length of the buffer $buf.", __func__, FILE_NAME, __LINE__);
  }
  
  wchar_t* path_w = utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  errno = 0;
  int32_t placed_length = win32_readlink(path_w, buf, bufsiz);
  if (placed_length == -1) {
    env->die(env, stack, "[System Error]readlink() failed:%s. $path is \"%s\".", env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = placed_length;
  
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
