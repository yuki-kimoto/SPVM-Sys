package SPVM::Sys::Process;

1;

=head1 Name

SPVM::Sys::Process - Process System Call

=head1 Usage
  
  use Sys::Process;
  use Sys::Process::Constant as PROCESS;
  
  # exit
  Sys::Process->exit(PROCESS->EXIT_FAILURE);
  
  # waitpid
  my $wstatus;
  my $changed_process_id = Sys::Process->waitpid($process_id, \$wstatus, PROCESS->WNOHANG);
  
  # getpid
  my $process_id = Sys::Process->getpid;
  
  # sleep
  Sys::Process->sleep(5);

=head1 Description

C<Sys::Process> provides the methods to call the system call for the process manipulation.

=head1 Class Methods

=head2 fork

C<static method fork : int ();>

fork() creates a new process by duplicating the calling process. The new process, referred to as the child, is an exact duplicate of the calling process, referred to as the parent, except for the following points:

See the detail of the L<fork|https://linux.die.net/man/2/fork> function in the case of Linux.

=head2 getpriority

C<static method getpriority : int ($which : int, $who : int);>

The scheduling priority of the process, process group, or user, as indicated by which and who is obtained with the getpriority() call and set with the setpriority() call.

See the detail of the L<getpriority|https://linux.die.net/man/2/getpriority> function in the case of Linux.

=head2 setpriority

C<static method setpriority : int ($which : int, $who : int, $prio : int);>

The scheduling priority of the process, process group, or user, as indicated by which and who is obtained with the getpriority() call and set with the setpriority() call.

See the detail of the L<setpriority|https://linux.die.net/man/2/setpriority> function in the case of Linux.

=head2 sleep

C<static method sleep : int ($seconds : int);>

sleep() makes the calling thread sleep until seconds seconds have elapsed or a signal arrives which is not ignored.

See the detail of the L<sleep|https://linux.die.net/man/3/sleep> function in the case of Linux.

=head2 wait

C<static method wait : int ($wstatus : int*);>

All of these system calls are used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed. A state change is considered to be: the child terminated; the child was stopped by a signal; or the child was resumed by a signal. In the case of a terminated child, performing a wait allows the system to release the resources associated with the child; if a wait is not performed, then the terminated child remains in a "zombie" state (see NOTES below).

See the detail of the L<wait|https://linux.die.net/man/2/wait> function in the case of Linux.

See L</"Waiting Status Checking Methods"> about checking the waiting status.

=head2 waitpid

C<static method waitpid : int ($pid : int, $wstatus : int*, $options : int);>

All of these system calls are used to wait for state changes in a child of the calling process, and obtain information about the child whose state has changed. A state change is considered to be: the child terminated; the child was stopped by a signal; or the child was resumed by a signal. In the case of a terminated child, performing a wait allows the system to release the resources associated with the child; if a wait is not performed, then the terminated child remains in a "zombie" state (see NOTES below).

See the detail of the L<waitpid|https://linux.die.net/man/2/waitpid> function in the case of Linux.

See L<Sys::Process::Constant|SPVM::Sys::Process::Constant> about the constant value for the options.

See L</"Waiting Status Checking Methods"> about checking the waiting status.

=head2 system

C<static method system : int ($command : string);>

system() executes a command specified in command by calling /bin/sh -c command, and returns after the command has been completed. During execution of the command, SIGCHLD will be blocked, and SIGINT and SIGQUIT will be ignored.

See the detail of the L<system|https://linux.die.net/man/3/system> function in the case of Linux.

See L</"Waiting Status Checking Methods"> about checking the return value.

=head2 exit

C<static method exit : int ($status : int);>

The exit() function causes normal process termination and the value of status & 0377 is returned to the parent (see wait(2)).

See the detail of the L<exit|https://linux.die.net/man/3/exit> function in the case of Linux.

See L<Sys::Process::Constant|SPVM::Sys::Process::Constant> about the constant value for the status.

=head2 pipe

C<static method pipe : int ($pipe_fds : int[]);>

pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe. For further details, see pipe(7).

See the detail of the L<pipe|https://linux.die.net/man/2/pipe> function in the case of Linux.

=head2 _pipe

  static method _pipe : int ($pipe_fds : int[], $psize : int, $textmode : int);

See the detail of the L<_pipe|https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/pipe?view=msvc-170> function in Windows.

=head2 getpgid

C<static method getpgid : int ($pid : int);>

All of these interfaces are available on Linux, and are used for getting and setting the process group ID (PGID) of a process. The preferred, POSIX.1-specified ways of doing this are: getpgid(void), for retrieving the calling process's PGID; and setpgid(), for setting a process's PGID.

See the detail of the L<getpgid|https://linux.die.net/man/2/getpgid> function in the case of Linux.

=head2 setpgid

C<static method setpgid : int ($pid : int, $pgid : int);>

All of these interfaces are available on Linux, and are used for getting and setting the process group ID (PGID) of a process. The preferred, POSIX.1-specified ways of doing this are: getpgid(void), for retrieving the calling process's PGID; and setpgid(), for setting a process's PGID.

See the detail of the L<setpgid|https://linux.die.net/man/2/setpgid> function in the case of Linux.

=head2 getpid

C<static method getpid : int ();>

getpid() returns the process ID of the calling process. (This is often used by routines that generate unique temporary filenames.)

See the detail of the L<getpid|https://linux.die.net/man/2/getpid> function in the case of Linux.

=head2 getppid

C<static method getppid : int ();>

getppid() returns the process ID of the parent of the calling process.

See the detail of the L<getppid|https://linux.die.net/man/2/getppid> function in the case of Linux.

=head2 execv

C<static method execv : int ($path : string, $args : string[]);>

The execv(), execvp(), and execvpe() functions provide an array of pointers to null-terminated strings that represent the argument list available to the new program. The first argument, by convention, should point to the filename associated with the file being executed. The array of pointers must be terminated by a NULL pointer.

See the detail of the L<https://linux.die.net/man/3/execv> function in the case of Linux.

=head2 Waiting Status Checking Methods

=head3 WIFEXITED

C<static method WIFEXITED : int ($wstatus : int);>

=head3 WEXITSTATUS

C<static method WEXITSTATUS : int ($wstatus : int);>

=head3 WIFSIGNALED

C<static method WIFSIGNALED : int ($wstatus : int);>

=head3 WTERMSIG

C<static method WTERMSIG : int ($wstatus : int);>

=head3 WCOREDUMP

C<static method WCOREDUMP : int ($wstatus : int);>

=head3 WIFSTOPPED

C<static method WIFSTOPPED : int ($wstatus : int);>

=head3 WSTOPSIG

C<static method WSTOPSIG : int ($wstatus : int);>

=head3 WIFCONTINUED

C<static method WIFCONTINUED : int ($wstatus : int);>

=head2 usleep

C<static method usleep : int ($usec : int);>

The usleep() function suspends execution of the calling thread for (at least) usec microseconds. The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers.

See the detail of the L<usleep|https://linux.die.net/man/3/usleep> function in the case of Linux.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

