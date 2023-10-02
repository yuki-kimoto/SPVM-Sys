package SPVM::Sys::Socket::Util;



1;

=head1 Name

SPVM::Sys::Socket::Util - Socket Utilities

=head1 Description

The Sys::Socket::Util class of L<SPVM> has methods for socket utilities.

=head1 Usage

  use Sys::Socket::Util;

=head1 Class Methods

=head2 sockaddr_in

C<static method sockaddr_in : L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> ($port : int, $in_addr : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>);>

Creates a L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> object given a port $port and a L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> object $in_addr, and returns it.

The address family is set to C<AF_INET>.

Exceptions:

$in_addr must be defined. Otherwise an exception is thrown.

=head2 sockaddr_in6

C<static method sockaddr_in6 : L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6> ($port : int, $in6_addr : L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr>);>

Creates a L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6> object given a port $port and a L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr> object $in_addr, and returns it.

The address family is set to C<AF_INET6>.

Exceptions:

$in6_addr must be defined. Otherwise an exception is thrown.

=head2 sockaddr_un

C<static method sockaddr_un : L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un> ($path : string);>

Creates a L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un> object given a path $path, and returns it.

The address family is set to C<AF_UNIX>.

Exceptions:

$path must be defined. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

