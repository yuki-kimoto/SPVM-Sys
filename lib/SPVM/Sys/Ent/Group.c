#include "spvm_native.h"

#include <grp.h>

static const char* FILE_NAME = "Sys/Ent/Group.c";

int32_t SPVM__Sys__Ent__Group__gr_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].oval = env->new_string(env, stack, st_group->gr_name, strlen(st_group->gr_name));
  
  return 0;
}

int32_t SPVM__Sys__Ent__Group__gr_passwd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].oval = env->new_string(env, stack, st_group->gr_passwd, strlen(st_group->gr_passwd));
  
  return 0;
}
int32_t SPVM__Sys__Ent__Group__gr_gid(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  stack[0].ival = st_group->gr_gid;
  
  return 0;
}

int32_t SPVM__Sys__Ent__Group__gr_mem(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_group = stack[0].oval;
  
  struct group* st_group = env->get_pointer(env, stack, obj_group);
  
  char** gr_mems = st_group->gr_mem;
  
  char* gr_mem = (char*)gr_mems;
  
  int32_t gr_mem_length = 0;
  while (gr_mem) {
    gr_mem_length++;
    gr_mem++;
  }
  
  void* obj_gr_mems = env->new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, gr_mem_length);
  
  for (int32_t i = 0; i < gr_mem_length; i++) {
    char* gr_mem = gr_mems[i];
    void* obj_gr_mem = env->new_string(env, stack, gr_mem, strlen(gr_mem));
    env->set_elem_object(env, stack, obj_gr_mems, i, obj_gr_mem);
  }
  
  stack[0].oval = obj_gr_mems;
  
  return 0;
}
