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

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 connect

  static method connect : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen : int);

The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. The addrlen argument specifies the size of addr. The format of the address in addr is determined by the address space of the socket sockfd; see socket(2) for further details.

See the detail of the L<connect|https://linux.die.net/man/2/connect> function in the case of Linux.

The address(C<$addr>) is a L< Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr> object.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 bind

  static method bind : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen : int);

When a socket is created with socket(2), it exists in a name space (address family) but has no address assigned to it. bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd. addrlen specifies the size, in bytes, of the address structure pointed to by addr. Traditionally, this operation is called "assigning a name to a socket".

See the detail of the L<bind|https://linux.die.net/man/2/bind> function in the case of Linux.

The address(C<$addr>) is a L< Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr> object.

The address must be defined. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 accept

  static method accept : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

The accept() system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET). It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. The newly created socket is not in the listening state. The original socket sockfd is unaffected by this call.

See the detail of the L<accept|https://linux.die.net/man/2/accept> function in the case of Linux.

The address(C<$addr>) is a L< Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr> object.

The address must be defined. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 listen

  static method listen : int ($sockfd : int, $backlog : int);

listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept(2).

See the detail of the L<listen|https://linux.die.net/man/2/listen> function in the case of Linux.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 shutdown

  static method shutdown : int ($sockfd : int, $how : int);

The shutdown() call causes all or part of a full-duplex connection on the socket associated with sockfd to be shut down. If how is SHUT_RD, further receptions will be disallowed. If how is SHUT_WR, further transmissions will be disallowed. If how is SHUT_RDWR, further receptions and transmissions will be disallowed.

See the detail of the L<shutdown|https://linux.die.net/man/2/shutdown> function in the case of Linux.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 recv

  static method recv : int ($sockfd : int, $buf : mutable string, $len : int, $flags : int);

The recv() call is normally used only on a connected socket (see connect(2)) and is identical to recvfrom() with a NULL src_addr argument.

See the detail of the L<recv|https://linux.die.net/man/2/recv> function in the case of Linux.

The buffer(C<$buf> must be defined. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 send

  static method send : int ($sockfd : int, $buf : string, $len : int, $flags : int);

The send() call may be used only when the socket is in a connected state (so that the intended recipient is known). The only difference between send() and write(2) is the presence of flags. With a zero flags argument, send() is equivalent to write(2). Also, the following call

The buffer(C<$buf> must be defined. Otherwise an exception will be thrown.

See the detail of the L<send|https://linux.die.net/man/2/send> function in the case of Linux.

=head2 getpeername

  static method getpeername : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

getpeername() returns the address of the peer connected to the socket sockfd, in the buffer pointed to by addr. The addrlen argument should be initialized to indicate the amount of space pointed to by addr. On return it contains the actual size of the name returned (in bytes). The name is truncated if the buffer provided is too small.

See the detail of the L<getpeername|https://linux.die.net/man/2/getpeername> function in the case of Linux.

The address(C<$addr>) is a L< Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr> object.

The address must be defined. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 getsockname

  static method getsockname : int ($sockfd : int, $addr : Sys::Socket::Sockaddr, $addrlen_ref : int*);

getsockname() returns the current address to which the socket sockfd is bound, in the buffer pointed to by addr. The addrlen argument should be initialized to indicate the amount of space (in bytes) pointed to by addr. On return it contains the actual size of the socket address.

See the detail of the L<getsockname|https://linux.die.net/man/2/getsockname> function in the case of Linux.

The address(C<$addr>) is a L< Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr> object.

The address must be defined. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 socketpair

  static method socketpair : int ($domain : int, $type : int, $protocol : int, $sv : int[]);

The socketpair() call creates an unnamed pair of connected sockets in the specified domain, of the specified type, and using the optionally specified protocol. For further details of these arguments, see socket(2).

See the detail of the L<socketpair|https://linux.die.net/man/2/socketpair> function in the case of Linux.

The output of the socket pair(sv) must be defined. Otherwise an exception will be thrown.

The length of the output of the socket pair(sv) must be greater than or equal to 2. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 setsockopt

  static method setsockopt : int ($sockfd : int, $level : int, $optname : int, $optval : string, $optlen : int);

getsockopt() and setsockopt() manipulate options for the socket referred to by the file descriptor sockfd. Options may exist at multiple protocol levels; they are always present at the uppermost socket level.

See the detail of the L<setsockopt|https://linux.die.net/man/2/setsockopt> function in the case of Linux.

The option value must be defined. Otherwise an exception will be thrown.

The option length must be greater than or equal to 0. Otherwise an exception will be thrown.

The length of the option value must be less than or equal to the option length. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 setsockopt_int

  static method setsockopt_int : int ($sockfd : int, $level : int, $optname : int, $optval : int);

The same as L</"setsockopt">, but the option value can be specifed by the C<int> type.

=head2 getsockopt

  static method getsockopt : int ($sockfd : int, $level : int, $optname : int, $optval : mutable string, $optlen_ref : int*);

getsockopt() and setsockopt() manipulate options for the socket referred to by the file descriptor sockfd. Options may exist at multiple protocol levels; they are always present at the uppermost socket level.

See the detail of the L<getsockopt|https://linux.die.net/man/2/getsockopt> function in the case of Linux.

The option value must be defined. Otherwise an exception will be thrown.

The option length must be greater than or equal to 0. Otherwise an exception will be thrown.

The length of the option value must be less than or equal to the option length. Otherwise an exception will be thrown.

If the system call failed, an exception will be thrown with the error code set to the class id of the L<Error::System> class.

=head2 getsockopt_int

  static method getsockopt_int : int ($sockfd : int, $level : int, $optname : int, $optval_ref : int*);

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
