package SPVM::Sys::Signal;

1;

=head1 Name

SPVM::Sys::Signal - Signal System Call

=head1 Usage
  
  use Sys::Signal;
  use Sys::Signal::Constant as SIGNAL;
  
  # kill
  Sys::Signal->kill($process_id, SIGNAL->SIGINT);

=head1 Description

C<Sys::Signal> provides the methods to call the system call for the signal.

=head1 Class Methods

=head2 kill

  static method kill : int ($pid : int, $sig : int)

The kill() system call can be used to send any signal to any process group or process.

See the detail of the L<kill|https://linux.die.net/man/2/kill> function in the case of Linux.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the signal numbers specified by C<$sig> 

=head2 alarm

  static method alarm : int ($seconds : int)

alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds seconds.

See the detail of the L<alerm|https://linux.die.net/man/2/alarm> function in the case of Linux.

=head2 ualarm

  static method ualarm : long ($usecs : long, $interval : long)

The ualarm() function causes the signal SIGALRM to be sent to the invoking process after (not less than) usecs microseconds. The delay may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.

See the detail of the L<https://linux.die.net/man/3/ualarm> function in the case of Linux.
