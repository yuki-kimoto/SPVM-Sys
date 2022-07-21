#include "spvm_native.h"

#include <pwd.h>

static const char* FILE_NAME = "SPVM/Sys/Ent/Passwd.c";

int32_t SPVM__Sys__Ent__Passwd__pw_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].oval = env->new_string(env, stack, st_passwd->pw_name, strlen(st_passwd->pw_name));
  
  return 0;
}

int32_t SPVM__Sys__Ent__Passwd__pw_passwd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].oval = env->new_string(env, stack, st_passwd->pw_passwd, strlen(st_passwd->pw_passwd));
  
  return 0;
}
int32_t SPVM__Sys__Ent__Passwd__pw_uid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].ival = st_passwd->pw_uid;
  
  return 0;
}

int32_t SPVM__Sys__Ent__Passwd__pw_gid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].ival = st_passwd->pw_gid;
  
  return 0;
}

int32_t SPVM__Sys__Ent__Passwd__pw_gecos(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].oval = env->new_string(env, stack, st_passwd->pw_gecos, strlen(st_passwd->pw_gecos));
  
  return 0;
}

int32_t SPVM__Sys__Ent__Passwd__pw_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].oval = env->new_string(env, stack, st_passwd->pw_dir, strlen(st_passwd->pw_dir));
  
  return 0;
}

int32_t SPVM__Sys__Ent__Passwd__pw_shell(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_passwd = stack[0].oval;
  
  struct passwd* st_passwd = env->get_pointer(env, stack, obj_passwd);
  
  stack[0].oval = env->new_string(env, stack, st_passwd->pw_shell, strlen(st_passwd->pw_shell));
  
  return 0;
}
