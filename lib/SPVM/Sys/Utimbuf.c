#include "spvm_native.h"

#include <utime.h>

static const char* FILE_NAME = "Sys/Utimbuf.c";

int32_t SPVM__Sys__Utimbuf__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  
  struct utimbuf* st_utimbuf = env->new_memory_stack(env, stack, sizeof(struct utimbuf));
  
  void* obj_utimbuf = env->new_pointer_by_name(env, stack, "Sys::Utimbuf", st_utimbuf, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_utimbuf;
  
  return 0;
}

int32_t SPVM__Sys__Utimbuf__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  // File handle
  void* obj_utimbuf = stack[0].oval;
  
  struct utimbuf* st_utimbuf = env->get_pointer(env, stack, obj_utimbuf);
  if (st_utimbuf) {
    env->free_memory_stack(env, stack, st_utimbuf);
    env->set_pointer(env, stack, obj_utimbuf, NULL);
  }
  
  return 0;
}
