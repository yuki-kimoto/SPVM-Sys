package SPVM::Sys::Poll::PollfdArray;

our $VERSION = '0.01';

1;

=head1 Name

SPVM::Sys::Poll::PollfdArray - Sys::Poll::PollfdArray is a SPVM module

=head1 Usage

  use Sys::Poll::PollfdArray;
  
  my $pollfds = Sys::Poll::PollfdArray->new(1024);
  
=head1 Description

C<Sys::Poll::PollfdArray> is a L<SPVM> module.

C<Sys::Poll::PollfdArray> is the class for the array of C<struct pollfd> in C<C language>.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Class Methods

=head2 new

  static method new : Sys::IO::PollfdArray ($length : int);

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

=head2 length

  method length : int ();

=head2 fd

  method fd : int ($index : int);

=head2 set_fd

  method set_fd : void ($index : int, $fd : int);

=head2 events

  method events : short ($index : int);

=head2 set_events

  method set_events : void ($index : int, $events : short);

=head2 events

  method revents : short ($index : short);

=head2 set_revents

  method set_revents : void ($index : int, $revents : short);

=head1 Copyright & License

Copyright 2022-2022 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

