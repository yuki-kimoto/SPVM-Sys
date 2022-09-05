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

const char* FILE_NAME = "Sys/Socket/Sockaddr/In.c";

int32_t SPVM__Sys__Socket__Sockaddr__In__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  struct sockaddr_in* socket_address = env->new_memory_stack(env, stack, sizeof(struct sockaddr_in));

  void* obj_socket_address = env->new_pointer_by_name(env, stack, "Sys::Socket::Sockaddr::In", socket_address, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_socket_address;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_socket_address = stack[0].oval;
  
  struct sockaddr_in* socket_address = env->get_pointer(env, stack, obj_socket_address);
  
  if (socket_address) {
    env->free_memory_stack(env, stack, socket_address);
    env->set_pointer(env, stack, obj_socket_address, NULL);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__sin_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct sockaddr_in* socket_address = env->get_pointer(env, stack, obj_self);
  
  if (socket_address) {
    stack[0].ival = socket_address->sin_family;
  }
  else {
    assert(0);
  }
  
  return 0;
}
