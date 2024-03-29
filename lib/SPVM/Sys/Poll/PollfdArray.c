// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Windows 8.1+
#define _WIN32_WINNT 0x0603

#include "spvm_native.h"

#include <assert.h>

#if defined(_WIN32)
  #include <winsock2.h>
#else
  #include <poll.h>
#endif

static const char* FILE_NAME = "Sys/Poll/PollfdArray";

int32_t SPVM__Sys__Poll__PollfdArray__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  int32_t length = stack[0].ival;
  
  if (!(length >= 0)) {
    return env->die(env, stack, "The length must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t alloc_length = length == 0 ? sizeof(struct pollfd) * 1 : sizeof(struct pollfd) * length;
  
  struct pollfd* fds = env->new_memory_block(env, stack, alloc_length);
  
  int32_t fields_length = 1;
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Sys::Poll::PollfdArray", fds, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_int_by_name(env, stack, obj_self, "length", length, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  assert(fds);
  
  env->free_memory_block(env, stack, fds);
  env->set_pointer(env, stack, obj_self, NULL);
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__fd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t index = stack[1].ival;
  
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  int32_t fd = fds[index].fd;
  
  stack[0].ival = fd;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__set_fd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;

  int32_t index = stack[1].ival;
  
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  int32_t fd = stack[2].ival;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  fds[index].fd = fd;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__events(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t index = stack[1].ival;
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  int16_t events = fds[index].events;
  
  stack[0].ival = events;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__set_events(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;

  int32_t index = stack[1].ival;
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  int16_t events = stack[2].ival;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  fds[index].events = events;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__revents(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t index = stack[1].ival;
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  int16_t revents = fds[index].revents;
  
  stack[0].ival = revents;
  
  return 0;
}

int32_t SPVM__Sys__Poll__PollfdArray__set_revents(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;

  int32_t index = stack[1].ival;
  if (!(index >= 0)) {
    return env->die(env, stack, "$index must be greater than or equal to 0.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t length = env->get_field_int_by_name(env, stack, obj_self, "length", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!(index < length)) {
    return env->die(env, stack, "$index must be less than the value of the length field.", __func__, FILE_NAME, __LINE__);
  }

  int16_t revents = stack[2].ival;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_self);
  
  fds[index].revents = revents;
  
  return 0;
}
