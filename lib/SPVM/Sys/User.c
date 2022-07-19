#include "spvm_native.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

int32_t SPVM__Sys__User__getuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t real_user_id = getuid();
  
  stack[0].ival = real_user_id;
  
  return 0;
}

int32_t SPVM__Sys__User__geteuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t effective_user_id = geteuid();
  
  stack[0].ival  = effective_user_id;
  
  return 0;
}

int32_t SPVM__Sys__User__getgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t real_group_id = getgid();
  
  stack[0].ival = real_group_id;

  return 0;
}

int32_t SPVM__Sys__User__getegid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t effective_group_id = getegid();
  
  stack[0].ival = effective_group_id;
  
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
