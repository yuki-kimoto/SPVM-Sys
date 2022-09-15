#include "spvm_native.h"

#include <stdlib.h>

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
