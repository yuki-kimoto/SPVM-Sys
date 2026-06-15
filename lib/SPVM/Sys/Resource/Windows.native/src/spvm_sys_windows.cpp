#if defined(_WIN32)

// C++ headers
#include <thread>
#include <chrono>
#include <filesystem>
#include <system_error>

#include "spvm_sys_windows.h"

extern "C" {

#define SUFFIX	L"*"
#define	SLASH	L"\\"

WCHAR* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  env->push_caller_stack(env, stack, func_name, file, line);
  
  *error_id = 0;
  
  WCHAR* utf16le_string = NULL;
  
  if (utf8_string == NULL) {
    goto END_OF_FUNC;
  }
  
  {
    
    int32_t utf16le_string_length = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8_string,
        -1,
        NULL,
        0
    );
    
    if (utf16le_string_length == 0) {
      *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", __func__, __FILE__, __LINE__, GetLastError());
      goto END_OF_FUNC;
    }
    
    {
      SPVM_OBJ* obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
      WCHAR* utf16le_string_tmp = (WCHAR*)env->get_elems_short(env, stack, obj_utf16le_string);
      
      utf16le_string_length = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8_string,
        -1,
        utf16le_string_tmp,
        utf16le_string_length
      );
      
      if (utf16le_string_length == 0) {
        *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error converting UTF-8 to UTF-16LE: %lu.", __func__, __FILE__, __LINE__, GetLastError());
        goto END_OF_FUNC;
      }
      
      {
        utf16le_string = utf16le_string_tmp;
      }
    }
  }
  
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

int32_t spvm_sys_windows_is_symlink(SPVM_ENV* env, SPVM_VALUE* stack, const char* path) {
  
  int32_t error_id = 0;
  
  int32_t my_errno = 0;
  
  int32_t is_sym = 0;
  
  HANDLE handle = NULL;
  
  if (!path) {
    my_errno = EFAULT;
    env->set_error_id(env, stack, env->die(env, stack, "The path $path must be defined.", __func__, __FILE__, __LINE__));
    goto END_OF_FUNC;
  }
  
  {
    WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, __FILE__, __LINE__);
    if (error_id) {
      my_errno = EILSEQ;
      env->set_error_id(env, stack, error_id);
      goto END_OF_FUNC;
    }
    
    {
      env->push_caller_stack(env, stack, __func__, __FILE__, __LINE__ + 1);
      handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(path_w);
      env->pop_caller_stack(env, stack);
      
      if (handle == INVALID_HANDLE_VALUE) {
        spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
        my_errno = errno;
        goto END_OF_FUNC;
      }
      
      {
        errno = 0;
        env->push_caller_stack(env, stack, __func__, __FILE__, __LINE__ + 1);
        is_sym = spvm_sys_windows_is_symlink_by_handle(env, stack, handle);
        env->pop_caller_stack(env, stack);
        if (errno) {
          my_errno = errno;
          goto END_OF_FUNC;
        }
      }
    }
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    // No error check because of read-only file handle
    CloseHandle(handle);
  }
  
  errno = my_errno;
  
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
      env->set_error_id(env, stack, env->die(env, stack, "Directory $dir must be defined.", __func__, __FILE__, __LINE__));
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }
  
  WCHAR* dir_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, dir, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) {
    errno = EILSEQ;
    env->set_error_id(env, stack, error_id);
    return (SPVM_SYS_WINDOWS_DIR *) 0;
  }
  
  if (dir_w[0] == L'\0')
    {
      errno = ENOTDIR;
      env->set_error_id(env, stack, env->die(env, stack, "Directory $dir must be a non-empty string.", __func__, __FILE__, __LINE__));
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributesW (dir_w);
  if (rc == INVALID_FILE_ATTRIBUTES)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). %d: %s. $dir='%s'.", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno), dir);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      env->die(env, stack, "[System Error]GetFileAttributesW() failed(%d: %s). %d: %s. $dir='%s'.", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno), dir);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Make an absolute pathname.  */
  _wfullpath (szFullPath, dir_w, MAX_PATH);

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
      env->die(env, stack, "[System Error]malloc() failed(%d:%s).", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno));
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Create the search expression. */
  wcscpy (nd->dd_name, szFullPath);

  /* Add on a slash if the path does not end with one. */
  if (nd->dd_name[0] != L'\0' &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != L'/' &&
      nd->dd_name[wcslen (nd->dd_name) - 1] != L'\\')
    {
      wcscat (nd->dd_name, SLASH);
    }

  /* Add on the search pattern */
  wcscat (nd->dd_name, SUFFIX);

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
      env->set_error_id(env, stack, env->die(env, stack, "Directory stream $dirp must be defined.", __func__, __FILE__, __LINE__));
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
      env->die(env, stack, "[System Error]_wfindnext64() failed(%d: %s). Windows Error Code: %d.", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno), winerr);
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
      wcscpy (dirp->dd_dir.d_name, dirp->dd_dta.name);
      return &dirp->dd_dir;
    }

  return (SPVM_SYS_WINDOWS_WDIRENT *) 0;
}


/*
 * closedir
 *
 * Frees up resources allocated by opendir.
 */
int spvm_sys_windows_closedir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp) {
  int status;

  errno = 0;
  status = 0;

  if (!dirp)
    {
      errno = EFAULT;
      env->die(env, stack, "Directry stream $dirp must be defined.", __func__, __FILE__, __LINE__);
      env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      return -1;
    }

  if (dirp->dd_handle != -1)
    {
      status = _findclose (dirp->dd_handle);
      if (status == -1) {
        env->die(env, stack, "[System Error]_findclose() failed(%d: %s).", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno));
        env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
      }
    }

  /* Delete the dir structure. */
  free (dirp);

  return status;
}

/*
 * rewinddir
 *
 * Return to the beginning of the directory "stream". We simply call findclose
 * and then reset things like an opendir.
 */
void spvm_sys_windows_rewinddir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      env->set_error_id(env, stack, env->die(env, stack, "Directory stream $dirp must be defined.", __func__, __FILE__, __LINE__));
      return;
    }

  if (dirp->dd_handle != -1)
    {
      if (_findclose (dirp->dd_handle) == -1)
        {
          env->die(env, stack, "[System Error]_findclose() failed(%d: %s).", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno));
          env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
        }
    }

  dirp->dd_handle = -1;
  dirp->dd_stat = 0;
}

/*
 * telldir
 *
 * Returns the "position" in the "directory stream" which can be used with
 * seekdir to go back to an old entry. We simply return the value in stat.
 */
long spvm_sys_windows_telldir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      env->set_error_id(env, stack, env->die(env, stack, "Directory stream $dirp must be defined.", __func__, __FILE__, __LINE__));
      return -1;
    }
  return dirp->dd_stat;
}

/*
 * seekdir
 *
 * Seek to an entry previously returned by telldir. We rewind the directory
 * and call readdir repeatedly until either dd_stat is the position number
 * or -1 (off the end). This is not perfect, in that the directory may
 * have changed while we weren't looking. But that is probably the case with
 * any such system.
 */
void spvm_sys_windows_seekdir (SPVM_ENV* env, SPVM_VALUE* stack, SPVM_SYS_WINDOWS_DIR * dirp, long offset) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      env->set_error_id(env, stack, env->die(env, stack, "Directory stream $dirp must be defined.", __func__, __FILE__, __LINE__));
      return;
    }

  if (offset < -1)
    {
      /* Seeking to an invalid position. */
      errno = EINVAL;
      env->set_error_id(env, stack, env->die(env, stack, "Invalid directory position $offset.", __func__, __FILE__, __LINE__));
      return;
    }
  else if (offset == -1)
    {
      /* Seek past end. */
      if (dirp->dd_handle != -1)
	{
	  if (_findclose (dirp->dd_handle) == -1)
            {
              env->die(env, stack, "[System Error]_findclose() failed(%d: %s).", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno));
              env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
            }
	}
      dirp->dd_handle = -1;
      dirp->dd_stat = -1;
    }
  else
    {
      /* Rewind and read forward to the appropriate index. */
      spvm_sys_windows_rewinddir (env, stack, dirp);

      while ((dirp->dd_stat < offset) && spvm_sys_windows_readdir(env, stack, dirp))
	;
    }
}

int spvm_sys_windows_ftruncate(SPVM_ENV* env, SPVM_VALUE* stack, int fd, int64_t length) {
  
  int32_t ret_errno = _chsize_s(fd, length);
  
  int status = 0;
  if (!(ret_errno == 0)) {
    errno = ret_errno;
    status = -1;
    env->die(env, stack, "[System Error]spvm_sys_windows_ftruncate() failed(%d: %s).", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    env->set_error_id(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
  }
  
  return status;
}

unsigned int spvm_sys_windows_sleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  return 0;
}

int spvm_sys_windows_usleep(SPVM_ENV* env, SPVM_VALUE* stack, unsigned int usec) {
  std::this_thread::sleep_for(std::chrono::microseconds(usec));
  return 0;
}

int spvm_sys_windows_gettimeofday (SPVM_ENV* env, SPVM_VALUE* stack, struct timeval* tv, void* tz) {
  auto now = std::chrono::system_clock::now();
  
  auto duration = now.time_since_epoch();
  
  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - seconds);
  
  if (tv != NULL) {
    tv->tv_sec = static_cast<long>(seconds.count());
    tv->tv_usec = static_cast<long>(microseconds.count());
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

// The output is the same as Perl's spvm_sys_windows_file_time_to_epoch in Win32.c
static time_t spvm_sys_windows_file_time_to_epoch(SPVM_ENV* env, SPVM_VALUE* stack, FILETIME file_time) {
  SYSTEMTIME system_time;
  struct tm st_tm = {0};
  
  time_t epoch = -1;
  
  if (!FileTimeToSystemTime(&file_time, &system_time)) {
    spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
    goto END_OF_FUNC;
  }
  
  {
    st_tm.tm_year = system_time.wYear - 1900;
    st_tm.tm_mon = system_time.wMonth - 1;
    st_tm.tm_mday = system_time.wDay;
    st_tm.tm_hour = system_time.wHour;
    st_tm.tm_min = system_time.wMinute;
    st_tm.tm_sec = system_time.wSecond;
    
    epoch = _mkgmtime(&st_tm);
  }
  
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
        
        {
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
              
              {
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
                
                {
                  if (!(file_info.dwFileAttributes & FILE_ATTRIBUTE_READONLY)) {
                    st_stat->st_mode |= S_IWRITE;
                  }
                  st_stat->st_mode |= S_IREAD;
                }
              }
            }
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
  
  {
    /* owner == user == group */
    st_stat->st_mode |= (st_stat->st_mode & 0700) >> 3;
    st_stat->st_mode |= (st_stat->st_mode & 0700) >> 6;
    
    status = 0;
  }
  
  END_OF_FUNC:
  
  return status;
}

int32_t spvm_sys_windows_stat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat) {
  
  int32_t error_id = 0;
  
  WCHAR* path_w = (WCHAR*)spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, __FILE__, __LINE__);
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
      env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "_follow_symlinks_to", 1, &error_id, __func__, __FILE__, __LINE__);
      if (error_id) {
        goto END_OF_FUNC;
      }
      
      {
        obj_resolved_link_text = stack[0].oval;
      }
    }
    const char* resolved_link_text = env->get_chars(env, stack, obj_resolved_link_text);
    
    WCHAR* resolved_link_text_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, resolved_link_text, &error_id, __func__, __FILE__, __LINE__);
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
  
  {
    int32_t result = spvm_sys_windows_fstat_by_handle(env, stack, handle, st_stat);
    
    if (result == -1) {
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]spvm_sys_windows_stat() failed(%d: %s). $path='%s'.", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    }
    
    return -1;
  }
  
  return 0;
}

int32_t spvm_sys_windows_lstat(SPVM_ENV* env, SPVM_VALUE* stack, const char* path, SPVM_SYS_WINDOWS_STAT *st_stat) {   
  
  int32_t error_id = 0;
  
  HANDLE handle = NULL;
  
  WCHAR* path_w = spvm_sys_windows_utf8_to_win_wchar(env, stack, path, &error_id, __func__, __FILE__, __LINE__);
  if (error_id) {
    goto END_OF_FUNC;
  }
  
  {
    handle = spvm_sys_windows_util_CreateFileW_reparse_point_for_read(path_w);
    if (handle == INVALID_HANDLE_VALUE) {
      spvm_sys_windows_util_win_last_error_to_errno(EINVAL);
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
      goto END_OF_FUNC;
    }
    
    {
      int32_t result = spvm_sys_windows_fstat_by_handle(env, stack, handle, st_stat);
      
      if (result == -1) {
        error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
        goto END_OF_FUNC;
      }
      
      {
        int32_t is_sym = spvm_sys_windows_is_symlink_by_handle(env, stack, handle);
        
        if (is_sym) {
          SPVM_OBJ* obj_link_text = NULL;
          stack[0].oval = env->new_string(env, stack, path, strlen(path));
          env->call_class_method_by_name(env, stack, "Sys::IO::Windows", "win_readlink", 1, &error_id, __func__, __FILE__, __LINE__);
          if (error_id) {
            goto END_OF_FUNC;
          }
          
          {
            obj_link_text = stack[0].oval;
            
            int32_t link_text_length = env->length(env, stack, obj_link_text);
            
            st_stat->st_mode = (st_stat->st_mode & ~S_IFMT) | S_IFLNK;
            st_stat->st_size = link_text_length;
          }
        }
      }
    }
  }
  
  END_OF_FUNC:
  
  if (!(handle == INVALID_HANDLE_VALUE)) {
    CloseHandle(handle);
  }
  
  if (error_id) {
    if (errno) {
      env->die(env, stack, "[System Error]spvm_sys_windows_lstat() failed(%d: %s). $path='%s'.", __func__, __FILE__, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
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

} // extern "C"

#endif // defined(_WIN32)
