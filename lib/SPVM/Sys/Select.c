#include "spvm_native.h"

#ifdef _WIN32
# include <winsock2.h>
#else
# include <sys/select.h>
#endif

#include <errno.h>

const char* FILE_NAME = "Sys/Select.c";

int32_t SPVM__Sys__Select__select(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t fd = stack[0].ival;
  if (!(fd >= 0)) {
    return env->die(env, stack, "The $fd must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  if (!(fd < FD_SETSIZE)) {
    return env->die(env, stack, "The $fd must be less than FD_SETSIZE", FILE_NAME, __LINE__);
  }
  
  void* obj_readfds = stack[1].oval;
  fd_set* readfds = NULL;
  if (obj_readfds) {
    readfds = env->get_pointer(env, stack, obj_readfds);
  }
  
  void* obj_writefds = stack[2].oval;
  fd_set* writefds = NULL;
  if (obj_writefds) {
    writefds = env->get_pointer(env, stack, obj_writefds);
  }
  
  void* obj_exceptfds = stack[3].oval;
  fd_set* exceptfds = NULL;
  if (obj_exceptfds) {
    exceptfds = env->get_pointer(env, stack, obj_exceptfds);
  }
  
  void* obj_timeout = stack[4].oval;
  struct timeval* timeout = NULL;
  if (obj_timeout) {
    timeout = env->get_pointer(env, stack, obj_timeout);
  }
  
  int32_t updated_fds_count = select(fd, readfds, writefds, exceptfds, timeout);
  
  if (updated_fds_count == -1) {
    env->die(env, stack, "[System Error]select failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = updated_fds_count;
  
  return 0;
}
