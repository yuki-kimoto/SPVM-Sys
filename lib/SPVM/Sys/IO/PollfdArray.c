#include "spvm_native.h"

#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <poll.h>
#endif

const char* FILE_NAME = "Sys/IO/PollfdArray";

int32_t SPVM__Sys__IO__PollfdArray__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t length = stack[0].ival;
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  struct pollfd* fds = env->new_memory_stack(env, stack, sizeof(struct pollfd) * length);
  
  int32_t fields_length = 1;
  void* obj_fds = env->new_pointer_with_fields_by_name(env, stack, "Sys::IO::PollfdArray", fds, fields_length, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_pointer_field_int(env, stack, obj_fds, 0, length);
  
  stack[0].oval = obj_fds;
  
  return 0;
}

int32_t SPVM__Sys__IO__PollfdArray__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_fds = stack[0].oval;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_fds);
  
  if (fds) {
    env->free_memory_stack(env, stack, fds);
    env->set_pointer(env, stack, obj_fds, NULL);
  }
  
  return 0;
}
