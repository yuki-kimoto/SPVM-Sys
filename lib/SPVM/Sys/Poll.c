// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#if defined(_WIN32)
  #include "spvm_sys_windows.h"
  #include <winsock2.h>
#else
  #include <poll.h>
#endif

#include <errno.h>

#include "spvm_socket_util.h"
#include "spvm_native.h"

static const char* FILE_NAME = "Sys/Poll.c";

int32_t SPVM__Sys__Poll__poll(SPVM_ENV* env, SPVM_VALUE* stack) {
  SPVM_OBJ* obj_fds = stack[0].oval;
  
  int32_t nfds = stack[1].ival;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_fds);
  
  int32_t timeout = stack[2].ival;
  
#if defined(_WIN32)
  int32_t ready_count = WSAPoll(fds, nfds, timeout);
#else
  int32_t ready_count = poll(fds, nfds, timeout);
#endif

  if (ready_count == -1) {
    env->die(env, stack, "[System Error]poll() failed(%d: %s)", __func__, FILE_NAME, __LINE__, spvm_socket_errno(), spvm_socket_strerror(env, stack, spvm_socket_errno(), 0));
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  stack[0].ival = ready_count;
  
  return 0;
}
