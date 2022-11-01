#include "spvm_native.h"



static const char* FILE_NAME = "Sys/Signal/Constant.c";

int32_t SPVM__Sys__Signal__Constant__BUS_ADRALN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_ADRALN
  stack[0].ival = BUS_ADRALN;
  return 0;
#else
  env->die(env, stack, "BUS_ADRALN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__BUS_ADRERR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_ADRERR
  stack[0].ival = BUS_ADRERR;
  return 0;
#else
  env->die(env, stack, "BUS_ADRERR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__BUS_MCEERR_AO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_MCEERR_AO
  stack[0].ival = BUS_MCEERR_AO;
  return 0;
#else
  env->die(env, stack, "BUS_MCEERR_AO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__BUS_MCEERR_AR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_MCEERR_AR
  stack[0].ival = BUS_MCEERR_AR;
  return 0;
#else
  env->die(env, stack, "BUS_MCEERR_AR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__BUS_MCERR_(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_MCERR_
  stack[0].ival = BUS_MCERR_;
  return 0;
#else
  env->die(env, stack, "BUS_MCERR_ is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__BUS_OBJERR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef BUS_OBJERR
  stack[0].ival = BUS_OBJERR;
  return 0;
#else
  env->die(env, stack, "BUS_OBJERR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_CONTINUED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_CONTINUED
  stack[0].ival = CLD_CONTINUED;
  return 0;
#else
  env->die(env, stack, "CLD_CONTINUED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_DUMPED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_DUMPED
  stack[0].ival = CLD_DUMPED;
  return 0;
#else
  env->die(env, stack, "CLD_DUMPED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_EXITED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_EXITED
  stack[0].ival = CLD_EXITED;
  return 0;
#else
  env->die(env, stack, "CLD_EXITED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_KILLED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_KILLED
  stack[0].ival = CLD_KILLED;
  return 0;
#else
  env->die(env, stack, "CLD_KILLED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_STOPPED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_STOPPED
  stack[0].ival = CLD_STOPPED;
  return 0;
#else
  env->die(env, stack, "CLD_STOPPED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__CLD_TRAPPED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef CLD_TRAPPED
  stack[0].ival = CLD_TRAPPED;
  return 0;
#else
  env->die(env, stack, "CLD_TRAPPED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTDIV(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTDIV
  stack[0].ival = FPE_FLTDIV;
  return 0;
#else
  env->die(env, stack, "FPE_FLTDIV is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTINV(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTINV
  stack[0].ival = FPE_FLTINV;
  return 0;
#else
  env->die(env, stack, "FPE_FLTINV is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTOVF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTOVF
  stack[0].ival = FPE_FLTOVF;
  return 0;
#else
  env->die(env, stack, "FPE_FLTOVF is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTRES(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTRES
  stack[0].ival = FPE_FLTRES;
  return 0;
#else
  env->die(env, stack, "FPE_FLTRES is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTSUB(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTSUB
  stack[0].ival = FPE_FLTSUB;
  return 0;
#else
  env->die(env, stack, "FPE_FLTSUB is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_FLTUND(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_FLTUND
  stack[0].ival = FPE_FLTUND;
  return 0;
#else
  env->die(env, stack, "FPE_FLTUND is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_INTDIV(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_INTDIV
  stack[0].ival = FPE_INTDIV;
  return 0;
#else
  env->die(env, stack, "FPE_INTDIV is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FPE_INTOVF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FPE_INTOVF
  stack[0].ival = FPE_INTOVF;
  return 0;
#else
  env->die(env, stack, "FPE_INTOVF is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__FUTEX_WAIT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef FUTEX_WAIT
  stack[0].ival = FUTEX_WAIT;
  return 0;
#else
  env->die(env, stack, "FUTEX_WAIT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_BADSTK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_BADSTK
  stack[0].ival = ILL_BADSTK;
  return 0;
#else
  env->die(env, stack, "ILL_BADSTK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_COPROC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_COPROC
  stack[0].ival = ILL_COPROC;
  return 0;
#else
  env->die(env, stack, "ILL_COPROC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_ILLADR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_ILLADR
  stack[0].ival = ILL_ILLADR;
  return 0;
#else
  env->die(env, stack, "ILL_ILLADR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_ILLOPC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_ILLOPC
  stack[0].ival = ILL_ILLOPC;
  return 0;
#else
  env->die(env, stack, "ILL_ILLOPC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_ILLOPN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_ILLOPN
  stack[0].ival = ILL_ILLOPN;
  return 0;
#else
  env->die(env, stack, "ILL_ILLOPN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_ILLTRP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_ILLTRP
  stack[0].ival = ILL_ILLTRP;
  return 0;
#else
  env->die(env, stack, "ILL_ILLTRP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_PRVOPC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_PRVOPC
  stack[0].ival = ILL_PRVOPC;
  return 0;
#else
  env->die(env, stack, "ILL_PRVOPC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__ILL_PRVREG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef ILL_PRVREG
  stack[0].ival = ILL_PRVREG;
  return 0;
#else
  env->die(env, stack, "ILL_PRVREG is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_ERR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_ERR
  stack[0].ival = POLL_ERR;
  return 0;
#else
  env->die(env, stack, "POLL_ERR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_HUP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_HUP
  stack[0].ival = POLL_HUP;
  return 0;
#else
  env->die(env, stack, "POLL_HUP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_IN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_IN
  stack[0].ival = POLL_IN;
  return 0;
#else
  env->die(env, stack, "POLL_IN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_MSG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_MSG
  stack[0].ival = POLL_MSG;
  return 0;
#else
  env->die(env, stack, "POLL_MSG is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_OUT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_OUT
  stack[0].ival = POLL_OUT;
  return 0;
#else
  env->die(env, stack, "POLL_OUT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__POLL_PRI(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef POLL_PRI
  stack[0].ival = POLL_PRI;
  return 0;
#else
  env->die(env, stack, "POLL_PRI is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGBUS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGBUS
  stack[0].ival = SIGBUS;
  return 0;
#else
  env->die(env, stack, "SIGBUS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGCHLD(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGCHLD
  stack[0].ival = SIGCHLD;
  return 0;
#else
  env->die(env, stack, "SIGCHLD is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGCONT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGCONT
  stack[0].ival = SIGCONT;
  return 0;
#else
  env->die(env, stack, "SIGCONT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGEMT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGEMT
  stack[0].ival = SIGEMT;
  return 0;
#else
  env->die(env, stack, "SIGEMT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGEV_SIGNAL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGEV_SIGNAL
  stack[0].ival = SIGEV_SIGNAL;
  return 0;
#else
  env->die(env, stack, "SIGEV_SIGNAL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGFPE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGFPE
  stack[0].ival = SIGFPE;
  return 0;
#else
  env->die(env, stack, "SIGFPE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGILL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGILL
  stack[0].ival = SIGILL;
  return 0;
#else
  env->die(env, stack, "SIGILL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGINFO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGINFO
  stack[0].ival = SIGINFO;
  return 0;
#else
  env->die(env, stack, "SIGINFO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGIO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGIO
  stack[0].ival = SIGIO;
  return 0;
#else
  env->die(env, stack, "SIGIO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGKILL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGKILL
  stack[0].ival = SIGKILL;
  return 0;
#else
  env->die(env, stack, "SIGKILL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGLOST(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGLOST
  stack[0].ival = SIGLOST;
  return 0;
#else
  env->die(env, stack, "SIGLOST is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGPOLL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGPOLL
  stack[0].ival = SIGPOLL;
  return 0;
#else
  env->die(env, stack, "SIGPOLL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGPWR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGPWR
  stack[0].ival = SIGPWR;
  return 0;
#else
  env->die(env, stack, "SIGPWR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGRTMAX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGRTMAX
  stack[0].ival = SIGRTMAX;
  return 0;
#else
  env->die(env, stack, "SIGRTMAX is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGRTMIN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGRTMIN
  stack[0].ival = SIGRTMIN;
  return 0;
#else
  env->die(env, stack, "SIGRTMIN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGSEGV(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGSEGV
  stack[0].ival = SIGSEGV;
  return 0;
#else
  env->die(env, stack, "SIGSEGV is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGSTOP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGSTOP
  stack[0].ival = SIGSTOP;
  return 0;
#else
  env->die(env, stack, "SIGSTOP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGSYS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGSYS
  stack[0].ival = SIGSYS;
  return 0;
#else
  env->die(env, stack, "SIGSYS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGTRAP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGTRAP
  stack[0].ival = SIGTRAP;
  return 0;
#else
  env->die(env, stack, "SIGTRAP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGTSTP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGTSTP
  stack[0].ival = SIGTSTP;
  return 0;
#else
  env->die(env, stack, "SIGTSTP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGTTIN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGTTIN
  stack[0].ival = SIGTTIN;
  return 0;
#else
  env->die(env, stack, "SIGTTIN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGTTOU(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGTTOU
  stack[0].ival = SIGTTOU;
  return 0;
#else
  env->die(env, stack, "SIGTTOU is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGUNUSED(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGUNUSED
  stack[0].ival = SIGUNUSED;
  return 0;
#else
  env->die(env, stack, "SIGUNUSED is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGXCPU(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGXCPU
  stack[0].ival = SIGXCPU;
  return 0;
#else
  env->die(env, stack, "SIGXCPU is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIGXFSZ(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIGXFSZ
  stack[0].ival = SIGXFSZ;
  return 0;
#else
  env->die(env, stack, "SIGXFSZ is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_ASYNCIO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_ASYNCIO
  stack[0].ival = SI_ASYNCIO;
  return 0;
#else
  env->die(env, stack, "SI_ASYNCIO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_KERNEL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_KERNEL
  stack[0].ival = SI_KERNEL;
  return 0;
#else
  env->die(env, stack, "SI_KERNEL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_MESGQ(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_MESGQ
  stack[0].ival = SI_MESGQ;
  return 0;
#else
  env->die(env, stack, "SI_MESGQ is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_QUEUE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_QUEUE
  stack[0].ival = SI_QUEUE;
  return 0;
#else
  env->die(env, stack, "SI_QUEUE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_SIGIO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_SIGIO
  stack[0].ival = SI_SIGIO;
  return 0;
#else
  env->die(env, stack, "SI_SIGIO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_TIMER(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_TIMER
  stack[0].ival = SI_TIMER;
  return 0;
#else
  env->die(env, stack, "SI_TIMER is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_TKILL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_TKILL
  stack[0].ival = SI_TKILL;
  return 0;
#else
  env->die(env, stack, "SI_TKILL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SI_USER(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SI_USER
  stack[0].ival = SI_USER;
  return 0;
#else
  env->die(env, stack, "SI_USER is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__TRAP_BRANCH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef TRAP_BRANCH
  stack[0].ival = TRAP_BRANCH;
  return 0;
#else
  env->die(env, stack, "TRAP_BRANCH is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__TRAP_BRKPT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef TRAP_BRKPT
  stack[0].ival = TRAP_BRKPT;
  return 0;
#else
  env->die(env, stack, "TRAP_BRKPT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__TRAP_HWBKPT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef TRAP_HWBKPT
  stack[0].ival = TRAP_HWBKPT;
  return 0;
#else
  env->die(env, stack, "TRAP_HWBKPT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__TRAP_TRACE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef TRAP_TRACE
  stack[0].ival = TRAP_TRACE;
  return 0;
#else
  env->die(env, stack, "TRAP_TRACE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

/*

int32_t SPVM__Sys__Signal__Constant__SIG_DFL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIG_DFL
  stack[0].ival = SIG_DFL;
  return 0;
#else
  env->die(env, stack, "SIG_DFL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIG_ERR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIG_ERR
  stack[0].ival = SIG_ERR;
  return 0;
#else
  env->die(env, stack, "SIG_ERR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

int32_t SPVM__Sys__Signal__Constant__SIG_IGN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SIG_IGN
  stack[0].ival = SIG_IGN;
  return 0;
#else
  env->die(env, stack, "SIG_IGN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif

}

*/