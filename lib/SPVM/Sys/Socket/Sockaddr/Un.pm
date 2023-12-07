package SPVM::Sys::Socket::Sockaddr::Un;

1;

=head1 Name

SPVM::Sys::Socket::Sockaddr::Un - struct sockaddr_un in the C language

=head1 Usage

  use Sys::Socket::Sockaddr::Un;

=head1 Description

C<Sys::Socket::Sockaddr::Un> is the class for the C<struct sockaddr_un> in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Inheritance

This class inherits L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un> ();>

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head2 sa_family

C<method sa_family : int ()>

Returns C<sa_family>. This is the overriden method of the L<sa_family|SPVM::Sys::Socket::Sockaddr/"sa_family"> method in the Sys::Socket::Sockaddr class.

=head2 sun_family

C<method sun_family : int ();>

Returns C<sun_family>.

=head2 set_sun_family

C<method set_sun_family : void ($family : int)>

Sets C<sun_family>.

=head2 sun_path

C<method sun_path : string ();>

Copies C<sun_path>.

=head2 set_sun_path

C<method set_sun_path : void ($path : string)>

Sets C<sun_path>.

=head2 size

C<method size : int ()>

The size of C<struct sockaddr_un>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

