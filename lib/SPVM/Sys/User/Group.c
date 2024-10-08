// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#ifndef _WIN32

#include <grp.h>

#endif

static const char* FILE_NAME = "Sys/User/Group.c";

int32_t SPVM__Sys__User__Group__gr_name(SPVM_ENV* env, SPVM_VALUE* stack) {

#if defined(_WIN32)
  env->die(env, stack, "Sys::User::Group#gr_name method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].oval = env->new_string(env, stack, st_group->gr_name, strlen(st_group->gr_name));
  
  return 0;
#endif
}

int32_t SPVM__Sys__User__Group__gr_passwd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
#if defined(_WIN32)
  env->die(env, stack, "Sys::User::Group#gr_passwd method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].oval = env->new_string(env, stack, st_group->gr_passwd, strlen(st_group->gr_passwd));
  
  return 0;
#endif
}
int32_t SPVM__Sys__User__Group__gr_gid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
#if defined(_WIN32)
  env->die(env, stack, "Sys::User::Group#gr_gid method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].ival = st_group->gr_gid;
  
  return 0;
#endif
}

int32_t SPVM__Sys__User__Group__gr_mem(SPVM_ENV* env, SPVM_VALUE* stack) {
  
#if defined(_WIN32)
  env->die(env, stack, "Sys::User::Group#gr_mem method is not supported in this system(defined(_WIN32)).", __func__, FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS;
#else
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  char** gr_mems = st_group->gr_mem;
  
  char* gr_mem = (char*)gr_mems;
  
  int32_t gr_mem_length = 0;
  while (gr_mem) {
    gr_mem_length++;
    gr_mem++;
  }
  
  void* obj_gr_mems = env->new_string_array(env, stack, gr_mem_length);
  
  for (int32_t i = 0; i < gr_mem_length; i++) {
    char* gr_mem = gr_mems[i];
    void* obj_gr_mem = env->new_string(env, stack, gr_mem, strlen(gr_mem));
    env->set_elem_object(env, stack, obj_gr_mems, i, obj_gr_mem);
  }
  
  stack[0].oval = obj_gr_mems;
  
  return 0;
#endif
}
