#include "spvm_native.h"

#include <errno.h>

#ifdef _WIN32
  
#else
#include <netdb.h>
#endif

const char* FILE_NAME = "Sys/Net.c";

int32_t SPVM__Sys__Net__sethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  return env->die(env, stack, "sethostent is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  sethostent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Net__endhostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "endhostent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  endhostent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Net__gethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "gethostent is not supported in this system", FILE_NAME, __LINE__);
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


int32_t SPVM__Sys__Net__setnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  return env->die(env, stack, "setnetent is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t stayopen = stack[0].ival;
  errno = 0;
  setnetent(stayopen);
#endif

  return 0;
}


int32_t SPVM__Sys__Net__endnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "endnetent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  endnetent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__Net__getnetent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getnetent is not supported in this system", FILE_NAME, __LINE__);
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

