#include "spvm_native.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

const char* FILE_NAME = "SPVM/System.c";

int32_t SPVM__System__rmdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  int32_t count = 0;
  if (obj_file) {
    const char* file = env->get_chars(env, stack, obj_file);
    int32_t error_code = rmdir(file);
    if (error_code == 0) {
      count++;
    }
  }
  
  stack[0].ival = count;
  
  return 0;
}

int32_t SPVM__System__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_file = stack[0].oval;
  
  int32_t count = 0;
  if (obj_file) {
    const char* file = env->get_chars(env, stack, obj_file);
    int32_t error_code = unlink(file);
    if (error_code == 0) {
      count++;
    }
  }
  
  stack[0].ival = count;
  
  return 0;
}

int32_t SPVM__System__getcwd(SPVM_ENV* env, SPVM_VALUE* stack) {

  char* cur_dir = getcwd(NULL, 0);
  
  void* obj_cur_dir = NULL;
  if (cur_dir) {
    int32_t cur_dir_len = strlen(cur_dir);
    for (int32_t i = 0; i < cur_dir_len; i++) {
      if (cur_dir[i] == '\\') {
        cur_dir[i] = '/';
      }
    }
    obj_cur_dir = env->new_string_nolen(env, stack, cur_dir);
    free(cur_dir);
  }
  
  stack[0].oval = obj_cur_dir;

  return 0;
}

int32_t SPVM__System__ftest_r(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_w(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_x(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_o(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_R(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_W(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_X(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_O(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_e(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__System__ftest_z(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_s(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_f(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__System__ftest_d(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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

int32_t SPVM__System__ftest_l(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_p(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_S(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_b(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_c(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_t(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_u(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_g(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_k(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_T(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_B(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_M(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_A(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}

int32_t SPVM__System__ftest_C(SPVM_ENV* env, SPVM_VALUE* stack) {

  return env->die(env, stack, "Not yet implemented", FILE_NAME, __LINE__);

  return 0;
}
