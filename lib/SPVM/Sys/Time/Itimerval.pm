package SPVM::Sys::Time::Itimerval;

1;

=head1 Name

SPVM::Sys::Time::Itimerval - struct timeval in the C language

=head1 Usage
  
  use Sys::Time::Itimerval;
  
  my $tv = Sys::Time::Itimerval->new;
  
  my $it_interval = $tv->it_interval;
  $tv->set_it_interval(12);
  
  my $it_value = $tv->it_value;
  $tv->set_it_value(34);

=head1 Description

C<Sys::Time::Itimerval> represents C<struct timeval> in the C language.

See L<gettimeofday(2) - Linux man page|https://linux.die.net/man/2/gettimeofday> about C<struct timeval> in Linux.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval> ()>

Creates a new C<Sys::Time::Itimerval> object.

  my $tv = Sys::Time::Itimerval->new;

=head1 Instance Methods

=head2 it_interval

C<method it_interval : L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval> ()>

Copies C<it_interval>.

  my $it_interval = $tv->it_interval;

=head2 set_it_interval

C<method set_it_interval : void ($it_interval : L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval>)>

Sets C<it_interval>.

  $tv->set_it_interval(12);

=head2 it_value
  
C<method it_value : L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval> ()>

Copies C<it_value>.

  my $it_value = $tv->it_value;

=head2 set_it_value

C<method set_it_value : void ($it_value : L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval>)>

Sets C<it_value>.

  $tv->set_it_value(34);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

