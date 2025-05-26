#ifndef SPVM__SYS__WINDOWS__H
#define SPVM__SYS__WINDOWS__H

#if defined(_WIN32)
#include <windows.h>

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

#endif // defined(_WIN32)

#endif // SPVM__SYS__WINDOWS__H
