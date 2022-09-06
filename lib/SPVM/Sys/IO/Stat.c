#include "spvm_native.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

const char* FILE_NAME = "Sys/IO/Stat.c";

int32_t SPVM__Sys__IO__Stat__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  struct stat* stat = env->new_memory_stack(env, stack, sizeof(struct stat));

  void* obj_stat = env->new_pointer_by_name(env, stack, "Sys::IO::Stat", stat, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_stat;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__stat(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_stat = stack[1].oval;
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat must be defined", FILE_NAME, __LINE__);
  }
  
  struct stat* stat_buf = env->get_pointer(env, stack, obj_stat);
  
  int32_t status = stat(path, stat_buf);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]stat failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__lstat(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  return env->die(env, stack, "lstat is not supported in this system", FILE_NAME, __LINE__);
#else

  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_lstat = stack[0].oval;
  
  if (!obj_lstat) {
    return env->die(env, stack, "The lstat must be defined", FILE_NAME, __LINE__);
  }
  
  struct stat* stat_buf = env->get_pointer(env, stack, obj_lstat);
  
  int32_t status = lstat(path, stat_buf);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]lstat failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Stat__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    env->free_memory_stack(env, stack, stat);
    env->set_pointer(env, stack, obj_stat, NULL);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mode(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].ival = stat->st_mode;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_size(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].lval = stat->st_size;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_mtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].lval = stat->st_mtime;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_atime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].lval = stat->st_atime;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_ctime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].lval = stat->st_ctime;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__Stat__st_uid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stat = stack[0].oval;
  
  struct stat* stat = env->get_pointer(env, stack, obj_stat);
  
  if (stat) {
    stack[0].lval = stat->st_uid;
  }
  else {
    assert(0);
  }
  
  return 0;
}
