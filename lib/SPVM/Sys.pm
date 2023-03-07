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
