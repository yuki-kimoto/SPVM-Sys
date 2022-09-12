package SPVM::Sys::Socket;

1;

=head1 Name

SPVM::Sys::Socket - Socket System Call

=head1 Usage
  
  use Sys::Socket;

=head1 Description

C<Sys::Socket> is the class for system calls of socket.

=head1 Class Methods

=head2 socket

  static method socket : int ($domain : int, $type : int, $protocol : int);

socket() creates an endpoint for communication and returns a descriptor.
The domain argument specifies a communication domain; this selects the protocol family which will be used for communication. These families are defined in <sys/socket.h>. The currently understood formats include:

See the detail of the L<socket|https://linux.die.net/man/2/socket> function in the case of Linux.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::Sysytem> class.

=head2 connect

  static method connect : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen : int);

=head2 bind

  static method bind : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen : int);

=head2 accept

  static method accept : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

=head2 listen

  static method listen : int ($sockfd : int, $backlog : int);

=head2 shutdown

  static method shutdown : int ($sockfd : int, $how : int);

=head2 recv

  static method recv : int ($sockfd : int, $buf : mutable string, $len : int, $flags : int);

=head2 send

  static method send : int ($sockfd : int, $buf : string, $len : int, $flags : int);

=head2 getpeername

  static method getpeername : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

=head2 getsockname

  static method getsockname : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

=head2 socketpair

  static method socketpair : int ($domain : int, $type : int, $protocol : int, $pair : int[]);

=head2 setsockopt

  static method setsockopt : int ($sockfd : int, $level : int, $optname : int, $optval : string, $optlen : int);

=head2 setsockopt_int

  static method setsockopt_int : int ($sockfd : int, $level : int, $optname : int, $optval : int);

=head2 getsockopt

  static method getsockopt : int ($sockfd : int, $level : int, $optname : int, $optval_ref : string[], $optlen_ref : int*);

=head2 getsockopt_int

  static method getsockopt_int : int ($sockfd : int, $level : int, $optname : int, $optval_ref : int*);

=head2 getaddrinfo

  static method getaddrinfo : int ($node : string, $service : string,
                $hints : Sys::Socket::Addrinfo,
                $res : Sys::Socket::Addrinfo[]);

=head2 getnameinfo

  static method getnameinfo : int ($addr : Sys::Socket::Sockaddr, $addrlen : int,
                $host : mutable string, $hostlen : int,
                $serv : mutable string, $servlen : int, $flag : int);

=head2 gai_strerror

  static method gai_strerror : string($gai_error_code : int);

=head2 inet_aton

  static method inet_aton : int ($input_address : string, $output_address : Sys::Socket::In_addr);

=head2 inet_ntoa

  static method inet_ntoa : string ($in_addr : Sys::Socket::In_addr);

=head2 inet_pton

  static method inet_pton : int ($address_family : int, $input_address : string, $output_address : object of Sys::Socket::In_addr|Sys::Socket::In6_addr);

=head2 inet_ntop

  static method inet_ntop : string ($address_family : int, $input_address : object of Sys::Socket::In_addr|Sys::Socket::In6_addr, $output_address : mutable string, $size : int);

=head2 htonl

  static method htonl : int ($host_int : int);

=head2 htons

  static method htons : short ($host_short : short);

=head2 ntohl

  static method ntohl : int ($net_int : int);

=head2 ntohs

  static method ntohs : short ($net_short : short);

=head2 ioctlsocket

  static method ioctlsocket : int ($fd : int, $request : int, $request_arg_ref : int*);

=head2 closesocket

  static method closesocket : int ($fd : int);

=head2 WSAPoll

  static method WSAPoll : int ($fds : Sys::IO::PollfdArray, $nfds : int, $timeout : int);

=head2 ioctl_int_portable

  static method ioctl_int_portable : int ($fd : int, $request : int, $request_arg_ref : int*) {
    if (Sys->is_D_WIN32) {
      return Sys::Socket->ioctlsocket($fd, $request, $request_arg_ref);
    }
    else {
      my $int_object = Int->new($$request_arg_ref);
      return Sys::IO->ioctl($fd, $request, $int_object);
      $$request_arg_ref = $int_object->value;
    }
  }

=head2 poll_portable

  static method poll_portable : int ($fds : Sys::IO::PollfdArray, $nfds : int, $timeout : int) {
    if (Sys->is_D_WIN32) {
      return Sys::Socket->WSAPoll($fds, $nfds, $timeout);
    }
    else {
      return Sys::IO->poll($fds, $nfds, $timeout);
    }
  }

=head2 close_portable

  static method close_portable : int ($fd : int) {
    if (Sys->is_D_WIN32) {
      return Sys::Socket->closesocket($fd);
    }
    else {
      return Sys::IO->close($fd);
    }
  }
