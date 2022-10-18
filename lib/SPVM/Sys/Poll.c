#include "spvm_native.h"

#ifdef _WIN32
#  include <winsock2.h>
#else
#  include <poll.h>
#endif

#include <errno.h>

const char* FILE_NAME = "Sys/Poll.c";

int32_t SPVM__Sys__Poll__poll(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "The \"poll\" method in the class \"Sys::Poll\" is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  void* obj_fds = stack[0].oval;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_fds);
  
  int32_t nfds = stack[1].ival;
  
  int32_t timeout = stack[2].ival;
  
  int32_t ready_count = poll(fds, nfds, timeout);
  
  if (ready_count == -1) {
    env->die(env, stack, "[System Error]poll failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = ready_count;
  
  return 0;
#endif
}
