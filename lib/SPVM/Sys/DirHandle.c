#include "spvm_native.h"
#include <stdio.h>
#include <dirent.h>

const char* FILE_NAME = "IO/DirHandle.c";

int32_t SPVM__Sys__DirHandle__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Dir handle
  void* odh = stack[0].oval;
  if (odh != NULL) {
    DIR* dh = env->get_pointer(env, stack, odh);
    if (dh) {
      int32_t ret = closedir(dh);
      env->set_pointer(env, stack, odh, NULL);
      
      if (ret == EOF) {
        return env->die(env, stack, "Can't close the file stream at %s line %d", FILE_NAME, __LINE__);
      }
    }
  }
  
  return 0;
}
