#include "spvm_native.h"

#ifdef _WIN32
# include <ws2tcpip.h>
# include <io.h>
#else
# include <sys/fcntl.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>
# define closesocket(fd) close(fd)
#endif

int32_t SPVM__Sys__Socket__gai_strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t gai_error_code = stack[0].ival;
  
  const char* ret_gai_strerror = gai_strerror(gai_error_code);
  
  if (ret_gai_strerror) {
    int32_t ret_gai_strerror_length = strlen(ret_gai_strerror);
    
    void* obj_gai_strerror = env->new_string(env, stack, ret_gai_strerror, ret_gai_strerror_length);
    stack[0].oval = obj_gai_strerror;
  }
  else {
    stack[0].oval = NULL;
  }
  
  return 0;
}
