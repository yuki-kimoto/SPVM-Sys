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

Gets the value of C<AF_ALG>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_APPLETALK

  static method AF_APPLETALK : int ();

Gets the value of C<AF_APPLETALK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_AX25

  static method AF_AX25 : int ();

Gets the value of C<AF_AX25>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_BLUETOOTH

  static method AF_BLUETOOTH : int ();

Gets the value of C<AF_BLUETOOTH>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_CAN

  static method AF_CAN : int ();

Gets the value of C<AF_CAN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_DEC

  static method AF_DEC : int ();

Gets the value of C<AF_DEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_IB

  static method AF_IB : int ();

Gets the value of C<AF_IB>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_INET

  static method AF_INET : int ();

Gets the value of C<AF_INET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_INET6

  static method AF_INET6 : int ();

Gets the value of C<AF_INET6>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_IPX

  static method AF_IPX : int ();

Gets the value of C<AF_IPX>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_KCM

  static method AF_KCM : int ();

Gets the value of C<AF_KCM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_KEY

  static method AF_KEY : int ();

Gets the value of C<AF_KEY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_LLC

  static method AF_LLC : int ();

Gets the value of C<AF_LLC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_LOCAL

  static method AF_LOCAL : int ();

Gets the value of C<AF_LOCAL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_MPLS

  static method AF_MPLS : int ();

Gets the value of C<AF_MPLS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_NETLINK

  static method AF_NETLINK : int ();

Gets the value of C<AF_NETLINK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_PACKET

  static method AF_PACKET : int ();

Gets the value of C<AF_PACKET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_PPPOX

  static method AF_PPPOX : int ();

Gets the value of C<AF_PPPOX>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_RDS

  static method AF_RDS : int ();

Gets the value of C<AF_RDS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_TIPC

  static method AF_TIPC : int ();

Gets the value of C<AF_TIPC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_UNIX

  static method AF_UNIX : int ();

Gets the value of C<AF_UNIX>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_UNSPEC

  static method AF_UNSPEC : int ();

Gets the value of C<AF_UNSPEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_VSOCK

  static method AF_VSOCK : int ();

Gets the value of C<AF_VSOCK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_X25

  static method AF_X25 : int ();

Gets the value of C<AF_X25>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AF_XDP

  static method AF_XDP : int ();

Gets the value of C<AF_XDP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_ANY

  static method INADDR_ANY : int ();

Gets the value of C<INADDR_ANY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_BROADCAST

  static method INADDR_BROADCAST : int ();

Gets the value of C<INADDR_BROADCAST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_LOOPBACK

  static method INADDR_LOOPBACK : int ();

Gets the value of C<INADDR_LOOPBACK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INADDR_NONE

  static method INADDR_NONE : int ();

Gets the value of C<INADDR_NONE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_IP

  static method IPPROTO_IP : int ();

Gets the value of C<IPPROTO_IP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_SCTP

  static method IPPROTO_SCTP : int ();

Gets the value of C<IPPROTO_SCTP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_TCP

  static method IPPROTO_TCP : int ();

Gets the value of C<IPPROTO_TCP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_UDP

  static method IPPROTO_UDP : int ();

Gets the value of C<IPPROTO_UDP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_UDPLITE

  static method IPPROTO_UDPLITE : int ();

Gets the value of C<IPPROTO_UDPLITE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_LOWDELAY

  static method IPTOS_LOWDELAY : int ();

Gets the value of C<IPTOS_LOWDELAY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_MINCOST

  static method IPTOS_MINCOST : int ();

Gets the value of C<IPTOS_MINCOST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_RELIABILITY

  static method IPTOS_RELIABILITY : int ();

Gets the value of C<IPTOS_RELIABILITY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPTOS_THROUGHPUT

  static method IPTOS_THROUGHPUT : int ();

Gets the value of C<IPTOS_THROUGHPUT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ADD_MEMBERSHIP

  static method IP_ADD_MEMBERSHIP : int ();

Gets the value of C<IP_ADD_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ADD_SOURCE_MEMBERSHIP

  static method IP_ADD_SOURCE_MEMBERSHIP : int ();

Gets the value of C<IP_ADD_SOURCE_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_BIND_ADDRESS_NO_PORT

  static method IP_BIND_ADDRESS_NO_PORT : int ();

Gets the value of C<IP_BIND_ADDRESS_NO_PORT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_BLOCK_SOURCE

  static method IP_BLOCK_SOURCE : int ();

Gets the value of C<IP_BLOCK_SOURCE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_DROP_MEMBERSHIP

  static method IP_DROP_MEMBERSHIP : int ();

Gets the value of C<IP_DROP_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_DROP_SOURCE_MEMBERSHIP

  static method IP_DROP_SOURCE_MEMBERSHIP : int ();

Gets the value of C<IP_DROP_SOURCE_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_FREEBIND

  static method IP_FREEBIND : int ();

Gets the value of C<IP_FREEBIND>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_HDRINCL

  static method IP_HDRINCL : int ();

Gets the value of C<IP_HDRINCL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MSFILTER

  static method IP_MSFILTER : int ();

Gets the value of C<IP_MSFILTER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MTU

  static method IP_MTU : int ();

Gets the value of C<IP_MTU>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MTU_DISCOVER

  static method IP_MTU_DISCOVER : int ();

Gets the value of C<IP_MTU_DISCOVER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_ALL

  static method IP_MULTICAST_ALL : int ();

Gets the value of C<IP_MULTICAST_ALL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_IF

  static method IP_MULTICAST_IF : int ();

Gets the value of C<IP_MULTICAST_IF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_LOOP

  static method IP_MULTICAST_LOOP : int ();

Gets the value of C<IP_MULTICAST_LOOP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_MULTICAST_TTL

  static method IP_MULTICAST_TTL : int ();

Gets the value of C<IP_MULTICAST_TTL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_NODEFRAG

  static method IP_NODEFRAG : int ();

Gets the value of C<IP_NODEFRAG>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_OPTION

  static method IP_OPTION : int ();

Gets the value of C<IP_OPTION>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_OPTIONS

  static method IP_OPTIONS : int ();

Gets the value of C<IP_OPTIONS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ORIGDSTADDR

  static method IP_ORIGDSTADDR : int ();

Gets the value of C<IP_ORIGDSTADDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PASSSEC

  static method IP_PASSSEC : int ();

Gets the value of C<IP_PASSSEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PKTINFO

  static method IP_PKTINFO : int ();

Gets the value of C<IP_PKTINFO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_DO

  static method IP_PMTUDISC_DO : int ();

Gets the value of C<IP_PMTUDISC_DO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_DONT

  static method IP_PMTUDISC_DONT : int ();

Gets the value of C<IP_PMTUDISC_DONT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_PROBE

  static method IP_PMTUDISC_PROBE : int ();

Gets the value of C<IP_PMTUDISC_PROBE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_PMTUDISC_WANT

  static method IP_PMTUDISC_WANT : int ();

Gets the value of C<IP_PMTUDISC_WANT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RCVDSTADDR

  static method IP_RCVDSTADDR : int ();

Gets the value of C<IP_RCVDSTADDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVERR

  static method IP_RECVERR : int ();

Gets the value of C<IP_RECVERR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVIF

  static method IP_RECVIF : int ();

Gets the value of C<IP_RECVIF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVOPTS

  static method IP_RECVOPTS : int ();

Gets the value of C<IP_RECVOPTS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVORIGDSTADDR

  static method IP_RECVORIGDSTADDR : int ();

Gets the value of C<IP_RECVORIGDSTADDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVTOS

  static method IP_RECVTOS : int ();

Gets the value of C<IP_RECVTOS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RECVTTL

  static method IP_RECVTTL : int ();

Gets the value of C<IP_RECVTTL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_RETOPTS

  static method IP_RETOPTS : int ();

Gets the value of C<IP_RETOPTS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_ROUTER_ALERT

  static method IP_ROUTER_ALERT : int ();

Gets the value of C<IP_ROUTER_ALERT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TOS

  static method IP_TOS : int ();

Gets the value of C<IP_TOS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TRANSPARENT

  static method IP_TRANSPARENT : int ();

Gets the value of C<IP_TRANSPARENT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_TTL

  static method IP_TTL : int ();

Gets the value of C<IP_TTL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IP_UNBLOCK_SOURCE

  static method IP_UNBLOCK_SOURCE : int ();

Gets the value of C<IP_UNBLOCK_SOURCE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MCAST_EXCLUDE

  static method MCAST_EXCLUDE : int ();

Gets the value of C<MCAST_EXCLUDE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MCAST_INCLUDE

  static method MCAST_INCLUDE : int ();

Gets the value of C<MCAST_INCLUDE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CMSG_CLOEXEC

  static method MSG_CMSG_CLOEXEC : int ();

Gets the value of C<MSG_CMSG_CLOEXEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CONFIRM

  static method MSG_CONFIRM : int ();

Gets the value of C<MSG_CONFIRM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_CTRUNC

  static method MSG_CTRUNC : int ();

Gets the value of C<MSG_CTRUNC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_DONTROUTE

  static method MSG_DONTROUTE : int ();

Gets the value of C<MSG_DONTROUTE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_DONTWAIT

  static method MSG_DONTWAIT : int ();

Gets the value of C<MSG_DONTWAIT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_EOR

  static method MSG_EOR : int ();

Gets the value of C<MSG_EOR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_ERRQUEUE

  static method MSG_ERRQUEUE : int ();

Gets the value of C<MSG_ERRQUEUE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_ERRQUIE

  static method MSG_ERRQUIE : int ();

Gets the value of C<MSG_ERRQUIE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_MORE

  static method MSG_MORE : int ();

Gets the value of C<MSG_MORE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_NOSIGNAL

  static method MSG_NOSIGNAL : int ();

Gets the value of C<MSG_NOSIGNAL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_OOB

  static method MSG_OOB : int ();

Gets the value of C<MSG_OOB>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_PEEK

  static method MSG_PEEK : int ();

Gets the value of C<MSG_PEEK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_TRUNC

  static method MSG_TRUNC : int ();

Gets the value of C<MSG_TRUNC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_WAITALL

  static method MSG_WAITALL : int ();

Gets the value of C<MSG_WAITALL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 PF_INET

  static method PF_INET : int ();

Gets the value of C<PF_INET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 PF_UNIX

  static method PF_UNIX : int ();

Gets the value of C<PF_UNIX>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SCM_RIGHTS

  static method SCM_RIGHTS : int ();

Gets the value of C<SCM_RIGHTS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SCM_SECURITY

  static method SCM_SECURITY : int ();

Gets the value of C<SCM_SECURITY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_CLOEXEC

  static method SOCK_CLOEXEC : int ();

Gets the value of C<SOCK_CLOEXEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_DGRAM

  static method SOCK_DGRAM : int ();

Gets the value of C<SOCK_DGRAM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_NONBLOCK

  static method SOCK_NONBLOCK : int ();

Gets the value of C<SOCK_NONBLOCK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_PACKET

  static method SOCK_PACKET : int ();

Gets the value of C<SOCK_PACKET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_RAW

  static method SOCK_RAW : int ();

Gets the value of C<SOCK_RAW>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_RDM

  static method SOCK_RDM : int ();

Gets the value of C<SOCK_RDM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_SEQPACKET

  static method SOCK_SEQPACKET : int ();

Gets the value of C<SOCK_SEQPACKET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOCK_STREAM

  static method SOCK_STREAM : int ();

Gets the value of C<SOCK_STREAM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOL_IP

  static method SOL_IP : int ();

Gets the value of C<SOL_IP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOL_SOCKET

  static method SOL_SOCKET : int ();

Gets the value of C<SOL_SOCKET>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SOMAXCONN

  static method SOMAXCONN : int ();

Gets the value of C<SOMAXCONN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_BROADCAST

  static method SO_BROADCAST : int ();

Gets the value of C<SO_BROADCAST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_OFFENDER

  static method SO_EE_OFFENDER : int ();

Gets the value of C<SO_EE_OFFENDER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_ICMP

  static method SO_EE_ORIGIN_ICMP : int ();

Gets the value of C<SO_EE_ORIGIN_ICMP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_ICMP6

  static method SO_EE_ORIGIN_ICMP6 : int ();

Gets the value of C<SO_EE_ORIGIN_ICMP6>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_LOCAL

  static method SO_EE_ORIGIN_LOCAL : int ();

Gets the value of C<SO_EE_ORIGIN_LOCAL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_EE_ORIGIN_NONE

  static method SO_EE_ORIGIN_NONE : int ();

Gets the value of C<SO_EE_ORIGIN_NONE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ERROR

  static method SO_ERROR : int ();

Gets the value of C<SO_ERROR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_KEEPALIVE

  static method SO_KEEPALIVE : int ();

Gets the value of C<SO_KEEPALIVE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PEERSEC

  static method SO_PEERSEC : int ();

Gets the value of C<SO_PEERSEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_REUSEADDR

  static method SO_REUSEADDR : int ();

Gets the value of C<SO_REUSEADDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_CORK

  static method TCP_CORK : int ();

Gets the value of C<TCP_CORK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 UDP_CORK

  static method UDP_CORK : int ();

Gets the value of C<UDP_CORK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INET_ADDRSTRLEN

  static method INET_ADDRSTRLEN : int ();

Gets the value of C<INET_ADDRSTRLEN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 INET6_ADDRSTRLEN

  static method INET6_ADDRSTRLEN : int ();

Gets the value of C<INET6_ADDRSTRLEN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_IPV6

  static method IPPROTO_IPV6 : int ();

Gets the value of C<IPPROTO_IPV6>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPPROTO_ICMP

  static method IPPROTO_ICMP : int ();

Gets the value of C<IPPROTO_ICMP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_ADDRFORM

  static method IPV6_ADDRFORM : int ();

Gets the value of C<IPV6_ADDRFORM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_ADD_MEMBERSHIP

  static method IPV6_ADD_MEMBERSHIP : int ();

Gets the value of C<IPV6_ADD_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_AUTHHDR

  static method IPV6_AUTHHDR : int ();

Gets the value of C<IPV6_AUTHHDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_DROP_MEMBERSHIP

  static method IPV6_DROP_MEMBERSHIP : int ();

Gets the value of C<IPV6_DROP_MEMBERSHIP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_DSTOPS

  static method IPV6_DSTOPS : int ();

Gets the value of C<IPV6_DSTOPS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_DSTOPTS

  static method IPV6_DSTOPTS : int ();

Gets the value of C<IPV6_DSTOPTS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_FLOWINFO

  static method IPV6_FLOWINFO : int ();

Gets the value of C<IPV6_FLOWINFO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_HOPLIMIT

  static method IPV6_HOPLIMIT : int ();

Gets the value of C<IPV6_HOPLIMIT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_HOPOPTS

  static method IPV6_HOPOPTS : int ();

Gets the value of C<IPV6_HOPOPTS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_MTU

  static method IPV6_MTU : int ();

Gets the value of C<IPV6_MTU>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_MTU_DISCOVER

  static method IPV6_MTU_DISCOVER : int ();

Gets the value of C<IPV6_MTU_DISCOVER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_MULTICAST_HOPS

  static method IPV6_MULTICAST_HOPS : int ();

Gets the value of C<IPV6_MULTICAST_HOPS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_MULTICAST_IF

  static method IPV6_MULTICAST_IF : int ();

Gets the value of C<IPV6_MULTICAST_IF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_MULTICAST_LOOP

  static method IPV6_MULTICAST_LOOP : int ();

Gets the value of C<IPV6_MULTICAST_LOOP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_PKTINFO

  static method IPV6_PKTINFO : int ();

Gets the value of C<IPV6_PKTINFO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_RECVERR

  static method IPV6_RECVERR : int ();

Gets the value of C<IPV6_RECVERR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_ROUTER_ALERT

  static method IPV6_ROUTER_ALERT : int ();

Gets the value of C<IPV6_ROUTER_ALERT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_RTHDR

  static method IPV6_RTHDR : int ();

Gets the value of C<IPV6_RTHDR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_UNICAST_HOPS

  static method IPV6_UNICAST_HOPS : int ();

Gets the value of C<IPV6_UNICAST_HOPS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IPV6_V6ONLY

  static method IPV6_V6ONLY : int ();

Gets the value of C<IPV6_V6ONLY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 PF_INET6

  static method PF_INET6 : int ();

Gets the value of C<PF_INET6>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ACCEPTCONN

  static method SO_ACCEPTCONN : int ();

Gets the value of C<SO_ACCEPTCONN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ATTACH_BPF

  static method SO_ATTACH_BPF : int ();

Gets the value of C<SO_ATTACH_BPF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ATTACH_FILTER

  static method SO_ATTACH_FILTER : int ();

Gets the value of C<SO_ATTACH_FILTER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ATTACH_REUSEPORT_CBPF

  static method SO_ATTACH_REUSEPORT_CBPF : int ();

Gets the value of C<SO_ATTACH_REUSEPORT_CBPF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_ATTACH_REUSEPORT_EBPF

  static method SO_ATTACH_REUSEPORT_EBPF : int ();

Gets the value of C<SO_ATTACH_REUSEPORT_EBPF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_BINDTODEVICE

  static method SO_BINDTODEVICE : int ();

Gets the value of C<SO_BINDTODEVICE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_BSDCOMPAT

  static method SO_BSDCOMPAT : int ();

Gets the value of C<SO_BSDCOMPAT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_BUSY_POLL

  static method SO_BUSY_POLL : int ();

Gets the value of C<SO_BUSY_POLL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_DEBUG

  static method SO_DEBUG : int ();

Gets the value of C<SO_DEBUG>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_DETACH_BPF

  static method SO_DETACH_BPF : int ();

Gets the value of C<SO_DETACH_BPF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_DETACH_FILTER

  static method SO_DETACH_FILTER : int ();

Gets the value of C<SO_DETACH_FILTER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_DOMAIN

  static method SO_DOMAIN : int ();

Gets the value of C<SO_DOMAIN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_DONTROUTE

  static method SO_DONTROUTE : int ();

Gets the value of C<SO_DONTROUTE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_INCOMING_CPU

  static method SO_INCOMING_CPU : int ();

Gets the value of C<SO_INCOMING_CPU>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_INCOMING_NAPI_ID

  static method SO_INCOMING_NAPI_ID : int ();

Gets the value of C<SO_INCOMING_NAPI_ID>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_LINGER

  static method SO_LINGER : int ();

Gets the value of C<SO_LINGER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_LOCK_FILTER

  static method SO_LOCK_FILTER : int ();

Gets the value of C<SO_LOCK_FILTER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_MARK

  static method SO_MARK : int ();

Gets the value of C<SO_MARK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_OOBINLINE

  static method SO_OOBINLINE : int ();

Gets the value of C<SO_OOBINLINE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PASSCRED

  static method SO_PASSCRED : int ();

Gets the value of C<SO_PASSCRED>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PASSSEC

  static method SO_PASSSEC : int ();

Gets the value of C<SO_PASSSEC>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PEEK_OFF

  static method SO_PEEK_OFF : int ();

Gets the value of C<SO_PEEK_OFF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PEERCRED

  static method SO_PEERCRED : int ();

Gets the value of C<SO_PEERCRED>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PRIORITY

  static method SO_PRIORITY : int ();

Gets the value of C<SO_PRIORITY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_PROTOCOL

  static method SO_PROTOCOL : int ();

Gets the value of C<SO_PROTOCOL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_RCVBUF

  static method SO_RCVBUF : int ();

Gets the value of C<SO_RCVBUF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_RCVBUFFORCE

  static method SO_RCVBUFFORCE : int ();

Gets the value of C<SO_RCVBUFFORCE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_RCVLOWAT

  static method SO_RCVLOWAT : int ();

Gets the value of C<SO_RCVLOWAT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_RCVTIMEO

  static method SO_RCVTIMEO : int ();

Gets the value of C<SO_RCVTIMEO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_REUSEPORT

  static method SO_REUSEPORT : int ();

Gets the value of C<SO_REUSEPORT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_RXQ_OVFL

  static method SO_RXQ_OVFL : int ();

Gets the value of C<SO_RXQ_OVFL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_SELECT_ERR_QUEUE

  static method SO_SELECT_ERR_QUEUE : int ();

Gets the value of C<SO_SELECT_ERR_QUEUE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_SNDBUF

  static method SO_SNDBUF : int ();

Gets the value of C<SO_SNDBUF>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_SNDBUFFORCE

  static method SO_SNDBUFFORCE : int ();

Gets the value of C<SO_SNDBUFFORCE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_SNDLOWAT

  static method SO_SNDLOWAT : int ();

Gets the value of C<SO_SNDLOWAT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_SNDTIMEO

  static method SO_SNDTIMEO : int ();

Gets the value of C<SO_SNDTIMEO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_TIMESTAMP

  static method SO_TIMESTAMP : int ();

Gets the value of C<SO_TIMESTAMP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_TIMESTAMPNS

  static method SO_TIMESTAMPNS : int ();

Gets the value of C<SO_TIMESTAMPNS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SO_TYPE

  static method SO_TYPE : int ();

Gets the value of C<SO_TYPE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_BCAST

  static method MSG_BCAST : int ();

Gets the value of C<MSG_BCAST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_COPY

  static method MSG_COPY : int ();

Gets the value of C<MSG_COPY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_EXCEPT

  static method MSG_EXCEPT : int ();

Gets the value of C<MSG_EXCEPT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_MCAST

  static method MSG_MCAST : int ();

Gets the value of C<MSG_MCAST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 MSG_NOERROR

  static method MSG_NOERROR : int ();

Gets the value of C<MSG_NOERROR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SHUT_RD

  static method SHUT_RD : int ();

Gets the value of C<SHUT_RD>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SHUT_WR

  static method SHUT_WR : int ();

Gets the value of C<SHUT_WR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SHUT_RDWR

  static method SHUT_RDWR : int ();

Gets the value of C<SHUT_RDWR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_CONGESTION

  static method TCP_CONGESTION : int ();

Gets the value of C<TCP_CONGESTION>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_DEFER_ACCEPT

  static method TCP_DEFER_ACCEPT : int ();

Gets the value of C<TCP_DEFER_ACCEPT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_INFO

  static method TCP_INFO : int ();

Gets the value of C<TCP_INFO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_KEEPCNT

  static method TCP_KEEPCNT : int ();

Gets the value of C<TCP_KEEPCNT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_KEEPIDLE

  static method TCP_KEEPIDLE : int ();

Gets the value of C<TCP_KEEPIDLE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_KEEPINTVL

  static method TCP_KEEPINTVL : int ();

Gets the value of C<TCP_KEEPINTVL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_LINGER2

  static method TCP_LINGER2 : int ();

Gets the value of C<TCP_LINGER2>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_MAXSEG

  static method TCP_MAXSEG : int ();

Gets the value of C<TCP_MAXSEG>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_NODELAY

  static method TCP_NODELAY : int ();

Gets the value of C<TCP_NODELAY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_QUICKACK

  static method TCP_QUICKACK : int ();

Gets the value of C<TCP_QUICKACK>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_SYNCNT

  static method TCP_SYNCNT : int ();

Gets the value of C<TCP_SYNCNT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_SYNQ_HSIZE

  static method TCP_SYNQ_HSIZE : int ();

Gets the value of C<TCP_SYNQ_HSIZE>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_USER_TIMEOUT

  static method TCP_USER_TIMEOUT : int ();

Gets the value of C<TCP_USER_TIMEOUT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 TCP_WINDOW_CLAMP

  static method TCP_WINDOW_CLAMP : int ();

Gets the value of C<TCP_WINDOW_CLAMP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IN6ADDR_ANY

  static method IN6ADDR_ANY : int ();

Get the value initialized by C<IN6ADDR_ANY_INIT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 IN6ADDR_LOOPBACK

  static method IN6ADDR_LOOPBACK : int ();

Get the value initialized by C<IN6ADDR_LOOPBACK_INIT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 NI_MAXHOST

  static method NI_MAXHOST : int ();

Gets the value of C<NI_MAXHOST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 NI_MAXSERV

  static method NI_MAXSERV : int ();

Gets the value of C<NI_MAXSERV>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_ADDRESS

  static method ICMP_ADDRESS : int ();

Gets the value of C<ICMP_ADDRESS>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_DEST_UNREACH

  static method ICMP_DEST_UNREACH : int ();

Gets the value of C<ICMP_DEST_UNREACH>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_ECHO

  static method ICMP_ECHO : int ();

Gets the value of C<ICMP_ECHO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_ECHOREPLY

  static method ICMP_ECHOREPLY : int ();

Gets the value of C<ICMP_ECHOREPLY>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_ECHOREQUEST

  static method ICMP_ECHOREQUEST : int ();

Gets the value of C<ICMP_ECHOREQUEST>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_FILTER

  static method ICMP_FILTER : int ();

Gets the value of C<ICMP_FILTER>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_FRAG_NEEDED

  static method ICMP_FRAG_NEEDED : int ();

Gets the value of C<ICMP_FRAG_NEEDED>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_PARAMETERPROB

  static method ICMP_PARAMETERPROB : int ();

Gets the value of C<ICMP_PARAMETERPROB>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_REDIRECT

  static method ICMP_REDIRECT : int ();

Gets the value of C<ICMP_REDIRECT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_SOURCE_QUENCH

  static method ICMP_SOURCE_QUENCH : int ();

Gets the value of C<ICMP_SOURCE_QUENCH>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_TIMESTAMP

  static method ICMP_TIMESTAMP : int ();

Gets the value of C<ICMP_TIMESTAMP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 ICMP_TIME_EXCEEDED

  static method ICMP_TIME_EXCEEDED : int ();

Gets the value of C<ICMP_TIME_EXCEEDED>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

