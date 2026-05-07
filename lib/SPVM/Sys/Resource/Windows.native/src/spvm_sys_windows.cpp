#if defined(_WIN32)

// C++ headers
#include <chrono>
#include <filesystem>
#include <system_error>

#include "spvm_sys_windows.h"

extern "C" {

#define SUFFIX	L"*"
#define	SLASH	L"\\"

WCHAR* spvm_sys_windows_utf8_to_win_wchar(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
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
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error calculating length: %lu.", func_name, file, line, GetLastError());
    return NULL;
  }
  
  SPVM_OBJ* obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
  WCHAR* utf16le_string = (WCHAR*)env->get_elems_short(env, stack, obj_utf16le_string);
  
  utf16le_string_length = MultiByteToWideChar(
    CP_UTF8,
    0,
    utf8_string,
    -1,
    utf16le_string,
    utf16le_string_length
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_win_wchar failed:Error converting UTF-8 to UTF-16LE: %lu.", func_name, file, line, GetLastError());
    return NULL;
  }
  
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

void spvm_sys_windows_win_last_error_to_errno(int32_t default_errno) {
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

static HANDLE spvm_sys_windows_CreateFileW_for_read_common(const WCHAR* path_w, int32_t file_flag) {

  HANDLE handle = CreateFileW(path_w, GENERIC_READ,
    FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
    file_flag|FILE_FLAG_BACKUP_SEMANTICS, 0
  );
  
  return handle;
}

HANDLE spvm_sys_windows_CreateFileW_for_read(const WCHAR* path_w) {
  
  return spvm_sys_windows_CreateFileW_for_read_common(path_w, 0);
}

HANDLE spvm_sys_windows_CreateFileW_reparse_point_for_read(const WCHAR* path_w) {

  return spvm_sys_windows_CreateFileW_for_read_common(path_w, FILE_FLAG_OPEN_REPARSE_POINT);
}

int32_t spvm_sys_windows_is_symlink_by_handle(HANDLE handle) {
  
  int32_t is_sym = 0;
  
  SPVM_SYS_WINDOWS_REPARSE_DATA_BUFFER linkdata = {0};
  if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0, &linkdata, sizeof(linkdata), NULL, NULL)) {
    if (GetLastError() == ERROR_NOT_A_REPARSE_POINT) {
      goto END_OF_FUNC;
    }
    else {
      spvm_sys_windows_win_last_error_to_errno(EINVAL);
      goto END_OF_FUNC;
    }
  }
  
  if (linkdata.ReparseTag == IO_REPARSE_TAG_SYMLINK || linkdata.ReparseTag == IO_REPARSE_TAG_MOUNT_POINT) {
    is_sym = 1;
  }
  
  END_OF_FUNC:
  
  return is_sym;
}

int spvm_sys_windows_is_symlink(const WCHAR* path_w) {
  std::error_code var_error_code;
  std::filesystem::path var_path(path_w);
  
  std::filesystem::file_status var_file_status = std::filesystem::symlink_status(var_path, var_error_code);
  
  if (var_error_code) {
    SetLastError(var_error_code.value());
    spvm_sys_windows_win_last_error_to_errno(EINVAL);
    return 0;
  }
  
  WIN32_FILE_ATTRIBUTE_DATA var_data;
  if (GetFileAttributesExW(path_w, GetFileExInfoStandard, &var_data)) {
    if (var_data.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) {
      return 1;
    }
  }
  
  return 0;
}

/*
 * opendir
 *
 * Returns a pointer to a DIR structure appropriately filled in to begin
 * searching a directory.
 */
SPVM_SYS_WINDOWS_DIR* spvm_sys_windows_opendir (const WCHAR *szPath) {
  SPVM_SYS_WINDOWS_DIR *nd;
  unsigned int rc;
  WCHAR szFullPath[MAX_PATH];

  errno = 0;

  if (!szPath)
    {
      errno = EFAULT;
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  if (szPath[0] == L'\0')
    {
      errno = ENOTDIR;
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Attempt to determine if the given path really is a directory. */
  rc = GetFileAttributesW (szPath);
  if (rc == INVALID_FILE_ATTRIBUTES)
    {
      /* call GetLastError for more error info */
      errno = ENOENT;
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }
  if (!(rc & FILE_ATTRIBUTE_DIRECTORY))
    {
      /* Error, entry exists but not a directory. */
      errno = ENOTDIR;
      return (SPVM_SYS_WINDOWS_DIR *) 0;
    }

  /* Make an absolute pathname.  */
  _wfullpath (szFullPath, szPath, MAX_PATH);

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
SPVM_SYS_WINDOWS_WDIRENT* spvm_sys_windows_readdir (SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  /* Check for valid DIR struct. */
  if (!dirp)
    {
      errno = EFAULT;
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
	  if (winerr == ERROR_NO_MORE_FILES)
	    errno = 0;
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
int spvm_sys_windows_closedir (SPVM_SYS_WINDOWS_DIR * dirp) {
  int rc;

  errno = 0;
  rc = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return -1;
    }

  if (dirp->dd_handle != -1)
    {
      rc = _findclose (dirp->dd_handle);
    }

  /* Delete the dir structure. */
  free (dirp);

  return rc;
}

/*
 * rewinddir
 *
 * Return to the beginning of the directory "stream". We simply call findclose
 * and then reset things like an opendir.
 */
void spvm_sys_windows_rewinddir (SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (dirp->dd_handle != -1)
    {
      _findclose (dirp->dd_handle);
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
long spvm_sys_windows_telldir (SPVM_SYS_WINDOWS_DIR * dirp) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
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
void spvm_sys_windows_seekdir (SPVM_SYS_WINDOWS_DIR * dirp, long lPos) {
  errno = 0;

  if (!dirp)
    {
      errno = EFAULT;
      return;
    }

  if (lPos < -1)
    {
      /* Seeking to an invalid position. */
      errno = EINVAL;
      return;
    }
  else if (lPos == -1)
    {
      /* Seek past end. */
      if (dirp->dd_handle != -1)
	{
	  _findclose (dirp->dd_handle);
	}
      dirp->dd_handle = -1;
      dirp->dd_stat = -1;
    }
  else
    {
      /* Rewind and read forward to the appropriate index. */
      spvm_sys_windows_rewinddir (dirp);

      while ((dirp->dd_stat < lPos) && spvm_sys_windows_readdir (dirp))
	;
    }
}

int spvm_sys_windows_ftruncate(int fd, int64_t length) {
  return _chsize_s(fd, length);
}

unsigned int spvm_sys_windows_sleep(unsigned int seconds) {
  Sleep(seconds * 1000);
  return 0;
}

int spvm_sys_windows_usleep(unsigned int usec) {
  Sleep(usec / 1000);
  return 0;
}

#define FILETIME_1970 116444736000000000ull /* seconds between 1/1/1601 and 1/1/1970 */
#define HECTONANOSEC_PER_SEC 10000000ull

static int getntptimeofday (struct timespec *tp, SPVM_SYS_WINDOWS_TIMEZONE *z)
{
  int res = 0;
  union {
    unsigned long long ns100; /*time since 1 Jan 1601 in 100ns units */
    FILETIME ft;
  }  _now;
  TIME_ZONE_INFORMATION  TimeZoneInformation;
  DWORD tzi;

  if (z != NULL)
    {
      if ((tzi = GetTimeZoneInformation(&TimeZoneInformation)) != TIME_ZONE_ID_INVALID) {
	z->tz_minuteswest = TimeZoneInformation.Bias;
	if (tzi == TIME_ZONE_ID_DAYLIGHT)
	  z->tz_dsttime = 1;
	else
	  z->tz_dsttime = 0;
      }
    else
      {
	z->tz_minuteswest = 0;
	z->tz_dsttime = 0;
      }
    }

  if (tp != NULL) {
    typedef void (WINAPI * GetSystemTimeAsFileTime_t)(LPFILETIME);
    static GetSystemTimeAsFileTime_t GetSystemTimeAsFileTime_p /* = 0 */;

    /* Set function pointer during first call */
    GetSystemTimeAsFileTime_t get_time =
      __atomic_load_n (&GetSystemTimeAsFileTime_p, __ATOMIC_RELAXED);
    if (get_time == NULL) {
      /* Use GetSystemTimePreciseAsFileTime() if available (Windows 8 or later) */
      get_time = (GetSystemTimeAsFileTime_t)(intptr_t) GetProcAddress (
        GetModuleHandle ("kernel32.dll"),
        "GetSystemTimePreciseAsFileTime"); /* <1us precision on Windows 10 */
      if (get_time == NULL)
        get_time = GetSystemTimeAsFileTime; /* >15ms precision on Windows 10 */
      __atomic_store_n (&GetSystemTimeAsFileTime_p, get_time, __ATOMIC_RELAXED);
    }

    get_time (&_now.ft);	/* 100 nano-seconds since 1-1-1601 */
    _now.ns100 -= FILETIME_1970;	/* 100 nano-seconds since 1-1-1970 */
    tp->tv_sec = _now.ns100 / HECTONANOSEC_PER_SEC;	/* seconds since 1-1-1970 */
    tp->tv_nsec = (long) (_now.ns100 % HECTONANOSEC_PER_SEC) * 100; /* nanoseconds */
  }
  return res;
}

int spvm_sys_windows_gettimeofday (struct timeval *p, SPVM_SYS_WINDOWS_TIMEZONE *z)
{
  struct timespec tp;

  if (getntptimeofday (&tp, z))
    return -1;
  p->tv_sec=tp.tv_sec;
  p->tv_usec=(tp.tv_nsec/1000);
  return 0;
}

int spvm_sys_windows_clock_gettime(int clk_id, struct timespec *ts) {
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

} // extern "C"

#endif // defined(_WIN32)
