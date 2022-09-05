#include "spvm_native.h"

const char* FILE_NAME = "Sys/IO/Stat.c";

int32_t SPVM__Sys__Socket__Sockaddr__In__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  struct sockaddr_in* address = env->new_memory_stack(env, stack, sizeof(sockaddr_in));

  void* obj_address = env->new_pointer_by_name(env, stack, "Sys::Socket::Sockaddr::In", address, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_address = stack[0].oval;
  
  struct sockaddr_in* address = env->get_pointer(env, stack, obj_address);
  
  if (address) {
    env->free_memory_stack(env, stack, address);
    env->set_pointer(env, stack, obj_address, NULL);
  }
  
  return 0;
}
