// lseek off_t become 64bit 
#define _FILE_OFFSET_BITS 64

#include "spvm_native.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <utime.h>

#ifndef _WIN32
  #include <poll.h>
  #include <sys/ioctl.h>
#endif

const char* FILE_NAME = "Sys/IO.c";

int32_t SPVM__Sys__IO__rmdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  int32_t status = rmdir(path);
  if (status == -1) {
    env->die(env, stack, "[System Error]rmdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;

  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  int32_t status = unlink(path);
  if (status == -1) {
    env->die(env, stack, "[System Error]unlink failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__close(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t fd = stack[0].ival;

  int32_t status = close(fd);
  if (status == -1) {
    env->die(env, stack, "[System Error]close failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__clearerr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  clearerr(stream);
  
  return 0;
}

int32_t SPVM__Sys__IO__feof(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t ret = feof(stream);
  
  stack[0].ival = ret;
  
  return 0;
}

int32_t SPVM__Sys__IO__ferror(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t ret = ferror(stream);
  
  stack[0].ival = ret;
  
  return 0;
}

int32_t SPVM__Sys__IO__fileno(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t fd = fileno(stream);

  if (fd == -1) {
    env->die(env, stack, "[System Error]fileno failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = fd;
  
  return 0;
}

int32_t SPVM__Sys__IO__open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t items = env->get_args_stack_length(env, stack);
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  int32_t flags = stack[1].ival;
  
  int32_t mode = 0;
  if (items > 2) {
    mode = stack[2].ival;
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  int32_t fd = open(path, flags, mode);
  if (fd == -1) {
    env->die(env, stack, "[System Error]open failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = fd;
  
  return 0;
}

int32_t SPVM__Sys__IO__fopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  void* obj_mode = stack[1].oval;
  
  if (!obj_mode) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
  }
  
  const char* mode = env->get_chars(env, stack, obj_mode);
  
  FILE* stream = fopen(path, mode);
  if (!stream) {
    env->die(env, stack, "[System Error]fopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  void* obj_stream = env->new_pointer_by_name(env, stack, "Sys::FileStream", stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__fdopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t fd = stack[0].ival;
  
  void* obj_mode = stack[1].oval;
  
  if (!obj_mode) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
  }
  
  const char* mode = env->get_chars(env, stack, obj_mode);
  
  FILE* stream = fdopen(fd, mode);
  if (!stream) {
    env->die(env, stack, "[System Error]fdopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  void* obj_stream = env->new_pointer_by_name(env, stack, "Sys::FileStream", stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__freopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_mode = stack[1].oval;
  
  if (!obj_mode) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
  }
  
  const char* mode = env->get_chars(env, stack, obj_mode);
  
  void* obj_stream = stack[2].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);

  FILE* new_stream = freopen(path, mode, stream);
  if (!new_stream) {
    env->die(env, stack, "[System Error]freopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  void* obj_new_stream = env->new_pointer_by_name(env, stack, "Sys::FileStream", new_stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_new_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__fread(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_buffer = stack[0].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);
  
  int32_t size = stack[1].ival;
  if (!(size >= 0)) {
    return env->die(env, stack, "The size must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  int32_t data_length = stack[2].ival;
  if (!(data_length >= 0)) {
    return env->die(env, stack, "The data length must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (size == 0 || data_length == 0) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!((buffer_length / size) <= data_length)) {
    return env->die(env, stack, "The buffer length / the size must be less than or equal to the data length", FILE_NAME, __LINE__);
  }
  
  void* obj_stream = stack[3].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t fread_length = fread(buffer, size, data_length, stream);
  
  stack[0].ival = fread_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__fwrite(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_buffer = stack[0].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);
  
  int32_t size = stack[1].ival;
  if (!(size >= 0)) {
    return env->die(env, stack, "The size must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  int32_t data_length = stack[2].ival;
  if (!(data_length >= 0)) {
    return env->die(env, stack, "The data length must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (size == 0 || data_length == 0) {
    stack[0].ival = 0;
    return 0;
  }
  
  if (!((buffer_length / size) <= data_length)) {
    return env->die(env, stack, "The buffer length / the size must be less than or equal to the data length", FILE_NAME, __LINE__);
  }
  
  void* obj_stream = stack[3].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t fwrite_length = fwrite(buffer, size, data_length, stream);
  
  stack[0].ival = fwrite_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__fclose(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t status = fclose(stream);
  if (status == EOF) {
    env->die(env, stack, "[System Error]fclose failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__fflush(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t status = fflush(stream);
  if (status == EOF) {
    env->die(env, stack, "[System Error]fflush failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__flock(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "The \"flock\" method in the class \"Sys::IO\" is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  int32_t fd = stack[0].ival;

  int32_t operation = stack[1].ival;
  
  int32_t status = flock(fd, operation);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]flock failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__read(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t fd = stack[0].ival;
  
  void* obj_buffer = stack[1].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);

  int32_t count = stack[2].ival;
  
  if (!(count >= 0)) {
    return env->die(env, stack, "The count must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(count < buffer_length)) {
    return env->die(env, stack, "The count must be less than the length of the buffer", FILE_NAME, __LINE__);
  }
  
  int32_t read_length = read(fd, buffer, count);
  if (read_length == -1) {
    env->die(env, stack, "[System Error]read failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = read_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t fd = stack[0].ival;
  
  void* obj_buffer = stack[1].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);

  int32_t count = stack[2].ival;
  
  if (!(count >= 0)) {
    return env->die(env, stack, "The count must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(count < buffer_length)) {
    return env->die(env, stack, "The count must be less than the length of the buffer", FILE_NAME, __LINE__);
  }
  
  int32_t write_length = write(fd, buffer, count);
  if (write_length == -1) {
    env->die(env, stack, "[System Error]write failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = write_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__getc(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t ch = getc(stream);
  
  stack[0].ival = ch;
  
  return 0;
}

int32_t SPVM__Sys__IO__fgets(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_buffer = stack[0].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The buffer must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);
  
  int32_t size = stack[1].ival;
  if (!(size >= 0)) {
    return env->die(env, stack, "The size must be more than or equal to 0", FILE_NAME, __LINE__);
  }
  
  void* obj_stream = stack[2].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  char* ret_buffer = fgets(buffer, size, stream);
  
  if (ret_buffer) {
    stack[0].oval = obj_buffer;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__chdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  int32_t status = chdir(path);
  if (status == -1) {
    env->die(env, stack, "[System Error]chdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__chmod(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int32_t mode = stack[1].ival;

  int32_t status = chmod(path, mode);
  if (status == -1) {
    env->die(env, stack, "[System Error]chmod failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__chown(SPVM_ENV* env, SPVM_VALUE* stack) {
  
#ifdef _WIN32
  env->die(env, stack, "chown is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int32_t owner = stack[1].ival;

  int32_t group = stack[2].ival;

  int32_t status = chown(path, owner, group);
  if (status == -1) {
    env->die(env, stack, "[System Error]chown failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__mkdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int32_t mode = stack[1].ival;

#ifdef _WIN32
  int32_t status = mkdir(path);
#else
  int32_t status = mkdir(path, mode);
#endif

  if (status == -1) {
    env->die(env, stack, "[System Error]mkdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__fseek(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int64_t offset = stack[1].lval;
  
  if (!(offset >= 0)) {
    return env->die(env, stack, "The offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }

  int32_t whence = stack[2].ival;

  int32_t status = fseek(stream, offset, whence);
  if (status == -1) {
    env->die(env, stack, "[System Error]fseek failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__ftell(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int64_t offset = ftell(stream);
  if (offset == -1) {
    env->die(env, stack, "[System Error]ftell failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].lval = offset;
  
  return 0;
}

int32_t SPVM__Sys__IO__opendir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The dir must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);

  DIR* dir_stream = opendir(dir);
  if (!dir_stream) {
    env->die(env, stack, "[System Error]opendir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  void* obj_dir_stream = env->new_pointer_by_name(env, stack, "Sys::DirStream", dir_stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_dir_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__closedir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dir_stream = stack[0].oval;
  
  if (!obj_dir_stream) {
    return env->die(env, stack, "The directory object must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dir_stream = env->get_pointer(env, stack, obj_dir_stream);
  
  int32_t status = closedir(dir_stream);
  if (status == -1) {
    env->die(env, stack, "[System Error]closedir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }

  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__readdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_dir_stream = stack[0].oval;
  
  if (!obj_dir_stream) {
    return env->die(env, stack, "The directory entry must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dir_stream = env->get_pointer(env, stack, obj_dir_stream);
  
  errno = 0;
  struct dirent* dirent = readdir(dir_stream);
  if (errno != 0) {
    env->die(env, stack, "[System Error]readdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  if (dirent) {
    void* obj_dirent = env->new_pointer_by_name(env, stack, "Sys::IO::Dirent", dirent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_dirent;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__rewinddir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dir_stream = stack[0].oval;
  
  if (!obj_dir_stream) {
    return env->die(env, stack, "The directory object must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dir_stream = env->get_pointer(env, stack, obj_dir_stream);
  
  rewinddir(dir_stream);
  
  return 0;
}

int32_t SPVM__Sys__IO__telldir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dir_stream = stack[0].oval;
  
  if (!obj_dir_stream) {
    return env->die(env, stack, "The directory object must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dir_stream = env->get_pointer(env, stack, obj_dir_stream);
  
  int64_t offset = telldir(dir_stream);
  if (offset == -1) {
    env->die(env, stack, "[System Error]telldir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].lval = offset;
  
  return 0;
}

int32_t SPVM__Sys__IO__seekdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_dir_stream = stack[0].oval;
  
  if (!obj_dir_stream) {
    return env->die(env, stack, "The directory object must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dir_stream = env->get_pointer(env, stack, obj_dir_stream);

  int64_t offset = stack[1].ival;
  
  if (!(offset >= 0)) {
    return env->die(env, stack, "The offset must be less than or equal to 0", FILE_NAME, __LINE__);
  }
  
  seekdir(dir_stream, offset);
  
  return 0;
}

int32_t SPVM__Sys__IO__truncate(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int64_t offset = stack[1].ival;
  
  if (!(offset >= 0)) {
    return env->die(env, stack, "The offset must be less than or equal to 0", FILE_NAME, __LINE__);
  }

  int32_t status = truncate(path, offset);
  if (status == -1) {
    env->die(env, stack, "[System Error]truncate failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__lseek(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t fd = stack[0].ival;
  
  int64_t offset = stack[1].lval;
  
  if (!(offset >= 0)) {
    return env->die(env, stack, "The offset must be greater than or equal to 0", FILE_NAME, __LINE__);
  }

  int32_t whence = stack[2].ival;

  int64_t cur_offset = lseek(fd, offset, whence);
  if (cur_offset == -1) {
    env->die(env, stack, "[System Error]lseek failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__umask(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t mode = stack[0].ival;
  
  int32_t old_mode = umask(mode);
  
  stack[0].ival = old_mode;
  
  return 0;
}

int32_t SPVM__Sys__IO__rename(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The old path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  void* obj_new_path = stack[1].oval;
  
  if (!obj_new_path) {
    return env->die(env, stack, "The new path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* new_path = env->get_chars(env, stack, obj_new_path);
  
  int32_t status = rename(path, new_path);
  if (status == -1) {
    env->die(env, stack, "[System Error]rename failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__readlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "readlink is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The old path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  void* obj_buffer = stack[1].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The new path must be defined", FILE_NAME, __LINE__);
  }
  
  char* buffer = (char*)env->get_chars(env, stack, obj_buffer);
  int32_t buffer_length = env->length(env, stack, obj_buffer);
  
  int32_t arg_buffer_length = stack[2].ival;
  
  if (!(arg_buffer_length >= 0)) {
    return env->die(env, stack, "The buffer length of the argument must be greater than or equal to 0", FILE_NAME, __LINE__);
  }
  
  if (!(arg_buffer_length <= buffer_length)) {
    return env->die(env, stack, "The buffer length of the argument must be less than or equal to the length of the buffer", FILE_NAME, __LINE__);
  }
  
  int32_t placed_length = readlink(path, buffer, arg_buffer_length);
  if (placed_length == -1) {
    env->die(env, stack, "[System Error]readlink failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = placed_length;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__symlink(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "symlink is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  int32_t e = 0;
  
  void* obj_target = stack[0].oval;
  
  if (!obj_target) {
    return env->die(env, stack, "The target must be defined", FILE_NAME, __LINE__);
  }
  
  const char* target = env->get_chars(env, stack, obj_target);

  void* obj_link_path = stack[1].oval;
  
  if (!obj_link_path) {
    return env->die(env, stack, "The link path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* link_path = env->get_chars(env, stack, obj_link_path);
  
  int32_t status = symlink(target, link_path);
  if (status == -1) {
    env->die(env, stack, "[System Error]symlink failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__utime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_file = stack[0].oval;
  
  if (!obj_file) {
    return env->die(env, stack, "The file must be defined", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);

  void* obj_buffer = stack[1].oval;
  struct utimbuf* st_buffer;
  if (obj_buffer) {
    st_buffer = env->get_pointer(env, stack, obj_buffer);
  }
  else {
    st_buffer = NULL;
  }
  
  int32_t status = utime(file, st_buffer);
  if (status == -1) {
    env->die(env, stack, "[System Error]utime failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__access(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);
  
  int32_t mode = stack[1].ival;
  
  int32_t status = access(path, mode);
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__stat(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_stat = stack[1].oval;
  
  if (!obj_stat) {
    return env->die(env, stack, "The stat must be defined", FILE_NAME, __LINE__);
  }
  
  struct stat* stat_buf = env->get_pointer(env, stack, obj_stat);
  
  int32_t status = stat(path, stat_buf);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]stat failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
}

int32_t SPVM__Sys__IO__lstat(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  return env->die(env, stack, "lstat is not supported on this system", FILE_NAME, __LINE__);
#else

  int32_t e = 0;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  const char* path = env->get_chars(env, stack, obj_path);
  
  void* obj_lstat = stack[1].oval;
  
  if (!obj_lstat) {
    return env->die(env, stack, "The lstat must be defined", FILE_NAME, __LINE__);
  }
  
  struct stat* stat_buf = env->get_pointer(env, stack, obj_lstat);
  
  int32_t status = lstat(path, stat_buf);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]lstat failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__fcntl(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  return env->die(env, stack, "fcntl is not supported on this system", FILE_NAME, __LINE__);
#else
  
  int32_t e = 0;
  
  int32_t items = env->get_args_stack_length(env, stack);
  
  int32_t fd = stack[0].ival;
  
  int32_t command = stack[1].ival;
  
  int32_t status;
  
  void* obj_arg;
  if (items <= 2) {
    ret = fcntl(fd, command);
  }
  else {
    void* obj_arg = stack[2].oval;
    
    if (!obj_arg) {
      ret = fcntl(fd, command, NULL);
    }
    else {
      int32_t arg_basic_type_id = env->get_object_basic_type_id(env, stack, obj_arg);
      int32_t arg_type_dimension = env->get_object_type_dimension(env, stack, obj_arg);
      
      // Int
      if (arg_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS && arg_type_dimension == 0) {
        int32_t arg_int32 = env->get_field_int_by_name(env, stack, obj_arg, "Int", "value", &e, FILE_NAME, __LINE__);
        if (e) { return e; }
        
        int arg_int = arg_int32;
        
        ret = fcntl(fd, command, arg_int);
      }
      // A pointer class
      else if (env->is_pointer_class(env, stack, obj_arg)) {
        void* arg = env->get_pointer(env, stack, obj_arg);
        ret = fcntl(fd, command, arg);
      }
      else {
        return env->die(env, stack, "The command argument must be an Int object or the object that is a pointer class such as Sys::IO::Flock", FILE_NAME, __LINE__);
      }
    }
  }
  
  stack[0].ival = ret;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__ioctl(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef _WIN32
  env->die(env, stack, "ioctl is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  int32_t e = 0;
  
  int32_t fd = stack[0].ival;
  
  int32_t request = stack[1].ival;
  
  void* obj_arg = stack[2].oval;
  
  char* arg = NULL;
  if (obj_arg) {
    arg = (char*)env->get_chars(env, stack, obj_arg);
  }
  
  int32_t ret = ioctl(fd, request, arg);

  if (ret == -1) {
    env->die(env, stack, "[System Error]ioctl failed:%s", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = ret;
  
  return 0;
#endif
}

int32_t SPVM__Sys__IO__ioctl_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t* int32_arg_ref = stack[2].iref;
  
  int int_arg = *int32_arg_ref;
  
  void* obj_arg = env->new_string(env, stack, NULL, sizeof(int));
  char* arg = (char*)env->get_chars(env, stack, obj_arg);
  memcpy(arg, &int_arg, sizeof(int));
  
  stack[2].oval = obj_arg;
  
  int32_t error = SPVM__Sys__IO__ioctl(env, stack);
  
  int int_arg_output;
  memcpy(&int_arg_output, arg, sizeof(int));
  
  *int32_arg_ref = int_arg_output;
  
  return error;
}

int32_t SPVM__Sys__IO__poll(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef _WIN32
  env->die(env, stack, "The \"poll\" method in the class \"Sys::IO\" is not supported on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#else
  
  void* obj_fds = stack[0].oval;
  
  struct pollfd* fds = env->get_pointer(env, stack, obj_fds);
  
  int32_t nfds = stack[1].ival;
  
  int32_t timeout = stack[2].ival;
  
  int32_t status = poll(fds, nfds, timeout);
  
  if (status == -1) {
    env->die(env, stack, "[System Error]poll failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  }
  
  stack[0].ival = status;
  
  return 0;
#endif
}

