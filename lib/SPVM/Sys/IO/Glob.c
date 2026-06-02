#ifdef __linux__
  // Enable X/Open System Interfaces (SUSv4) functions and POSIX.1-2008 standard functions
  #define _XOPEN_SOURCE 700

  // Enable BSD and System V extensions
  #define _DEFAULT_SOURCE
#endif

#include "spvm_native.h"

#include "spvm_sys_io_glob.h"
#include "spvm_sys_io_glob.c"

static const char* FILE_NAME = "Sys/IO/Glob.c";

int32_t SPVM__Sys__IO__Glob__bsd_glob(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_pattern = stack[0].oval;
  if (!obj_pattern) {
    return env->die(env, stack, "The $pattern must be defined", __func__, FILE_NAME, __LINE__);
  }
  char* pattern = (char*)env->get_chars(env, stack, obj_pattern);
  
  if (pattern[0] == '~') {
    return env->die(env, stack, "The \"~\" expansion is not supported", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_SYS_IO_GLOB st_glob;
  int32_t flags = 0;
  
  flags |= SPVM_SYS_IO_GLOB_C_BRACE | SPVM_SYS_IO_GLOB_C_NOMAGIC | SPVM_SYS_IO_GLOB_C_QUOTE | SPVM_SYS_IO_GLOB_C_ALPHASORT;
  
#ifdef WIN32
  flags |= SPVM_SYS_IO_GLOB_C_NOCASE;
#endif
  
  memset(&st_glob, 0, sizeof(SPVM_SYS_IO_GLOB));
  
  int32_t status = spvm_sys_io_glob_bsd_glob(env, stack, pattern, flags, &st_glob);
  
  int32_t e = 0;
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]glob failed:%s. The files specified by the \"%s\" pattern can't be get", __func__, FILE_NAME, __LINE__, env->strerror(env, stack, errno, 0), pattern);
    e = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  else {
    int32_t paths_length = st_glob.gl_pathc;
    
    void* obj_paths = env->new_string_array(env, stack, paths_length);
    
    for (int i = 0; i < st_glob.gl_pathc; i++) {
      const char* path = st_glob.gl_pathv[i];
      int32_t path_length = strlen(path);
      void* obj_path = env->new_string(env, stack, path, path_length);
      env->set_elem_object(env, stack, obj_paths, i, obj_path);
    }
    
    stack[0].oval = obj_paths;
  }
  
  spvm_sys_io_glob_bsd_globfree(env, stack, &st_glob);
  
  return e;
}

