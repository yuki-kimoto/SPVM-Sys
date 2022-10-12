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
