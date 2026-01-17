package SPVM::Sys::Time::Timespec;

1;

=head1 Name

SPVM::Sys::Time::Timespec - struct timespec in the C language

=head1 Description

Sys::Time::Timespec class in L<SPVM> represents L<struct timespec|https://linux.die.net/man/2/clock_gettime> in the C language.

=head1 Usage
  
  use Sys::Time::Timespec;
  
  my $ts = Sys::Time::Timespec->new;
  
  my $ts = Sys::Time::Timespec->new(5, 300_000_000);
  
  my $ts_sec = $ts->tv_sec;
  $ts->set_tv_sec(12);
  
  my $ts_nsec = $ts->tv_nsec;
  $ts->set_tv_nsec(34);

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Class Methods

=head2 new

C<static method new : L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> ($tv_sec : long = 0, $tv_nsec : long = 0);>

Creates a new L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object with the given L</"tv_sec"> and L</"tv_nsec">.

Before creating the object, this method calls L</"check"> to validate the range of the arguments. If the arguments are invalid (e.g., L</"tv_nsec"> is out of the range [0, 999,999,999]), an exception is thrown.

The internal L<struct timespec|https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/time.h.html> is allocated in memory and managed by this object.

Example:

  my $ts = Sys::Time::Timespec->new(1737158400L, 500L);
  
=head2 check

C<static method check : void ($tv_sec : long, $tv_nsec : long);>

Validates the range of the given L</"tv_sec"> and L</"tv_nsec">.

If L</"tv_nsec"> is not greater than or equal to 0 and less than or equal to 999,999,999, an exception is thrown.

=head1 Instance Methods

=head2 tv_sec

C<method tv_sec : long ()>

Returns C<tv_sec>.

=head2 set_tv_sec

C<method set_tv_sec : void ($ts_sec : long);>

Sets C<tv_sec>.

=head2 tv_nsec
  
C<method tv_nsec : long ()>

Returns C<tv_nsec>.

=head2 set_tv_nsec

C<method set_tv_nsec : void ($ts_nsec : long);>

Sets C<tv_nsec>.

=head2 clone

C<method clone : L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> ();>

Creates a new L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object that is a copy of the current instance.

The new object will have the same L</"tv_sec"> and L</"tv_nsec"> values as the original.

=head2 DESTROY

C<native method DESTROY : void ();>

The destructor.

=head1 See Also

=over 2

=item * L<Sys|SPVM::Sys>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

