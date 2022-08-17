#include "spvm_native.h"

#include <sys/types.h>
#include <unistd.h>

int32_t SPVM__Sys__Process__alarm(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t seconds = stack[0].ival;
  
  int32_t rest_time = alarm(seconds);
  
  stack[0].ival = rest_time;
  
  return 0;
}

int32_t SPVM__Sys__Process__fork(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t seconds = stack[0].ival;
  
  int32_t ret = fork();
  
  stack[0].ival = ret;
  
  return 0;
}
