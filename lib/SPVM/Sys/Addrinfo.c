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

static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_NEW = 1;
static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO = 2;

static const char* FILE_NAME = "Sys/Addrinfo.c";

int32_t SPVM__Sys__Addrinfo__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  struct addrinfo* addrinfo = env->new_memory_stack(env, stack, sizeof(struct addrinfo*));

  void* obj_addrinfo = env->new_pointer_by_name(env, stack, "Sys::Addrinfo", addrinfo, &e, FILE_NAME, __LINE__);
  env->set_pointer_any_info(env, stack, obj_addrinfo, (void*)(intptr_t)ADDRINFO_MEMORY_ALLOCATED_BY_NEW);
  
  return 0;
}

int32_t SPVM__Sys__Addrinfo__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Dir handle
  void* obj_addrinfo = stack[0].oval;
  if (obj_addrinfo != NULL) {
    struct addrinfo* addrinfo = env->get_pointer(env, stack, obj_addrinfo);
    if (addrinfo) {
      int32_t memory_allocated_way = (intptr_t)env->get_pointer_any_info(env, stack, obj_addrinfo);
      if (memory_allocated_way == ADDRINFO_MEMORY_ALLOCATED_BY_NEW) {
        env->free_memory_stack(env, stack, addrinfo);
      }
      else if (memory_allocated_way == ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO) {
        freeaddrinfo(addrinfo);
      }
      else {
        assert(0);
      }
      
      env->set_pointer(env, stack, obj_addrinfo, NULL);
    }
  }
  
  return 0;
}

