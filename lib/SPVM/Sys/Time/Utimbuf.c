// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>
#include <utime.h>

static const char* FILE_NAME = "Sys/Time/Utimbuf.c";

int32_t SPVM__Sys__Time__Utimbuf__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  struct utimbuf* st_utimbuf = env->new_memory_block(env, stack, sizeof(struct utimbuf));
  
  void* obj_utimbuf = env->new_pointer_object_by_name(env, stack, "Sys::Time::Utimbuf", st_utimbuf, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_utimbuf;
  
  return 0;
}

int32_t SPVM__Sys__Time__Utimbuf__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // File handle
  void* obj_utimbuf = stack[0].oval;
  
  struct utimbuf* st_utimbuf = env->get_pointer(env, stack, obj_utimbuf);
  
  assert(st_utimbuf);
  
  env->free_memory_block(env, stack, st_utimbuf);
  env->set_pointer(env, stack, obj_utimbuf, NULL);
  
  return 0;
}

int32_t SPVM__Sys__Time__Utimbuf__actime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_utimbuf = stack[0].oval;
  
  struct utimbuf* st_buffer = env->get_pointer(env, stack, obj_utimbuf);
  
  stack[0].lval = st_buffer->actime;
  
  return 0;
}

int32_t SPVM__Sys__Time__Utimbuf__set_actime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_utimbuf = stack[0].oval;
  
  int64_t actime = stack[1].lval;
  
  struct utimbuf* st_buffer = env->get_pointer(env, stack, obj_utimbuf);
  
  st_buffer->actime = actime;
  
  return 0;
}

int32_t SPVM__Sys__Time__Utimbuf__modtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_utimbuf = stack[0].oval;
  
  struct utimbuf* st_buffer = env->get_pointer(env, stack, obj_utimbuf);
  
  stack[0].lval = st_buffer->modtime;
  
  return 0;
}

int32_t SPVM__Sys__Time__Utimbuf__set_modtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_utimbuf = stack[0].oval;
  
  int64_t modtime = stack[1].lval;
  
  struct utimbuf* st_buffer = env->get_pointer(env, stack, obj_utimbuf);
  
  st_buffer->modtime = modtime;
  
  return 0;
}
