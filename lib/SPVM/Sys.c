#include "spvm_native.h"

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

int32_t SPVM__Sys__is_D_WIN64(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t ok;
  
#ifdef _WIN64
  ok = 1;
#else
  ok = 0;
#endif
  
  stack[0].ival = ok;
  
  return 0;
}
