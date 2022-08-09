// _XOPEN_SOURCE is needed for the following functions
// chroot
#define _XOPEN_SOURCE


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

const char* FILE_NAME = "SPVM/Sys/IO.c";

int32_t SPVM__Sys__IO__rmdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The directory must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);
  int32_t status = rmdir(dir);
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]rmdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__unlink(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_file = stack[0].oval;

  if (!obj_file) {
    return env->die(env, stack, "The file must be defined", FILE_NAME, __LINE__);
  }
  
  const char* file = env->get_chars(env, stack, obj_file);
  int32_t status = unlink(file);
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]unlink failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__close(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t fd = stack[0].ival;

  int32_t status = close(fd);
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]close failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__fclose(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_stream = stack[0].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The file stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int32_t status = fclose(stream);
  if (!(status == 0)) {
    env->die(env, stack, "[System Error]fclose failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
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
  
  int32_t ret = fileno(stream);
  
  stack[0].ival = ret;
  
  return 0;
}

int32_t SPVM__Sys__IO__open(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
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
    return error_system_class_id;
  }
  
  stack[0].ival = fd;
  
  return 0;
}

int32_t SPVM__Sys__IO__fopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
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
    return error_system_class_id;
  }
  
  void* obj_stream = env->new_pointer_by_name(env, stack, "Sys::FileHandle", stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__fdopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t fd = stack[0].ival;
  
  void* obj_mode = stack[1].oval;
  
  if (!obj_mode) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
  }
  
  const char* mode = env->get_chars(env, stack, obj_mode);
  
  FILE* stream = fdopen(fd, mode);
  if (!stream) {
    env->die(env, stack, "[System Error]fdopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  void* obj_stream = env->new_pointer_by_name(env, stack, "Sys::FileHandle", stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__freopen(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
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
  
  void* obj_stream = stack[1].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);

  FILE* new_stream = freopen(path, mode, stream);
  if (!new_stream) {
    env->die(env, stack, "[System Error]freopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  void* obj_new_stream = env->new_pointer_by_name(env, stack, "Sys::FileHandle", new_stream, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_new_stream;
  
  return 0;
}

int32_t SPVM__Sys__IO__read(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t fd = stack[0].ival;
  
  void* obj_buffer = stack[1].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
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
    return error_system_class_id;
  }
  
  stack[0].ival = read_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__write(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t fd = stack[0].ival;
  
  void* obj_buffer = stack[1].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
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
    return error_system_class_id;
  }
  
  stack[0].ival = write_length;
  
  return 0;
}

int32_t SPVM__Sys__IO__fread(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_buffer = stack[0].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
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
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_buffer = stack[0].oval;
  
  if (!obj_buffer) {
    return env->die(env, stack, "The mode must be defined", FILE_NAME, __LINE__);
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

int32_t SPVM__Sys__IO__EOF(SPVM_ENV* env, SPVM_VALUE* stack) {

  stack[0].ival = EOF;
  
  return 0;
}

int32_t SPVM__Sys__IO__chdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The directory must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);
  int32_t status = chdir(dir);
  if (status == -1) {
    env->die(env, stack, "[System Error]chdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__chmod(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int32_t mode = stack[1].ival;

  int32_t status = chmod(path, mode);
  if (status == -1) {
    env->die(env, stack, "[System Error]chmod failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__chown(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
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
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__flock(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  int32_t fd = stack[0].ival;
  
  int32_t operation = stack[1].ival;

  int32_t status = flock(fd, operation);
  if (status == -1) {
    env->die(env, stack, "[System Error]flock failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__mkdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_path = stack[0].oval;
  
  if (!obj_path) {
    return env->die(env, stack, "The path must be defined", FILE_NAME, __LINE__);
  }
  
  const char* path = env->get_chars(env, stack, obj_path);

  int32_t mode = stack[1].ival;

  int32_t status = mkdir(path, mode);
  if (status == -1) {
    env->die(env, stack, "[System Error]mkdir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__fseek(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;

  void* obj_stream = stack[1].oval;
  
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
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__ftell(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;

  void* obj_stream = stack[1].oval;
  
  if (!obj_stream) {
    return env->die(env, stack, "The stream must be defined", FILE_NAME, __LINE__);
  }
  
  FILE* stream = env->get_pointer(env, stack, obj_stream);
  
  int64_t offset = ftell(stream);
  if (offset == -1) {
    env->die(env, stack, "[System Error]ftell failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  stack[0].lval = offset;
  
  return 0;
}

int32_t SPVM__Sys__IO__chroot(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The directory must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);
  int32_t status = chroot(dir);
  if (status == -1) {
    env->die(env, stack, "[System Error]chroot failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__opendir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dir = stack[0].oval;
  
  if (!obj_dir) {
    return env->die(env, stack, "The dir must be defined", FILE_NAME, __LINE__);
  }
  
  const char* dir = env->get_chars(env, stack, obj_dir);

  DIR* dirent = opendir(dir);
  if (!dirent) {
    env->die(env, stack, "[System Error]opendir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  void* obj_dirent = env->new_pointer_by_name(env, stack, "Sys::DirHandle", dirent, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_dirent;
  
  return 0;
}

int32_t SPVM__Sys__IO__closedir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dirent = stack[0].oval;
  
  if (!obj_dirent) {
    return env->die(env, stack, "The directory object must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dirent = env->get_pointer(env, stack, obj_dirent);
  
  int32_t status = closedir(dirent);
  if (status == -1) {
    env->die(env, stack, "[System Error]closedir failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  return 0;
}

int32_t SPVM__Sys__IO__readdir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  int32_t error_system_class_id = SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM;
  
  void* obj_dh = stack[0].oval;
  
  if (!obj_dh) {
    return env->die(env, stack, "The directory entry must be defined", FILE_NAME, __LINE__);
  }
  
  DIR* dh = env->get_pointer(env, stack, obj_dh);
  
  errno = 0;
  struct dirent* dirent = readdir(dh);
  if (!dirent && errno != 0) {
    env->die(env, stack, "[System Error]freopen failed:%s.", env->strerror(env, stack, errno, 0), FILE_NAME, __LINE__);
    return error_system_class_id;
  }
  
  if (dirent) {
    void* obj_dirent = env->new_pointer_by_name(env, stack, "Sys::Ent::Dir", dirent, &e, FILE_NAME, __LINE__);
    if (e) { return e; }
    stack[0].oval = obj_dirent;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return 0;
}
