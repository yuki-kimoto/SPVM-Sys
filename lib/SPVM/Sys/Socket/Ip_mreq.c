#include "spvm_native.h"

#include <assert.h>

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

const char* FILE_NAME = "Sys/Socket/Ip_mreq.c";

int32_t SPVM__Sys__Socket__Ip_mreq__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__imr_multiaddr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  struct ip_mreq* multi_request = env->get_pointer(env, stack, obj_self);
  
  if (multi_request) {
    struct in_addr address = multi_request->imr_multiaddr;

    struct in_addr* address_ret = env->new_memory_stack(env, stack, sizeof(struct in_addr));
    *address_ret = address;

    void* obj_address_ret = env->new_pointer_by_name(env, stack, "Sys::Socket::In_addr", address_ret, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    
    stack[0].oval = obj_address_ret;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__set_imr_multiaddr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct ip_mreq* multi_request = env->get_pointer(env, stack, obj_self);
  
  if (multi_request) {
    void* obj_address = stack[1].oval;
    struct in_addr* address = env->get_pointer(env, stack, obj_address);

    multi_request->imr_multiaddr = *address;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__imr_interface(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  struct ip_mreq* multi_request = env->get_pointer(env, stack, obj_self);
  
  if (multi_request) {
    struct in_addr address = multi_request->imr_interface;

    struct in_addr* address_ret = env->new_memory_stack(env, stack, sizeof(struct in_addr));
    *address_ret = address;

    void* obj_address_ret = env->new_pointer_by_name(env, stack, "Sys::Socket::In_addr", address_ret, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    
    stack[0].oval = obj_address_ret;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__In__set_imr_interface(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct ip_mreq* multi_request = env->get_pointer(env, stack, obj_self);
  
  if (multi_request) {
    void* obj_address = stack[1].oval;
    struct in_addr* address = env->get_pointer(env, stack, obj_address);

    multi_request->imr_interface = *address;
  }
  else {
    assert(0);
  }
  
  return 0;
}
