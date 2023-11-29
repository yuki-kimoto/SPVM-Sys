package SPVM::Sys::Select::Fd_set;

1;

=head1 Name

SPVM::Sys::Select::Fd_set - fd_set Type in C Language

=head1 Usage

  use Sys::Select::Fd_set;
  
  my $fd_set = Sys::Select::Fd_set->new;

=head1 Description

C<Sys::Select::Fd_set> is the class for the C<fd_set> type in the C language.

See L<select(2) - Linux man page|https://linux.die.net/man/2/select> in Linux.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Select::Fd_set|SPVM::Sys::Select::Fd_set> ();>

Create a new C<Sys::Select::Fd_set> object.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

