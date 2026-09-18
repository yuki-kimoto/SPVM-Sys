package SPVM::Sys::Socket::Util;



1;

=head1 Name

SPVM::Sys::Socket::Util - Socket Utilities

=head1 Description

Sys::Socket::Util class in L<SPVM> has methods for socket utilities.

=head1 Usage

  use Sys::Socket::Util;

=head1 Class Methods

=head2 inet_aton

C<static method inet_aton : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> ($address : string);>

Creates a new L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> object and calls L<Sys::Socket#inet_aton|SPVM::Sys::Socket/"inet_aton"> method with it, and returns it.

=head2 inet_ntoa

C<static method inet_ntoa : string ($in_addr : Sys::Socket::In_addr);>

Calls L<Sys::Socket#inet_ntoa|SPVM::Sys::Socket/"inet_ntoa"> method, and returns its return value.

=head2 inet_pton

C<static method inet_pton : L<Sys::Socket::In_addr_base|SPVM::Sys::Socket::In_addr_base> ($family : int, $address : string);>

Creates a new L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> object or a new L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr> according to the address family $family.

And calls L<Sys::Socket#inet_aton|SPVM::Sys::Socket/"inet_aton"> method with it, and returns it.

Excetpions:

If the address family $family is not available, an excetpion is thrown.

=head2 inet_ntop

C<static method inet_ntop : string ($family : int, $in_addr : L<Sys::Socket::In_addr_base|SPVM::Sys::Socket::In_addr_base>);>

Calls L<Sys::Socket#inet_ntop|SPVM::Sys::Socket/"inet_ntop"> method given enough address buffer $dst.

And the got address $dst is truncated to the length the address and returns it.

=head2 sockaddr_in

C<static method sockaddr_in : L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> ($port : int, $in_addr : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>);>

Creates a new L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> object given the port $port and the address $in_addr, and returns it.

The address family is set to C<AF_INET>.

Exceptions:

$in_addr must be defined. Otherwise an exception is thrown.

=head2 sockaddr_in6

C<static method sockaddr_in6 : L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6> ($port : int, $in6_addr : L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr>);>

Creates a new L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6> object given the port $port and the address $in_addr, and returns it.

The address family is set to C<AF_INET6>.

Exceptions:

$in6_addr must be defined. Otherwise an exception is thrown.

=head2 sockaddr_un

C<static method sockaddr_un : L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un> ($path : string);>

Creates a new L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un> object given the path $path, and returns it.

The address family is set to C<AF_UNIX>.

Exceptions:

$path must be defined. Otherwise an exception is thrown.

=head2 set_tcp_keepalive

C<static method set_tcp_keepalive : void ($socket_fd : int, $onoff : int, $keepidle_sec : int, $keepintvl_sec : int = -1);>

Sets the TCP keep-alive settings (C<SO_KEEPALIVE>, C<TCP_KEEPIDLE>/C<TCP_KEEPALIVE>, and C<TCP_KEEPINTVL>) in a portable way.

Parameters:

=over 2

=item * C<$socket_fd> : The socket file descriptor.

=item * C<$onoff> : Set to 1 to enable TCP keep-alive, or 0 to disable it.

=item * C<$keepidle_sec> : The time (in seconds) the connection remains idle before TCP starts sending keep-alive probes.

=item * C<$keepintvl_sec> : The time (in seconds) between individual keep-alive probes. If this value is negative (default is -1), C<$keepidle_sec> is used for this value for maximum portability.

=back

Notes:

This method ensures consistent keep-alive behavior across different platforms. When C<$keepintvl_sec> is not specified, it applies the same duration (C<$keepidle_sec>) to both the initial idle time and the retransmission interval.

On Windows, this method calls L<Sys::Socket#win_set_tcp_keepalive|SPVM::Sys::Socket/"win_set_tcp_keepalive"> via C<WSAIoctl> with the C<SIO_KEEPALIVE_VALS> control code. The time values are converted to milliseconds.

On macOS, it uses the C<TCP_KEEPALIVE> constant for the idle time, while on other systems like Linux, it uses C<TCP_KEEPIDLE>. It also sets C<TCP_KEEPINTVL> and C<SO_KEEPALIVE> via L<Sys#setsockopt|SPVM::Sys/"setsockopt">.

Note that Windows does not support retrieving these time settings via C<getsockopt>, and the number of retries (C<TCP_KEEPCNT>) is fixed by the system (typically 10 on Windows).

See also L<Sys::Socket#win_set_tcp_keepalive|SPVM::Sys::Socket/"win_set_tcp_keepalive">.

=head1 See Also

=over 2

=item * L<Sys|SPVM::Sys>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

