#include "spvm_native.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

const char* FILE_NAME = "Sys/FileTest.c";

int32_t SPVM__Sys__FileTest__r(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__w(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__x(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__o(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__R(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__W(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__X(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__O(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__e(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "A file name must be specified", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  
  int32_t result;
  
  struct stat st;
  int32_t stat_result = stat(file, &st);
  if (stat_result != 0) {
    result = 0;
  }
  else {
    result = 1;
  }
  
  stack[0].ival = result;
  
  return 0;
}

int32_t SPVM__Sys__FileTest__z(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__s(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__f(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "A file name must be specified", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  
  int32_t result;
  
  struct stat st;
  int32_t stat_result = stat(file, &st);
  if (stat_result != 0) {
    result = 0;
  }
  else {
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
      result = 0;
    }
    else {
      result = 1;
    }
  }
  
  stack[0].ival = result;
  
  return 0;
}

int32_t SPVM__Sys__FileTest__d(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "A file name must be specified", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  
  int32_t result;
  
  struct stat st;
  int32_t stat_result = stat(file, &st);
  if (stat_result != 0) {
    result = 0;
  }
  else {
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
      result = 1;
    }
    else {
      result = 0;
    }
  }
  
  stack[0].ival = result;
  
  return 0;
}

int32_t SPVM__Sys__FileTest__l(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__p(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__S(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__b(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__c(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__t(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__u(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__g(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__k(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__T(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__B(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__M(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__A(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__Sys__FileTest__C(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}
