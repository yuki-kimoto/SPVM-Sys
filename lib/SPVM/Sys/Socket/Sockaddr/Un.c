#include "spvm_native.h"

#include <assert.h>

#ifdef _WIN32
# include <ws2tcpip.h>
# include <io.h>
#else
#include <sys/socket.h>
#include <sys/un.h>
#endif

const char* FILE_NAME = "Sys/Socket/Sockaddr/Un.c";

int32_t SPVM__Sys__Socket__Sockaddr__Un__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  struct sockaddr_un* socket_address = env->new_memory_stack(env, stack, sizeof(struct sockaddr_un));

  void* obj_socket_address = env->new_pointer_by_name(env, stack, "Sys::Socket::Sockaddr::Un", socket_address, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_socket_address;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__Un__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_socket_address = stack[0].oval;
  
  struct sockaddr_un* socket_address = env->get_pointer(env, stack, obj_socket_address);
  
  if (socket_address) {
    env->free_memory_stack(env, stack, socket_address);
    env->set_pointer(env, stack, obj_socket_address, NULL);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__Un__sun_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct sockaddr_un* socket_address = env->get_pointer(env, stack, obj_self);
  
  if (socket_address) {
    stack[0].ival = socket_address->sun_family;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__Un__set_sun_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct sockaddr_un* socket_address = env->get_pointer(env, stack, obj_self);
  
  if (socket_address) {
    socket_address->sun_family = stack[1].ival;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__Un__sun_path(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct sockaddr_un* socket_address = env->get_pointer(env, stack, obj_self);
  
  if (socket_address) {
    void* obj_path;
    if (socket_address->sun_path) {
      obj_path = env->new_string(env, stack, socket_address->sun_path, strlen(socket_address->sun_path));
    }
    else {
      obj_path = NULL;
    };
    
    stack[0].oval = obj_path;
  }
  else {
    assert(0);
  }
  
  return 0;
}

int32_t SPVM__Sys__Socket__Sockaddr__Un__set_sun_path(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct sockaddr_un* socket_address = env->get_pointer(env, stack, obj_self);
  
  if (socket_address) {
    void* obj_path = stack[1].oval;
    
    const char* path = env->get_chars(env, stack, obj_path);
    int32_t path_length = env->length(env, stack, obj_path);
    
    if (!(path_length <= 91)) {
      return env->die(env, stack, "The length of the path must be less than or equal to 91", FILE_NAME, __LINE__);
    }
    
    memset(socket_address->sun_path, 0, strlen(socket_address->sun_path));
    memcpy(socket_address->sun_path, path, path_length);
  }
  else {
    assert(0);
  }
  
  return 0;
}
