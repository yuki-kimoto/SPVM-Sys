#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#include "spvm_native.h"

#include "SPVM__Sys__IO__Glob__glob.h"
#include "SPVM__Sys__IO__Glob__glob.c"

static const char* FILE_NAME = "Sys/IO/Glob.c";

int32_t SPVM__Sys__IO__Glob__glob(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_pattern = stack[0].oval;
  if (!obj_pattern) {
    return env->die(env, stack, "The $pattern must be defined", __func__, FILE_NAME, __LINE__);
  }
  char* pattern = (char*)env->get_chars(env, stack, obj_pattern);
  
  if (pattern[0] == '~') {
    return env->die(env, stack, "The \"~\" expansion is not supported", __func__, FILE_NAME, __LINE__);
  }
  
  glob_t pglob;
  int32_t flags = 0;
  void* errfunc = NULL;
  
  memset(&pglob, 0, sizeof(glob_t));
  
  int32_t status = glob(pattern, flags, errfunc, &pglob);
  
  int32_t e = 0;
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]glob failed:%s. The files specified by the \"%s\" pattern can't be get", __func__, FILE_NAME, __LINE__, env->strerror(env, stack, errno, 0), pattern);
    e = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  else {
    int32_t paths_length = pglob.gl_pathc;
    
    void* obj_paths = env->new_string_array(env, stack, paths_length);
    
    for (int i = 0; i < pglob.gl_pathc; i++) {
      const char* path = pglob.gl_pathv[i];
      int32_t path_length = strlen(path);
      void* obj_path = env->new_string(env, stack, path, path_length);
      env->set_elem_object(env, stack, obj_paths, i, obj_path);
    }
    
    stack[0].oval = obj_paths;
  }
  
  globfree(&pglob);
  
  return e;
}
