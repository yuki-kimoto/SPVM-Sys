#include "spvm_native.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int32_t SPVM__Sys__User__getuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t uid = getuid();
  
  stack[0].ival = uid;
  
  return 0;
}

int32_t SPVM__Sys__User__geteuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t euid = geteuid();
  
  stack[0].ival  = euid;
  
  return 0;
}

int32_t SPVM__Sys__User__getgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t gid = getgid();
  
  stack[0].ival = gid;

  return 0;
}

int32_t SPVM__Sys__User__getegid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t egid = getegid();
  
  stack[0].ival = egid;
  
  return 0;
}

int32_t SPVM__Sys__User__setuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t uid = stack[0].ival;
  int32_t error_code = setuid(uid);
  
  stack[0].ival = error_code;
  
  return 0;
}

int32_t SPVM__Sys__User__seteuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t euid = stack[0].ival;
  int32_t error_code = seteuid(euid);
  
  stack[0].ival = error_code;
  
  return 0;
}

int32_t SPVM__Sys__User__setgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t gid = stack[0].ival;
  int32_t error_code = setgid(gid);
  
  stack[0].ival = error_code;

  return 0;
}

int32_t SPVM__Sys__User__setegid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t egid = stack[0].ival;
  int32_t error_code = setegid(egid);
  
  stack[0].ival = error_code;
  
  return 0;
}

int32_t SPVM__Sys__User__endgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getgrgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getgrnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getlogin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getpwnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getpwuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__setgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__setpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}
