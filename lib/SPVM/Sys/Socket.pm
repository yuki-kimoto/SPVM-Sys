package SPVM::Sys::Socket;

1;

=head1 Name

SPVM::Sys::Socket - System Calls for Sockets

=head1 Description

The Sys::Socket class in L<SPVM> has methods to call system calls for sockets.

=head1 Usage
  
  use Sys::Socket;
  use Sys::Socket::Constant as SOCKET;
  
  my $socket_fd = Sys::Socket->socket(SOCKET->AF_INET, SOCKET->SOCK_STREAM, 0);

=head1 Class Methods

=head2 htonl

C<static method htonl : int ($hostlong : int);>

Calls the L<htonl|https://linux.die.net/man/3/htonl> function and returns its return value.

=head2 htons

C<static method htons : short ($hostshort : short);>

Calls the L<htons|https://linux.die.net/man/3/htons> function and returns its return value.

=head2 ntohl

C<static method ntohl : int ($netlong : int);>

Calls the L<ntohl|https://linux.die.net/man/3/ntohl> function and returns its return value.

=head2 ntohs

C<static method ntohs : short ($netshort : short);>

Calls the L<ntohs|https://linux.die.net/man/3/ntohs> function and returns its return value.

=head2 inet_aton

C<static method inet_aton : int ($cp : string, $inp : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>);>

Calls the L<inet_aton|https://linux.die.net/man/3/inet_aton> function and returns its return value.

=head2 inet_ntoa

C<static method inet_ntoa : string ($in : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>);>

Calls the L<inet_ntoa|https://linux.die.net/man/3/inet_ntoa> function and returns its return value.

=head2 inet_pton

C<static method inet_pton : int ($af : int, $src : string, $dst : object of Sys::Socket::In_addr|Sys::Socket::In6_addr);>

Calls the L<inet_pton|https://linux.die.net/man/3/inet_pton> function and returns its return value.

See L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant> about constant values given to $af.

=head2 inet_ntop

C<static method inet_ntop : mutable string ($af : int, $src : object of Sys::Socket::In_addr|Sys::Socket::In6_addr, $dst : mutable string, $size : int);>

Calls the L<inet_ntop|https://linux.die.net/man/3/inet_ntop> function and returns its return value.

See L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant> about constant values given to $af.

=head2 socket

C<static method socket : int ($domain : int, $type : int, $protocol : int);>

Calls the L<socket|https://linux.die.net/man/2/socket> function and returns its return value.

See L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant> about constant values given to $domain, $type, and $protocal.

=head2 connect

C<static method connect : int ($sockfd : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen : int);>

Calls the L<connect|https://linux.die.net/man/2/connect> function and returns its return value.

=head2 bind

C<static method bind : int ($sockfd : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen : int);>

Calls the L<bind|https://linux.die.net/man/2/bind> function and returns its return value.

=head2 accept

C<static method accept : int ($sockfd : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen_ref : int*);>

Calls the L<accept|https://linux.die.net/man/2/accept> function and returns its return value.

=head2 listen

C<static method listen : int ($sockfd : int, $backlog : int);>

Calls the L<listen|https://linux.die.net/man/2/listen> function and returns its return value.

=head2 shutdown

C<static method shutdown : int ($sockfd : int, $how : int);>

Calls the L<shutdown|https://linux.die.net/man/2/shutdown> function and returns its return value.

See L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant> about constant values given to $how.

=head2 recv

C<static method recv : int ($sockfd : int, $buf : mutable string, $len : int, $flags : int, $buf_offset : int = 0);>

Calls the L<recv|https://linux.die.net/man/2/recv> function and returns its return value.

=head2 send

C<static method send : int ($sockfd : int, $buf : string, $len : int, $flags : int, $buf_offset : int = 0);>

Calls the L<send|https://linux.die.net/man/2/send> function and returns its return value.

=head2 sendto

C<static method sendto : int ($sockfd : int, $buf : string, $len : int, $flags : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen : int, $buf_offset : int = 0);>

Calls the L<sendto|https://linux.die.net/man/2/sendto> function and returns its return value.

=head2 getpeername

C<static method getpeername : int ($sockfd : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen_ref : int*);>

Calls the L<getpeername|https://linux.die.net/man/2/getpeername> function and returns its return value.

Exceptions:

The address must be defined. Otherwise an exception is thrown.

If the system call failed, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 getsockname

C<static method getsockname : int ($sockfd : int, $addr : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $addrlen_ref : int*);>

Calls the L<getsockname|https://linux.die.net/man/2/getsockname> function and returns its return value.

Excetpions:

The address must be defined. Otherwise an exception is thrown.

If the getsockname function failed, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 socketpair

C<static method socketpair : int ($domain : int, $type : int, $protocol : int, $sv : int[]);>

Calls the L<socketpair|https://linux.die.net/man/2/socketpair> function and returns its return value.

See L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant> about constant values given to $domain, $type, and $protocol.

Exceptions:

The output of the socket pair(sv) must be defined. Otherwise an exception is thrown.

The length of the output of the socket pair(sv) must be greater than or equal to 2. Otherwise an exception is thrown.

If the system call failed, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 setsockopt

C<static method setsockopt : int ($sockfd : int, $level : int, $optname : int, $optval : string, $optlen : int);>

Calls the L<setsockopt|https://linux.die.net/man/2/setsockopt> function and returns its return value.

Exceptions:

The option value must be defined. Otherwise an exception is thrown.

The option length must be greater than or equal to 0. Otherwise an exception is thrown.

The length of the option value must be less than or equal to the option length. Otherwise an exception is thrown.

If the system call failed, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 getsockopt

C<static method getsockopt : int ($sockfd : int, $level : int, $optname : int, $optval : mutable string, $optlen_ref : int*);>

Calls the L<getsockopt|https://linux.die.net/man/2/getsockopt> function and returns its return value.

Exceptions:

The option value must be defined. Otherwise an exception is thrown.

The option length must be greater than or equal to 0. Otherwise an exception is thrown.

The length of the option value must be less than or equal to the option length. Otherwise an exception is thrown.

If the system call failed, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

Excamples:

$optval is a string. The following is an example to get an int value.

  my $optval_int_ref = [0];
  Fn->memcpy($result_ref, 0, $optval, 0, 4);
  my $optval_int = $optval_int_ref->[0];

=head2 getaddrinfo

C<static method getaddrinfo : int ($node : string, $service : string,>
                $hints : Sys::Socket::Addrinfo,
                $res : Sys::Socket::Addrinfo[]);

Calls the L<getaddrinfo|https://linux.die.net/man/3/getaddrinfo> function and returns its return value.

Exceptions:

The response must be defined. Otherwise an exception is thrown.

The length of the array of the response must be greater than or equal to 1. Otherwise an exception is thrown.

If a system error occur, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 getnameinfo

C<static method getnameinfo : int ($sa : L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>, $salen : int,>
                $host : mutable string, $hostlen : int,
                $serv : mutable string, $servlen : int, $flags : int);

Calls the L<getnameinfo|https://linux.die.net/man/3/getaddrinfo> function and returns its return value.

Excetpions:

If a system error occur, an exception is thrown with C<eval_error_id> set to the class id of the L<Error::System> class.

=head2 gai_strerror

C<static method gai_strerror : string($errcode : int);>

Calls the L<getnameinfo|https://linux.die.net/man/3/gai_strerror> function and returns its return value.

=head2 close

C<static method close : int ($fd : int);>

Calls the L</"closesocket"> method in Windows.

Calls the L<close|Sys::IO/"close"> method in the the L<Sys::IO|SPVM::Sys::IO> class in other OSs.

=head2 sockatmark

C<static method sockatmark : int ($sockfd : int);>

Calls the L<sockatmark|https://linux.die.net/man/3/sockatmark> function and returns its return value.

=head2 ioctlsocket

C<static method ioctlsocket : int ($fd : int, $request : int, $request_arg_ref : int[] = undef);>

Calls the L<ioctlsocket|https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket> function and returns its return value.

See the L<ioctlsocket|https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket> function in Windows.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

