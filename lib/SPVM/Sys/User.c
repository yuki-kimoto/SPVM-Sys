#include "spvm_native.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

const char* FILE_NAME = "SPVM/Sys/User.c";

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

int32_t SPVM__Sys__User__setpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  setpwent();
  
  return 0;
}


int32_t SPVM__Sys__User__endpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  endpwent();
  
  return 0;
}

int32_t SPVM__Sys__User__setgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  setgrent();
  
  return 0;
}

int32_t SPVM__Sys__User__endgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  endgrent();
  
  return 0;
}

int32_t SPVM__Sys__User__getgroups(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t error_system_class_id = env->get_class_id(env, "Error::System");
  assert(error_system_class_id >= 2);
  
  int32_t groups_length = getgroups(0, NULL);
  if (groups_length < 0) {
    env->die(env, stack, "getgroups fails:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  void* obj_groups = env->new_int_array(env, stack, groups_length);
  int32_t* groups = env->get_elems_int(env, stack, obj_groups);
  
  assert(sizeof(gid_t) == sizeof(int32_t));
  
  int32_t ret = getgroups(groups_length, groups);
  if (ret < 0) {
    env->die(env, stack, "getgroups fails:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  stack[0].oval = obj_groups;
  
  return 0;
}

int32_t SPVM__Sys__User__setgroups(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t error_system_class_id = env->get_class_id(env, "Error::System");

  assert(sizeof(gid_t) == sizeof(int32_t));
  
  void* obj_groups = stack[0].oval;
  if (!obj_groups) {
    return env->die(env, stack, "Groups must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t* groups = env->get_elems_int(env, stack, obj_groups);
  int32_t groups_length = env->length(env, stack, obj_groups);
  
  errno = 0;
  int32_t ret = setgroups(groups_length, groups);
  if (ret < 0) {
    env->die(env, stack, "setgroups fails:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__User__getpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  errno = 0;
  struct passwd* pwent = getpwent();
  
  if (pwent == NULL) {
    stack[0].oval = NULL;
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Passwd", pwent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
  
  return 0;
}

int32_t SPVM__Sys__User__getpwuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  int32_t uid = stack[0].ival;
  
  errno = 0;
  struct passwd* pwent = getpwuid(uid);
  
  if (pwent == NULL) {
    stack[0].oval = NULL;
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Passwd", pwent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
  
  return 0;
}

int32_t SPVM__Sys__User__getpwnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Sys__User__getgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  errno = 0;
  struct group* grent = getgrent();
  
  if (grent == NULL) {
    stack[0].oval = NULL;
  }
  else {
    void* obj_sys_ent_group = env->new_pointer_by_name(env, stack, "Sys::Ent::Group", grent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_group;
  }
  
  return 0;
}

int32_t SPVM__Sys__User__getgrgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  int32_t gid = stack[0].ival;
  
  errno = 0;
  struct group* grent = getgrgid(gid);
  
  if (grent == NULL) {
    stack[0].oval = NULL;
  }
  else {
    void* obj_sys_ent_group = env->new_pointer_by_name(env, stack, "Sys::Ent::Group", grent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_group;
  }
  
  return 0;
}

int32_t SPVM__Sys__User__getgrnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}
