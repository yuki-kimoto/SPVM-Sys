#if defined(_WIN32)

#include "spvm_sys_windows.h"

// C++ headers
#include <thread>
#include <chrono>

extern "C" {

#define SUFFIX	L"*"
#define	SLASH	L"\\"

static const char* FILE_NAME = "spvm_sys_windows.cpp";

WCHAR* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  SPVM_OBJ* obj_utf16le_string;
  WCHAR* utf16le_string_tmp;
  int32_t utf16le_string_length;
  
  env->push_caller_stack(env, stack, func_name, file, line);
  
  *error_id = 0;
  
  WCHAR* utf16le_string = NULL;
  
  if (utf8_string == NULL) {
    goto END_OF_FUNC;
  }
  
  utf16le_string_length = MultiByteToWideChar(
      CP_UTF8,
      0,
      utf8_string,
      -1,
      NULL,
      0
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", __func__, FILE_NAME, __LINE__, GetLastError());
    goto END_OF_FUNC;
  }
  
  obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
  utf16le_string_tmp = (WCHAR*)env->get_elems_short(env, stack, obj_utf16le_string);
  
  utf16le_string_length = MultiByteToWideChar(
    CP_UTF8,
    0,
    utf8_string,
    -1,
    utf16le_string_tmp,
    utf16le_string_length
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error converting UTF-8 to UTF-16LE: %lu.", __func__, FILE_NAME, __LINE__, GetLastError());
    goto END_OF_FUNC;
  }
  
  utf16le_string = utf16le_string_tmp;
  
  END_OF_FUNC:
  
  env->pop_caller_stack(env, stack);
  
  return utf16le_string;
}

const char* spvm_sys_windows_win_wchar_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, WCHAR* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
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
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", func_name, file, line, GetLastError());
    return NULL;
  }
  
  SPVM_OBJ* obj_utf8_string = env->new_string(env, stack, NULL, utf8_string_length);
  
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
    *error_id = env->die(env, stack,  "win_WCHARo_utf8 failed:Error converting UTF-16LE to UTF-8: %lu.", func_name, file, line, GetLastError());
    return NULL;
  }
  
  return utf8_string;
}

int32_t spvm_sys_windows_is_symlink_by_handle(SPVM_ENV* env, SPVM_VALUE* stack, HANDLE handle) {
  
  int32_t is_sym = 0;
  
  SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER linkdata = {0};
  if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), NULL, NULL)) {
    if (GetLastError() == ERROR_NOT_A_REPARSE_POINT) {
      goto END_OF_FUNC;
    }
    else {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      goto END_OF_FUNC;
    }
  }
  
  if (linkdata.ReparseTag == IO_REPARSE_TAG_SYMLINK || linkdata.ReparseTag == IO_REPARSE_TAG_MOUNT_POINT) {
    is_sym = 1;
  }
  
  END_OF_FUNC:
  
  return is_sym;
}

/*
 * opendir
 *
 * Returns a pointer to a DIR structure appropriately filled in to begin
 * searching a directory.
 */
SPVM_SYS_WINDOWS_DIR* spvm_sys_windows_opendir(SPVM_ENV* env, SPVM_VALUE* stack, const char* dir) {
  
  int32_t error_id = 0;
  
  SPVM_SYS_WINDOWS_DIR *nd;
  unsigned int rc;
  WCHAR szFullPath[MAX_PATH];
  
  errno = 0;

  if (!dir)
    {
      errno = EFAULT;
      env->set_error_id(env, stack, env->die(env, stack, "Directory $dir must be defined.", __func__, FILE_NAME, __LINE__));
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }
  
  WCHAR* dir_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, dir, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    errno = EILSEQ;
    env->set_error_id(env, stack, error_id);
    return (SPVM_SYS_WINDOWS_DIR *) 0;
  }
  
  if (dir_w[0] == L'\0')
    {
      errno = ENOTDIR;
      env->set_error_id(env, stack, env->die(env, stack, "Directory $dir must be a non-empty string.", __func__, FILE_NAME, __LINE__));
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributesW (dir_w);
  if (rc == INVALID_FILE_ATTRIBUTES)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). %d: %s. $dir='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), dir);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). %d: %s. $dir='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), dir);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Make an absolute path.  */
  _wfullpath (szFullPath, dir_w, MAX_PATH);
  
  size_t full_path_len = wcslen(szFullPath);
  size_t slash_len = wcslen(SLASH);
  size_t suffix_len = wcslen(SUFFIX);
  size_t total_len = full_path_len + slash_len + suffix_len + 1;
  
  /* Allocate enough space to store DIR structure and the complete
   * directory path given. */
  nd = (SPVM_SYS_WINDOWS_DIR *) malloc (sizeof (SPVM_SYS_WINDOWS_DIR) + (wcslen (szFullPath)
					   + wcslen (SLASH)
					   + wcslen (SUFFIX) + 1)
					  * sizeof (WCHAR));

  if (!nd)
    {
      /* Error, out of memory. */
      errno = ENOMEM;
      env->die(env, stack, "[System Error]malloc() failed(%d:%s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Create the search expression. */
  wcscpy_s(nd->dd_name, total_len, szFullPath);

  /* Add on a slash if the path does not end with one. */
  if (nd->dd_name[0] != L'\0' &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != L'/' &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != L'\\')
    {
      wcscat_s(nd->dd_name, total_len, SLASH);
    }

  /* Add on the search pattern */
  wcscat_s(nd->dd_name, total_len, SUFFIX);

  /* Initialize handle to -1 so that a premature closedir doesn't try
   * to call _findclose on it. */
  nd->dd_handle = -1;

  /* Initialize the status. */
  nd->dd_stat = 0;

  /* Initialize the dirent structure. ino and reclen are invalid under
   * Win32, and name simply points at the appropriate part of the
   * findfirst_t structure. */
  nd->dd_dir.d_ino = 0;
  nd->dd_dir.d_reclen = 0;
  nd->dd_dir.d_namlen = 0;
  memset (nd->dd_dir.d_name, 0, 260 * sizeof(nd->dd_dir.d_name[0])  /*FILENAME_MAX*/);

  return nd;
}


/*
 * readdir
 *
 * Return a pointer to a dirent structure filled with the information on the
 * next entry in the directory.
 */
SPVM_SYS_WINDOWS_WDIRENT* spvm_sys_windows_readdir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  /* Check for valid DIR struct. */
  if (!dirp)
    {
      errno = EFAULT;
      env->set_error_id(env, stack, env->die(env, stack, "Directory stream $dirp must be defined.", __func__, FILE_NAME, __LINE__));
      return (SPVM_SYS_WINDOWS_WDIRENT *) 0;
    }

  if (dirp->dd_stat < 0)
    {
      /* We have already returned all files in the directory
       * (or the structure has an invalid dd_stat). */
      return (SPVM_SYS_WINDOWS_WDIRENT *) 0;
    }
  else if (dirp->dd_stat == 0)
    {
      /* We haven't started the search yet. */
      /* Start the search */
      dirp->dd_handle = _wfindfirst64 (dirp->dd_name, &(dirp->dd_dta));

      if (dirp->dd_handle == -1)
	{
	  /* Whoops! Seems there are no files in that
	   * directory. */
	  dirp->dd_stat = -1;
	}
      else
	{
	  dirp->dd_stat = 1;
	}
    }
  else
    {
      /* Get the next search entry. */
      if (_wfindnext64 (dirp->dd_handle, &(dirp->dd_dta)))
	{
	  /* We are off the end or otherwise error.
	     _findnext sets errno to ENOENT if no more file
	     Undo this. */
	  DWORD winerr = GetLastError ();
	  if (winerr == ERROR_NO_MORE_FILES) {
      errno = 0;
    } else {
      errno = EIO;
      env->die(env, stack, "[System Error]_wfindnext64() failed(%d: %s). Windows Error Code: %d.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), winerr);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
    }
	  _findclose (dirp->dd_handle);
	  dirp->dd_handle = -1;
	  dirp->dd_stat = -1;
	}
      else
	{
	  /* Update the status to indicate the correct
	   * number. */
	  dirp->dd_stat++;
	}
    }

  if (dirp->dd_stat > 0)
    {
      /* Successfully got an entry. Everything about the file is
       * already appropriately filled in except the length of the
       * file name. */
      dirp->dd_dir.d_namlen = wcslen (dirp->dd_dta.name);
      wcscpy_s(dirp->dd_dir.d_name, 260, dirp->dd_dta.name);
      return &dirp->dd_dir;
    }

  return (SPVM_SYS_WINDOWS_WDIRENT *) 0;
}

int spvm_sys_windows_closedir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR* dirp) {
  int32_t status;
  
  assert(dirp);
  
  if (dirp->dd_handle != -1) {
    status = _findclose(dirp->dd_handle);
    if (status == -1) {
      env->die(env, stack, "[System Error]_findclose() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
      goto END_OF_FUNC;
    }
  }
  else {
    status = 0;
  }
  
  END_OF_FUNC:
  
  free(dirp);
  
  return status;
}

void spvm_sys_windows_rewinddir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR* dirp) {
  
  assert(dirp);
  
  if (dirp->dd_handle != -1) {
    /* Ensure the existing directory search handle is closed before rewinding.
     * On Windows, there is no way to seek to the beginning of a directory 
     * search session, so we must close the handle and re-open it 
     * on the next readdir call. */
    if (_findclose(dirp->dd_handle) == -1) {
      spvm_warn("[abort]_findclose() failed(%d: %s).", errno, env->strerror_nolen(env, stack, errno));
      abort();
    }
  }
  
  dirp->dd_handle = -1;
  dirp->dd_stat = 0;
}

int64_t spvm_sys_windows_telldir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR* dirp) {
  
  assert(dirp);
  
  return dirp->dd_stat;
}

void spvm_sys_windows_seekdir(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR* dirp, int64_t offset) {
  int32_t my_errno = 0;
  
  assert(dirp);
  assert(offset >= 0);
  
  spvm_sys_windows_rewinddir (env, stack, dirp);
  
  while (1) {
    if (dirp->dd_stat >= offset) {
      break;
    }
    errno = 0;
    SPVM_SYS_WINDOWS_WDIRENT* dirent = spvm_sys_windows_readdir(env, stack, dirp);
    if (!dirent) {
      if (!(errno == 0)) {
        spvm_warn("[abort]spvm_sys_windows_readdir failed(%d: %s).", errno, env->strerror_nolen(env, stack, errno));
        abort();
      }
      break;
    }
  }
}

int spvm_sys_windows_ftruncate(SPVM_ENV* env, SPVM_VALUE* stack, int fd, int64_t length) {
  
  int32_t status;
  int32_t my_errno = _chsize_s(fd, length);
  if (my_errno == 0) {
    status = 0;
  }
  else {
    status = -1;
    env->die(env, stack, "[System Error]spvm_sys_windows_ftruncate() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

// The output is the same as Perl's spvm_sys_windows_file_time_to_epoch in Win32.c
static time_t spvm_sys_windows_file_time_to_epoch(SPVM_ENV* env, SPVM_VALUE* stack, FILETIME file_time) {
  SYSTEMTIME system_time;
  struct tm st_tm = {0};
  
  time_t epoch = -1;
  
  if (!FileTimeToSystemTime(&file_time, &system_time)) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
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
int32_t spvm_sys_windows_fstat_by_handle(SPVM_ENV* env, SPVM_VALUE* stack, HANDLE handle, SPVM_SYS_WINDOWS_STAT *st_stat) {
  
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
            spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
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
        
        st_stat->st_atime = spvm_sys_windows_file_time_to_epoch(env, stack, file_info.ftLastAccessTime);
        st_stat->st_mtime = spvm_sys_windows_file_time_to_epoch(env, stack, file_info.ftLastWriteTime);
        st_stat->st_ctime = spvm_sys_windows_file_time_to_epoch(env, stack, file_info.ftCreationTime);
        
        if (reparse_type) {
          /* https://docs.microsoft.com/en-us/openspecs/windows_protocols/ms-fscc/c8e77b37-3909-4fe6-a4ea-2b9d423b1ee4
             describes all of these as WSL only, but the AF_UNIX tag
             is known to be used for AF_UNIX sockets without WSL.
          */
          st_stat->st_mode = 0;
          switch ((uint32_t)reparse_type) {
            case IO_REPARSE_TAG_AF_UNIX: {
              st_stat->st_mode = S_IFSOCK;
              break;
            }
            case IO_REPARSE_TAG_LX_FIFO: {
              st_stat->st_mode = S_IFIFO;
              break;
            }
            case IO_REPARSE_TAG_LX_CHR: {
              st_stat->st_mode = S_IFCHR;
              break;
            }
            case IO_REPARSE_TAG_LX_BLK: {
              st_stat->st_mode = S_IFBLK;
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
            st_stat->st_mode = S_IFDIR | S_IREAD | S_IEXEC;
            /* duplicate the logic from the end of the old win32_stat() */
            if (!(file_info.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
              st_stat->st_mode |= S_IWRITE;
            }
          }
          else {
            st_stat->st_mode = _S_IFREG;
            
            int32_t needed_len = GetFinalPathNameByHandleW(handle, NULL, 0, 0);
            
            if (needed_len == 0) {
              spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
              goto END_OF_FUNC;
            }
            
            WCHAR* path_w = (WCHAR*)env->new_memory_block(env, stack, sizeof(WCHAR) * (needed_len + 1));
            
            int32_t len = GetFinalPathNameByHandleW(handle, path_w, needed_len + 1, 0);
            
            if (len) {
              if (len > 4 &&
                (_wcsicmp(path_w + len - 4, L".exe") == 0 ||
                 _wcsicmp(path_w + len - 4, L".bat") == 0 ||
                 _wcsicmp(path_w + len - 4, L".cmd") == 0 ||
                 _wcsicmp(path_w + len - 4, L".com") == 0))
              {
                st_stat->st_mode |= S_IEXEC;
              }
            }
            
            env->free_memory_block(env, stack, path_w);
            
            if (!len) {
              spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
              goto END_OF_FUNC;
            }
            
            if (!(file_info.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
              st_stat->st_mode |= S_IWRITE;
            }
            st_stat->st_mode |= S_IREAD;
          }
        }
      }
      else {
        spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
        goto END_OF_FUNC;
      }
      break;
    }
    case FILE_TYPE_CHAR:
    case FILE_TYPE_PIPE:
    {
      st_stat->st_mode = (type == FILE_TYPE_CHAR) ? S_IFCHR : S_IFIFO;
      if (handle == GetStdHandle(STD_INPUT_HANDLE) ||
        handle == GetStdHandle(STD_OUTPUT_HANDLE) ||
        handle == GetStdHandle(STD_ERROR_HANDLE)) {
        st_stat->st_mode |= S_IWRITE | S_IREAD;
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

int32_t spvm_sys_windows_stat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat) {
  
  int32_t result;
  
  int32_t error_id = 0;
  
  WCHAR* path_w = (WCHAR*)spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
  
  HANDLE handle =
      CreateFileW(path_w, FILE_READ_ATTRIBUTES,
                  FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                  NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  
  int32_t ReparseTag = 0;
  if (handle == INVALID_HANDLE_VALUE) {
    SPVM_OBJ* obj_resolved_link_text = NULL;
    {
      SPVM_OBJ* obj_link_text = NULL;
      stack[0].oval = env->new_string(env, stack, path, strlen(path));
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
    
    handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(resolved_link_text_w);
    
    if (handle == INVALID_HANDLE_VALUE) {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  result = spvm_sys_windows_fstat_by_handle(env, stack, handle, st_stat);
  
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
      env->die(env, stack, "[System Error]spvm_sys_windows_stat() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    }
    
    return -1;
  }
  
  return 0;
}

int32_t spvm_sys_windows_lstat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat) {   
  
  int32_t result;
  int32_t is_sym;
  
  int32_t error_id = 0;
  
  HANDLE handle = NULL;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  
  handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(path_w);
  if (handle == INVALID_HANDLE_VALUE) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  result = spvm_sys_windows_fstat_by_handle(env, stack, handle, st_stat);
  
  if (result == -1) {
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  is_sym = spvm_sys_windows_is_symlink_by_handle(env, stack, handle);
  
  if (is_sym) {
    SPVM_OBJ* obj_link_text = NULL;
    stack[0].oval = env->new_string(env, stack, path, strlen(path));
    env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "win_readlink", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      goto END_OF_FUNC;
    }
    
    obj_link_text = stack[0].oval;
    
    int32_t link_text_length = env->length(env, stack, obj_link_text);
    
    st_stat->st_mode = (st_stat->st_mode & ~S_IFMT) | S_IFLNK;
    st_stat->st_size = link_text_length;
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]spvm_sys_windows_lstat() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    }
    
    return -1;
  }
  
  return 0;
}

HANDLE spvm_sys_windows_util_CreateFileW_for_read_common(const WCHAR* path_w, int32_t file_flag) {

  HANDLE handle = CreateFileW(path_w, GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
    file_flag|FILE_FLAG_BACKUP_SEMANTICS, 0
  );
  
  return handle;
}

HANDLE spvm_sys_windows_util_CreateFileW_for_read(const WCHAR* path_w) {
  
  return spvm_sys_windows_util_CreateFileW_for_read_common(path_w, 0);
}

HANDLE spvm_sys_windows_util_CreateFileW_reparse_point_for_read(const WCHAR* path_w) {

  return spvm_sys_windows_util_CreateFileW_for_read_common(path_w, FILE_FLAG_OPEN_REPARSE_POINT);
}

void spvm_sys_windows_util_win_last_error_to_errno(int32_t default_errno) {
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
    {
      errno = ENOENT;
      break;
    }
    case ERROR_ALREADY_EXISTS: {
      errno = EEXIST;
      break;
    }
    case ERROR_ACCESS_DENIED: {
      errno = EACCES;
      break;
    }
    case ERROR_PRIVILEGE_NOT_HELD: {
      errno = EPERM;
      break;
    }
    case ERROR_NOT_SAME_DEVICE: {
      errno = EXDEV;
      break;
    }
    case ERROR_DISK_FULL: {
      errno = ENOSPC;
      break;
    }
    case ERROR_NOT_ENOUGH_QUOTA: {
      errno = EDQUOT;
      break;
    }
    default: {
      errno = default_errno;
    }
  }
}

static inline int lc_set_errno(int result)
{
    if (result != 0) {
        errno = result;
        return -1;
    }
    return 0;
}

#define POW10_9                 1000000000

int spvm_sys_windows_clock_getres(SPVM_ENV* env, SPVM_VALUE* stack, int32_t clock_id, struct timespec *res)
{
    int32_t id = clock_id;

    switch(id) {
    case CLOCK_REALTIME:
    case CLOCK_MONOTONIC:
        {
            LARGE_INTEGER pf;

            if (QueryPerformanceFrequency(&pf) == 0)
                return lc_set_errno(EINVAL);

            res->tv_sec = 0;
            res->tv_nsec = (int) ((POW10_9 + (pf.QuadPart >> 1)) / pf.QuadPart);
            if (res->tv_nsec < 1)
                res->tv_nsec = 1;

            return 0;
        }

    case CLOCK_REALTIME_COARSE:
    case CLOCK_PROCESS_CPUTIME_ID:
    case CLOCK_THREAD_CPUTIME_ID:
        {
            DWORD   timeAdjustment, timeIncrement;
            BOOL    isTimeAdjustmentDisabled;

            (void) GetSystemTimeAdjustment(&timeAdjustment, &timeIncrement, &isTimeAdjustmentDisabled);
            res->tv_sec = 0;
            res->tv_nsec = timeIncrement * 100;

            return 0;
        }
    default:
        break;
    }

    return lc_set_errno(EINVAL);
}

unsigned int spvm_sys_windows_sleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  return 0;
}

int spvm_sys_windows_usleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int usec) {
  std::this_thread::sleep_for(std::chrono::microseconds(usec));
  return 0;
}

int spvm_sys_windows_gettimeofday (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_TIMEVAL* tv, void* tz) {
  auto now = std::chrono::system_clock::now();
  
  auto duration = now.time_since_epoch();
  
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - seconds);
  
  if (tv != NULL) {
    tv->tv_sec = static_cast<int64_t>(seconds.count());
    tv->tv_usec = static_cast<int32_t>(microseconds.count());
  }
  
  return 0;
}

int spvm_sys_windows_clock_gettime(SPVM_ENV* env, SPVM_VALUE* stack, int clk_id, struct timespec *ts) {
  /* Check null pointer */
  if (ts == nullptr) {
    errno = EINVAL;
    return -1;
  }

  std::chrono::nanoseconds duration;

  /* clk_id is int32_t, so logic is identical on all compilers */
  if (clk_id == CLOCK_MONOTONIC) {
    /* Monotonic time */
    duration = std::chrono::steady_clock::now().time_since_epoch();
  } else if (clk_id == CLOCK_REALTIME) {
    /* Wall clock time */
    duration = std::chrono::system_clock::now().time_since_epoch();
  } else {
    /* Unsupported ID */
    errno = EINVAL;
    return -1;
  }
  
  /* Convert to seconds and nanoseconds */
  auto sec = std::chrono::duration_cast<std::chrono::seconds>(duration);
  auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(duration - sec);

  /* Set to C struct */
  ts->tv_sec = static_cast<time_t>(sec.count());
  ts->tv_nsec = static_cast<long>(nsec.count());

  return 0;
}

int spvm_sys_windows_nanosleep(SPVM_ENV* env, SPVM_VALUE* stack, const struct timespec* req, struct timespec* rem) {
  
  assert(req);
  
  if (!req || req->tv_nsec < 0 || req->tv_nsec >= 1000000000) {
    errno = EINVAL;
    return -1;
  }
  
  auto duration = std::chrono::seconds(req->tv_sec) + std::chrono::nanoseconds(req->tv_nsec);
  
  auto start = std::chrono::steady_clock::now();
  std::this_thread::sleep_for(duration);
  auto elapsed = std::chrono::steady_clock::now() - start;
  
  if (elapsed < duration) {
    if (rem) {
      auto remaining = duration - elapsed;
      auto rem_sec = std::chrono::duration_cast<std::chrono::seconds>(remaining);
      auto rem_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(remaining - rem_sec);
      
      rem->tv_sec = (time_t)rem_sec.count();
      rem->tv_nsec = (long)rem_nsec.count();
    }
    
    errno = EINTR;
    return -1;
  }
  
  return 0;
}

int spvm_sys_windows_execv(SPVM_ENV* env, SPVM_VALUE* stack, const char *path, char *const argv[]) {
  
  int32_t args_length;
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  
  int status = -1;
  WCHAR** argv_w = NULL;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  args_length = 0;
  while (argv[args_length] != NULL) {
    args_length++;
  }
  
  argv_w = (WCHAR**)env->new_memory_block(env, stack, sizeof(WCHAR*) * (args_length + 1));
  for (int32_t i = 0; i < args_length; i++) {
    char* arg = argv[i];
    WCHAR* arg_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, arg, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      my_errno = EILSEQ;
      goto END_OF_FUNC;
    }
    
    argv_w[i] = arg_w;
  }
  
  status = _wexecv(path_w, (const WCHAR *const *)argv_w);
  my_errno = errno;
  if (status == -1) {
    env->die(env, stack, "[System Error]_wexecv() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (argv_w) {
    env->free_memory_block(env, stack, argv_w);
  }
  
  errno = my_errno;
  
  return status;
}

FILE* spvm_sys_windows_fopen(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, const char* mode) {
  
  WCHAR* mode_w;
  
  assert(path);
  assert(mode);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  
  FILE* fs = NULL;
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  mode_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, mode, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  fs = _wfopen(path_w, mode_w);
  my_errno = errno;
  if (!fs) {
    env->die(env, stack, "[System Error]_wfopen() failed(%d: %s). $path='%s', $mode='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path, mode);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return fs;
}

int spvm_sys_windows_open(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, int intmode, int perms) {
  
  assert(path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  
  int32_t fd;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  fd = _wopen(path_w, intmode, perms);
  my_errno = errno;
  if (fd == -1) {
    env->die(env, stack, "[System Error]_wopen() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return fd;
}

int spvm_sys_windows_chmod(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, int mode) {
  
  int32_t status;
  
  assert(path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  status = _wchmod(path_w, mode);
  if (status == -1) {
    my_errno = errno;
    env->die(env, stack, "[System Error]_wchmod() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

int spvm_sys_windows_chdir(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {
  
  int32_t status;
  
  assert(path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  status = _wchdir(path_w);
  if (status == -1) {
    my_errno = errno;
    env->die(env, stack, "[System Error]_wchdir() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

int32_t spvm_sys_windows_is_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {

  WCHAR* path_w;
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  int32_t is_sym = 0;
  HANDLE handle = NULL;
  
  if (!path) {
    my_errno = EFAULT;
    env->set_error_id(env, stack, env->die(env, stack, "Path $path must be defined.", __func__, FILE_NAME, __LINE__));
    goto END_OF_FUNC;
  }
  
  path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    env->set_error_id(env, stack, error_id);
    goto END_OF_FUNC;
  }
  
  env->push_caller_stack(env, stack, __func__, FILE_NAME, __LINE__ + 1);
  handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(path_w);
  env->pop_caller_stack(env, stack);
  
  if (handle == INVALID_HANDLE_VALUE) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    my_errno = errno;
    goto END_OF_FUNC;
  }
  
  errno = 0;
  env->push_caller_stack(env, stack, __func__, FILE_NAME, __LINE__ + 1);
  is_sym = spvm_sys_windows_is_symlink_by_handle(env, stack, handle);
  env->pop_caller_stack(env, stack);
  if (errno) {
    my_errno = errno;
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    // No error check because of read-only file handle
    CloseHandle(handle);
  }

  errno = my_errno;

  return is_sym;
}

SPVM_OBJ* spvm_sys_windows_realpath(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {
  
  assert(path);
  
  HANDLE handle;
  SPVM_OBJ* obj_resolved_path;
  const char* resolved_link_text;
  WCHAR* resolved_link_text_w;
  int32_t needed_len;
  SPVM_OBJ* obj_resolved_path_w;
  WCHAR* resolved_path_w;
  int32_t len;
  char* resolved_path_tmp;
  char* resolved_path;
  int32_t resolved_path_length;
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  handle = NULL;
  obj_resolved_path = NULL;
  
  SPVM_OBJ* obj_resolved_link_text = NULL;
  {
    stack[0].oval = env->new_string_nolen(env, stack, path);
    env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "_follow_symlinks_to", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) {
      my_errno = EINVAL;
      goto END_OF_FUNC;
    }
    obj_resolved_link_text = stack[0].oval;
  }
  
  resolved_link_text = env->get_chars(env, stack, obj_resolved_link_text);
  resolved_link_text_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, resolved_link_text, &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(resolved_link_text_w);
  if (handle == INVALID_HANDLE_VALUE) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    goto END_OF_FUNC;
  }
  
  needed_len = GetFinalPathNameByHandleW(handle, NULL, 0, 0);
  if (needed_len == 0) {
    env->die(env, stack, "[System Error]GetFinalPathNameByHandleW() failed. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
    my_errno = EINVAL;
    goto END_OF_FUNC;
  }
  
  obj_resolved_path_w = env->new_short_array(env, stack, needed_len);
  resolved_path_w = (WCHAR*)env->get_elems_short(env, stack, obj_resolved_path_w);
  
  len = GetFinalPathNameByHandleW(handle, resolved_path_w, needed_len, 0);
  if (len == 0) {
    env->die(env, stack, "[System Error]GetFinalPathNameByHandleW() failed. $path='%s'.", __func__, FILE_NAME, __LINE__, path);
    my_errno = EINVAL;
    goto END_OF_FUNC;
  }
  
  resolved_path_tmp = (char*)spvm_sys_windows_win_wchar_to_utf8(env, stack, resolved_path_w, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  obj_resolved_path = env->new_string(env, stack, resolved_path_tmp, strlen(resolved_path_tmp));
  resolved_path = (char*)env->get_chars(env, stack, obj_resolved_path);
  resolved_path_length = env->length(env, stack, obj_resolved_path);
  
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
  
  END_OF_FUNC:
  
  if (handle != INVALID_HANDLE_VALUE) {
    CloseHandle(handle);
  }
  
  return obj_resolved_path;
}

int spvm_sys_windows_unlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {
  
  DWORD attrs;
  
  assert(path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  int32_t status = -1;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  attrs = GetFileAttributesW(path_w);
  
  if (attrs == 0xFFFFFFFF) {
    errno = ENOENT;
    my_errno = errno;
    env->die(env, stack, "[System Error]GetFileAttributesW() failed. errno=%d(%s), $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    goto END_OF_FUNC;
  }
  
  if (attrs & FILE_ATTRIBUTE_READONLY) {
    SetFileAttributesW(path_w, attrs & ~FILE_ATTRIBUTE_READONLY);
    status = _wunlink(path_w);
    if (status == -1) {
      my_errno = errno;
      env->die(env, stack, "[System Error]_wunlink() failed. errno=%d(%s), $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
      SetFileAttributesW(path_w, attrs);
    }
  }
  else if ((attrs & (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY))
    == (FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_DIRECTORY)
         && spvm_sys_windows_is_symlink(env, stack, path))
  {
    status = _wrmdir(path_w);
    if (status == -1) {
      my_errno = errno;
      env->die(env, stack, "[System Error]_wrmdir() failed. errno=%d(%s), $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    }
  }
  else {
    status = _wunlink(path_w);
    if (status == -1) {
      my_errno = errno;
      env->die(env, stack, "[System Error]_wunlink() failed. errno=%d(%s), $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    }
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

int spvm_sys_windows_rename(SPVM_ENV* env, SPVM_VALUE* stack, const char* old_path, const char* new_path) {
  
  WCHAR* new_path_w;
  DWORD flags;
  int32_t success;
  
  assert(old_path);
  assert(new_path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  int32_t status = -1;
  
  WCHAR* old_path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, old_path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  new_path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, new_path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  flags = MOVEFILE_COPY_ALLOWED;
  if (!(_wcsicmp(new_path_w, old_path_w) == 0)) {
    flags |= MOVEFILE_REPLACE_EXISTING;
  }
  
  success = MoveFileExW(old_path_w, new_path_w, flags);
  status = success ? 0 : -1;
  if (status == -1) {
    spvm_sys_windows_util_win_last_error_to_errno(EACCES);
    my_errno = errno;
    env->die(env, stack, "[System Error]MoveFileExW(). errno=%d(%s), $old_path='%s', $new_path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), old_path, new_path);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

static inline int32_t spvm_sys_windows_is_path_separator(WCHAR ch_w) {
  return (ch_w == L'/' || ch_w == L'\\');
};

int spvm_sys_windows_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* old_path, const char* new_path) {
  
  WCHAR* new_path_w;
  int32_t old_path_w_length;
  int32_t success;
  int32_t old_path_is_dir;
  DWORD create_flags;
  
  assert(old_path);
  assert(new_path);
  
  int32_t error_id = 0;
  int32_t my_errno = 0;
  int32_t status = -1;
  
  WCHAR* old_path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, old_path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  new_path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, new_path, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    my_errno = EILSEQ;
    goto END_OF_FUNC;
  }
  
  // Win32 (or perhaps NTFS) won't follow symlinks containing /, so replace any with \\.
  old_path_w_length = wcslen(old_path_w);
  for (int32_t i = 0; i < old_path_w_length; i++) {
    if (old_path_w[i] == L'/') {
      old_path_w[i] = L'\\';
    }
  }
  
  create_flags = SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;
  /* are we linking to a directory?
     CreateSymlinkW() needs to know if the target is a directory,
     If it looks like a directory name:
      - ends in slash
      - is just . or ..
      - ends in /. or /.. (with either slash)
      - is a simple drive letter
     assume it's a directory.
     Otherwise if the old_path_w is relative we need to make a relative path
     based on the new_path_w to check if the target is a directory.
  */
  old_path_is_dir = 0;
  if (old_path_w_length >= 1 && spvm_sys_windows_is_path_separator(old_path_w[old_path_w_length - 1])) {
    old_path_is_dir = 1;
  }
  else if (wcscmp(old_path_w, L"..") == 0) {
    old_path_is_dir = 1;
  }
  else if (wcscmp(old_path_w, L".") == 0) {
    old_path_is_dir = 1;
  }
  else if (old_path_w_length >= 2 && spvm_sys_windows_is_path_separator(old_path_w[old_path_w_length - 2]) && old_path_w[old_path_w_length - 1] == L'.') {
    old_path_is_dir = 1;
  }
  else if (old_path_w_length >= 3 && wcscmp(old_path_w+old_path_w_length - 3, L"\\..") == 0) {
    old_path_is_dir = 1;
  }
  else if (old_path_w_length == 2 && old_path_w[1] == L':') {
    old_path_is_dir = 1;
  }
  
  if (old_path_is_dir) {
    create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
  }
  else {
    const WCHAR *resolved_path_w = NULL;
    WCHAR *resolved_path_w_tmp = NULL;
    
    int32_t old_path_is_abs = 0;
    if (old_path_w_length >= 3 && old_path_w[1] == L':') {
      /* relative to current directory on a drive, or absolute */
      old_path_is_abs = 1;
    }
    else if (old_path_w[0] == L'\\') {
      old_path_is_abs = 1;
    }
    
    if (old_path_is_abs) {
      resolved_path_w = old_path_w;
    }
    else {
      int32_t last_sep_index = -1;
      size_t new_path_w_length = wcslen(new_path_w);
      for (int32_t i = new_path_w_length - 1; i >= 0; i--) {
        char ch = new_path_w[i];
        if (ch == '\\' || ch == '/') {
          last_sep_index = i;
          break;
        }
      }
      
      if (last_sep_index >= 0) {
        resolved_path_w_tmp = (WCHAR*)env->new_memory_block(env, stack, (last_sep_index + 1 + old_path_w_length + 1) * sizeof(WCHAR));
        memcpy(resolved_path_w_tmp, new_path_w, sizeof(WCHAR) * (last_sep_index + 1));
        memcpy(resolved_path_w_tmp + (last_sep_index + 1), old_path_w, old_path_w_length);
        resolved_path_w = resolved_path_w_tmp;
      }
      else {
        /* new_path_w is just a filename */
        resolved_path_w = old_path_w;
      }
    }
    
    DWORD dest_attr = GetFileAttributesW(resolved_path_w);
    if (dest_attr != (DWORD)-1 && (dest_attr & FILE_ATTRIBUTE_DIRECTORY)) {
      create_flags |= SYMBOLIC_LINK_FLAG_DIRECTORY;
    }
    
    if (resolved_path_w_tmp) {
      env->free_memory_block(env, stack, resolved_path_w_tmp);
    }
  }
  
  success = CreateSymbolicLinkW(new_path_w, old_path_w, create_flags);
  status = success ? 0 : -1;
  if (status == -1) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    my_errno = errno;
    env->die(env, stack, "[System Error]CreateSymbolicLinkW() failed. errno=%d(%s), $old_path='%s', $new_path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), old_path, new_path);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  errno = my_errno;
  
  return status;
}

} // extern "C"

#endif // defined(_WIN32)
