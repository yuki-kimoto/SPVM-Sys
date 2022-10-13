#include "spvm_native.h"

#include <sys/time.h>
#include <errno.h>

static const char* FILE_NAME = "Sys/Time.c";

int32_t SPVM__Sys__Time__gettimeofday(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_tv = stack[0].oval;
  
  struct timeval* st_tv = NULL;
  if (obj_tv) {
    st_tv = env->get_pointer(env, stack, obj_tv);
  }
  
  void* obj_tz = stack[1].oval;
  
  struct timezone* st_tz = NULL;
  if (obj_tz) {
    st_tz = env->get_pointer(env, stack, obj_tz);
  }
  
  int32_t status = gettimeofday(st_tv, st_tz);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]gettimeofday failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Time__timersub(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_a = stack[0].oval;
  struct timeval* st_a = NULL;
  if (obj_a) {
    st_a = env->get_pointer(env, stack, obj_a);
  }
  else {
    return env->die(env, stack, "The a must be defined", FILE_NAME, __LINE__);
  }

  void* obj_b = stack[1].oval;
  struct timeval* st_b = NULL;
  if (obj_b) {
    st_b = env->get_pointer(env, stack, obj_b);
  }
  else {
    return env->die(env, stack, "The b must be defined", FILE_NAME, __LINE__);
  }
  
  void* obj_res = stack[2].oval;
  struct timeval* st_res = NULL;
  if (obj_res) {
    st_res = env->get_pointer(env, stack, obj_res);
  }
  else {
    return env->die(env, stack, "The res must be defined", FILE_NAME, __LINE__);
  }
  
  timersub(st_a, st_b, st_res);
  
  return 0;
}
