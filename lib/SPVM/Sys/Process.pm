package SPVM::Sys::Process;

1;

=head1 Name

SPVM::Sys::Process - Process Manipulation

=head1 Usage
  
  use Sys::Process;

=head1 Description

C<Sys::Process> is the class for the process manipulation.

=head1 Class Methods

=head2 alarm

  native static method alarm : int ($seconds : int);

=head2 fork

  native static method fork : int ();

=head2 getpriority

  native static method getpriority : int ($which : int, $who : int);

=head2 setpriority

  native static method setpriority : int ($which : int, $who : int, $prio : int);

=head2 sleep

  native static method sleep : int ($seconds : int);

=head2 kill

  native static method kill : int ($pid : int, $sig : int);

=head2 wait

  native static method wait : int ($wstatus : int*);

=head2 waitpid

  native static method waitpid : int ($pid : int, $wstatus : int*, $options : int);

=head2 system

  native static method system : int ($command : string);

=head2 exit

  native static method exit : int ($status : int);

=head2 pipe

  native static method pipe : int ($pipe_fds : int[]);

=head2 getpgrp

  native static method getpgrp : int ();

=head2 setpgrp

  native static method setpgrp : int ();

=head2 getpid

  native static method getpid : int ();

=head2 getppid

  native static method getppid : int ();

=head2 execv

  native static method execv : int ($path : string, $args : string[]);

=head2 times

  native static method times : long ($buffer : Sys::Process::Tms);
