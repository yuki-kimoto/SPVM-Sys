#include "spvm_native.h"

#include <stdlib.h>
#include <errno.h>

static const char* FILE_NAME = "Sys.c";

int32_t SPVM__Sys__is_D_WIN32(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t ok;
  
#ifdef _WIN32
  ok = 1;
#else
  ok = 0;
#endif
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__Sys__defined(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* obj_macro_name = stack[0].oval;
  
  if (!obj_macro_name) {
    return env->die(env, stack, "The $macro_name must be defined", FILE_NAME, __LINE__);
  }

  const char* macro_name = env->get_chars(env, stack, obj_macro_name);
  
  int32_t defined = 0;
  if (strcmp(macro_name, "__GNUC__") == 0) {
#   ifdef __GNUC__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__clang__") == 0) {
#   ifdef __clang__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_MSC_VER") == 0) {
#   ifdef _MSC_VER
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__BORLANDC__") == 0) {
#   ifdef __BORLANDC__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__INTEL_COMPILER") == 0) {
#   ifdef __INTEL_COMPILER
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__unix") == 0) {
#   ifdef __unix
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__unix__") == 0) {
#   ifdef __unix__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__linux") == 0) {
#   ifdef __linux
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__linux__") == 0) {
#   ifdef __linux__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__FreeBSD__") == 0) {
#   ifdef __FreeBSD__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__NetBSD__") == 0) {
#   ifdef __NetBSD__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_WIN32") == 0) {
#   ifdef _WIN32
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "WIN32") == 0) {
#   ifdef WIN32
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_WIN64") == 0) {
#   ifdef _WIN64
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_WINDOWS") == 0) {
#   ifdef _WINDOWS
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_CONSOLE") == 0) {
#   ifdef _CONSOLE
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "WINVER") == 0) {
#   ifdef WINVER
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_WIN32_WINDOWS") == 0) {
#   ifdef _WIN32_WINDOWS
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "_WIN32_WINNT") == 0) {
#   ifdef _WIN32_WINNT
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "WINCEOSVER") == 0) {
#   ifdef WINCEOSVER
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__CYGWIN__") == 0) {
#   ifdef __CYGWIN__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__CYGWIN32__") == 0) {
#   ifdef __CYGWIN32__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__MINGW32__") == 0) {
#   ifdef __MINGW32__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__MINGW64__") == 0) {
#   ifdef __MINGW64__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__APPLE__") == 0) {
#   ifdef __APPLE__
      defined = 1;
#   endif
  }
  else if (strcmp(macro_name, "__MACH__") == 0) {
#   ifdef __MACH__
      defined = 1;
#   endif
  }
  else {
    return env->die(env, stack, "The macro name \"%s\" is not supported yet", macro_name, FILE_NAME, __LINE__);
  }
  
  stack[0].ival = defined;
  
  return 0;
}

int32_t SPVM__Sys__getenv(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* obj_name = stack[0].oval;
  
  if (!obj_name) {
    return env->die(env, stack, "The name must be defined", FILE_NAME, __LINE__);
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

int32_t SPVM__Sys__setenv(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "setenv is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  void* obj_name = stack[0].oval;
  if (!obj_name) {
    return env->die(env, stack, "The name must be defined", FILE_NAME, __LINE__);
  }
  const char* name = env->get_chars(env, stack, obj_name);

  void* obj_value = stack[1].oval;
  if (!obj_value) {
    return env->die(env, stack, "The value must be defined", FILE_NAME, __LINE__);
  }
  const char* value = env->get_chars(env, stack, obj_value);
  
  int32_t overwrite = stack[2].ival;
  
  int32_t status = setenv(name, value, overwrite);

  if (status == -1) {
    env->die(env, stack, "[System Error]setenv failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__unsetenv(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "unsetenv is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  void* obj_name = stack[0].oval;
  if (!obj_name) {
    return env->die(env, stack, "The name must be defined", FILE_NAME, __LINE__);
  }
  const char* name = env->get_chars(env, stack, obj_name);

  int32_t status = unsetenv(name);

  if (status == -1) {
    env->die(env, stack, "[System Error]unsetenv failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}
