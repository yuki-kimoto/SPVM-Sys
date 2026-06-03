use v5.20.3;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';

GetOptions(
  'meta' => \my $meta,
  'no-build-spvm-modules' => \my $no_build_spvm_modules,
  'debug' => \my $debug,
  'build-type=s' => \my $build_type,
);

if ($meta) {
  $no_build_spvm_modules = 1;
}

if ($debug) {
  $build_type = 'Debug';
}

my %configure_and_runtime_requires = (
  'SPVM' => '0.990155',
  'SPVM::Resource::SocketUtil' => '1.002',
  'SPVM::Resource::Utf8proc' => '0.004',
);

WriteMakefile(
  NAME              => 'SPVM::Sys',
  VERSION_FROM      => 'lib/SPVM/Sys.pm',
  LICENSE           => 'mit',
  ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
    (ABSTRACT_FROM  => 'lib/SPVM/Sys.pm',
     AUTHOR         => 'Yuki Kimoto<kimoto.yuki@gmail.com>') : ()),
  test => {TESTS => 't/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => 'https://github.com/yuki-kimoto/SPVM-Sys.git',
        web  => 'https://github.com/yuki-kimoto/SPVM-Sys',
      },
      bugtracker => {
        web => "https://github.com/yuki-kimoto/SPVM-Sys/issues",
      },
    },
  },
  CONFIGURE_REQUIRES => {
    %configure_and_runtime_requires,
  },
  PREREQ_PM         => {
    %configure_and_runtime_requires,
    'SPVM::Errno' => '0.06',
    'SPVM::Math' => '1.006',
  },
);

sub MY::postamble {
  
  my $make_rule = '';
  
  unless ($no_build_spvm_modules) {
    require SPVM::Builder::Util::API;
    
    my $options = {};
    if (defined $build_type) {
      $options->{build_type} = $build_type;
    }
    
    $options->{native_classes} = [qw(
      Sys::IO
      Sys::IO::Windows
      Sys::IO::Constant
      Sys::IO::FileStream
      Sys::IO::DirStream
      Sys::IO::Dirent
      Sys::IO::Flock
      Sys::IO::Stat
      Sys::IO::Glob
      Sys::Process
      Sys::Process::Constant
      Sys::User
      Sys::User::Passwd
      Sys::User::Group
      Sys::Socket
      Sys::Socket::Errno
      Sys::Socket::Constant
      Sys::Socket::Addrinfo
      Sys::Socket::AddrinfoLinkedList
      Sys::Socket::Sockaddr
      Sys::Socket::Sockaddr::In
      Sys::Socket::Sockaddr::In6
      Sys::Socket::Sockaddr::Un
      Sys::Socket::Sockaddr::Storage
      Sys::Socket::In_addr
      Sys::Socket::In6_addr
      Sys::Socket::Ipv6_mreq
      Sys::Socket::Ip_mreq_source
      Sys::Socket::Ip_mreq
      Sys::Time
      Sys::Time::Constant
      Sys::Time::Timeval
      Sys::Time::Timespec
      Sys::Time::Timezone
      Sys::Time::Itimerval
      Sys::Time::Tm
      Sys::Time::Tms
      Sys::Time::Utimbuf
      Sys::Select
      Sys::Select::Fd_set
      Sys::Select::Constant
      Sys::Poll
      Sys::Poll::PollfdArray
      Sys::Poll::Constant
      Sys::Ioctl
      Sys::Ioctl::Constant
      Sys::Signal
      Sys::Signal::Handler
      Sys::Signal::Constant
      Sys::OS
      Sys::Env
    )];
    
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_parallel($options);
  }
  
  return $make_rule;
}

1;
