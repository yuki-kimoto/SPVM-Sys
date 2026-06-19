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
  typedef SPVM_SYS_WINDOWS_DIR MY_DIR;
#else
  #include <dirent.h>
  typedef DIR MY_DIR;
#endif

#include <assert.h>
#include <stdio.h>
#include <errno.h>

#include "spvm_native.h"

static const char* FILE_NAME = "Sys/IO/DirStream.c";

int32_t SPVM__Sys__IO__DirStream__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  SPVM_OBJ* obj_self = stack[0].oval;
  
  int32_t closed = env->get_field_byte_by_name(env, stack, obj_self, "closed", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  MY_DIR* dir_stream = (MY_DIR*)env->get_pointer(env, stack, obj_self);
  
  assert(dir_stream);
  
  if (!closed) {
#if defined(_WIN32)
    env->push_caller_stack(env, stack, __func__, FILE_NAME, __LINE__ + 1);
    int32_t status = spvm_sys_windows_closedir(env, stack, dir_stream);
    env->pop_caller_stack(env, stack);
    
    if (status == -1) {
      return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    }
#else
    int32_t status = closedir(dir_stream);
    if (status == -1) {
      env->die(env, stack, "[System Error]closedir() failed. errno=%d(%s).", __func__, FILE_NAME, __LINE__, errno, env->strerror_nolen(env, stack, errno));
      return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    }
#endif

    env->set_pointer(env, stack, obj_self, NULL);
  }
  
  return 0;
}
