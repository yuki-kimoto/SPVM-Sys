package SPVM::Sys::Socket::Sockaddr::Storage;

1;

=head1 Name

SPVM::Sys::Socket::Sockaddr::Storage - struct sockaddr_storage in the C language

=head1 Usage

  use Sys::Socket::Sockaddr::Storage;

=head1 Description

C<Sys::Socket::Sockaddr::Storage> is the class for the C<struct sockaddr_storage> in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Inheritance

This class inherits L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Socket::Sockaddr::Storage|SPVM::Sys::Socket::Sockaddr::Storage> ();>

Create a new C<Sys::Socket::Sockaddr::Storage> object.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ()>

The destructor.

=head2 sa_family

C<method sa_family : int ()>

Returns C<sa_family>. This is the overriden method of the L<sa_family|SPVM::Sys::Socket::Sockaddr/"sa_family"> method in the Sys::Socket::Sockaddr class.

=head2 ss_family

C<method ss_family : int ()>

Returns C<ss_family>.

=head2 set_ss_family

C<method set_ss_family : void ($family : int)>

Sets C<ss_family>.

=head2 size

C<method size : int ()>

The size of C<struct sockaddr_storage>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

