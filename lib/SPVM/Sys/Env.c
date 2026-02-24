// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
#define _XOPEN_SOURCE 700

#include "spvm_native.h"

#include <stdlib.h>
#include <errno.h>

static const char* FILE_NAME = "Sys/Env.c";

int32_t SPVM__Sys__Env__getenv(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* obj_name = stack[0].oval;
  
  if (!obj_name) {
    return env->die(env, stack, "The environment variable name $name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* name = env->get_chars(env, stack, obj_name);
  
  char* value = getenv(name);
  
  void* obj_value;
  if (value) {
    obj_value = env->new_string(env, stack, value, strlen(value));
  }
  else {
    obj_value = NULL;
  }
  
  stack[0].oval = obj_value;
  
  return 0;
}

int32_t SPVM__Sys__Env__setenv(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::Env#setenv method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_name = stack[0].oval;
  
  void* obj_value = stack[1].oval;
  
  if (!obj_name) {
    return env->die(env, stack, "The environment variable name $name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* name = env->get_chars(env, stack, obj_name);
  
  if (!obj_value) {
    return env->die(env, stack, "The environment variable value $value must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* value = env->get_chars(env, stack, obj_value);
  
  int32_t overwrite = stack[2].ival;
  
  // Required: _XOPEN_SOURCE 700 on Linux and macOS
  int32_t status = setenv(name, value, overwrite);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]setenv() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__Env__unsetenv(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die(env, stack, "Sys::Env#unsetenv method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_name = stack[0].oval;
  if (!obj_name) {
    return env->die(env, stack, "The environment variable name $name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* name = env->get_chars(env, stack, obj_name);
  
  // Required: _XOPEN_SOURCE 700 on Linux and macOS
  int32_t status = unsetenv(name);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]unsetenv() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__Env___putenv_s(SPVM_ENV* env, SPVM_VALUE* stack) {
#if !defined(_WIN32)
  env->die(env, stack, "Sys::Env#_putenv_s method is not supported in this system(!defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_name = stack[0].oval;
  
  void* obj_value = stack[1].oval;
  
  if (!obj_name) {
    return env->die(env, stack, "The environment variable name $name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* name = env->get_chars(env, stack, obj_name);
  
  if (!obj_value) {
    return env->die(env, stack, "The environment variable value $value must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* value = env->get_chars(env, stack, obj_value);
  
  int32_t status = _putenv_s(name, value);
  
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]_putenv_s() failed(%d: %s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}
