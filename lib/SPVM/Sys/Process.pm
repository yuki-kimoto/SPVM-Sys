package SPVM::Sys::Process;

1;

=head1 Name

SPVM::Sys::Process - Process Manipulation

=head1 Usage
  
  use Sys::Process;
  use Sys::Process::Constant as Proc;
  
  # exit
  Sys::Process->exit(Proc->EXIT_FAILURE);
  
  # waitpid
  my $wstatus;
  my $changed_process_id = Sys::Process->waitpid($process_id, \$wstatus, Proc->WNOHANG);
  
  # getpid
  my $process_id = Sys::Process->getpid;
  
  # sleep
  Sys::Process->sleep(5);

=head1 Description

C<Sys::Process> is the class for the process manipulation.

=head1 Class Methods

=head2 alarm

  native static method alarm : int ($seconds : int);

The alarm() function shall cause the system to generate a SIGALRM signal for the process after the number of realtime seconds specified by seconds have elapsed. Processor scheduling delays may prevent the process from handling the signal as soon as it is generated.

See the detail of the L<alerm|https://linux.die.net/man/3/alarm> function in the case of Linux.

=head2 fork

  native static method fork : int ();

The fork() function shall create a new process. The new process (child process) shall be an exact copy of the calling process (parent process) except as detailed below:

See the detail of the L<fork|https://linux.die.net/man/3/fork> function in the case of Linux.

=head2 getpriority

  native static method getpriority : int ($which : int, $who : int);

The getpriority() function shall obtain the nice value of a process, process group, or user. The setpriority() function shall set the nice value of a process, process group, or user to value+ {NZERO}.

See the detail of the L<getpriority|https://linux.die.net/man/3/getpriority> function in the case of Linux.

=head2 setpriority

  native static method setpriority : int ($which : int, $who : int, $prio : int);

The getpriority() function shall obtain the nice value of a process, process group, or user. The setpriority() function shall set the nice value of a process, process group, or user to value+ {NZERO}.

See the detail of the L<setpriority|https://linux.die.net/man/3/setpriority> function in the case of Linux.

=head2 sleep

  native static method sleep : int ($seconds : int);

sleep() makes the calling thread sleep until seconds seconds have elapsed or a signal arrives which is not ignored.

See the detail of the L<sleep|https://linux.die.net/man/3/sleep> function in the case of Linux.

=head2 kill

  native static method kill : int ($pid : int, $sig : int);

The kill() function shall send a signal to a process or a group of processes specified by pid. The signal to be sent is specified by sig and is either one from the list given in <signal.h> or 0. If sig is 0 (the null signal), error checking is performed but no signal is actually sent. The null signal can be used to check the validity of pid.

See the detail of the L<kill|https://linux.die.net/man/3/kill> function in the case of Linux.

=head2 wait

  native static method wait : int ($wstatus : int*);

The wait() and waitpid() functions shall obtain status information pertaining to one of the caller's child processes. Various options permit status information to be obtained for child processes that have terminated or stopped. If status information is available for two or more child processes, the order in which their status is reported is unspecified.

See the detail of the L<wait|https://linux.die.net/man/3/wait> function in the case of Linux.

See L</"Waiting Status Checking Methods"> about checking the waiting status.

=head2 waitpid

  native static method waitpid : int ($pid : int, $wstatus : int*, $options : int);

The wait() and waitpid() functions shall obtain status information pertaining to one of the caller's child processes. Various options permit status information to be obtained for child processes that have terminated or stopped. If status information is available for two or more child processes, the order in which their status is reported is unspecified.

See the detail of the L<waitpid|https://linux.die.net/man/3/wait> function in the case of Linux.

See L<Sys::Process::Constant|SPVM::Sys::Process::Constant> about the constant value for the options.

See L</"Waiting Status Checking Methods"> about checking the waiting status.

=head2 system

  native static method system : int ($command : string);

The value returned is -1 on error (e.g., fork(2) failed), and the return status of the command otherwise. This latter return status is in the format specified in wait(2). Thus, the exit code of the command will be WEXITSTATUS(status). In case /bin/sh could not be executed, the exit status will be that of a command that does exit(127).

See the detail of the L<system|https://linux.die.net/man/3/system> function in the case of Linux.

See L</"Waiting Status Checking Methods"> about checking the return value.

=head2 exit

  native static method exit : int ($status : int);

The exit() function causes normal process termination and the value of status & 0377 is returned to the parent (see wait(2)).

See the detail of the L<exit|https://linux.die.net/man/3/exit> function in the case of Linux.

See L<Sys::Process::Constant|SPVM::Sys::Process::Constant> about the constant value for the status.

=head2 pipe

  native static method pipe : int ($pipe_fds : int[]);

The pipe() function shall create a pipe and place two file descriptors, one each into the arguments fildes[0] and fildes[1], that refer to the open file descriptions for the read and write ends of the pipe. Their integer values shall be the two lowest available at the time of the pipe() call. The O_NONBLOCK and FD_CLOEXEC flags shall be clear on both file descriptors. (The fcntl() function can be used to set both these flags.)

See the detail of the L<pipe|https://linux.die.net/man/3/pipe> function in the case of Linux.

=head2 getpgrp

  native static method getpgrp : int ();

The getpgrp() function shall return the process group ID of the calling process.

See the detail of the L<getpgrp|https://linux.die.net/man/3/getpgrp> function in the case of Linux.

=head2 setpgrp

  native static method setpgrp : int ();

If the calling process is not already a session leader, setpgrp() sets the process group ID of the calling process to the process ID of the calling process. If setpgrp() creates a new session, then the new session has no controlling terminal.

See the detail of the L<setpgrp|https://linux.die.net/man/3/setpgrp> function in the case of Linux.

=head2 getpid

  native static method getpid : int ();

The getpid() function shall return the process ID of the calling process.

See the detail of the L<getpid|https://linux.die.net/man/3/getpid> function in the case of Linux.

=head2 getppid

  native static method getppid : int ();

The getppid() function shall return the parent process ID of the calling process.

See the detail of the L<getppid|https://linux.die.net/man/3/getppid> function in the case of Linux.

=head2 execv

  native static method execv : int ($path : string, $args : string[]);

The exec() family of functions replaces the current process image with a new process image. The functions described in this manual page are front-ends for execve(2). (See the manual page for execve(2) for further details about the replacement of the current process image.)

See the detail of the L<execv|https://linux.die.net/man/3/execv> function in the case of Linux.

=head2 times

  native static method times : long ($buffer : Sys::Process::Tms);

The times() function shall fill the tms structure pointed to by buffer with time-accounting information. The tms structure is defined in <sys/times.h>.

See the detail of the L<times|https://linux.die.net/man/3/times> function in the case of Linux.

=head2 Waiting Status Checking Methods

=head3 WIFEXITED

  native static method WIFEXITED : int ($wstatus : int);

=head3 WEXITSTATUS

  native static method WEXITSTATUS : int ($wstatus : int);

=head3 WIFSIGNALED

  native static method WIFSIGNALED : int ($wstatus : int);

=head3 WTERMSIG

  native static method WTERMSIG : int ($wstatus : int);

=head3 WCOREDUMP

  native static method WCOREDUMP : int ($wstatus : int);

=head3 WIFSTOPPED

  native static method WIFSTOPPED : int ($wstatus : int);

=head3 WSTOPSIG

  native static method WSTOPSIG : int ($wstatus : int);

=head3 WIFCONTINUED

  native static method WIFCONTINUED : int ($wstatus : int);

