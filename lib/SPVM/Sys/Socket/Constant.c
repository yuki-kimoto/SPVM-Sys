#include "spvm_native.h"

#include "spvm_native.h"

#include <errno.h>
#include <assert.h>

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

static const char* FILE_NAME = "Sys/Socket/Constant.c";


int32_t SPVM__Sys__Socket__Constant__AF_ALG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_ALG
  stack[0].ival = AF_ALG;
  return 0;
#else
  env->die(env, stack, "AF_ALG is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_APPLETALK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_APPLETALK
  stack[0].ival = AF_APPLETALK;
  return 0;
#else
  env->die(env, stack, "AF_APPLETALK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_AX25(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_AX25
  stack[0].ival = AF_AX25;
  return 0;
#else
  env->die(env, stack, "AF_AX25 is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_BLUETOOTH(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_BLUETOOTH
  stack[0].ival = AF_BLUETOOTH;
  return 0;
#else
  env->die(env, stack, "AF_BLUETOOTH is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_CAN(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_CAN
  stack[0].ival = AF_CAN;
  return 0;
#else
  env->die(env, stack, "AF_CAN is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_DEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_DEC
  stack[0].ival = AF_DEC;
  return 0;
#else
  env->die(env, stack, "AF_DEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_IB(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_IB
  stack[0].ival = AF_IB;
  return 0;
#else
  env->die(env, stack, "AF_IB is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_INET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_INET
  stack[0].ival = AF_INET;
  return 0;
#else
  env->die(env, stack, "AF_INET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_INET6(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_INET6
  stack[0].ival = AF_INET6;
  return 0;
#else
  env->die(env, stack, "AF_INET6 is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_IPX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_IPX
  stack[0].ival = AF_IPX;
  return 0;
#else
  env->die(env, stack, "AF_IPX is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_KCM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_KCM
  stack[0].ival = AF_KCM;
  return 0;
#else
  env->die(env, stack, "AF_KCM is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_KEY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_KEY
  stack[0].ival = AF_KEY;
  return 0;
#else
  env->die(env, stack, "AF_KEY is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_LLC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_LLC
  stack[0].ival = AF_LLC;
  return 0;
#else
  env->die(env, stack, "AF_LLC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_LOCAL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_LOCAL
  stack[0].ival = AF_LOCAL;
  return 0;
#else
  env->die(env, stack, "AF_LOCAL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_MPLS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_MPLS
  stack[0].ival = AF_MPLS;
  return 0;
#else
  env->die(env, stack, "AF_MPLS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_NETLINK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_NETLINK
  stack[0].ival = AF_NETLINK;
  return 0;
#else
  env->die(env, stack, "AF_NETLINK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_PACKET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_PACKET
  stack[0].ival = AF_PACKET;
  return 0;
#else
  env->die(env, stack, "AF_PACKET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_PPPOX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_PPPOX
  stack[0].ival = AF_PPPOX;
  return 0;
#else
  env->die(env, stack, "AF_PPPOX is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_RDS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_RDS
  stack[0].ival = AF_RDS;
  return 0;
#else
  env->die(env, stack, "AF_RDS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_TIPC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_TIPC
  stack[0].ival = AF_TIPC;
  return 0;
#else
  env->die(env, stack, "AF_TIPC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_UNIX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_UNIX
  stack[0].ival = AF_UNIX;
  return 0;
#else
  env->die(env, stack, "AF_UNIX is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_UNSPEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_UNSPEC
  stack[0].ival = AF_UNSPEC;
  return 0;
#else
  env->die(env, stack, "AF_UNSPEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_VSOCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_VSOCK
  stack[0].ival = AF_VSOCK;
  return 0;
#else
  env->die(env, stack, "AF_VSOCK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_X25(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_X25
  stack[0].ival = AF_X25;
  return 0;
#else
  env->die(env, stack, "AF_X25 is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__AF_XDP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef AF_XDP
  stack[0].ival = AF_XDP;
  return 0;
#else
  env->die(env, stack, "AF_XDP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__INADDR_ANY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef INADDR_ANY
  stack[0].ival = INADDR_ANY;
  return 0;
#else
  env->die(env, stack, "INADDR_ANY is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__INADDR_BROADCAST(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef INADDR_BROADCAST
  stack[0].ival = INADDR_BROADCAST;
  return 0;
#else
  env->die(env, stack, "INADDR_BROADCAST is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__INADDR_LOOPBACK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef INADDR_LOOPBACK
  stack[0].ival = INADDR_LOOPBACK;
  return 0;
#else
  env->die(env, stack, "INADDR_LOOPBACK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPPROTO_IP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPPROTO_IP
  stack[0].ival = IPPROTO_IP;
  return 0;
#else
  env->die(env, stack, "IPPROTO_IP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPPROTO_SCTP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPPROTO_SCTP
  stack[0].ival = IPPROTO_SCTP;
  return 0;
#else
  env->die(env, stack, "IPPROTO_SCTP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPPROTO_TCP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPPROTO_TCP
  stack[0].ival = IPPROTO_TCP;
  return 0;
#else
  env->die(env, stack, "IPPROTO_TCP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPPROTO_UDP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPPROTO_UDP
  stack[0].ival = IPPROTO_UDP;
  return 0;
#else
  env->die(env, stack, "IPPROTO_UDP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPPROTO_UDPLITE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPPROTO_UDPLITE
  stack[0].ival = IPPROTO_UDPLITE;
  return 0;
#else
  env->die(env, stack, "IPPROTO_UDPLITE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPTOS_LOWDELAY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPTOS_LOWDELAY
  stack[0].ival = IPTOS_LOWDELAY;
  return 0;
#else
  env->die(env, stack, "IPTOS_LOWDELAY is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPTOS_MINCOST(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPTOS_MINCOST
  stack[0].ival = IPTOS_MINCOST;
  return 0;
#else
  env->die(env, stack, "IPTOS_MINCOST is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPTOS_RELIABILITY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPTOS_RELIABILITY
  stack[0].ival = IPTOS_RELIABILITY;
  return 0;
#else
  env->die(env, stack, "IPTOS_RELIABILITY is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IPTOS_THROUGHPUT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IPTOS_THROUGHPUT
  stack[0].ival = IPTOS_THROUGHPUT;
  return 0;
#else
  env->die(env, stack, "IPTOS_THROUGHPUT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_ADD_MEMBERSHIP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_ADD_MEMBERSHIP
  stack[0].ival = IP_ADD_MEMBERSHIP;
  return 0;
#else
  env->die(env, stack, "IP_ADD_MEMBERSHIP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_ADD_SOURCE_MEMBERSHIP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_ADD_SOURCE_MEMBERSHIP
  stack[0].ival = IP_ADD_SOURCE_MEMBERSHIP;
  return 0;
#else
  env->die(env, stack, "IP_ADD_SOURCE_MEMBERSHIP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_BIND_ADDRESS_NO_PORT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_BIND_ADDRESS_NO_PORT
  stack[0].ival = IP_BIND_ADDRESS_NO_PORT;
  return 0;
#else
  env->die(env, stack, "IP_BIND_ADDRESS_NO_PORT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_BLOCK_SOURCE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_BLOCK_SOURCE
  stack[0].ival = IP_BLOCK_SOURCE;
  return 0;
#else
  env->die(env, stack, "IP_BLOCK_SOURCE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_DROP_MEMBERSHIP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_DROP_MEMBERSHIP
  stack[0].ival = IP_DROP_MEMBERSHIP;
  return 0;
#else
  env->die(env, stack, "IP_DROP_MEMBERSHIP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_DROP_SOURCE_MEMBERSHIP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_DROP_SOURCE_MEMBERSHIP
  stack[0].ival = IP_DROP_SOURCE_MEMBERSHIP;
  return 0;
#else
  env->die(env, stack, "IP_DROP_SOURCE_MEMBERSHIP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_FREEBIND(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_FREEBIND
  stack[0].ival = IP_FREEBIND;
  return 0;
#else
  env->die(env, stack, "IP_FREEBIND is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_HDRINCL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_HDRINCL
  stack[0].ival = IP_HDRINCL;
  return 0;
#else
  env->die(env, stack, "IP_HDRINCL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MSFILTER(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MSFILTER
  stack[0].ival = IP_MSFILTER;
  return 0;
#else
  env->die(env, stack, "IP_MSFILTER is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MTU(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MTU
  stack[0].ival = IP_MTU;
  return 0;
#else
  env->die(env, stack, "IP_MTU is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MTU_DISCOVER(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MTU_DISCOVER
  stack[0].ival = IP_MTU_DISCOVER;
  return 0;
#else
  env->die(env, stack, "IP_MTU_DISCOVER is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MULTICAST_ALL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MULTICAST_ALL
  stack[0].ival = IP_MULTICAST_ALL;
  return 0;
#else
  env->die(env, stack, "IP_MULTICAST_ALL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MULTICAST_IF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MULTICAST_IF
  stack[0].ival = IP_MULTICAST_IF;
  return 0;
#else
  env->die(env, stack, "IP_MULTICAST_IF is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MULTICAST_LOOP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MULTICAST_LOOP
  stack[0].ival = IP_MULTICAST_LOOP;
  return 0;
#else
  env->die(env, stack, "IP_MULTICAST_LOOP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_MULTICAST_TTL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_MULTICAST_TTL
  stack[0].ival = IP_MULTICAST_TTL;
  return 0;
#else
  env->die(env, stack, "IP_MULTICAST_TTL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_NODEFRAG(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_NODEFRAG
  stack[0].ival = IP_NODEFRAG;
  return 0;
#else
  env->die(env, stack, "IP_NODEFRAG is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_OPTION(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_OPTION
  stack[0].ival = IP_OPTION;
  return 0;
#else
  env->die(env, stack, "IP_OPTION is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_OPTIONS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_OPTIONS
  stack[0].ival = IP_OPTIONS;
  return 0;
#else
  env->die(env, stack, "IP_OPTIONS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_ORIGDSTADDR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_ORIGDSTADDR
  stack[0].ival = IP_ORIGDSTADDR;
  return 0;
#else
  env->die(env, stack, "IP_ORIGDSTADDR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PASSSEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PASSSEC
  stack[0].ival = IP_PASSSEC;
  return 0;
#else
  env->die(env, stack, "IP_PASSSEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PKTINFO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PKTINFO
  stack[0].ival = IP_PKTINFO;
  return 0;
#else
  env->die(env, stack, "IP_PKTINFO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PMTUDISC_DO(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PMTUDISC_DO
  stack[0].ival = IP_PMTUDISC_DO;
  return 0;
#else
  env->die(env, stack, "IP_PMTUDISC_DO is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PMTUDISC_DONT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PMTUDISC_DONT
  stack[0].ival = IP_PMTUDISC_DONT;
  return 0;
#else
  env->die(env, stack, "IP_PMTUDISC_DONT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PMTUDISC_PROBE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PMTUDISC_PROBE
  stack[0].ival = IP_PMTUDISC_PROBE;
  return 0;
#else
  env->die(env, stack, "IP_PMTUDISC_PROBE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_PMTUDISC_WANT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_PMTUDISC_WANT
  stack[0].ival = IP_PMTUDISC_WANT;
  return 0;
#else
  env->die(env, stack, "IP_PMTUDISC_WANT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RCVDSTADDR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RCVDSTADDR
  stack[0].ival = IP_RCVDSTADDR;
  return 0;
#else
  env->die(env, stack, "IP_RCVDSTADDR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVERR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVERR
  stack[0].ival = IP_RECVERR;
  return 0;
#else
  env->die(env, stack, "IP_RECVERR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVIF(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVIF
  stack[0].ival = IP_RECVIF;
  return 0;
#else
  env->die(env, stack, "IP_RECVIF is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVOPTS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVOPTS
  stack[0].ival = IP_RECVOPTS;
  return 0;
#else
  env->die(env, stack, "IP_RECVOPTS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVORIGDSTADDR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVORIGDSTADDR
  stack[0].ival = IP_RECVORIGDSTADDR;
  return 0;
#else
  env->die(env, stack, "IP_RECVORIGDSTADDR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVTOS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVTOS
  stack[0].ival = IP_RECVTOS;
  return 0;
#else
  env->die(env, stack, "IP_RECVTOS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RECVTTL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RECVTTL
  stack[0].ival = IP_RECVTTL;
  return 0;
#else
  env->die(env, stack, "IP_RECVTTL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_RETOPTS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_RETOPTS
  stack[0].ival = IP_RETOPTS;
  return 0;
#else
  env->die(env, stack, "IP_RETOPTS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_ROUTER_ALERT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_ROUTER_ALERT
  stack[0].ival = IP_ROUTER_ALERT;
  return 0;
#else
  env->die(env, stack, "IP_ROUTER_ALERT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_TOS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_TOS
  stack[0].ival = IP_TOS;
  return 0;
#else
  env->die(env, stack, "IP_TOS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_TRANSPARENT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_TRANSPARENT
  stack[0].ival = IP_TRANSPARENT;
  return 0;
#else
  env->die(env, stack, "IP_TRANSPARENT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_TTL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_TTL
  stack[0].ival = IP_TTL;
  return 0;
#else
  env->die(env, stack, "IP_TTL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__IP_UNBLOCK_SOURCE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef IP_UNBLOCK_SOURCE
  stack[0].ival = IP_UNBLOCK_SOURCE;
  return 0;
#else
  env->die(env, stack, "IP_UNBLOCK_SOURCE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MCAST_EXCLUDE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MCAST_EXCLUDE
  stack[0].ival = MCAST_EXCLUDE;
  return 0;
#else
  env->die(env, stack, "MCAST_EXCLUDE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MCAST_INCLUDE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MCAST_INCLUDE
  stack[0].ival = MCAST_INCLUDE;
  return 0;
#else
  env->die(env, stack, "MCAST_INCLUDE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_CMSG_CLOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_CMSG_CLOEXEC
  stack[0].ival = MSG_CMSG_CLOEXEC;
  return 0;
#else
  env->die(env, stack, "MSG_CMSG_CLOEXEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_CONFIRM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_CONFIRM
  stack[0].ival = MSG_CONFIRM;
  return 0;
#else
  env->die(env, stack, "MSG_CONFIRM is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_CTRUNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_CTRUNC
  stack[0].ival = MSG_CTRUNC;
  return 0;
#else
  env->die(env, stack, "MSG_CTRUNC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_DONTROUTE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_DONTROUTE
  stack[0].ival = MSG_DONTROUTE;
  return 0;
#else
  env->die(env, stack, "MSG_DONTROUTE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_DONTWAIT(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_DONTWAIT
  stack[0].ival = MSG_DONTWAIT;
  return 0;
#else
  env->die(env, stack, "MSG_DONTWAIT is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_EOR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_EOR
  stack[0].ival = MSG_EOR;
  return 0;
#else
  env->die(env, stack, "MSG_EOR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_ERRQUEUE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_ERRQUEUE
  stack[0].ival = MSG_ERRQUEUE;
  return 0;
#else
  env->die(env, stack, "MSG_ERRQUEUE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_ERRQUIE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_ERRQUIE
  stack[0].ival = MSG_ERRQUIE;
  return 0;
#else
  env->die(env, stack, "MSG_ERRQUIE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_MORE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_MORE
  stack[0].ival = MSG_MORE;
  return 0;
#else
  env->die(env, stack, "MSG_MORE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_NOSIGNAL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_NOSIGNAL
  stack[0].ival = MSG_NOSIGNAL;
  return 0;
#else
  env->die(env, stack, "MSG_NOSIGNAL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_OOB(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_OOB
  stack[0].ival = MSG_OOB;
  return 0;
#else
  env->die(env, stack, "MSG_OOB is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_PEEK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_PEEK
  stack[0].ival = MSG_PEEK;
  return 0;
#else
  env->die(env, stack, "MSG_PEEK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_TRUNC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_TRUNC
  stack[0].ival = MSG_TRUNC;
  return 0;
#else
  env->die(env, stack, "MSG_TRUNC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__MSG_WAITALL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef MSG_WAITALL
  stack[0].ival = MSG_WAITALL;
  return 0;
#else
  env->die(env, stack, "MSG_WAITALL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__PF_INET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef PF_INET
  stack[0].ival = PF_INET;
  return 0;
#else
  env->die(env, stack, "PF_INET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__PF_UNIX(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef PF_UNIX
  stack[0].ival = PF_UNIX;
  return 0;
#else
  env->die(env, stack, "PF_UNIX is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SCM_RIGHTS(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SCM_RIGHTS
  stack[0].ival = SCM_RIGHTS;
  return 0;
#else
  env->die(env, stack, "SCM_RIGHTS is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SCM_SECURITY(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SCM_SECURITY
  stack[0].ival = SCM_SECURITY;
  return 0;
#else
  env->die(env, stack, "SCM_SECURITY is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_CLOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_CLOEXEC
  stack[0].ival = SOCK_CLOEXEC;
  return 0;
#else
  env->die(env, stack, "SOCK_CLOEXEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_DGRAM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_DGRAM
  stack[0].ival = SOCK_DGRAM;
  return 0;
#else
  env->die(env, stack, "SOCK_DGRAM is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_NONBLOCK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_NONBLOCK
  stack[0].ival = SOCK_NONBLOCK;
  return 0;
#else
  env->die(env, stack, "SOCK_NONBLOCK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_PACKET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_PACKET
  stack[0].ival = SOCK_PACKET;
  return 0;
#else
  env->die(env, stack, "SOCK_PACKET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_RAW(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_RAW
  stack[0].ival = SOCK_RAW;
  return 0;
#else
  env->die(env, stack, "SOCK_RAW is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_RDM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_RDM
  stack[0].ival = SOCK_RDM;
  return 0;
#else
  env->die(env, stack, "SOCK_RDM is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_SEQPACKET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_SEQPACKET
  stack[0].ival = SOCK_SEQPACKET;
  return 0;
#else
  env->die(env, stack, "SOCK_SEQPACKET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOCK_STREAM(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOCK_STREAM
  stack[0].ival = SOCK_STREAM;
  return 0;
#else
  env->die(env, stack, "SOCK_STREAM is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOL_IP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOL_IP
  stack[0].ival = SOL_IP;
  return 0;
#else
  env->die(env, stack, "SOL_IP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SOL_SOCKET(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SOL_SOCKET
  stack[0].ival = SOL_SOCKET;
  return 0;
#else
  env->die(env, stack, "SOL_SOCKET is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_BROADCAST(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_BROADCAST
  stack[0].ival = SO_BROADCAST;
  return 0;
#else
  env->die(env, stack, "SO_BROADCAST is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_EE_OFFENDER(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_EE_OFFENDER
  stack[0].ival = SO_EE_OFFENDER;
  return 0;
#else
  env->die(env, stack, "SO_EE_OFFENDER is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_EE_ORIGIN_ICMP(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_EE_ORIGIN_ICMP
  stack[0].ival = SO_EE_ORIGIN_ICMP;
  return 0;
#else
  env->die(env, stack, "SO_EE_ORIGIN_ICMP is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_EE_ORIGIN_ICMP6(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_EE_ORIGIN_ICMP6
  stack[0].ival = SO_EE_ORIGIN_ICMP6;
  return 0;
#else
  env->die(env, stack, "SO_EE_ORIGIN_ICMP6 is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_EE_ORIGIN_LOCAL(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_EE_ORIGIN_LOCAL
  stack[0].ival = SO_EE_ORIGIN_LOCAL;
  return 0;
#else
  env->die(env, stack, "SO_EE_ORIGIN_LOCAL is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_EE_ORIGIN_NONE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_EE_ORIGIN_NONE
  stack[0].ival = SO_EE_ORIGIN_NONE;
  return 0;
#else
  env->die(env, stack, "SO_EE_ORIGIN_NONE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_ERROR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_ERROR
  stack[0].ival = SO_ERROR;
  return 0;
#else
  env->die(env, stack, "SO_ERROR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_KEEPALIVE(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_KEEPALIVE
  stack[0].ival = SO_KEEPALIVE;
  return 0;
#else
  env->die(env, stack, "SO_KEEPALIVE is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_PEERSEC(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_PEERSEC
  stack[0].ival = SO_PEERSEC;
  return 0;
#else
  env->die(env, stack, "SO_PEERSEC is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__SO_REUSEADDR(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef SO_REUSEADDR
  stack[0].ival = SO_REUSEADDR;
  return 0;
#else
  env->die(env, stack, "SO_REUSEADDR is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__TCP_CORK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef TCP_CORK
  stack[0].ival = TCP_CORK;
  return 0;
#else
  env->die(env, stack, "TCP_CORK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}

int32_t SPVM__Sys__Socket__Constant__UDP_CORK(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef UDP_CORK
  stack[0].ival = UDP_CORK;
  return 0;
#else
  env->die(env, stack, "UDP_CORK is not defined on this system", FILE_NAME, __LINE__);
  return SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED;
#endif
  
}
