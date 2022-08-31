package SPVM::Sys::Socket::Constant;

1;

=head1 Name

SPVM::Sys::Socket::Constant - Socket Constant Values

=head1 Usage

  use Sys::Socket::Constant as Sock;
  
  Sock->AF_INET;
  Sock->SOL_SOCKET;
  
=head1 Description

C<Sys::Socket::Constant> is a class to provide the socket constant values.

=head1 Class Methods

=head2 AF_ALG

  static method AF_ALG : int ();

Get the error number of C<AF_ALG>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_APPLETALK

  static method AF_APPLETALK : int ();

Get the error number of C<AF_APPLETALK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_AX25

  static method AF_AX25 : int ();

Get the error number of C<AF_AX25>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_BLUETOOTH

  static method AF_BLUETOOTH : int ();

Get the error number of C<AF_BLUETOOTH>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_CAN

  static method AF_CAN : int ();

Get the error number of C<AF_CAN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_DEC

  static method AF_DEC : int ();

Get the error number of C<AF_DEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_IB

  static method AF_IB : int ();

Get the error number of C<AF_IB>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_INET

  static method AF_INET : int ();

Get the error number of C<AF_INET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_INET6

  static method AF_INET6 : int ();

Get the error number of C<AF_INET6>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_IPX

  static method AF_IPX : int ();

Get the error number of C<AF_IPX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_KCM

  static method AF_KCM : int ();

Get the error number of C<AF_KCM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_KEY

  static method AF_KEY : int ();

Get the error number of C<AF_KEY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_LLC

  static method AF_LLC : int ();

Get the error number of C<AF_LLC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_LOCAL

  static method AF_LOCAL : int ();

Get the error number of C<AF_LOCAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_MPLS

  static method AF_MPLS : int ();

Get the error number of C<AF_MPLS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_NETLINK

  static method AF_NETLINK : int ();

Get the error number of C<AF_NETLINK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_PACKET

  static method AF_PACKET : int ();

Get the error number of C<AF_PACKET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_PPPOX

  static method AF_PPPOX : int ();

Get the error number of C<AF_PPPOX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_RDS

  static method AF_RDS : int ();

Get the error number of C<AF_RDS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_TIPC

  static method AF_TIPC : int ();

Get the error number of C<AF_TIPC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_UNIX

  static method AF_UNIX : int ();

Get the error number of C<AF_UNIX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_UNSPEC

  static method AF_UNSPEC : int ();

Get the error number of C<AF_UNSPEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_VSOCK

  static method AF_VSOCK : int ();

Get the error number of C<AF_VSOCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_X25

  static method AF_X25 : int ();

Get the error number of C<AF_X25>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_XDP

  static method AF_XDP : int ();

Get the error number of C<AF_XDP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_ANY

  static method INADDR_ANY : int ();

Get the error number of C<INADDR_ANY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_BROADCAST

  static method INADDR_BROADCAST : int ();

Get the error number of C<INADDR_BROADCAST>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_LOOPBACK

  static method INADDR_LOOPBACK : int ();

Get the error number of C<INADDR_LOOPBACK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_IP

  static method IPPROTO_IP : int ();

Get the error number of C<IPPROTO_IP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_SCTP

  static method IPPROTO_SCTP : int ();

Get the error number of C<IPPROTO_SCTP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_TCP

  static method IPPROTO_TCP : int ();

Get the error number of C<IPPROTO_TCP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_UDP

  static method IPPROTO_UDP : int ();

Get the error number of C<IPPROTO_UDP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_UDPLITE

  static method IPPROTO_UDPLITE : int ();

Get the error number of C<IPPROTO_UDPLITE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_LOWDELAY

  static method IPTOS_LOWDELAY : int ();

Get the error number of C<IPTOS_LOWDELAY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_MINCOST

  static method IPTOS_MINCOST : int ();

Get the error number of C<IPTOS_MINCOST>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_RELIABILITY

  static method IPTOS_RELIABILITY : int ();

Get the error number of C<IPTOS_RELIABILITY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_THROUGHPUT

  static method IPTOS_THROUGHPUT : int ();

Get the error number of C<IPTOS_THROUGHPUT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ADD_MEMBERSHIP

  static method IP_ADD_MEMBERSHIP : int ();

Get the error number of C<IP_ADD_MEMBERSHIP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ADD_SOURCE_MEMBERSHIP

  static method IP_ADD_SOURCE_MEMBERSHIP : int ();

Get the error number of C<IP_ADD_SOURCE_MEMBERSHIP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_BIND_ADDRESS_NO_PORT

  static method IP_BIND_ADDRESS_NO_PORT : int ();

Get the error number of C<IP_BIND_ADDRESS_NO_PORT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_BLOCK_SOURCE

  static method IP_BLOCK_SOURCE : int ();

Get the error number of C<IP_BLOCK_SOURCE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_DROP_MEMBERSHIP

  static method IP_DROP_MEMBERSHIP : int ();

Get the error number of C<IP_DROP_MEMBERSHIP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_DROP_SOURCE_MEMBERSHIP

  static method IP_DROP_SOURCE_MEMBERSHIP : int ();

Get the error number of C<IP_DROP_SOURCE_MEMBERSHIP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_FREEBIND

  static method IP_FREEBIND : int ();

Get the error number of C<IP_FREEBIND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_HDRINCL

  static method IP_HDRINCL : int ();

Get the error number of C<IP_HDRINCL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MSFILTER

  static method IP_MSFILTER : int ();

Get the error number of C<IP_MSFILTER>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MTU

  static method IP_MTU : int ();

Get the error number of C<IP_MTU>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MTU_DISCOVER

  static method IP_MTU_DISCOVER : int ();

Get the error number of C<IP_MTU_DISCOVER>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_ALL

  static method IP_MULTICAST_ALL : int ();

Get the error number of C<IP_MULTICAST_ALL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_IF

  static method IP_MULTICAST_IF : int ();

Get the error number of C<IP_MULTICAST_IF>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_LOOP

  static method IP_MULTICAST_LOOP : int ();

Get the error number of C<IP_MULTICAST_LOOP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_TTL

  static method IP_MULTICAST_TTL : int ();

Get the error number of C<IP_MULTICAST_TTL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_NODEFRAG

  static method IP_NODEFRAG : int ();

Get the error number of C<IP_NODEFRAG>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_OPTION

  static method IP_OPTION : int ();

Get the error number of C<IP_OPTION>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_OPTIONS

  static method IP_OPTIONS : int ();

Get the error number of C<IP_OPTIONS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ORIGDSTADDR

  static method IP_ORIGDSTADDR : int ();

Get the error number of C<IP_ORIGDSTADDR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PASSSEC

  static method IP_PASSSEC : int ();

Get the error number of C<IP_PASSSEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PKTINFO

  static method IP_PKTINFO : int ();

Get the error number of C<IP_PKTINFO>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_DO

  static method IP_PMTUDISC_DO : int ();

Get the error number of C<IP_PMTUDISC_DO>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_DONT

  static method IP_PMTUDISC_DONT : int ();

Get the error number of C<IP_PMTUDISC_DONT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_PROBE

  static method IP_PMTUDISC_PROBE : int ();

Get the error number of C<IP_PMTUDISC_PROBE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_WANT

  static method IP_PMTUDISC_WANT : int ();

Get the error number of C<IP_PMTUDISC_WANT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RCVDSTADDR

  static method IP_RCVDSTADDR : int ();

Get the error number of C<IP_RCVDSTADDR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVERR

  static method IP_RECVERR : int ();

Get the error number of C<IP_RECVERR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVIF

  static method IP_RECVIF : int ();

Get the error number of C<IP_RECVIF>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVOPTS

  static method IP_RECVOPTS : int ();

Get the error number of C<IP_RECVOPTS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVORIGDSTADDR

  static method IP_RECVORIGDSTADDR : int ();

Get the error number of C<IP_RECVORIGDSTADDR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVTOS

  static method IP_RECVTOS : int ();

Get the error number of C<IP_RECVTOS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVTTL

  static method IP_RECVTTL : int ();

Get the error number of C<IP_RECVTTL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RETOPTS

  static method IP_RETOPTS : int ();

Get the error number of C<IP_RETOPTS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ROUTER_ALERT

  static method IP_ROUTER_ALERT : int ();

Get the error number of C<IP_ROUTER_ALERT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TOS

  static method IP_TOS : int ();

Get the error number of C<IP_TOS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TRANSPARENT

  static method IP_TRANSPARENT : int ();

Get the error number of C<IP_TRANSPARENT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TTL

  static method IP_TTL : int ();

Get the error number of C<IP_TTL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_UNBLOCK_SOURCE

  static method IP_UNBLOCK_SOURCE : int ();

Get the error number of C<IP_UNBLOCK_SOURCE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MCAST_EXCLUDE

  static method MCAST_EXCLUDE : int ();

Get the error number of C<MCAST_EXCLUDE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MCAST_INCLUDE

  static method MCAST_INCLUDE : int ();

Get the error number of C<MCAST_INCLUDE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CMSG_CLOEXEC

  static method MSG_CMSG_CLOEXEC : int ();

Get the error number of C<MSG_CMSG_CLOEXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CONFIRM

  static method MSG_CONFIRM : int ();

Get the error number of C<MSG_CONFIRM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CTRUNC

  static method MSG_CTRUNC : int ();

Get the error number of C<MSG_CTRUNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_DONTROUTE

  static method MSG_DONTROUTE : int ();

Get the error number of C<MSG_DONTROUTE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_DONTWAIT

  static method MSG_DONTWAIT : int ();

Get the error number of C<MSG_DONTWAIT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_EOR

  static method MSG_EOR : int ();

Get the error number of C<MSG_EOR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_ERRQUEUE

  static method MSG_ERRQUEUE : int ();

Get the error number of C<MSG_ERRQUEUE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_ERRQUIE

  static method MSG_ERRQUIE : int ();

Get the error number of C<MSG_ERRQUIE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_MORE

  static method MSG_MORE : int ();

Get the error number of C<MSG_MORE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_NOSIGNAL

  static method MSG_NOSIGNAL : int ();

Get the error number of C<MSG_NOSIGNAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_OOB

  static method MSG_OOB : int ();

Get the error number of C<MSG_OOB>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_PEEK

  static method MSG_PEEK : int ();

Get the error number of C<MSG_PEEK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_TRUNC

  static method MSG_TRUNC : int ();

Get the error number of C<MSG_TRUNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_WAITALL

  static method MSG_WAITALL : int ();

Get the error number of C<MSG_WAITALL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 PF_INET

  static method PF_INET : int ();

Get the error number of C<PF_INET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 PF_UNIX

  static method PF_UNIX : int ();

Get the error number of C<PF_UNIX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SCM_RIGHTS

  static method SCM_RIGHTS : int ();

Get the error number of C<SCM_RIGHTS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SCM_SECURITY

  static method SCM_SECURITY : int ();

Get the error number of C<SCM_SECURITY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_CLOEXEC

  static method SOCK_CLOEXEC : int ();

Get the error number of C<SOCK_CLOEXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_DGRAM

  static method SOCK_DGRAM : int ();

Get the error number of C<SOCK_DGRAM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_NONBLOCK

  static method SOCK_NONBLOCK : int ();

Get the error number of C<SOCK_NONBLOCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_PACKET

  static method SOCK_PACKET : int ();

Get the error number of C<SOCK_PACKET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_RAW

  static method SOCK_RAW : int ();

Get the error number of C<SOCK_RAW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_RDM

  static method SOCK_RDM : int ();

Get the error number of C<SOCK_RDM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_SEQPACKET

  static method SOCK_SEQPACKET : int ();

Get the error number of C<SOCK_SEQPACKET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_STREAM

  static method SOCK_STREAM : int ();

Get the error number of C<SOCK_STREAM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOL_IP

  static method SOL_IP : int ();

Get the error number of C<SOL_IP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOL_SOCKET

  static method SOL_SOCKET : int ();

Get the error number of C<SOL_SOCKET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_BROADCAST

  static method SO_BROADCAST : int ();

Get the error number of C<SO_BROADCAST>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_OFFENDER

  static method SO_EE_OFFENDER : int ();

Get the error number of C<SO_EE_OFFENDER>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_ICMP

  static method SO_EE_ORIGIN_ICMP : int ();

Get the error number of C<SO_EE_ORIGIN_ICMP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_ICMP6

  static method SO_EE_ORIGIN_ICMP6 : int ();

Get the error number of C<SO_EE_ORIGIN_ICMP6>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_LOCAL

  static method SO_EE_ORIGIN_LOCAL : int ();

Get the error number of C<SO_EE_ORIGIN_LOCAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_NONE

  static method SO_EE_ORIGIN_NONE : int ();

Get the error number of C<SO_EE_ORIGIN_NONE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ERROR

  static method SO_ERROR : int ();

Get the error number of C<SO_ERROR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_KEEPALIVE

  static method SO_KEEPALIVE : int ();

Get the error number of C<SO_KEEPALIVE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PEERSEC

  static method SO_PEERSEC : int ();

Get the error number of C<SO_PEERSEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_REUSEADDR

  static method SO_REUSEADDR : int ();

Get the error number of C<SO_REUSEADDR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_CORK

  static method TCP_CORK : int ();

Get the error number of C<TCP_CORK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 UDP_CORK

  static method UDP_CORK : int ();

Get the error number of C<UDP_CORK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Copyright & License

Copyright 2022-2022 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.
