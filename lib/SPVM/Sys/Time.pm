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

=head2 clock_getres

  static method clock_getres : int ($clk_id : int, $res : Sys::Time::Timespec)

The functions clock_getres() retrieves the time of the specified clock clk_id.

See L<clock_getres(3) - Linux man page|https://linux.die.net/man/3/clock_getres> in Linux.

The C<$res> is a L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec> object.

=head2 setitimer

  static method setitimer : int ($which : int, $new_value : Sys::Time::Itimerval, $old_value : Sys::Time::Itimerval)

The function setitimer() sets the specified timer to the value in new_value. If old_value is non-NULL, the old value of the timer is stored there.

See L<setitimer(2) - Linux man page|https://linux.die.net/man/2/setitimer> in Linux.

The C<$new_value> is a L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval> object.

The C<$old_value> is a L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval> object.

=head2 getitimer

  static method getitimer : int ($which : int, $curr_value : Sys::Time::Itimerval)

The function getitimer() fills the structure pointed to by curr_value with the current setting for the timer specified by which (one of ITIMER_REAL, ITIMER_VIRTUAL, or ITIMER_PROF).

See L<getitimer(2) - Linux man page|https://linux.die.net/man/2/getitimer> in Linux.

The C<$curr_value> is a L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval> object.

