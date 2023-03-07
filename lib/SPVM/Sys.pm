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

=head2 getenv

  static method getenv : string ($name : string);

The alias for the L<getenv|SPVM::Sys::Env/"getenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head2 setenv

  static method setenv : int ($name : string, $value : string, $overwrite : int);

The alias for the L<setenv|SPVM::Sys::Env/"setenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head2 unsetenv

  static method unsetenv : int ($name : string);

The alias for the L<unsetenv|SPVM::Sys::Env/"unsetenv"> method in the L<Sys::Env|SPVM::Sys::Env> class.

=head2 defined

  static method defined : int ($macro_name : string, $value = undef : object of Int|Long|Double);

The alias for the L<defined|SPVM::Sys::OS/"defined"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head2 get_osname

  static method get_osname : string ()

The alias for the L<get_osname|SPVM::Sys::OS/"get_osname"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head2 is_windows

  static method is_windows : int ();

The alias for the L<is_windows|SPVM::Sys::OS/"is_windows"> method in the L<Sys::OS|SPVM::Sys::OS> class.

=head2 A

  static method A : double ($file : string);

The alias for the L<A|SPVM::Sys::FileTest/"A"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 C

  static method C : double ($file : string);

The alias for the L<C|SPVM::Sys::FileTest/"C"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 M

  static method M : double ($file : string);

The alias for the L<M|SPVM::Sys::FileTest/"M"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 O

  static method O : int ($file : string);

The alias for the L<O|SPVM::Sys::FileTest/"O"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 R

  static method R : int ($file : string);

The alias for the L<R|SPVM::Sys::FileTest/"R"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 S

  static method S : int ($file : string);

The alias for the L<S|SPVM::Sys::FileTest/"S"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 W

  static method W : int ($file : string);

The alias for the L<W|SPVM::Sys::FileTest/"W"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 X

  static method X : int ($file : string);

The alias for the L<X|SPVM::Sys::FileTest/"X"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 b

  static method b : int ($file : string);

The alias for the L<b|SPVM::Sys::FileTest/"b"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 c

  static method c : int ($file : string);

The alias for the L<c|SPVM::Sys::FileTest/"c"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 d

  static method d : int ($file : string);

The alias for the L<d|SPVM::Sys::FileTest/"d"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 e

  static method e : int ($file : string);

The alias for the L<e|SPVM::Sys::FileTest/"e"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 f

  static method f : int ($file : string);

The alias for the L<f|SPVM::Sys::FileTest/"f"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 g

  static method g : int ($file : string);

The alias for the L<g|SPVM::Sys::FileTest/"g"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 k

  static method k : int ($file : string);

The alias for the L<k|SPVM::Sys::FileTest/"k"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 l

  static method l : int ($file : string);

The alias for the L<l|SPVM::Sys::FileTest/"l"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 o

  static method o : int ($file : string);

The alias for the L<o|SPVM::Sys::FileTest/"o"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 p

  static method p : int ($file : string);

The alias for the L<p|SPVM::Sys::FileTest/"p"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 r

  static method r : int ($file : string);

The alias for the L<r|SPVM::Sys::FileTest/"r"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 s

  static method s : long ($file : string);

The alias for the L<s|SPVM::Sys::FileTest/"s"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 u

  static method u : int ($file : string);

The alias for the L<u|SPVM::Sys::FileTest/"u"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 w

  static method w : int ($file : string);

The alias for the L<w|SPVM::Sys::FileTest/"w"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 x

  static method x : int ($file : string);

The alias for the L<x|SPVM::Sys::FileTest/"x"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 z

  static method z : int ($file : string);

The alias for the L<A|SPVM::Sys::FileTest/"z"> method in the L<Sys::FileTest|SPVM::Sys::FileTest> class.

=head2 ioctl

  static method ioctl : int ($fd : int, $request : int, $request_arg = undef : object of Byte|Short|Int|Long|Float|Double|object);

The alias for the L<ioctl|SPVM::Sys::Ioctl/"ioctl"> method in the L<Sys::Ioctl|SPVM::Sys::Ioctl> class.

=head2 getuid

  static method getuid : int ();

The alias for the L<getuid|SPVM::Sys::User/"getuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 geteuid

  static method geteuid : int ();

The alias for the L<geteuid|SPVM::Sys::User/"geteuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getgid

  static method getgid : int ();

The alias for the L<getgid|SPVM::Sys::User/"getgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getegid

  static method getegid : int ();

The alias for the L<getegid|SPVM::Sys::User/"getegid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setuid

  static method setuid : int ($uid : int);

The alias for the L<setuid|SPVM::Sys::User/"setuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 seteuid

  static method seteuid : int ($euid : int);

The alias for the L<seteuid|SPVM::Sys::User/"seteuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setgid

  static method setgid : int ($gid : int);

The alias for the L<setgid|SPVM::Sys::User/"setgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setegid

  static method setegid : int ($egid : int);

The alias for the L<setegid|SPVM::Sys::User/"setegid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setpwent

  static method setpwent : void ();

The alias for the L<setpwent|SPVM::Sys::User/"setpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 endpwent

  static method endpwent : void ();

The alias for the L<endpwent|SPVM::Sys::User/"endpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getpwent

  static method getpwent : Sys::User::Passwd ();

The alias for the L<getpwent|SPVM::Sys::User/"getpwent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setgrent

  static method setgrent : void ();

The alias for the L<setgrent|SPVM::Sys::User/"setgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 endgrent

  static method endgrent : void ();

The alias for the L<endgrent|SPVM::Sys::User/"endgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getgrent

  static method getgrent : Sys::User::Group ();

The alias for the L<getuid|SPVM::Sys::User/"getgrent"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getgroups

  static method getgroups : int[] ();

The alias for the L<getgroups|SPVM::Sys::User/"getgroups"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 setgroups

  static method setgroups : int ($groups : int[]);

The alias for the L<setgroups|SPVM::Sys::User/"setgroups"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getpwuid

  static method getpwuid : Sys::User::Passwd ($id : int);

The alias for the L<getpwuid|SPVM::Sys::User/"getpwuid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getpwnam

  static method getpwnam : Sys::User::Passwd ($name : string);

The alias for the L<getpwnam|SPVM::Sys::User/"getpwnam"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getgrgid

  static method getgrgid : Sys::User::Group ($id : int);

The alias for the L<getgrgid|SPVM::Sys::User/"getgrgid"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 getgrnam

  static method getgrnam : Sys::User::Group ($name : string);

The alias for the L<getgrnam|SPVM::Sys::User/"getgrnam"> method in the L<Sys::User|SPVM::Sys::User> class.

=head2 times

  static method times : Sys::Time::Tms ();

The alias for the L<timesp|SPVM::Sys::Time/"timesp"> method in the L<Sys::Time|SPVM::Sys::Time> class.

=head2 time

  static method time : long ();

The alias for the L<time|SPVM::Time/"time"> method in the L<Time|SPVM::Time> class.

=head2 localtime

  static method localtime : Time::Info ($time : long);

The alias for the L<localtime|SPVM::Time/"localtime"> method in the L<Time|SPVM::Time> class.

=head2 gmtime

  static method gmtime : Time::Info ($time : long);

The alias for the L<gmtime|SPVM::Time/"gmtime"> method in the L<Time|SPVM::Time> class.

=head2 getpriority

  static method getpriority : int ($which : int, $who : int);

The alias for the L<getpriority|SPVM::Sys::Process/"getpriority"> method in the L<Process|SPVM::Process> class.

=head2 setpriority

  static method setpriority : int ($which : int, $who : int, $prio : int);

The alias for the L<setpriority|SPVM::Sys::Process/"setpriority"> method in the L<Process|SPVM::Process> class.

=head2 sleep

  static method sleep : int ($seconds : int);

The alias for the L<sleep|SPVM::Sys::Process/"sleep"> method in the L<Process|SPVM::Process> class.

=head2 

  static method wait : int ($wstatus_ref : int*);

The alias for the L<wait|SPVM::Sys::Process/"wait"> method in the L<Process|SPVM::Process> class.

=head2 waitpid

  static method waitpid : int ($pid : int, $wstatus_ref : int*, $options : int);

The alias for the L<waitpid|SPVM::Sys::Process/"waitpid"> method in the L<Process|SPVM::Process> class.

=head2 system

  static method system : int ($command : string);

The alias for the L<system|SPVM::Sys::Process/"system"> method in the L<Process|SPVM::Process> class.

=head2 exit

  static method exit : int ($status : int);

The alias for the L<exit|SPVM::Sys::Process/"exit"> method in the L<Process|SPVM::Process> class.

=head2 pipe

  static method pipe : int ($pipe_fds : int[]);

The alias for the L<pipe|SPVM::Sys::Process/"pipe"> method in the L<Process|SPVM::Process> class.

=head2 getpgid

  static method getpgid : int ($pid : int);

The alias for the L<getpgid|SPVM::Sys::Process/"getpgid"> method in the L<Process|SPVM::Process> class.

=head2 setpgid

  static method setpgid : int ($pid : int, $pgid : int);

The alias for the L<setpgid|SPVM::Sys::Process/"setpgid"> method in the L<Process|SPVM::Process> class.

=head2 getpid

  static method getpid : int ();

The alias for the L<getpid|SPVM::Sys::Process/"getpid"> method in the L<Process|SPVM::Process> class.

=head2 getppid

  static method getppid : int ();

The alias for the L<getppid|SPVM::Sys::Process/"getppid"> method in the L<Process|SPVM::Process> class.

=head2 exec

  static method exec : int ($path : string, $args : string[]);

The alias for the L<execv|SPVM::Sys::Process/"execv"> method in the L<Process|SPVM::Process> class.

=head2 stat

  static method stat : Sys::IO::Stat ($path : string);

The alias for the L<statp|SPVM::Sys::IO::Stat/"statp"> method in the L<IO::Stat|SPVM::IO::Stat> class.

=head2 lstat

  static method lstat : Sys::IO::Stat ($path : string);

The alias for the L<lstatp|SPVM::Sys::IO::Stat/"lstatp"> method in the L<IO::Stat|SPVM::IO::Stat> class.

=head2 mkdir

  static method mkdir : int ($path : string, $mode : int) {

The alias for the L<mkdir|SPVM::Sys::IO/"mkdir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 umask

  static method umask : int ($mode : int) {

The alias for the L<umask|SPVM::Sys::IO/"umask"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 rmdir

  static method rmdir : int ($path : string) {

The alias for the L<rmdir|SPVM::Sys::IO/"rmdir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 unlink

  static method unlink : int ($pathname : string) {

The alias for the L<unlink|SPVM::Sys::IO/"unlink"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 rename

  static method rename : int ($oldpath : string, $newpath : string) {

The alias for the L<rename|SPVM::Sys::IO/"rename"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 chdir

  static method chdir : int ($path : string) {

The alias for the L<chdir|SPVM::Sys::IO/"chdir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 chmod

  static method chmod : int ($mode :int, $path : string) {

The alias for the L<chmodp|SPVM::Sys::IO/"chmodp"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 chown

  static method chown : int ($owner : int, $group : int, $path : string) {

The alias for the L<chownp|SPVM::Sys::IO/"chownp"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 symlink

  static method symlink : int ($oldpath : string, $newpath : string) {

The alias for the L<symlink|SPVM::Sys::IO/"symlink"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 readlink

  static method readlink : int ($file : string) {

The alias for the L<readlinkp|SPVM::Sys::IO/"readlinkp"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 opendir

  static method opendir : Sys::IO::DirStream ($dir : string) {

The alias for the L<opendir|SPVM::Sys::IO/"opendir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 closedir

  static method closedir : int ($dirp : Sys::IO::DirStream) {

The alias for the L<closedir|SPVM::Sys::IO/"closedir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 readdir

  static method readdir : Sys::IO::Dirent ($dirp : Sys::IO::DirStream) {

The alias for the L<readdir|SPVM::Sys::IO/"readdir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 rewinddir

  static method rewinddir : void ($dirp : Sys::IO::DirStream) {

The alias for the L<rewinddir|SPVM::Sys::IO/"rewinddir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 telldir

  static method telldir : long ($dirp : Sys::IO::DirStream) {

The alias for the L<telldir|SPVM::Sys::IO/"telldir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 seekdir

  static method seekdir : void ($dirp : Sys::IO::DirStream, $offset : long) {

The alias for the L<seekdir|SPVM::Sys::IO/"seekdir"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head2 utime

  static method utime : int ($atime : long, $mtime : long, $filename : string) {

The alias for the L<utime|SPVM::Sys::IO/"utime"> method in the L<Sys::IO|SPVM::Sys::IO> class.

=head1 Modules

All modules included in this distribution.

=head2 Sys::Env

=head4 L<Sys::Env|SPVM::Sys::Env>

=head2 Sys::FileTest

=head4 L<Sys::FileTest|SPVM::Sys::FileTest>

=head2 Sys::IO

=head4 L<Sys::IO|SPVM::Sys::IO>

=head4 L<Sys::IO::Constant|SPVM::Sys::IO::Constant>

=head4 L<Sys::IO::Dirent|SPVM::Sys::IO::Dirent>

=head4 L<Sys::IO::DirStream|SPVM::Sys::IO::DirStream>

=head4 L<Sys::IO::FileStream|SPVM::Sys::IO::FileStream>

=head4 L<Sys::IO::Flock|SPVM::Sys::IO::Flock>

=head4 L<Sys::IO::Stat|SPVM::Sys::IO::Stat>

=head4 L<Sys::IO::Utimbuf|SPVM::Sys::IO::Utimbuf>

=head2 Sys::Ioctl

=head4 L<Sys::Ioctl|SPVM::Sys::Ioctl>

=head4 L<Sys::Ioctl::Constant|SPVM::Sys::Ioctl::Constant>

=head2 Sys::OS

=head4 L<Sys::OS|SPVM::Sys::OS>

=head2 Sys::Poll

=head4 L<Sys::Poll|SPVM::Sys::Poll>

=head4 L<Sys::Poll::Constant|SPVM::Sys::Poll::Constant>

=head4 L<Sys::Poll::PollfdArray|SPVM::Sys::Poll::PollfdArray>

=head2 Sys::Process

=head4 L<Sys::Process|SPVM::Sys::Process>

=head4 L<Sys::Process::Constant|SPVM::Sys::Process::Constant>

=head2 Sys::Select

=head4 L<Sys::Select|SPVM::Sys::Select>

=head4 L<Sys::Select::Constant|SPVM::Sys::Select::Constant>

=head4 L<Sys::Select::Fd_set|SPVM::Sys::Select::Fd_set>

=head2 Sys::Signal

=head4 L<Sys::Signal|SPVM::Sys::Signal>

=head4 L<Sys::Signal::Constant|SPVM::Sys::Signal::Constant>

=head4 L<Sys::Signal::Handler|SPVM::Sys::Signal::Handler>

=head4 L<Sys::Signal::Handler::Default|SPVM::Sys::Signal::Handler::Default>

=head4 L<Sys::Signal::Handler::Ignore|SPVM::Sys::Signal::Handler::Ignore>

=head4 L<Sys::Signal::Handler::Monitor|SPVM::Sys::Signal::Handler::Monitor>

=head4 L<Sys::Signal::Handler::Unknown|SPVM::Sys::Signal::Handler::Unknown>

=head2 Sys::Socket

=head4 L<Sys::Socket|SPVM::Sys::Socket>

=head4 L<Sys::Socket::Addrinfo|SPVM::Sys::Socket::Addrinfo>

=head4 L<Sys::Socket::AddrinfoLinkedList|SPVM::Sys::Socket::AddrinfoLinkedList>

=head4 L<Sys::Socket::Constant|SPVM::Sys::Socket::Constant>

=head4 L<Sys::Socket::Error|SPVM::Sys::Socket::Error>

=head4 L<Sys::Socket::Error::InetInvalidNetworkAddress|SPVM::Sys::Socket::Error::InetInvalidNetworkAddress>

=head4 L<Sys::Socket::In6_addr|SPVM::Sys::Socket::In6_addr>

=head4 L<Sys::Socket::In_addr|SPVM::Sys::Socket::In_addr>

=head4 L<Sys::Socket::Ip_mreq|SPVM::Sys::Socket::Ip_mreq>

=head4 L<Sys::Socket::Ip_mreq_source|SPVM::Sys::Socket::Ip_mreq_source>

=head4 L<Sys::Socket::Ipv6_mreq|SPVM::Sys::Socket::Ipv6_mreq>

=head4 L<Sys::Socket::Sockaddr|SPVM::Sys::Socket::Sockaddr>

=head4 L<Sys::Socket::Sockaddr::In|SPVM::Sys::Socket::Sockaddr::In>

=head4 L<Sys::Socket::Sockaddr::In6|SPVM::Sys::Socket::Sockaddr::In6>

=head4 L<Sys::Socket::Sockaddr::Interface|SPVM::Sys::Socket::Sockaddr::Interface>

=head4 L<Sys::Socket::Sockaddr::Storage|SPVM::Sys::Socket::Sockaddr::Storage>

=head4 L<Sys::Socket::Sockaddr::Un|SPVM::Sys::Socket::Sockaddr::Un>

=head2 Sys::Time

=head4 L<Sys::Time|SPVM::Sys::Time>

=head4 L<Sys::Time::Constant|SPVM::Sys::Time::Constant>

=head4 L<Sys::Time::Itimerval|SPVM::Sys::Time::Itimerval>

=head4 L<Sys::Time::Timespec|SPVM::Sys::Time::Timespec>

=head4 L<Sys::Time::Timeval|SPVM::Sys::Time::Timeval>

=head4 L<Sys::Time::Timezone|SPVM::Sys::Time::Timezone>

=head4 L<Sys::Time::Tms|SPVM::Sys::Time::Tms>

=head2 Sys::User

=head4 L<Sys::User|SPVM::Sys::User>

=head4 L<Sys::User::Group|SPVM::Sys::User::Group>

=head4 L<Sys::User::Passwd|SPVM::Sys::User::Passwd>

=head1 See Also

=head4 L<IO::File|SPVM::IO::File>

=head4 L<IO::Socket|SPVM::IO::Socket>

=head4 L<IO::Select|SPVM::IO::Select>

=head4 L<IO::Poll|SPVM::IO::Poll>

=head4 L<File::Spec|SPVM::File::Spec>

=head4 L<Cwd|SPVM::Cwd>

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
