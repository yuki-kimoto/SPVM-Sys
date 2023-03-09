#include "spvm_native.h"

#include <unistd.h>
#include <windows.h>
#include <errno.h>

#ifndef EDQUOT			/* Not in errno.h but wanted by POSIX.pm */
#  define EDQUOT		WSAEDQUOT
#endif

static const char* FILE_NAME = "Sys/IO/Windows.c";

int32_t SPVM__Sys__IO__Windows__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

// These implementations are originally copied form Perl win32/win32.c

typedef struct {
    USHORT SubstituteNameOffset;
    USHORT SubstituteNameLength;
    USHORT PrintNameOffset;
    USHORT PrintNameLength;
    ULONG  Flags;
    WCHAR  PathBuffer[MAX_PATH*3];
} MY_SYMLINK_REPARSE_BUFFER, *PMY_SYMLINK_REPARSE_BUFFER;

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
} MY_REPARSE_DATA_BUFFER, *PMY_REPARSE_DATA_BUFFER;

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

static BOOL
is_symlink_name(const char *name) {
    HANDLE f = CreateFileA(name, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                           FILE_FLAG_OPEN_REPARSE_POINT|FILE_FLAG_BACKUP_SEMANTICS, 0);
    BOOL result;

    if (f == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    result = is_symlink(f);
    CloseHandle(f);

    return result;
}

int32_t SPVM__Sys__IO__Windows__is_symlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The $path must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  int32_t success = is_symlink_name(path);
  
  stack[0].ival = success;
  
  return 0;
}

static int
win32_unlink(const char *filename) {
    int ret;
    DWORD attrs;
    
    attrs = GetFileAttributesA(filename);
    if (attrs == 0xFFFFFFFF) {
        errno = ENOENT;
        return -1;
    }
    if (attrs & FILE_ATTRIBUTE_READONLY) {
        (void)SetFileAttributesA(filename, attrs & ~FILE_ATTRIBUTE_READONLY);
        ret = unlink(filename);
        if (ret == -1)
            (void)SetFileAttributesA(filename, attrs);
    }
    else if ((attrs & (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY))
        == (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY)
             && is_symlink_name(filename)) {
        ret = rmdir(filename);
    }
    else {
        ret = unlink(filename);
    }
    
    return ret;
}

int32_t SPVM__Sys__IO__Windows__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  if (!obj_path) {
    return env->die(env, stack, "The $path must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  int32_t status = win32_unlink(path);
  
  stack[0].ival = status;
  
  return 0;
}

static int
win32_rename(const char *oname, const char *newname)
{
    char szOldName[MAX_PATH+1];
    BOOL bResult;
    DWORD dwFlags = MOVEFILE_COPY_ALLOWED;

    if (stricmp(newname, oname))
        dwFlags |= MOVEFILE_REPLACE_EXISTING;
    strcpy(szOldName, oname);

    bResult = MoveFileExA(szOldName, newname, dwFlags);
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

int32_t SPVM__Sys__IO__Windows__rename(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_oldpath = stack[0].oval;
  if (!obj_oldpath) {
    return env->die(env, stack, "The $oldpath must be defined", __func__, FILE_NAME, __LINE__);
  }
  const char* oldpath = env->get_chars(env, stack, obj_oldpath);
  
  void* obj_newpath = stack[0].oval;
  if (!obj_newpath) {
    return env->die(env, stack, "The $newpath must be defined", __func__, FILE_NAME, __LINE__);
  }
  const char* newpath = env->get_chars(env, stack, obj_newpath);
  
  int32_t status = win32_rename(oldpath, newpath);
  
  stack[0].ival = status;
  
  return 0;
}
