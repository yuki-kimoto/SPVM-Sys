#include "spvm_native.h"



int32_t SPVM__Sys__Hostent__sethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  return env->die(env, stack, "sethostent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  sethostent();
#endif

  return 0;
}


int32_t SPVM__Sys__Hostent__endhostent(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPVM__Sys__Hostent__gethostent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "gethostent is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  errno = 0;
  struct passwd* hostent = gethostent();
  
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
