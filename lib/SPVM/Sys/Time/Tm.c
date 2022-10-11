#include "spvm_native.h"

#include <time.h>

static const char* FILE_NAME = "Time/Tm.c";

int32_t SPVM__Sys__Time__Tm__new(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e;
  
  struct tm* st_tm = env->alloc_memory_block_zero(env, sizeof(struct tm));
  
  void* obj_tm = env->new_pointer_by_name(env, stack, "Time::Tm", st_tm, &e, FILE_NAME, __LINE__);
  if (e) { return e; }

  stack[0].oval = obj_tm;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  if (obj_tm != NULL) {
    struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
    env->free_memory_block(env, st_tm);
  }
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_sec;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_min(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_min;
  
  return 0;
}
int32_t SPVM__Sys__Time__Tm__tm_hour(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_hour;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_mday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_mday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_mon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_mon;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_year(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_year;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_wday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_wday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_yday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_yday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__tm_isdst(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  stack[0].ival = st_tm->tm_isdst;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t sec = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_sec = sec;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_min(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t min = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_min = min;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_hour(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t hour = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_hour = hour;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_mday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t mday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_mday = mday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_mon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t mon = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_mon = mon;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_year(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t year = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_year = year;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_wday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t wday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_wday = wday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_yday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t yday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_yday = yday;
  
  return 0;
}

int32_t SPVM__Sys__Time__Tm__set_tm_isdst(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_tm = stack[0].oval;
  
  int32_t isdst = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_tm);
  
  st_tm->tm_isdst = isdst;
  
  return 0;
}
