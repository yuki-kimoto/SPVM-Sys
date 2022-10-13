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

  static method gettimeofday ($tv : Sys::Time::Timeval, $tz : Sys::Time::Timezone)

The functions gettimeofday() can get the time as well as a timezone. The tv argument is a struct timeval (as specified in <sys/time.h>):

See L<gettimeofday(2) - Linux man page|https://linux.die.net/man/2/gettimeofday> in Linux.

=head2 clock

  static method clock : long ()

The value returned is the CPU time used so far as a clock_t; to get the number of seconds used, divide by CLOCKS_PER_SEC.

See L<clock(3) - Linux man page|https://linux.die.net/man/3/clock> in Linux.

=head2 clock_gettime

  static method clock_gettime : int ($clk_id : int, $tp : Sys::Time::Timespec)

The functions clock_gettime() retrieves the time of the specified clock clk_id.

See L<clock_gettime(3) - Linux man page|https://linux.die.net/man/3/clock_gettime> in Linux.

The C<$tp> is a L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object.
