package SPVM::Sys;

our $VERSION = '0.42';

1;

=head1 Name

SPVM::Sys - System Calls for File IO, User, Process, Signal, Socket

=head1 Description

C<SPVM::Sys> is the C<Sys> class in L<SPVM> language. It provides system calls such as file IO, user manipulation, process, socket, time,

This distribution contains many modules for system calls such as L<Sys::IO|SPVM::Sys::IO>. See L</"Modules">.

=head1 Usage

  use Sys;
  
  my $path = Sys->getenv("PATH");
  
  my $is_windows = Sys->defined("_WIN32");

=head1 Class Methods

=head2 Environment Variable

=head3 getenv

  static method getenv : string ($name : string);

The alias for the L<getenv|SPVM::Sys::Env/"getenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head3 setenv

  static method setenv : int ($name : string, $value : string, $overwrite : int);

The alias for the L<setenv|SPVM::Sys::Env/"setenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head3 unsetenv

  static method unsetenv : int ($name : string);

The alias for the L<unsetenv|SPVM::Sys::Env/"unsetenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head2 OS

=head3 defined

  static method defined : int ($macro_name : string, $value = undef : object of Int|Long|Double);

The alias for the L<defined|SPVM::Sys::OS/"defined"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head3 get_osname

  static method get_osname : string ()

The alias for the L<get_osname|SPVM::Sys::OS/"get_osname"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head3 is_windows

  static method is_windows : int ();

The alias for the L<is_windows|SPVM::Sys::OS/"is_windows"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head2 File Test

=head3 A

  static method A : double ($file : string);

The alias for the L<A|SPVM::Sys::FileTest/"A"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 C

  static method C : double ($file : string);

The alias for the L<C|SPVM::Sys::FileTest/"C"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 M

  static method M : double ($file : string);

The alias for the L<M|SPVM::Sys::FileTest/"M"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 O

  static method O : int ($file : string);

The alias for the L<O|SPVM::Sys::FileTest/"O"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 R

  static method R : int ($file : string);

The alias for the L<R|SPVM::Sys::FileTest/"R"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 S

  static method S : int ($file : string);

The alias for the L<S|SPVM::Sys::FileTest/"S"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 W

  static method W : int ($file : string);

The alias for the L<W|SPVM::Sys::FileTest/"W"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 X

  static method X : int ($file : string);

The alias for the L<X|SPVM::Sys::FileTest/"X"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 b

  static method b : int ($file : string);

The alias for the L<b|SPVM::Sys::FileTest/"b"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 c

  static method c : int ($file : string);

The alias for the L<c|SPVM::Sys::FileTest/"c"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 d

  static method d : int ($file : string);

The alias for the L<d|SPVM::Sys::FileTest/"d"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 e

  static method e : int ($file : string);

The alias for the L<e|SPVM::Sys::FileTest/"e"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 f

  static method f : int ($file : string);

The alias for the L<f|SPVM::Sys::FileTest/"f"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 g

  static method g : int ($file : string);

The alias for the L<g|SPVM::Sys::FileTest/"g"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 k

  static method k : int ($file : string);

The alias for the L<k|SPVM::Sys::FileTest/"k"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 l

  static method l : int ($file : string);

The alias for the L<l|SPVM::Sys::FileTest/"l"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 o

  static method o : int ($file : string);

The alias for the L<o|SPVM::Sys::FileTest/"o"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 p

  static method p : int ($file : string);

The alias for the L<p|SPVM::Sys::FileTest/"p"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 r

  static method r : int ($file : string);

The alias for the L<r|SPVM::Sys::FileTest/"r"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 s

  static method s : long ($file : string);

The alias for the L<s|SPVM::Sys::FileTest/"s"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 u

  static method u : int ($file : string);

The alias for the L<u|SPVM::Sys::FileTest/"u"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 w

  static method w : int ($file : string);

The alias for the L<w|SPVM::Sys::FileTest/"w"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 x

  static method x : int ($file : string);

The alias for the L<x|SPVM::Sys::FileTest/"x"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head3 z

  static method z : int ($file : string);

The alias for the L<A|SPVM::Sys::FileTest/"z"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 IO Control

=head3 ioctl

  static method ioctl : int ($fd : int, $request : int, $request_arg = undef : object of Byte|Short|Int|Long|Float|Double|object);

The alias for the L<ioctl|SPVM::Sys::Ioctl/"ioctl"> method in the L<Sys::Ioctl|SPVM::Sys::Ioctl> class.

=head2 User

=head3 getuid

  static method getuid : int ();

The alias for the L<getuid|SPVM::Sys::User/"getuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 geteuid

  static method geteuid : int ();

The alias for the L<geteuid|SPVM::Sys::User/"geteuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getgid

  static method getgid : int ();

The alias for the L<getgid|SPVM::Sys::User/"getgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getegid

  static method getegid : int ();

The alias for the L<getegid|SPVM::Sys::User/"getegid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setuid

  static method setuid : int ($uid : int);

The alias for the L<setuid|SPVM::Sys::User/"setuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 seteuid

  static method seteuid : int ($euid : int);

The alias for the L<seteuid|SPVM::Sys::User/"seteuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setgid

  static method setgid : int ($gid : int);

The alias for the L<setgid|SPVM::Sys::User/"setgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setegid

  static method setegid : int ($egid : int);

The alias for the L< setegid|SPVM::Sys::User/"setegid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setpwent

  static method setpwent : void ();

The alias for the L<setpwent|SPVM::Sys::User/"setpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 endpwent

  static method endpwent : void ();

The alias for the L<endpwent|SPVM::Sys::User/"endpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getpwent

  static method getpwent : Sys::User::Passwd ();

The alias for the L<getpwent|SPVM::Sys::User/"getpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setgrent

  static method setgrent : void ();

The alias for the L<setgrent|SPVM::Sys::User/"setgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 endgrent

  static method endgrent : void ();

The alias for the L<endgrent|SPVM::Sys::User/"endgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getgrent

  static method getgrent : Sys::User::Group ();

The alias for the L<getuid|SPVM::Sys::User/"getgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getgroups

  static method getgroups : int[] ();

The alias for the L<getgroups|SPVM::Sys::User/"getgroups"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 setgroups

  static method setgroups : int ($groups : int[]);

The alias for the L<setgroups|SPVM::Sys::User/"setgroups"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getpwuid

  static method getpwuid : Sys::User::Passwd ($id : int);

The alias for the L<getpwuid|SPVM::Sys::User/"getpwuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getpwnam

  static method getpwnam : Sys::User::Passwd ($name : string);

The alias for the L<getpwnam|SPVM::Sys::User/"getpwnam"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getgrgid

  static method getgrgid : Sys::User::Group ($id : int);

The alias for the L<getgrgid|SPVM::Sys::User/"getgrgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head3 getgrnam

  static method getgrnam : Sys::User::Group ($name : string);

The alias for the L<getgrnam|SPVM::Sys::User/"getgrnam"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 Time

=head3 times

  static method times : Sys::Time::Tms ();

The alias for the L<timesp|SPVM::Sys::Time/"timesp"> method in the L<Sys::Time|SPVM::Sys::Time> class.

=head3 time

  static method time : long ();

The alias for the L<time|SPVM::Time/"time"> method in the L<Time|SPVM::Time> class.

=head3 localtime

  static method localtime : Time::Info ($time : long);

The alias for the L<localtime|SPVM::Time/"localtime"> method in the L<Time|SPVM::Time> class.

=head3 gmtime

  static method gmtime : Time::Info ($time : long);

The alias for the L<gmtime|SPVM::Time/"gmtime"> method in the L<Time|SPVM::Time> class.

=head3 getpriority

  static method getpriority : int ($which : int, $who : int);

The alias for the L<getpriority|SPVM::Sys::Process/"getpriority"> method in the L<Process|SPVM::Process> class.

=head3 setpriority

  static method setpriority : int ($which : int, $who : int, $prio : int);

The alias for the L<setpriority|SPVM::Sys::Process/"setpriority"> method in the L<Process|SPVM::Process> class.

=head3 sleep

  static method sleep : int ($seconds : int);

The alias for the L<sleep|SPVM::Sys::Process/"sleep"> method in the L<Process|SPVM::Process> class.

=head3 

  static method wait : int ($wstatus_ref : int*);

The alias for the L<wait|SPVM::Sys::Process/"wait"> method in the L<Process|SPVM::Process> class.

=head3 waitpid

  static method waitpid : int ($pid : int, $wstatus_ref : int*, $options : int);

The alias for the L<waitpid|SPVM::Sys::Process/"waitpid"> method in the L<Process|SPVM::Process> class.

=head3 system

  static method system : int ($command : string);

The alias for the L<system|SPVM::Sys::Process/"system"> method in the L<Process|SPVM::Process> class.

=head3 exit

  static method exit : int ($status : int);

The alias for the L<exit|SPVM::Sys::Process/"exit"> method in the L<Process|SPVM::Process> class.

=head3 pipe

  static method pipe : int ($pipe_fds : int[]);

The alias for the L<pipe|SPVM::Sys::Process/"pipe"> method in the L<Process|SPVM::Process> class.

=head3 getpgid

  static method getpgid : int ($pid : int);

The alias for the L<getpgid|SPVM::Sys::Process/"getpgid"> method in the L<Process|SPVM::Process> class.

=head3 setpgid

  static method setpgid : int ($pid : int, $pgid : int);

The alias for the L<setpgid|SPVM::Sys::Process/"setpgid"> method in the L<Process|SPVM::Process> class.

=head3 getpid

  static method getpid : int ();

The alias for the L<getpid|SPVM::Sys::Process/"getpid"> method in the L<Process|SPVM::Process> class.

=head3 getppid

  static method getppid : int ();

The alias for the L<getppid|SPVM::Sys::Process/"getppid"> method in the L<Process|SPVM::Process> class.

=head3 exec

  static method exec : int ($path : string, $args : string[]);

The alias for the L<execv|SPVM::Sys::Process/"execv"> method in the L<Process|SPVM::Process> class.

=head1 Modules

All modules included in this distribution.

=head2 Sys::Env

=head3 L<Sys::Env|SPVM::Sys::Env>

=head2 Sys::FileTest

=head3 L<Sys::FileTest|SPVM::Sys::FileTest>

=head2 Sys::IO

=head3 L<Sys::IO|SPVM::Sys::IO>

=head3 L<Sys::IO::Constant|SPVM::Sys::IO::Constant>

=head3 L<Sys::IO::Dirent|SPVM::Sys::IO::Dirent>

=head3 L<Sys::IO::DirStream|SPVM::Sys::IO::DirStream>

=head3 L<Sys::IO::FileStream|SPVM::Sys::IO::FileStream>

=head3 L<Sys::IO::Flock|SPVM::Sys::IO::Flock>

=head3 L<Sys::IO::Stat|SPVM::Sys::IO::Stat>

=head3 L<Sys::IO::Utimbuf|SPVM::Sys::IO::Utimbuf>

=head2 Sys::Ioctl

=head3 L<Sys::Ioctl|SPVM::Sys::Ioctl>

=head3 L<Sys::Ioctl::Constant|SPVM::Sys::Ioctl::Constant>

=head2 Sys::OS

=head3 L<Sys::OS|SPVM::Sys::OS>

=head2 Sys::Poll

=head3 L<Sys::Poll|SPVM::Sys::Poll>

=head3 L<Sys::Poll::Constant|SPVM::Sys::Poll::Constant>

=head3 L<Sys::Poll::PollfdArray|SPVM::Sys::Poll::PollfdArray>

=head2 Sys::Process

=head3 L<Sys::Process|SPVM::Sys::Process>

=head3 L<Sys::Process::Constant|SPVM::Sys::Process::Constant>

=head2 Sys::Select

=head3 L<Sys::Select|SPVM::Sys::Select>

=head3 L<Sys::Select::Constant|SPVM::Sys::Select::Constant>

=head3 L<Sys::Select::Fd_set|SPVM::Sys::Select::Fd_set>

=head2 Sys::Signal

=head3 L<Sys::Signal|SPVM::Sys::Signal>

=head3 L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>

=head3 L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler>

=head3 L<Sys::Signal::Handler::Default|SPVM::Sys::Signal::Handler::Default>

=head3 L<Sys::Signal::Handler::Ignore|SPVM::Sys::Signal::Handler::Ignore>

=head3 L<Sys::Signal::Handler::Monitor|SPVM::Sys::Signal::Handler::Monitor>

=head3 L<Sys::Signal::Handler::Unknown|SPVM::Sys::Signal::Handler::Unknown>

=head2 Sys::Socket

=head3 L<Sys::Socket|SPVM::Sys::Socket>

=head3 L<Sys::Socket::Addrinfo|SPVM::Sys::Socket::Addrinfo>

=head3 L<Sys::Socket::AddrinfoLinkedList|SPVM::Sys::Socket::AddrinfoLinkedList>

=head3 L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant>

=head3 L<Sys::Socket::Error|SPVM::Sys::Socket::Error>

=head3 L<Sys::Socket::Error::InetInvalidNetworkAddress|SPVM::Sys::Socket::Error::InetInvalidNetworkAddress>

=head3 L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr>

=head3 L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>

=head3 L<Sys::Socket::Ip_mreq|SPVM::Sys::Socket::Ip_mreq>

=head3 L<Sys::Socket::Ip_mreq_source|SPVM::Sys::Socket::Ip_mreq_source>

=head3 L<Sys::Socket::Ipv6_mreq|SPVM::Sys::Socket::Ipv6_mreq>

=head3 L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>

=head3 L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In>

=head3 L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6>

=head3 L<Sys::Socket::Sockaddr::Interface|SPVM::Sys::Socket::Sockaddr::Interface>

=head3 L<Sys::Socket::Sockaddr::Storage|SPVM::Sys::Socket::Sockaddr::Storage>

=head3 L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un>

=head2 Sys::Time

=head3 L<Sys::Time|SPVM::Sys::Time>

=head3 L<Sys::Time::Constant|SPVM::Sys::Time::Constant>

=head3 L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval>

=head3 L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec>

=head3 L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval>

=head3 L<Sys::Time::Timezone|SPVM::Sys::Time::Timezone>

=head3 L<Sys::Time::Tms|SPVM::Sys::Time::Tms>

=head2 Sys::User

=head3 L<Sys::User|SPVM::Sys::User>

=head3 L<Sys::User::Group|SPVM::Sys::User::Group>

=head3 L<Sys::User::Passwd|SPVM::Sys::User::Passwd>

=head1 Author

Yuki Kimoto(L<https://github.com/yuki-kimoto>)

=head1 Contributors

Gabor Szabo(L<https://github.com/szabgab>)

=head1 Repository

L<SPVM::Sys - Github|https://github.com/yuki-kimoto/SPVM-Sys>

=head1 Copyright & License

Copyright Yuki Kimoto 2022-2022, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.
