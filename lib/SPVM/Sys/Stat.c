#include "spvm_native.h"

#include <sys/stat.h>

const char* FILE_NAME = "Errno.c";


int32_t SPVM__Sys__Stat__S_CDF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_CDF
  stack[0].ival = S_CDF;
  return 0;
#else
  return env->die(env, stack, "S_CDF is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ENFMT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ENFMT
  stack[0].ival = S_ENFMT;
  return 0;
#else
  return env->die(env, stack, "S_ENFMT is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IF
  stack[0].ival = S_IF;
  return 0;
#else
  return env->die(env, stack, "S_IF is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFBLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFBLK
  stack[0].ival = S_IFBLK;
  return 0;
#else
  return env->die(env, stack, "S_IFBLK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFCHR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFCHR
  stack[0].ival = S_IFCHR;
  return 0;
#else
  return env->die(env, stack, "S_IFCHR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFCMP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFCMP
  stack[0].ival = S_IFCMP;
  return 0;
#else
  return env->die(env, stack, "S_IFCMP is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFDIR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFDIR
  stack[0].ival = S_IFDIR;
  return 0;
#else
  return env->die(env, stack, "S_IFDIR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFDOOR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFDOOR
  stack[0].ival = S_IFDOOR;
  return 0;
#else
  return env->die(env, stack, "S_IFDOOR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFIFO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFIFO
  stack[0].ival = S_IFIFO;
  return 0;
#else
  return env->die(env, stack, "S_IFIFO is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFLNK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFLNK
  stack[0].ival = S_IFLNK;
  return 0;
#else
  return env->die(env, stack, "S_IFLNK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFMPB(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFMPB
  stack[0].ival = S_IFMPB;
  return 0;
#else
  return env->die(env, stack, "S_IFMPB is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFMPC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFMPC
  stack[0].ival = S_IFMPC;
  return 0;
#else
  return env->die(env, stack, "S_IFMPC is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFMT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFMT
  stack[0].ival = S_IFMT;
  return 0;
#else
  return env->die(env, stack, "S_IFMT is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFNAM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFNAM
  stack[0].ival = S_IFNAM;
  return 0;
#else
  return env->die(env, stack, "S_IFNAM is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFNWK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFNWK
  stack[0].ival = S_IFNWK;
  return 0;
#else
  return env->die(env, stack, "S_IFNWK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFREG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFREG
  stack[0].ival = S_IFREG;
  return 0;
#else
  return env->die(env, stack, "S_IFREG is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFSHAD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFSHAD
  stack[0].ival = S_IFSHAD;
  return 0;
#else
  return env->die(env, stack, "S_IFSHAD is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFSOCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFSOCK
  stack[0].ival = S_IFSOCK;
  return 0;
#else
  return env->die(env, stack, "S_IFSOCK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IFWHT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IFWHT
  stack[0].ival = S_IFWHT;
  return 0;
#else
  return env->die(env, stack, "S_IFWHT is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_INSEM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_INSEM
  stack[0].ival = S_INSEM;
  return 0;
#else
  return env->die(env, stack, "S_INSEM is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_INSHD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_INSHD
  stack[0].ival = S_INSHD;
  return 0;
#else
  return env->die(env, stack, "S_INSHD is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IREAD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IREAD
  stack[0].ival = S_IREAD;
  return 0;
#else
  return env->die(env, stack, "S_IREAD is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IRGRP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IRGRP
  stack[0].ival = S_IRGRP;
  return 0;
#else
  return env->die(env, stack, "S_IRGRP is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IROTH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IROTH
  stack[0].ival = S_IROTH;
  return 0;
#else
  return env->die(env, stack, "S_IROTH is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IRUSR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IRUSR
  stack[0].ival = S_IRUSR;
  return 0;
#else
  return env->die(env, stack, "S_IRUSR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IRWXG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IRWXG
  stack[0].ival = S_IRWXG;
  return 0;
#else
  return env->die(env, stack, "S_IRWXG is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IRWXO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IRWXO
  stack[0].ival = S_IRWXO;
  return 0;
#else
  return env->die(env, stack, "S_IRWXO is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IRWXU(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IRWXU
  stack[0].ival = S_IRWXU;
  return 0;
#else
  return env->die(env, stack, "S_IRWXU is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISBLK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISBLK
  stack[0].ival = S_ISBLK(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISBLK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISCHR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISCHR
  stack[0].ival = S_ISCHR(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISCHR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISDIR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISDIR
  stack[0].ival = S_ISDIR(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISDIR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISFIFO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISFIFO
  stack[0].ival = S_ISFIFO(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISFIFO is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISGID(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISGID
  stack[0].ival = S_ISGID;
  return 0;
#else
  return env->die(env, stack, "S_ISGID is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISLNK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISLNK
  stack[0].ival = S_ISLNK(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISLNK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISREG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISREG
  stack[0].ival = S_ISREG(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISREG is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISSOCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISSOCK
  stack[0].ival = S_ISSOCK(stack[0].ival);
  return 0;
#else
  return env->die(env, stack, "S_ISSOCK is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISUID(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISUID
  stack[0].ival = S_ISUID;
  return 0;
#else
  return env->die(env, stack, "S_ISUID is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_ISVTX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_ISVTX
  stack[0].ival = S_ISVTX;
  return 0;
#else
  return env->die(env, stack, "S_ISVTX is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IWGRP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IWGRP
  stack[0].ival = S_IWGRP;
  return 0;
#else
  return env->die(env, stack, "S_IWGRP is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IWOTH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IWOTH
  stack[0].ival = S_IWOTH;
  return 0;
#else
  return env->die(env, stack, "S_IWOTH is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IWUSR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IWUSR
  stack[0].ival = S_IWUSR;
  return 0;
#else
  return env->die(env, stack, "S_IWUSR is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IXGRP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IXGRP
  stack[0].ival = S_IXGRP;
  return 0;
#else
  return env->die(env, stack, "S_IXGRP is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IXOTH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IXOTH
  stack[0].ival = S_IXOTH;
  return 0;
#else
  return env->die(env, stack, "S_IXOTH is not defined in this system", FILE_NAME, __LINE__);
#endif

}

int32_t SPVM__Sys__Stat__S_IXUSR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef S_IXUSR
  stack[0].ival = S_IXUSR;
  return 0;
#else
  return env->die(env, stack, "S_IXUSR is not defined in this system", FILE_NAME, __LINE__);
#endif

}
