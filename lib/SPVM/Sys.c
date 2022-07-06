#include "spvm_native.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

const char* FILE_NAME = "SPVM/Sys.c";

int32_t SPVM__Sys__rmdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  int32_t count = 0;
  if (obj_file) {
    const char* file = env->get_chars(env, stack, obj_file);
    int32_t error_code = rmdir(file);
    if (error_code == 0) {
      count++;
    }
  }
  
  stack[0].ival = count;
  
  return 0;
}

int32_t SPVM__Sys__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  int32_t count = 0;
  if (obj_file) {
    const char* file = env->get_chars(env, stack, obj_file);
    int32_t error_code = unlink(file);
    if (error_code == 0) {
      count++;
    }
  }
  
  stack[0].ival = count;
  
  return 0;
}
