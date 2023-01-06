#include "spvm_native.h"

#include <assert.h>
#include <stdio.h>
#include <errno.h>

const char* FILE_NAME = "Sys/IO/FileStream.c";

int32_t SPVM__Sys__IO__FileStream__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  // File handle
  void* obj_self = stack[0].oval;
  
  int32_t closed = env->get_field_int_by_name(env, stack, obj_self, "closed", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  FILE* fh = (FILE*)env->get_pointer(env, stack, obj_self);
  
  assert(fh);
  
  if (!env->get_pointer_no_need_free(env, stack, obj_self)) {
    if (!closed) {
      int32_t status = fclose(fh);
      if (status == EOF) {
        env->die(env, stack, "[System Error]fclose failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
        return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
      }
      env->set_pointer(env, stack, obj_self, NULL);
    }
  }
  
  return 0;
}
