#include "spvm_native.h"

#include <unistd.h>
#include <assert.h>
#include <errno.h>

#ifdef _WIN32
  
#else
#  include <pwd.h>
#  include <grp.h>
#endif

const char* FILE_NAME = "SPVM/Sys/User.c";

int32_t SPVM__Sys__User__getuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getuid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t uid = getuid();
  
  stack[0].ival = uid;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__geteuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "geteuid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t euid = geteuid();
  
  stack[0].ival  = euid;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getgid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t gid = getgid();
  
  stack[0].ival = gid;
#endif

  return 0;
}

int32_t SPVM__Sys__User__getegid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getegid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t egid = getegid();
  
  stack[0].ival = egid;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__setuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "setuid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t uid = stack[0].ival;
  int32_t error_code = setuid(uid);
  
  stack[0].ival = error_code;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__seteuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "seteuid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t euid = stack[0].ival;
  int32_t error_code = seteuid(euid);
  
  stack[0].ival = error_code;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__setgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "setgid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t gid = stack[0].ival;
  errno = 0;
  int32_t error_code = setgid(gid);
  
  stack[0].ival = error_code;
#endif

  return 0;
}

int32_t SPVM__Sys__User__setegid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "setegid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t egid = stack[0].ival;
  errno = 0;
  int32_t error_code = setegid(egid);
  
  stack[0].ival = error_code;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__setpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

#ifdef _WIN32
  return env->die(env, stack, "setpwent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  setpwent();
#endif

  return 0;
}


int32_t SPVM__Sys__User__endpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "endpwent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  endpwent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__setgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "setgrent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  setgrent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__endgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "endgrent is not supported in this system", FILE_NAME, __LINE__);
#else
  errno = 0;
  endgrent();
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getgroups(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getgroups is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t groups_length = getgroups(0, NULL);
  if (groups_length < 0) {
    env->die(env, stack, "[System Error]getgroups failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  void* obj_groups = env->new_int_array(env, stack, groups_length);
  int32_t* groups = env->get_elems_int(env, stack, obj_groups);
  
  assert(sizeof(gid_t) == sizeof(int32_t));
  
  int32_t ret = getgroups(groups_length, groups);
  if (ret < 0) {
    env->die(env, stack, "[System Error]getgroups failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  stack[0].oval = obj_groups;
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__setgroups(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "setgroups is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  assert(sizeof(gid_t) == sizeof(int32_t));
  
  void* obj_groups = stack[0].oval;
  if (!obj_groups) {
    return env->die(env, stack, "Groups must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t* groups = env->get_elems_int(env, stack, obj_groups);
  int32_t groups_length = env->length(env, stack, obj_groups);
  
  spvm_warn("AAAA %s", env->get_chars(env, stack, env->dump(env, stack, obj_groups)));
  
  int32_t ret = setgroups(groups_length, groups);
  if (ret < 0) {
    env->die(env, stack, "[System Error]setgroups failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getpwent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getpwent is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  errno = 0;
  struct passwd* pwent = getpwent();
  
  if (pwent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getpwent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Passwd", pwent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getpwuid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getpwuid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t uid = stack[0].ival;
  
  errno = 0;
  struct passwd* pwent = getpwuid(uid);
  
  if (pwent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getpwuid failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Passwd", pwent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getpwnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getpwnam is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_pwnam = stack[0].oval;
  
  if (!obj_pwnam) {
    return env->die(env, stack, "The user name must be defined", FILE_NAME, __LINE__);
  }
  const char* pwnam = env->get_chars(env, stack, obj_pwnam);
  
  errno = 0;
  struct passwd* pwent = getpwnam(pwnam);
  
  if (pwent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getpwnam failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_passwd = env->new_pointer_by_name(env, stack, "Sys::Ent::Passwd", pwent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_passwd;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getgrent(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getgrent is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  errno = 0;
  struct group* grent = getgrent();
  
  if (grent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getgrent failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_group = env->new_pointer_by_name(env, stack, "Sys::Ent::Group", grent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_group;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getgrgid(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getgrgid is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t gid = stack[0].ival;
  
  errno = 0;
  struct group* grent = getgrgid(gid);
  
  if (grent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getgrgid failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_group = env->new_pointer_by_name(env, stack, "Sys::Ent::Group", grent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_group;
  }
#endif
  
  return 0;
}

int32_t SPVM__Sys__User__getgrnam(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
#ifdef _WIN32
  return env->die(env, stack, "getgrnam is not supported in this system", FILE_NAME, __LINE__);
#else
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_grnam = stack[0].oval;
  
  if (!obj_grnam) {
    return env->die(env, stack, "The group name must be defined", FILE_NAME, __LINE__);
  }
  const char* grnam = env->get_chars(env, stack, obj_grnam);
  
  errno = 0;
  struct group* grent = getgrnam(grnam);
  
  if (grent == NULL) {
    if (errno) {
      env->die(env, stack, "[System Error]getgrnam failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
      return error_system_class_id;
    }
    else {
      stack[0].oval = NULL;
    }
  }
  else {
    void* obj_sys_ent_group = env->new_pointer_by_name(env, stack, "Sys::Ent::Group", grent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_sys_ent_group;
  }
#endif
  
  return 0;
}
