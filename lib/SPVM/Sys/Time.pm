package SPVM::Sys::Time;

1;

=head1 Name

SPVM::Sys::Time - Time System Call

=head1 Usage
  
  use Sys::Time;

=head1 Description

C<Sys::Process> provides the methods to call the system call for the time manipulation.

=head1 Class Methods

=head2 gettimeofday

  static method gettimeofday ($tv : Sys::Time::Timeval, $tz : Sys::Time::Timezone);

The functions gettimeofday() can get the time as well as a timezone. The tv argument is a struct timeval (as specified in <sys/time.h>):

See L<gettimeofday(2) - Linux man page|https://linux.die.net/man/2/gettimeofday> in Linux.

=head2 timersub

  static method timersub : void ($a : Sys::Time::Timeval, $b : Sys::Time::Timeval, $res : Sys::Time::Timeval);

timersub() subtracts the time value in b from the time value in a, and places the result in the timeval pointed to by res. The result is normalized such that res->tv_usec has a value in the range 0 to 999,999.

See L<timersub(3) - Linux man page|https://linux.die.net/man/3/timersub> in Linux.

Each C<$a>, C<$b>, and C<$res> is a L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval> object.
