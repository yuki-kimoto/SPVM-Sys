package SPVM::Sys::Socket::Ipv6_mreq;

1;

=head1 Name

SPVM::Sys::Socket::Ipv6_mreq - struct ipv6_mreq in the C language

=head1 Usage

  use Sys::Socket::Ipv6_mreq;

=head1 Description

C<Sys::Socket::Ipv6_mreq> is the class for the C<struct ipv6_mreq> in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Socket::Ipv6_mreq|SPVM::Sys::Socket::Ipv6_mreq> ();>

Create a new C<Sys::Socket::Ipv6_mreq> object.

=head1 Instance Methods

=head2 

C<method DESTROY : void ();>

=head2 ipv6mr_multiaddr

C<method ipv6mr_multiaddr : L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr> ();>

Get C<ipv6mr_multiaddr>. This is a L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr> object.

=head2 set_ipv6mr_multiaddr

C<method set_ipv6mr_multiaddr : void ($interface : L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr>);>

Set C<ipv6mr_multiaddr>. This is a L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr> object.

=head2 ipv6mr_interface

C<method ipv6mr_interface : int ();>

Get C<ipv6mr_interface>.

=head2 set_ipv6mr_interface

C<method set_ipv6mr_interface : void ($interface : int);>

Set C<ipv6mr_interface>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

