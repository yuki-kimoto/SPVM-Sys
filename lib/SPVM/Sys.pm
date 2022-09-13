package SPVM::Sys;

our $VERSION = '0.01';

1;

=head1 Name

SPVM::Sys - System Calls such as File IO, User, Process, Socket,

=head1 Caution

The C<Sys> module and the system modules will be highly changed without warnings.

L<SPVM> itself is yet experimental release.

=head1 Usage

  use Sys;
  
  my $is_windows = Sys->is_D_WIN32;

=head1 Description

C<Sys> is the class for system utilities such as file IO, user manipulation, process, socket,

=head1 Class Methods

=head2 is_D_WIN32

  static method is_D_WIN32 : int ()

If C<_WIN32> in C<C language> is defined, return C<1>. Otherwize return C<0>.

=head1 System Modules

=over 2

=item * L<Sys::IO|SPVM::Sys::IO>

=item * L<Sys::Socket|SPVM::Sys::Socket>

=item * L<Sys::Process|SPVM::Sys::Process>

=item * L<Sys::User|SPVM::Sys::User>

=item * L<Sys::FiteTest|SPVM::Sys::FiteTest>

=back

=head1 Copyright & License

Copyright Yuki Kimoto 2022-2022, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

