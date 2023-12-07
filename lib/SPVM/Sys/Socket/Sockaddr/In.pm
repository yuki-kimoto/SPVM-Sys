package SPVM::Sys::Socket::Sockaddr::In;

1;

=head1 Name

SPVM::Sys::Socket::Sockaddr::In - struct sockaddr_in in the C language

=head1 Usage

  use Sys::Socket::Sockaddr::In;

=head1 Description

C<Sys::Socket::Sockaddr::In> is the class for the C<struct sockaddr_in> in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Inheritance

This class inherits L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> ();>

Create a new C<Sys::Socket::Sockaddr::In> object.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head2 sa_family

C<method sa_family : int ()>

Returns C<sa_family>. This is the overriden method of the L<sa_family|SPVM::Sys::Socket::Sockaddr/"sa_family"> method in the Sys::Socket::Sockaddr class.

=head2 sin_family

C<method sin_family : int ();>
  
Returns C<sin_family>.

=head2 set_sin_family

C<method set_sin_family : void ($family : int);>

Sets C<sin_family>.

=head2 sin_addr

C<method sin_addr : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> ();>

Copies C<sin_addr>. This is a L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> object.

=head2 set_sin_addr

C<method set_sin_addr : void ($address : L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>);>

Sets C<sin_addr>. This is a L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr> object.

=head2 sin_port

C<method sin_port : int ();>

Returns C<sin_port>.

=head2 set_sin_port

C<method set_sin_port : void ($port : int);>

Sets C<sin_port>.

=head2 size

C<method size : int ()>

The size of C<struct sockaddr_in>.

=head2 clone

C<method clone : L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In> ()>

Clones this object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

