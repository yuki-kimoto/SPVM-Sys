// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Sys/IO/Stat.c";

#include <assert.h>
#include <errno.h>
#include <sys/stat.h>

#if defined(_WIN32)
  #include "spvm_sys_windows.h"
  
  // Exactly same as Perl's one in Win32.h
  #define _S_IFLNK ((unsigned)(_S_IFDIR | _S_IFCHR))
  
  // Exactly same as Perl's one in Win32.h
  #define _S_IFSOCK ((unsigned)(_S_IFDIR | _S_IFIFO))
  
  // Exactly same as Perl's one in Win32.h
  typedef DWORD Dev_t;
  
  // Exactly same as Perl's one in Win32.h
  typedef unsigned __int64 Ino_t;
  
  // This is different from Perl's ones, but it must be defined well
  typedef uint64_t Off_t;
  
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
#else // defined(_WIN32)
  typedef struct stat Stat_t;
#endif

#if defined(_WIN32)

// The output is the same as Perl's file_time_to_epoch in Win32.c
static time_t file_time_to_epoch(FILETIME file_time) {
  SYSTEMTIME system_time;
  struct tm st_tm = {0};
  
  time_t epoch = -1;
  
  if (!FileTimeToSystemTime(&file_time, &system_time)) {
    spvm_sys_windows_win_last_error_to_errno(EINVAL);
    goto END_OF_FUNC;
  }
  
  st_tm.tm_year = system_time.wYear - 1900;
  st_tm.tm_mon = system_time.wMonth - 1;
  st_tm.tm_mday = system_time.wDay;
  st_tm.tm_hour = system_time.wHour;
  st_tm.tm_min = system_time.wMinute;
  st_tm.tm_sec = system_time.wSecond;
  
  epoch = _mkgmtime(&st_tm);
  
  END_OF_FUNC:
  
  return epoch;
}

// The output data is the same as Perl's win32_stat_low in Win32.c.
static int32_t win_fstat_by_handle(SPVM_ENV* env, SPVM_VALUE* stack, HANDLE handle, Stat_t *st_stat) {
  
  int32_t status = -1;
  DWORD type = GetFileType(handle);
  
  switch (type) {
    case FILE_TYPE_DISK: {
      
      BY_HANDLE_FILE_INFORMATION file_info = {0};
      if (GetFileInformationByHandle(handle, &file_info)) {
        
        int32_t reparse_type = 0;
        SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER linkdata = {0};
        if (DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), NULL, NULL)) {
          reparse_type = linkdata.ReparseTag;
        }
        else {
          if (GetLastError() == ERROR_NOT_A_REPARSE_POINT) {
            // Do nothing
          }
          else {
            spvm_sys_windows_win_last_error_to_errno(EINVAL);
            goto END_OF_FUNC;
          }
        }
        
        st_stat->st_dev = file_info.dwVolumeSerialNumber;
        st_stat->st_ino = file_info.nFileIndexHigh;
        st_stat->st_ino <<= 32;
        st_stat->st_ino |= file_info.nFileIndexLow;
        st_stat->st_nlink = file_info.nNumberOfLinks;
        st_stat->st_uid = 0;
        st_stat->st_gid = 0;
        /* ucrt sets this to the drive letter for
           stat(), lets not reproduce that mistake */
        st_stat->st_rdev = 0;
        st_stat->st_size = file_info.nFileSizeHigh;
        st_stat->st_size <<= 32;
        st_stat->st_size |= file_info.nFileSizeLow;
        
        st_stat->st_atime = file_time_to_epoch(file_info.ftLastAccessTime);
        st_stat->st_mtime = file_time_to_epoch(file_info.ftLastWriteTime);
        st_stat->st_ctime = file_time_to_epoch(file_info.ftCreationTime);
        
        if (reparse_type) {
          /* https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-fscc/c8e77b37-3909-4fe6-a4ea-2b9d423b1ee4
             describes all of these as WSL only, but the AF_UNIX tag
             is known to be used for AF_UNIX sockets without WSL.
          */
          st_stat->st_mode = 0;
          switch (reparse_type) {
            case IO_REPARSE_TAG_AF_UNIX: {
              st_stat->st_mode = _S_IFSOCK;
              break;
            }
            case IO_REPARSE_TAG_LX_FIFO: {
              st_stat->st_mode = _S_IFIFO;
              break;
            }
            case IO_REPARSE_TAG_LX_CHR: {
              st_stat->st_mode = _S_IFCHR;
              break;
            }
            case IO_REPARSE_TAG_LX_BLK: {
              st_stat->st_mode = _S_IFBLK;
              break;
            }
            case IO_REPARSE_TAG_SYMLINK:
            case IO_REPARSE_TAG_MOUNT_POINT:
            {
              break;
            }
            default: {
              /* Is there anything else we can do here? */
              errno = EINVAL;
              goto END_OF_FUNC;
            }
          }
        }
        
        if (st_stat->st_mode == 0) {
          if (file_info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            st_stat->st_mode = _S_IFDIR | _S_IREAD | _S_IEXEC;
            /* duplicate the logic from the end of the old win32_stat() */
            if (!(file_info.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
              st_stat->st_mode |= S_IWRITE;
            }
          }
          else {
            WCHAR path_tmp_w[MAX_PATH+1];
            st_stat->st_mode = _S_IFREG;
            
            const char* path = NULL;
            int32_t len = GetFinalPathNameByHandleW(handle, path_tmp_w, sizeof(path_tmp_w), 0);
            if (len > 0) {
              int32_t scope_id = env->enter_scope(env, stack);
              
              WCHAR* path_w = env->new_memory_block(env, stack, sizeof(WCHAR) * (len + 1));
              
              len = GetFinalPathNameByHandleW(handle, path_w, len + 1, 0);
              
              assert(len > 0);
              
              int32_t error_id = 0;
              
              path = spvm_sys_windows_win_wchar_to_utf8(env, stack, path_w, &error_id, __func__, FILE_NAME, __LINE__);
              
              env->free_memory_block(env, stack, path_w);
              
              assert(error_id == 0);
              
              env->leave_scope(env, stack, scope_id);
            }
            
            if (path && len > 4 &&
              (_stricmp(path + len - 4, ".exe") == 0 ||
               _stricmp(path + len - 4, ".bat") == 0 ||
               _stricmp(path + len - 4, ".cmd") == 0 ||
               _stricmp(path + len - 4, ".com") == 0))
            {
              st_stat->st_mode |= _S_IEXEC;
            }
            if (!(file_info.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
              st_stat->st_mode |= _S_IWRITE;
            }
            st_stat->st_mode |= _S_IREAD;
          }
        }
      }
      else {
        spvm_sys_windows_win_last_error_to_errno(EINVAL);
        goto END_OF_FUNC;
      }
      break;
    }
    case FILE_TYPE_CHAR:
    case FILE_TYPE_PIPE:
    {
      st_stat->st_mode = (type == FILE_TYPE_CHAR) ? _S_IFCHR : _S_IFIFO;
      if (handle == GetStdHandle(STD_INPUT_HANDLE) ||
        handle == GetStdHandle(STD_OUTPUT_HANDLE) ||
        handle == GetStdHandle(STD_ERROR_HANDLE)) {
        st_stat->st_mode |= _S_IWRITE | _S_IREAD;
      }
      break;
    }
    default: {
      errno = EINVAL;
      goto END_OF_FUNC;
    }
  }
  
  /* owner == user == group */
  st_stat->st_mode |= (st_stat->st_mode & 0700) >> 3;
  st_stat->st_mode |= (st_stat->st_mode & 0700) >> 6;
  
  status = 0;
  
  END_OF_FUNC:
  
  return status;
}

static int32_t win_stat(SPVM_ENV* env, SPVM_VALUE* stack, Stat_t *st_stat) {
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  HANDLE handle =
      CreateFileA(path, FILE_READ_ATTRIBUTES,
                  FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                  NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  
  int32_t ReparseTag = 0;
  if (handle == INVALID_HANDLE_VALUE) {
    void* obj_resolved_link_text = NULL;
    {
      void* obj_link_text = NULL;
      stack[0].oval = obj_path;
      env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "_follow_symlinks_to", 1, &error_id, __func__, FILE_NAME, __LINE__);
      if (error_id) {
        goto END_OF_FUNC;
      }
      obj_resolved_link_text = stack[0].oval;
    }
    const char* resolved_link_text = env->get_chars(env, stack, obj_resolved_link_text);
    
    WCHAR* resolved_link_text_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, resolved_link_text, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      return error_id;
    }
    
    handle = spvm_sys_windows_CreateFileW_reparse_point_for_read(resolved_link_text_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      spvm_sys_windows_win_last_error_to_errno(EINVAL);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  int32_t result = win_fstat_by_handle(env, stack, handle, st_stat);
  
  if (result == -1) {
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]win_stat() failed(%d: %s). $path:\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    }
    
    return error_id;
  }
  
  return 0;
}

static int32_t win_lstat(SPVM_ENV* env, SPVM_VALUE* stack, Stat_t *st_stat) {   
  
  int32_t error_id = 0;
  
  void* obj_path = stack[0].oval;
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  
  HANDLE handle = spvm_sys_windows_CreateFileW_reparse_point_for_read(path_w);
  if (handle == INVALID_HANDLE_VALUE) {
    spvm_sys_windows_win_last_error_to_errno(EINVAL);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  int32_t result = win_fstat_by_handle(env, stack, handle, st_stat);
  
  if (result == -1) {
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  int32_t is_sym = spvm_sys_windows_is_symlink_by_handle(handle);
  
  if (is_sym) {
    void* obj_link_text = NULL;
    stack[0].oval = obj_path;
    env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "win_readlink", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      goto END_OF_FUNC;
    }
    obj_link_text = stack[0].oval;
    
    int32_t link_text_length = env->length(env, stack, obj_link_text);
    
    st_stat->st_mode = (st_stat->st_mode & ~_S_IFMT) | _S_IFLNK;
    st_stat->st_size = link_text_length;
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]win_lstat() failed(%d: %s). $path:\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    }
    
    return error_id;
  }
  
  return 0;
}

#endif // defined(_WIN32)

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
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
#if defined(_WIN32)
  stack[0].oval = obj_path;
  error_id = win_stat(env, stack, st_stat);
  int32_t status = error_id ? -1 : 0;
#else
  int32_t status = stat(path, st_stat);
#endif
  
  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]stat() failed(%d: %s). $path:\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__lstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_lstat);
  
#if defined(_WIN32)
  stack[0].oval = obj_path;
  error_id = win_lstat(env, stack, st_stat);
  int32_t status = error_id ? -1 : 0;
#else
  int32_t status = lstat(path, st_stat);
#endif

  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]lstat() failed(%d: %s). $path:\"%s\".", errno, env->strerror_nolen(env, stack, errno), path, __func__, FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__fstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t fd = stack[0].ival;
  
  void* obj_stat = stack[1].oval;
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat object $stat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  Stat_t* st_stat = env->get_pointer(env, stack, obj_stat);
  
  
#if defined(_WIN32)
  HANDLE handle = (HANDLE)_get_osfhandle(fd);
  int32_t status = win_fstat_by_handle(env, stack, handle, st_stat);
#else
  int32_t status = fstat(fd, st_stat);
#endif

  if (status == -1) {
    env->die(env, stack, "[System Error]fstat() failed(%d: %s).", errno, env->strerror_nolen(env, stack, errno), __func__, FILE_NAME, __LINE__);
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

