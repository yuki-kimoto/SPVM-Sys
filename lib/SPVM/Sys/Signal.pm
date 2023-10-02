package SPVM::Sys::Signal;

1;

=head1 Name

SPVM::Sys::Signal - Signal System Call

=head1 Usage
  
  use Sys::Signal;
  use Sys::Signal::Constant as SIGNAL;
  
  Sys::Signal->raise(SIGNAL->SIGTERM);

  Sys::Signal->kill($process_id, SIGNAL->SIGINT);

  Sys::Signal->signal(SIGNAL->SIGTERM, Sys::Signal->SIG_IGN);

=head1 Description

C<Sys::Signal> provides the methods to call the system call for the signal.

=head1 Class Variables

=head2 $SIG_DFL

  our $SIG_DFL : ro Sys::Signal::Handler::Default;

Gets a singlton L<Sys::Signal::Handler::Default|SPVM::Sys::Signal::Handler::Default> object that represents C<SIG_DFL> in C<C Language>.

=head2 $SIG_IGN

  our $SIG_IGN : ro Sys::Signal::Handler::Ignore;

Gets a singlton L<Sys::Signal::Handler::Ignore|SPVM::Sys::Signal::Handler::Ignore> object that represents C<SIG_IGN> in C<C Language>.

=head1 Class Methods

=head2 raise

C<static method raise : int ($sig : int)>

The raise() function sends a signal to the calling process or thread.

See L<raise(3) - Linux man page|https://linux.die.net/man/3/raise> in Linux.

Constant values specified in C<$sig> is defined in L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>.

=head2 kill

C<static method kill : int ($pid : int, $sig : int)>

The kill() system call can be used to send any signal to any process group or process.

See the L<kill(2) - Linux man page|https://linux.die.net/man/2/kill> in Linux.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about the signal numbers specified by C<$sig> 

Constant values specified in C<$sig> is defined in L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>.

=head2 alarm

C<static method alarm : int ($seconds : int)>

alarm() arranges for a SIGALRM signal to be delivered to the calling process in seconds seconds.

See L<alarm(2) - Linux man page|https://linux.die.net/man/2/alarm> in Linux.

=head2 ualarm

C<static method ualarm : int ($usecs : int, $interval : int)>

The ualarm() function causes the signal SIGALRM to be sent to the invoking process after (not less than) usecs microseconds. The delay may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.

See L<ualarm(3) - Linux man page|https://linux.die.net/man/3/ualarm> in Linux.

=head2 signal

C<static method signal : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler> ($signum : int, $handler : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler>);>

signal() sets the disposition of the signal signum to handler.

See L<signal(2) - Linux man page|https://linux.die.net/man/2/signal> in Linux.

Constant values specified in C<$signum> is defined in L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>.

The C<$handler> must be a L<Sys::Signal::Handler::Default|SPVM::Sys::Signal::Handler::Default> object or a L<Sys::Signal::Handler::Ignore|SPVM::Sys::Signal::Handler::Ignore> object

Exceptions:

$handler must be defined. Otherwise an exception is thrown.

$handler must be a Sys::Signal::Handler::Default object or a Sys::Signal::Handler::Ignore object. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

