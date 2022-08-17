#include "spvm_native.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <signal.h>

const char* FILE_NAME = "Sys/Process.c";

int32_t SPVM__Sys__Process__alarm(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t seconds = stack[0].ival;
  
  int32_t rest_time = alarm(seconds);
  
  stack[0].ival = rest_time;
  
  return 0;
}

int32_t SPVM__Sys__Process__fork(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t seconds = stack[0].ival;
  
  int32_t status = fork();
  
  if (status == -1) {
    env->die(env, stack, "[System Error]fork failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status ;
  
  return 0;
}

int32_t SPVM__Sys__Process__getpriority(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t which = stack[0].ival;
  int32_t who = stack[1].ival;
  
  errno = 0;
  int32_t nice = getpriority(which, who);
  if (errno != 0) {
    env->die(env, stack, "[System Error]getpriority failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = nice;
  
  return 0;
}

int32_t SPVM__Sys__Process__setpriority(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t which = stack[0].ival;
  int32_t who = stack[1].ival;
  int32_t prio = stack[2].ival;
  
  int32_t status = setpriority(which, who, prio);
  if (status == -1) {
    env->die(env, stack, "[System Error]setpriority failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Process__sleep(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t seconds = stack[0].ival;
  
  int32_t rest_time = sleep(seconds);
  
  stack[0].ival = rest_time;
  
  return 0;
}

int32_t SPVM__Sys__Process__kill(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t pid = stack[0].ival;
  int32_t sig = stack[1].ival;
  
  int32_t status = kill(pid, sig);
  if (status == -1) {
    env->die(env, stack, "[System Error]kill failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}
