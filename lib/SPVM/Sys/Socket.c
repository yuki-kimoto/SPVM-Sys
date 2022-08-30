#include "spvm_native.h"

#include <errno.h>
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

static const char* FILE_NAME = "Sys/Socket.c";

static int32_t FIELD_INDEX_ADDRINFO_MEMORY_ALLOCATED = 0;
static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_NEW = 1;
static int32_t ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO = 2;

int32_t SPVM__Sys__Socket__socket(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t socket_family = stack[0].ival;
  
  int32_t socket_type = stack[1].ival;
  
  int32_t protocol = stack[2].ival;
  
  int32_t sockfd = socket(socket_family, socket_type, protocol);
  
  if (sockfd == -1) {
    env->die(env, stack, "[System Error]socket failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = sockfd;
  
  return 0;
}

int32_t SPVM__Sys__Socket__connect(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  void* obj_addr = stack[1].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  const struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);
  
  int32_t addrlen = stack[2].ival;
  
  int32_t status = connect(sockfd, addr, addrlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]connect failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__bind(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  void* obj_addr = stack[1].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  const struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);
  
  int32_t addrlen = stack[2].ival;
  
  int32_t status = bind(sockfd, addr, addrlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]bind failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__listen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  int32_t backlog = stack[1].ival;
  
  int32_t status = listen(sockfd, backlog);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]listen failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__recv(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;

  void* obj_buf = stack[1].oval;
  
  if (!obj_buf) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buf = (char*)env->get_chars(env, stack, obj_buf);
  
  int32_t len = stack[2].ival;
  
  int32_t flags = stack[3].ival;
  
  int32_t bytes_length = recv(sockfd, buf, len, flags);
  
  if (bytes_length == -1) {
    env->die(env, stack, "[System Error]recv failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = bytes_length;
  
  return 0;
}

int32_t SPVM__Sys__Socket__send(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;

  void* obj_buf = stack[1].oval;
  
  if (!obj_buf) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  const char* buf = env->get_chars(env, stack, obj_buf);
  
  int32_t len = stack[2].ival;
  
  int32_t flags = stack[3].ival;
  
  int32_t bytes_length = send(sockfd, buf, len, flags);
  
  if (bytes_length == -1) {
    env->die(env, stack, "[System Error]send failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = bytes_length;
  
  return 0;
}

int32_t SPVM__Sys__Socket__socketpair(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t domain = stack[0].ival;

  int32_t type = stack[1].ival;

  int32_t protocol = stack[2].ival;

  void* obj_pair = stack[3].oval;
  
  if (!obj_pair) {
    return env->die(env, stack, "The output of the pair must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t* pair = env->get_elems_int(env, stack, obj_pair);
  int32_t pair_length = env->length(env, stack, obj_pair);
  
  if (!(pair_length >= 2)) {
    return env->die(env, stack, "The length of the output of the pair must be greater than or equal to 2", FILE_NAME, __LINE__);
  }
  
  assert(sizeof(int) == sizeof(int32_t));
  int32_t status = socketpair(domain, type, protocol, pair);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]socketpair failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__shutdown(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  int32_t how = stack[1].ival;
  
  int32_t status = shutdown(sockfd, how);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]shutdown failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__accept(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  void* obj_addr = stack[1].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);
  
  int32_t* addrlen_ref = stack[2].iref;
  
  socklen_t sl_addrlen = *addrlen_ref;
  
  int32_t status = accept(sockfd, addr, &sl_addrlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]accept failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  *addrlen_ref = sl_addrlen;
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__getpeername(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  void* obj_addr = stack[1].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);
  
  int32_t* addrlen_ref = stack[2].iref;
  
  socklen_t sl_addrlen = *addrlen_ref;
  
  int32_t status = getpeername(sockfd, addr, &sl_addrlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]getpeername failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  *addrlen_ref = sl_addrlen;
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__getsockname(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;
  
  void* obj_addr = stack[1].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);
  
  int32_t* addrlen_ref = stack[2].iref;
  
  socklen_t sl_addrlen = *addrlen_ref;
  
  int32_t status = getsockname(sockfd, addr, &sl_addrlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]getsockname failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  *addrlen_ref = sl_addrlen;
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__getaddrinfo(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e = 0;
  
  void* obj_node = stack[0].oval;
  
  const char* node = NULL;
  if (obj_node) {
    node = env->get_chars(env, stack, obj_node);
  }
  
  void* obj_service = stack[1].oval;
  
  const char* service = NULL;
  if (obj_service) {
    service = env->get_chars(env, stack, obj_service);
  }
  
  void* obj_hints = stack[2].oval;
  
  struct addrinfo *hints = NULL;
  if (obj_hints) {
    hints = env->get_pointer(env, stack, obj_hints);
  }
  
  void* obj_res_array = stack[3].oval;
  
  if (!obj_res_array) {
    return env->die(env, stack, "The response must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t res_length = env->length(env, stack, obj_res_array);
  
  if (res_length == 1) {
    return env->die(env, stack, "The length of the response must be 1", FILE_NAME, __LINE__);
  }
  
  struct addrinfo *res = NULL;
  int32_t status = getaddrinfo(node, service, hints, &res);
  
  if (status == 0) {
    int32_t fields_length = 1;
    void* obj_res = env->new_pointer_with_fields_by_name(env, stack, "Sys::Addrinfo", res, fields_length, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    env->set_pointer_field_int(env, stack, obj_res, FIELD_INDEX_ADDRINFO_MEMORY_ALLOCATED, ADDRINFO_MEMORY_ALLOCATED_BY_GETADDRINFO);
    env->set_elem_object(env, stack, obj_res_array, 0, obj_res);
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__getnameinfo(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e = 0;
  
  void* obj_addr = stack[0].oval;
  
  if (!obj_addr) {
    return env->die(env, stack, "The address must be defined", FILE_NAME, __LINE__);
  }
  
  const struct sockaddr* addr = env->get_pointer(env, stack, obj_addr);

  int32_t addrlen = stack[1].ival;
  
  void* obj_host = stack[2].oval;
  char* host = NULL;
  if (obj_host) {
    host = (char*)env->get_chars(env, stack, obj_host);
  }
  
  int32_t hostlen = stack[3].ival;
  
  void* obj_serv = stack[4].oval;
  char* serv = NULL;
  if (obj_serv) {
    serv = (char*)env->get_chars(env, stack, obj_serv);
  }
  
  int32_t servlen = stack[5].ival;

  int32_t flag = stack[6].ival;
  
  struct addrinfo *res = NULL;
  int32_t status = getnameinfo(addr, addrlen, host, hostlen, serv, servlen, flag);
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__gai_strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t gai_error_code = stack[0].ival;
  
  const char* ret_gai_strerror = gai_strerror(gai_error_code);
  
  if (ret_gai_strerror) {
    int32_t ret_gai_strerror_length = strlen(ret_gai_strerror);
    
    void* obj_gai_strerror = env->new_string(env, stack, ret_gai_strerror, ret_gai_strerror_length);
    stack[0].oval = obj_gai_strerror;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return 0;
}
