#include "spvm_native.h"

#ifdef _WIN32
# include <ws2tcpip.h>
# include <io.h>
#else
# include <sys/fcntl.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>
# define closesocket(fd) close(fd)
#endif

const char* FILE_NAME = "Sys/Socket/In_addr.c";

int32_t SPVM__Sys__Socket__In_addr__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  struct in_addr* address = env->new_memory_stack(env, stack, sizeof(struct in_addr));

  void* obj_address = env->new_pointer_by_name(env, stack, "Sys::Socket::In_addr", address, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Sys__Socket__In_addr__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_address = stack[0].oval;
  
  struct in_addr* address = env->get_pointer(env, stack, obj_address);
  
  if (address) {
    env->free_memory_stack(env, stack, address);
    env->set_pointer(env, stack, obj_address, NULL);
  }
  
  return 0;
}
