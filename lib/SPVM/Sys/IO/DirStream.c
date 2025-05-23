// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#undef MY_DIR
#if defined(_WIN32)
  #define MY_DIR _WDIR
#else
  #define MY_DIR DIR
#endif

static const char* FILE_NAME = "Sys/IO/DirStream.c";

int32_t SPVM__Sys__IO__DirStream__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t closed = env->get_field_byte_by_name(env, stack, obj_self, "closed", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  MY_DIR* dir_stream = (MY_DIR*)env->get_pointer(env, stack, obj_self);
  
  assert(dir_stream);
  
  if (!closed) {
#if defined(_WIN32)
    int32_t status = _wclosedir(dir_stream);
#else
    int32_t status = closedir(dir_stream);
#endif

    if (status == -1) {
      env->die(env, stack, "[System Error]closedir() failed:%s.", env->strerror_nolen(env, stack, errno), __func__, FILE_NAME, __LINE__);
      return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    }
    env->set_pointer(env, stack, obj_self, NULL);
  }
  
  return 0;
}
