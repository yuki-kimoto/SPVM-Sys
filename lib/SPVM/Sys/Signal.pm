package SPVM::Sys::Signal;

1;

=head1 Name

SPVM::Sys::Signal - Signals

=head1 Description

The Sys::Signal class has methods to manipulate signals.

=head1 Usage
  
  use Sys::Signal;
  use Sys::Signal::Constant as SIGNAL;
  
  Sys::Signal->raise(SIGNAL->SIGTERM);
  
  Sys::Signal->kill($process_id, SIGNAL->SIGINT);
  
  my $old_signal_handler = Sys::Signal->signal(SIGNAL->SIGTERM, Sys::Signal->SIG_IGN);

=head1 Class Methods

=head2 raise

C<static method raise : int ($sig : int);>

Calls the L<raise|https://linux.die.net/man/3/raise> function and returns its return value.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about constant values given to $sig.

Exceptions:

If the raise function failed, an exception is thrown and C<eval_error_id> is set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 kill

C<static method kill : int ($pid : int, $sig : int);>

Calls the L<kill - Linux man page|https://linux.die.net/man/2/kill> function and returns its return value.

See L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant> about constant values given to $sig.

Exceptions:

If the kill function failed, an exception is thrown and C<eval_error_id> is set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

If the OS is Windows, the following exception is thrown. kill is not supported in this system(defined(_WIN32)).

=head2 alarm

C<static method alarm : int ($seconds : int);>

Calls the L<alarm|https://linux.die.net/man/2/alarm> function and returns its return value.

Exceptions:

If the alarm function failed, an exception is thrown and C<eval_error_id> is set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

If the OS is Windows, the following exception is thrown. alarm is not supported in this system(defined(_WIN32)).

=head2 ualarm

C<static method ualarm : int ($usecs : int, $interval : int);>

Calls the L<ualarm|https://linux.die.net/man/3/ualarm> function and returns its return value.

Exceptions:

If the OS is Windows, the following exception is thrown. ualarm is not supported in this system(defined(_WIN32)).

=head2 signal

C<static method signal : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler> ($signum : int, $handler : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler>);>

signal() sets the disposition of the signal signum to handler.

See L<signal(2) - Linux man page|https://linux.die.net/man/2/signal> in Linux.

Constant values specified in C<$signum> is defined in L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>.

Exceptions:

$handler must be defined. Otherwise an exception is thrown.

=head2 signal_go

C<static method signal_go : Sys::Signal::Handler ($signum : int);>

signal() sets the disposition of the signal signum to L</"SIG_GO"> handler. This must not be used except for L<Go::OS::Signal|SPVM::Go::OS::Signal>. 

Returns the old signal handler.

=head2 SIG_DFL

  static method SIG_DFL : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler> ()

Creates a new signal handler that represents C<SIG_DFL>.

=head2 SIG_IGN

  static method SIG_IGN : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler> ();

Creates a new signal handler that represents C<SIG_IGN>.

=head2 SIG_GO

  static method SIG_GO : L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler> ();

Creates a new signal handler that represents the signal handler for L<Go::OS::Signal|SPVM::Go::OS::Signal>.

=head2 SET_SIG_GO_WRITE_FD

  static method SET_SIG_GO_WRITE_FD : void ();

Set a write file descriptor for L<Go::OS::Signal|SPVM::Go::OS::Signal>. This must not be used except for L<Go::OS::Signal|SPVM::Go::OS::Signal>. 

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

