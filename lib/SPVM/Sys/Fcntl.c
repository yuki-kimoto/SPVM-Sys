#include "spvm_native.h"

const char* FILE_NAME = "Sys/Fcntl.c";

int32_t SPVM__Sys__Fcntl__DN_ACCESS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_ACCESS
  stack[0].ival = DN_ACCESS;
  return 0;
#else
  return env->die(env, stack, "DN_ACCESS is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_ATTRIB(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_ATTRIB
  stack[0].ival = DN_ATTRIB;
  return 0;
#else
  return env->die(env, stack, "DN_ATTRIB is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_CREATE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_CREATE
  stack[0].ival = DN_CREATE;
  return 0;
#else
  return env->die(env, stack, "DN_CREATE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_DELETE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_DELETE
  stack[0].ival = DN_DELETE;
  return 0;
#else
  return env->die(env, stack, "DN_DELETE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_MODIFY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_MODIFY
  stack[0].ival = DN_MODIFY;
  return 0;
#else
  return env->die(env, stack, "DN_MODIFY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_MULTISHOT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_MULTISHOT
  stack[0].ival = DN_MULTISHOT;
  return 0;
#else
  return env->die(env, stack, "DN_MULTISHOT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__DN_RENAME(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef DN_RENAME
  stack[0].ival = DN_RENAME;
  return 0;
#else
  return env->die(env, stack, "DN_RENAME is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__FD_CLOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FD_CLOEXEC
  stack[0].ival = FD_CLOEXEC;
  return 0;
#else
  return env->die(env, stack, "FD_CLOEXEC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_ADD_SEALS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_ADD_SEALS
  stack[0].ival = F_ADD_SEALS;
  return 0;
#else
  return env->die(env, stack, "F_ADD_SEALS is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_DUPFD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_DUPFD
  stack[0].ival = F_DUPFD;
  return 0;
#else
  return env->die(env, stack, "F_DUPFD is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_DUPFD_CLOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_DUPFD_CLOEXEC
  stack[0].ival = F_DUPFD_CLOEXEC;
  return 0;
#else
  return env->die(env, stack, "F_DUPFD_CLOEXEC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETFD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETFD
  stack[0].ival = F_GETFD;
  return 0;
#else
  return env->die(env, stack, "F_GETFD is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETFL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETFL
  stack[0].ival = F_GETFL;
  return 0;
#else
  return env->die(env, stack, "F_GETFL is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETLEASE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETLEASE
  stack[0].ival = F_GETLEASE;
  return 0;
#else
  return env->die(env, stack, "F_GETLEASE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETLK
  stack[0].ival = F_GETLK;
  return 0;
#else
  return env->die(env, stack, "F_GETLK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETLK64(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETLK64
  stack[0].ival = F_GETLK64;
  return 0;
#else
  return env->die(env, stack, "F_GETLK64 is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETOWN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETOWN
  stack[0].ival = F_GETOWN;
  return 0;
#else
  return env->die(env, stack, "F_GETOWN is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETOWN_EX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETOWN_EX
  stack[0].ival = F_GETOWN_EX;
  return 0;
#else
  return env->die(env, stack, "F_GETOWN_EX is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETPIPE_SZ(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETPIPE_SZ
  stack[0].ival = F_GETPIPE_SZ;
  return 0;
#else
  return env->die(env, stack, "F_GETPIPE_SZ is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GETSIG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GETSIG
  stack[0].ival = F_GETSIG;
  return 0;
#else
  return env->die(env, stack, "F_GETSIG is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GET_FILE_RW_HINT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GET_FILE_RW_HINT
  stack[0].ival = F_GET_FILE_RW_HINT;
  return 0;
#else
  return env->die(env, stack, "F_GET_FILE_RW_HINT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GET_RW_HINT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GET_RW_HINT
  stack[0].ival = F_GET_RW_HINT;
  return 0;
#else
  return env->die(env, stack, "F_GET_RW_HINT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_GET_SEALS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_GET_SEALS
  stack[0].ival = F_GET_SEALS;
  return 0;
#else
  return env->die(env, stack, "F_GET_SEALS is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_NOTIFY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_NOTIFY
  stack[0].ival = F_NOTIFY;
  return 0;
#else
  return env->die(env, stack, "F_NOTIFY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OFD_GETLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OFD_GETLK
  stack[0].ival = F_OFD_GETLK;
  return 0;
#else
  return env->die(env, stack, "F_OFD_GETLK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OFD_SETLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OFD_SETLK
  stack[0].ival = F_OFD_SETLK;
  return 0;
#else
  return env->die(env, stack, "F_OFD_SETLK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OFD_SETLKW(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OFD_SETLKW
  stack[0].ival = F_OFD_SETLKW;
  return 0;
#else
  return env->die(env, stack, "F_OFD_SETLKW is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OWNER_PGRP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OWNER_PGRP
  stack[0].ival = F_OWNER_PGRP;
  return 0;
#else
  return env->die(env, stack, "F_OWNER_PGRP is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OWNER_PID(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OWNER_PID
  stack[0].ival = F_OWNER_PID;
  return 0;
#else
  return env->die(env, stack, "F_OWNER_PID is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_OWNER_TID(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_OWNER_TID
  stack[0].ival = F_OWNER_TID;
  return 0;
#else
  return env->die(env, stack, "F_OWNER_TID is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_RDLCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_RDLCK
  stack[0].ival = F_RDLCK;
  return 0;
#else
  return env->die(env, stack, "F_RDLCK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SEAL_FUTURE_WRITE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SEAL_FUTURE_WRITE
  stack[0].ival = F_SEAL_FUTURE_WRITE;
  return 0;
#else
  return env->die(env, stack, "F_SEAL_FUTURE_WRITE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SEAL_GROW(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SEAL_GROW
  stack[0].ival = F_SEAL_GROW;
  return 0;
#else
  return env->die(env, stack, "F_SEAL_GROW is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SEAL_SEAL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SEAL_SEAL
  stack[0].ival = F_SEAL_SEAL;
  return 0;
#else
  return env->die(env, stack, "F_SEAL_SEAL is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SEAL_SHRINK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SEAL_SHRINK
  stack[0].ival = F_SEAL_SHRINK;
  return 0;
#else
  return env->die(env, stack, "F_SEAL_SHRINK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SEAL_WRITE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SEAL_WRITE
  stack[0].ival = F_SEAL_WRITE;
  return 0;
#else
  return env->die(env, stack, "F_SEAL_WRITE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETFD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETFD
  stack[0].ival = F_SETFD;
  return 0;
#else
  return env->die(env, stack, "F_SETFD is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETFL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETFL
  stack[0].ival = F_SETFL;
  return 0;
#else
  return env->die(env, stack, "F_SETFL is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETLEASE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETLEASE
  stack[0].ival = F_SETLEASE;
  return 0;
#else
  return env->die(env, stack, "F_SETLEASE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETLK
  stack[0].ival = F_SETLK;
  return 0;
#else
  return env->die(env, stack, "F_SETLK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETLKW(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETLKW
  stack[0].ival = F_SETLKW;
  return 0;
#else
  return env->die(env, stack, "F_SETLKW is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETOWN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETOWN
  stack[0].ival = F_SETOWN;
  return 0;
#else
  return env->die(env, stack, "F_SETOWN is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETOWN_EX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETOWN_EX
  stack[0].ival = F_SETOWN_EX;
  return 0;
#else
  return env->die(env, stack, "F_SETOWN_EX is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETPIPE_SZ(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETPIPE_SZ
  stack[0].ival = F_SETPIPE_SZ;
  return 0;
#else
  return env->die(env, stack, "F_SETPIPE_SZ is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SETSIG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SETSIG
  stack[0].ival = F_SETSIG;
  return 0;
#else
  return env->die(env, stack, "F_SETSIG is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SET_FILE_RW_HINT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SET_FILE_RW_HINT
  stack[0].ival = F_SET_FILE_RW_HINT;
  return 0;
#else
  return env->die(env, stack, "F_SET_FILE_RW_HINT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_SET_RW_HINT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_SET_RW_HINT
  stack[0].ival = F_SET_RW_HINT;
  return 0;
#else
  return env->die(env, stack, "F_SET_RW_HINT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_UNLCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_UNLCK
  stack[0].ival = F_UNLCK;
  return 0;
#else
  return env->die(env, stack, "F_UNLCK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__F_WRLCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef F_WRLCK
  stack[0].ival = F_WRLCK;
  return 0;
#else
  return env->die(env, stack, "F_WRLCK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_APPEND(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_APPEND
  stack[0].ival = O_APPEND;
  return 0;
#else
  return env->die(env, stack, "O_APPEND is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_ASYNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_ASYNC
  stack[0].ival = O_ASYNC;
  return 0;
#else
  return env->die(env, stack, "O_ASYNC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_CLOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_CLOEXEC
  stack[0].ival = O_CLOEXEC;
  return 0;
#else
  return env->die(env, stack, "O_CLOEXEC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_CREAT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_CREAT
  stack[0].ival = O_CREAT;
  return 0;
#else
  return env->die(env, stack, "O_CREAT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_DIRECT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_DIRECT
  stack[0].ival = O_DIRECT;
  return 0;
#else
  return env->die(env, stack, "O_DIRECT is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_DIRECTORY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_DIRECTORY
  stack[0].ival = O_DIRECTORY;
  return 0;
#else
  return env->die(env, stack, "O_DIRECTORY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_DSYNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_DSYNC
  stack[0].ival = O_DSYNC;
  return 0;
#else
  return env->die(env, stack, "O_DSYNC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_EXCL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_EXCL
  stack[0].ival = O_EXCL;
  return 0;
#else
  return env->die(env, stack, "O_EXCL is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_LARGEFILE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_LARGEFILE
  stack[0].ival = O_LARGEFILE;
  return 0;
#else
  return env->die(env, stack, "O_LARGEFILE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_NOATIME(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_NOATIME
  stack[0].ival = O_NOATIME;
  return 0;
#else
  return env->die(env, stack, "O_NOATIME is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_NOCTTY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_NOCTTY
  stack[0].ival = O_NOCTTY;
  return 0;
#else
  return env->die(env, stack, "O_NOCTTY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_NOFOLLOW(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_NOFOLLOW
  stack[0].ival = O_NOFOLLOW;
  return 0;
#else
  return env->die(env, stack, "O_NOFOLLOW is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_NONBLOCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_NONBLOCK
  stack[0].ival = O_NONBLOCK;
  return 0;
#else
  return env->die(env, stack, "O_NONBLOCK is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_PATH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_PATH
  stack[0].ival = O_PATH;
  return 0;
#else
  return env->die(env, stack, "O_PATH is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_RDONLY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_RDONLY
  stack[0].ival = O_RDONLY;
  return 0;
#else
  return env->die(env, stack, "O_RDONLY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_RDWR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_RDWR
  stack[0].ival = O_RDWR;
  return 0;
#else
  return env->die(env, stack, "O_RDWR is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_SYNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_SYNC
  stack[0].ival = O_SYNC;
  return 0;
#else
  return env->die(env, stack, "O_SYNC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_TMPFILE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_TMPFILE
  stack[0].ival = O_TMPFILE;
  return 0;
#else
  return env->die(env, stack, "O_TMPFILE is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_TRUNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_TRUNC
  stack[0].ival = O_TRUNC;
  return 0;
#else
  return env->die(env, stack, "O_TRUNC is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}

int32_t SPVM__Sys__Fcntl__O_WRONLY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef O_WRONLY
  stack[0].ival = O_WRONLY;
  return 0;
#else
  return env->die(env, stack, "O_WRONLY is not defined in this system", FILE_NAME, __LINE__);
#endif
  
}



