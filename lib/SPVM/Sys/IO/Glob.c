#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#include "spvm_native.h"

#include "SPVM__Sys__IO__Glob.h"
#include "SPVM__Sys__IO__Glob.c"

static const char* FILE_NAME = "Sys/IO/Glob.c";

int32_t SPVM__Sys__IO__Glob__bsd_glob(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_pattern = stack[0].oval;
  if (!obj_pattern) {
    return env->die(env, stack, "Pattern $pattern must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* pattern = env->get_chars(env, stack, obj_pattern);
  
  int32_t flags = 0;
  flags |= GLOB_BRACE | GLOB_NOMAGIC | GLOB_QUOTE | GLOB_TILDE | GLOB_ALPHASORT;
#ifdef WIN32
  flags |= GLOB_NOCASE;
#endif
  
  void* errfunc = NULL;
  
  glob_t pglob = {0};
  
  int32_t status = bsd_glob(env, stack, pattern, flags, errfunc, &pglob);
  
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]bsd_glob failed:(%d:%s). $pattern='%s'.", __func__, FILE_NAME, __LINE__, errno, env->strerror(env, stack, errno, 0), pattern);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
    goto END_OF_FUNC;
  }
  
  int32_t paths_length = pglob.gl_pathc;
  void* obj_paths = env->new_string_array(env, stack, paths_length);
  for (int i = 0; i < pglob.gl_pathc; i++) {
    const char* path = pglob.gl_pathv[i];
    int32_t path_length = strlen(path);
    void* obj_path = env->new_string(env, stack, path, path_length);
    env->set_elem_object(env, stack, obj_paths, i, obj_path);
  }
  
  stack[0].oval = obj_paths;
  
  END_OF_FUNC:
  
  bsd_globfree(&pglob);
  
  return error_id;
}
