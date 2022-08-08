#include "spvm_native.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>

const char* FILE_NAME = "SPVM/Sys/IO.c";

int32_t SPVM__Sys__IO__rmdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The directory must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);
  int32_t status = rmdir(dir);
  if (!(status == 0)) {
    return env->die(env, stack, "[System Error]rmdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;

  if (!obj_file) {
    return env->die(env, stack, "The file must be defined", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  int32_t status = unlink(file);
  if (!(status == 0)) {
    return env->die(env, stack, "[System Error]unlink failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__close(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t fd = stack[0].ival;

  int32_t status = close(fd);
  if (!(status == 0)) {
    return env->die(env, stack, "[System Error]close failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
  }
  
  return 0;
}


