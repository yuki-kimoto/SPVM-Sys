#include "spvm_native.h"

#include <assert.h>

#ifdef _WIN32
# include <ws2tcpip.h>
# include <winsock2.h>
# include <io.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif

static int32_t FIELD_INDEX_ADDRINFO_MEMORY_ALLOCATED = 0;

static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_NEW = 1;
static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO = 2;

static const char* FILE_NAME = "Sys/Socket/Addrinfo.c";

int32_t SPVM__Sys__Socket__Addrinfo__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  struct addrinfo* addrinfo = env->new_memory_stack(env, stack, sizeof(struct addrinfo*));

  int32_t fields_length = 1;
  void* obj_addrinfo = env->new_pointer_with_fields_by_name(env, stack, "Sys::Socket::Addrinfo", addrinfo, fields_length, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  env->set_pointer_field_int(env, stack, obj_addrinfo, FIELD_INDEX_ADDRINFO_MEMORY_ALLOCATED, ADDRINFO_MEMORY_ALLOCATED_BY_NEW);
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* obj_addrinfo = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_addrinfo);
  
  assert(st_addrinfo);
  
  int32_t memory_allocated_way = (intptr_t)env->get_pointer_field_int(env, stack, obj_addrinfo, FIELD_INDEX_ADDRINFO_MEMORY_ALLOCATED);
  if (memory_allocated_way == ADDRINFO_MEMORY_ALLOCATED_BY_NEW) {
    env->free_memory_stack(env, stack, st_addrinfo);
  }
  else if (memory_allocated_way == ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO) {
    // freeaddrinfo(st_addrinfo);
  }
  else {
    assert(0);
  }
  
  env->set_pointer(env, stack, obj_addrinfo, NULL);
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__ai_flags(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  stack[0].ival = st_addrinfo->ai_flags;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__set_ai_flags(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  st_addrinfo->ai_flags = stack[1].ival;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__ai_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  stack[0].ival = st_addrinfo->ai_family;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__set_ai_family(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  st_addrinfo->ai_family = stack[1].ival;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__ai_socktype(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  stack[0].ival = st_addrinfo->ai_socktype;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__set_ai_socktype(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  st_addrinfo->ai_socktype = stack[1].ival;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__ai_protocol(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  stack[0].ival = st_addrinfo->ai_protocol;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__set_ai_protocol(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  st_addrinfo->ai_protocol = stack[1].ival;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__ai_addrlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  stack[0].ival = (int32_t)st_addrinfo->ai_addrlen;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__set_ai_addrlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  st_addrinfo->ai_addrlen = (socklen_t)stack[1].ival;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__copy_ai_addr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  struct sockaddr* ai_addr = st_addrinfo->ai_addr;
  
  void* obj_ai_addr_clone = NULL;
  if (ai_addr) {
    void* obj_ai_addr = env->new_pointer_by_name(env, stack, "Sys::Socket::Sockaddr", ai_addr, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    
    // Calls the clone method.
    {
      stack[0].oval = obj_ai_addr;
      int32_t args_stack_length = 1;
      e = env->call_instance_method_by_name(env, stack, obj_ai_addr, "clone", args_stack_length, FILE_NAME, __LINE__);
      if (e) { return e; };
      obj_ai_addr_clone = stack[0].oval;
    }
  }
  
  stack[0].oval = obj_ai_addr_clone;
  
  return 0;
}

int32_t SPVM__Sys__Socket__Addrinfo__copy_ai_canonname(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct addrinfo* st_addrinfo = env->get_pointer(env, stack, obj_self);
  
  char* ai_canonname = st_addrinfo->ai_canonname;
  
  void* obj_ai_canonname = NULL;
  if (ai_canonname) {
    obj_ai_canonname = env->new_string(env, stack, ai_canonname, strlen(ai_canonname));
  }
  
  stack[0].oval = obj_ai_canonname;
  
  return 0;
}
