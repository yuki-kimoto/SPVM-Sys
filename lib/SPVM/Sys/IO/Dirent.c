// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <dirent.h>

#undef MY_DIR
#undef MY_DIRENT

#undef MY_DIRENT

#if defined(_WIN32)
  #include "spvm_sys_windows.h"
  
  #define MY_DIRENT struct _wdirent
#else
  #define MY_DIRENT struct dirent
#endif

static const char* FILE_NAME = "Sys/IO/Dirent.c";

int32_t SPVM__Sys__IO__Dirent__d_ino(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dirent = stack[0].oval;
  
  MY_DIRENT* st_dirent = env->get_pointer(env, stack, obj_dirent);
  
  stack[0].ival = st_dirent->d_ino;
  
  return 0;
}

int32_t SPVM__Sys__IO__Dirent__d_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_dirent = stack[0].oval;
  
  MY_DIRENT* st_dirent = env->get_pointer(env, stack, obj_dirent);
  
#if defined(_WIN32)
  const WCHAR* d_name_w = st_dirent->d_name;
  const char* d_name = (char*)spvm_sys_windows_win_wchar_to_utf8(env, stack, (WCHAR*)d_name_w, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    return error_id;
  }
#else
  const char* d_name = st_dirent->d_name;
#endif
  
  int32_t d_name_length = strlen(d_name);
  
  void* obj_d_name = env->new_string(env, stack, d_name, d_name_length);
  
  stack[0].oval = obj_d_name;
  
  return 0;
}

int32_t SPVM__Sys__IO__Dirent__d_reclen(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(__CYGWIN__)
  env->die_v2(env, stack, "Sys::IO::Dirent#d_reclen method is not supported in this system(defined(__CYGWIN__)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  void* obj_dirent = stack[0].oval;
  
  MY_DIRENT* st_dirent = env->get_pointer(env, stack, obj_dirent);
  
  stack[0].ival = st_dirent->d_reclen;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Dirent__d_type(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die_v2(env, stack, "Sys::IO::Dirent#d_type method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  
  void* obj_dirent = stack[0].oval;
  
  MY_DIRENT* st_dirent = env->get_pointer(env, stack, obj_dirent);
  
  stack[0].ival = st_dirent->d_type;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__Dirent__d_off(SPVM_ENV* env, SPVM_VALUE* stack) {
#if defined(_WIN32)
  env->die_v2(env, stack, "Sys::IO::Dirent#d_off method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#elif defined(__CYGWIN__)
  env->die_v2(env, stack, "Sys::IO::Dirent#d_off method is not supported in this system(defined(__CYGWIN__)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#elif defined(__APPLE__)
  env->die_v2(env, stack, "Sys::IO::Dirent#d_off method is not supported in this system(defined(__APPLE__)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_dirent = stack[0].oval;
  
  MY_DIRENT* st_dirent = env->get_pointer(env, stack, obj_dirent);
  
  stack[0].lval = st_dirent->d_off;
  
  return 0;
#endif
}
