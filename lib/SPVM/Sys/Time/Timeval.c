// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions on Linux and macOS
#define _XOPEN_SOURCE 700

// Enable BSD and System V extensions on Linux
#define _DEFAULT_SOURCE


#include "spvm_native.h"

#include <sys/time.h>
#include <assert.h>

static const char* FILE_NAME = "Sys/Time/Timeval.c";

int32_t SPVM__Sys__Time__Timeval__check(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Get arguments from stack
  int64_t tv_sec = stack[0].lval;
  int64_t tv_usec = stack[1].lval;

  // Validation:
  // tv_usec must be in the range [0, 999,999].
  if (!(tv_usec >= 0 && tv_usec <= 999999L)) {
    return env->die(env, stack, "The tv_usec must be greater than or equal to 0 and less than or equal to 999,999.", __func__, FILE_NAME, __LINE__);
  }

  return 0;
}

int32_t SPVM__Sys__Time__Timeval__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Call check before allocation
  error_id = SPVM__Sys__Time__Timeval__check(env, stack);
  if (error_id) { return error_id; }
  
  struct timeval* tv = env->new_memory_block(env, stack, sizeof(struct timeval));
  
  tv->tv_sec = stack[0].lval;
  
  tv->tv_usec = stack[1].lval;
  
  void* obj_tv = env->new_pointer_object_by_name(env, stack, "Sys::Time::Timeval", tv, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_tv;
  
  return 0;
}

int32_t SPVM__Sys__Time__Timeval__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tv = stack[0].oval;
  
  struct timeval* tv = env->get_pointer(env, stack, obj_tv);
  
  assert(tv);
  
  env->free_memory_block(env, stack, tv);
  
  return 0;
}

int32_t SPVM__Sys__Time__Timeval__tv_sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tv = stack[0].oval;
  
  struct timeval* tv = env->get_pointer(env, stack, obj_tv);
  
  stack[0].lval = tv->tv_sec;
  
  return 0;
}

int32_t SPVM__Sys__Time__Timeval__set_tv_sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tv = stack[0].oval;
  
  int64_t tv_sec = stack[1].lval;
  
  struct timeval* tv = env->get_pointer(env, stack, obj_tv);
  
  tv->tv_sec = tv_sec;
  
  return 0;
}

int32_t SPVM__Sys__Time__Timeval__tv_usec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tv = stack[0].oval;
  
  struct timeval* tv = env->get_pointer(env, stack, obj_tv);
  
  stack[0].lval = tv->tv_usec;
  
  return 0;
}

int32_t SPVM__Sys__Time__Timeval__set_tv_usec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tv = stack[0].oval;
  
  int64_t tv_usec = stack[1].lval;
  
  struct timeval* tv = env->get_pointer(env, stack, obj_tv);
  
  tv->tv_usec = tv_usec;
  
  return 0;
}
