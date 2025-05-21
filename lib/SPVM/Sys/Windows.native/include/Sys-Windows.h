#ifndef SPVM__SYS__WINDOWS__H
#define SPVM__SYS__WINDOWS__H

#if defined(_WIN32)
#include <windows.h>

static void* utf8_to_utf16le(SPVM_ENV* env, SPVM_VALUE* stack, const char* utf8_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  *error_id = 0;
  
  if (utf8_string == NULL) {
    return NULL;
  }
  
  int32_t utf16le_string_length = MultiByteToWideChar(
      CP_UTF8,
      0,
      utf8_string,
      -1,
      NULL,
      0
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_utf16le failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  void* obj_utf16le_string = env->new_short_array(env, stack, utf16le_string_length);
  wchar_t* utf16le_string = env->get_elems_short(env, stack, obj_utf16le_string);
  
  utf16le_string_length = MultiByteToWideChar(
    CP_UTF8,
    0,
    utf8_string,
    -1,
    utf16le_string,
    utf16le_string_length
  );
  
  if (utf16le_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_utf16le failed:Error converting UTF-8 to UTF-16LE: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf16le_string;
}

static const char* utf16le_to_utf8(SPVM_ENV* env, SPVM_VALUE* stack, wchar_t* utf16le_string, int32_t* error_id, const char* func_name, const char* file, int32_t line) {
  
  if (utf16le_string == NULL) {
    return NULL;
  }
  
  int32_t utf8_string_length = WideCharToMultiByte(
    CP_UTF8,
    0,
    utf16le_string,
    -1,
    NULL,
    0,
    NULL,
    NULL
  );
  
  if (utf8_string_length == 0) {
    *error_id = env->die(env, stack,  "utf8_to_utf16le failed:Error calculating length: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  void* obj_utf8_string = env->new_string(env, stack, NULL, utf8_string_length);
  
  char* utf8_string = (char*)env->get_chars(env, stack, obj_utf8_string);
  
  utf8_string_length = WideCharToMultiByte(
    CP_UTF8,
    0,
    utf16le_string,
    -1,
    utf8_string,
    utf8_string_length,
    NULL,
    NULL
  );
  
  if (utf8_string_length == 0) {
    *error_id = env->die(env, stack,  "utf16le_to_utf8 failed:Error converting UTF-16LE to UTF-8: %lu.", GetLastError(), func_name, file, line);
    return NULL;
  }
  
  return utf8_string;
}

#endif // defined(_WIN32)

#endif // SPVM__SYS__WINDOWS__H
