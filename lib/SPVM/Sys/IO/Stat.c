// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#if defined(_WIN32)
  #include "spvm_sys_windows.h"
  typedef SPVM_SYS_WINDOWS_STAT MY_STAT;
#else
  #include <sys/stat.h>
  typedef struct stat MY_STAT;
#endif

#include <assert.h>
#include <errno.h>
#include <time.h>

#include "spvm_native.h"

static const char* FILE_NAME = "Sys/IO/Stat.c";

int32_t SPVM__Sys__IO__Stat__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  MY_STAT* st_stat = env->new_memory_block(env, stack, sizeof(MY_STAT));
  
  SPVM_OBJ* obj_stat = env->new_pointer_object_by_name(env, stack, "Sys::IO::Stat", st_stat, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_stat;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  assert(st_stat);
  
  env->free_memory_block(env, stack, st_stat);

  env->set_pointer(env, stack, obj_stat, NULL);
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__stat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_path = stack[0].oval;
  
  SPVM_OBJ* obj_stat = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat object $stat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
#if defined(_WIN32)
  stack[0].oval = obj_path;
  error_id = spvm_sys_windows_stat(env, stack, st_stat);
  int32_t status = error_id ? -1 : 0;
#else
  int32_t status = stat(path, st_stat);
#endif
  
  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]stat() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__lstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_path = stack[0].oval;
  
  SPVM_OBJ* obj_lstat = stack[1].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path $path must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  if (!obj_lstat) {
    return env->die(env, stack, "The stat object $lstat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_lstat);
  
#if defined(_WIN32)
  error_id = spvm_sys_windows_lstat(env, stack, path, st_stat);
  int32_t status = error_id ? -1 : 0;
#else
  int32_t status = lstat(path, st_stat);
#endif

  if (status == -1) {
    const char* path = env->get_chars(env, stack, obj_path);
    env->die(env, stack, "[System Error]lstat() failed(%d: %s). $path='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno), path);
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__fstat(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t fd = stack[0].ival;
  
  SPVM_OBJ* obj_stat = stack[1].oval;
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat object $stat must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  
#if defined(_WIN32)
  HANDLE handle = (HANDLE)_get_osfhandle(fd);
  int32_t status = spvm_sys_windows_fstat_by_handle(env, stack, handle, st_stat);
#else
  int32_t status = fstat(fd, st_stat);
#endif

  if (status == -1) {
    env->die(env, stack, "[System Error]fstat() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_dev(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_dev;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_ino(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_ino;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_mode;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_nlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_nlink;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_size(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_size;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_blksize(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_blksize method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_blksize;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::IO::Stat#st_blocks method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_blocks;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__st_uid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_uid;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_gid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].ival = st_stat->st_gid;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_rdev(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
  stack[0].lval = st_stat->st_rdev;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_atime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_atimespec.tv_sec;
#else
  stack[0].lval = st_stat->st_atime;
#endif

  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_mtimespec.tv_sec;
#else
  stack[0].lval = st_stat->st_mtime;
#endif
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_ctime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
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
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);

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
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
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
  SPVM_OBJ* obj_stat = stack[0].oval;
  
  MY_STAT* st_stat = env->get_pointer(env, stack, obj_stat);
  
#ifdef __APPLE__
  stack[0].lval = st_stat->st_ctimespec.tv_nsec;
#else
  stack[0].lval = st_stat->st_ctim.tv_nsec;
#endif
  
  return 0;
#endif
}

