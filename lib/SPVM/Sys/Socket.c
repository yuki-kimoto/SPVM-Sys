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


int inet_pton(int af, const char *src, void *dst);

int32_t SPVM__Sys__Socket__inet_pton(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t address_family = stack[0].ival;
  
  void* obj_input_address = stack[1].oval;
  
  if (!obj_input_address) {
    return env->die(env, stack, "The address family must be defined", FILE_NAME, __LINE__);
  }
  
  const char* input_address = env->get_chars(env, stack, obj_input_address);
  
  void* obj_output_address = stack[2].oval;
  
  if (!obj_output_address) {
    return env->die(env, stack, "The output address must be defined", FILE_NAME, __LINE__);
  }
  
  void* output_address = env->get_pointer(env, stack, obj_output_address);
  
  int32_t success = inet_pton(address_family, input_address, output_address);
  
  if (success == -1) {
    env->die(env, stack, "[System Error]inet_pton failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = success;
  
  return 0;
}

int32_t SPVM__Sys__Socket__inet_aton(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_input_address = stack[0].oval;
  
  if (!obj_input_address) {
    return env->die(env, stack, "The input address address must be defined", FILE_NAME, __LINE__);
  }
  
  const char* input_address = env->get_chars(env, stack, obj_input_address);
  
  void* obj_output_address = stack[0].oval;
  
  if (!obj_output_address) {
    return env->die(env, stack, "The output address must be defined", FILE_NAME, __LINE__);
  }
  
  struct in_addr* output_address = env->get_pointer(env, stack, obj_output_address);
  
  int32_t success = inet_aton(input_address, output_address);
  
  stack[0].ival = success;
  
  return 0;
}

int32_t SPVM__Sys__Socket__inet_ntop(SPVM_ENV* env, SPVM_VALUE* stack) {

  // The address family
  int32_t address_family = stack[0].ival;
  
  // The input address
  void* obj_input_address = stack[1].oval;
  if (!obj_input_address) {
    return env->die(env, stack, "The output address must be defined", FILE_NAME, __LINE__);
  }
  void* input_address = env->get_pointer(env, stack, obj_input_address);
  
  // The output address
  void* obj_output_address = stack[2].oval;
  if (!obj_output_address) {
    return env->die(env, stack, "The output address must be defined", FILE_NAME, __LINE__);
  }
  char* output_address = (char*)env->get_chars(env, stack, obj_output_address);
  
  // The size of the output address
  int32_t size = stack[3].ival;
  
  const char* output_address_ret = inet_ntop(address_family, input_address, output_address, size);
  
  void* obj_output_address_ret = NULL;
  if (output_address_ret) {
    obj_output_address_ret = obj_output_address;
  }
  else {
    obj_output_address_ret = NULL;
    env->die(env, stack, "[System Error]inet_ntop failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].oval = obj_output_address_ret;
  
  return 0;
}

const char *inet_ntop(int af, const void *src,
                      char *dst, socklen_t size);
                      

int32_t SPVM__Sys__Socket__inet_ntoa(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_input_address = stack[0].oval;
  
  if (!obj_input_address) {
    return env->die(env, stack, "The input address must be defined", FILE_NAME, __LINE__);
  }
  
  struct in_addr* input_address = env->get_pointer(env, stack, obj_input_address);
  
  char* output_address = inet_ntoa(*input_address);
  
  void* obj_output_address;
  if (output_address) {
    obj_output_address = env->new_string(env, stack, output_address, strlen(output_address));
  }
  else {
    assert(0);
  }
  
  stack[0].oval = obj_output_address;
  
  return 0;
}

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
#ifdef _WIN32
  env->die(env, stack, "socketpair is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  int32_t domain = stack[0].ival;

  int32_t type = stack[1].ival;

  int32_t protocol = stack[2].ival;

  void* obj_pair = stack[3].oval;
  
  if (!obj_pair) {
    return env->die(env, stack, "The pair must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t* pair = env->get_elems_int(env, stack, obj_pair);
  int32_t pair_length = env->length(env, stack, obj_pair);
  
  if (!(pair_length >= 2)) {
    return env->die(env, stack, "The length of the pair must be greater than or equal to 2", FILE_NAME, __LINE__);
  }
  
  int int_pair[2];
  int32_t status = socketpair(domain, type, protocol, int_pair);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]socketpair failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  pair[0] = int_pair[0];
  pair[1] = int_pair[1];
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__Socket__setsockopt(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;

  int32_t level = stack[1].ival;

  int32_t optname = stack[2].ival;

  void* obj_optval = stack[3].oval;
  char* optval = NULL;
  if (!obj_optval) {
    return env->die(env, stack, "The option value must be defined", FILE_NAME, __LINE__);
  }
  optval = (char*)env->get_chars(env, stack, obj_optval);

  int32_t optlen = stack[4].ival;
  
  int32_t status = setsockopt(sockfd, level, optname, optval, optlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]setsockopt failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__Socket__setsockopt_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t int32_optval = stack[3].ival;
  
  int int_optval = int32_optval;
  
  int32_t optlen = sizeof(int);

  void* obj_optval = env->new_string(env, stack, NULL, optlen);
  char* optval = (char*)env->get_chars(env, stack, obj_optval);
  memcpy(optval, &int_optval, optlen);
  
  stack[3].oval = obj_optval;

  stack[4].ival = optlen;
  
  return SPVM__Sys__Socket__setsockopt(env, stack);
}

int32_t SPVM__Sys__Socket__getsockopt(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t sockfd = stack[0].ival;

  int32_t level = stack[1].ival;

  int32_t optname = stack[2].ival;
  
  // string[1]
  void* obj_optval_ref = stack[3].oval;
  if (!obj_optval_ref) {
    return env->die(env, stack, "The reference of the option value must be defined", FILE_NAME, __LINE__);
  }
  int32_t optval_ref_length = env->length(env, stack, obj_optval_ref);
  if (!(optval_ref_length >= 1)) {
    return env->die(env, stack, "The length of the reference of the option value must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  void* obj_optval = env->get_elem_object(env, stack, obj_optval_ref, 0);
  char* optval = (char*)env->get_chars(env, stack, obj_optval);

  int32_t* optlen_ref = stack[4].iref;
  
  int int_optlen = *optlen_ref;
  int32_t status = getsockopt(sockfd, level, optname, optval, &int_optlen);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]getsockopt failed: %s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  void* obj_got_optval = env->new_string(env, stack, optval, int_optlen);
  env->set_elem_object(env, stack, obj_optval_ref, 0, obj_got_optval);
  
  *optlen_ref = int_optlen;
  
  stack[0].ival = status;
  
  return 0;
}


int32_t SPVM__Sys__Socket__getsockopt_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t int32_optval = stack[3].ival;
  
  int int_optval = int32_optval;
  
  int32_t optlen = sizeof(int);
  
  void* obj_optval_ref = env->new_string_array(env, stack, 1);
  
  void* obj_optval = env->new_string(env, stack, NULL, optlen);
  char* optval = (char*)env->get_chars(env, stack, obj_optval);
  memcpy(optval, &int_optval, optlen);
  env->set_elem_object(env, stack, obj_optval_ref, 0, obj_optval);
  
  stack[3].oval = obj_optval_ref;
  
  stack[4].iref = &optlen;
  
  return SPVM__Sys__Socket__getsockopt(env, stack);
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

int32_t SPVM__Sys__Socket__sethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  env->die(env, stack, "sethostent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  sethostent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Socket__endhostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "endhostent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  errno = 0;
  endhostent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__gethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "gethostent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  errno = 0;
  struct hostent* hostent = gethostent();
  
  if (hostent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]gethostent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Hostent", hostent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}


int32_t SPVM__Sys__Socket__setnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  env->die(env, stack, "setnetent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  setnetent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Socket__endnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "endnetent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  errno = 0;
  endnetent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__getnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "getnetent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  errno = 0;
  struct netent* netent = getnetent();
  
  if (netent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getnetent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Netent", netent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__setservent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  env->die(env, stack, "setservent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  setservent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Socket__endservent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "endservent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  errno = 0;
  endservent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__getservent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "getservent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  errno = 0;
  struct servent* servent = getservent();
  
  if (servent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getservent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Hostent", servent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__setprotoent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  env->die(env, stack, "setprotoent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  setprotoent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Socket__endprotoent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "endprotoent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  errno = 0;
  endprotoent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Socket__getprotoent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  env->die(env, stack, "getprotoent is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  errno = 0;
  struct protoent* protoent = getprotoent();
  
  if (protoent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getprotoent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Hostent", protoent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}
