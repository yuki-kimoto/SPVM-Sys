use 5.008_007;
use ExtUtils::MakeMaker;
use strict;
use warnings;
use Config;
use SPVM::Builder::Util::API;

WriteMakefile(
  NAME              => 'SPVM::Sys',
  VERSION_FROM      => 'lib/SPVM/Sys.pm',
  LICENSE           => 'perl_5',
  ($] >= 5.005 ?     ## Add these new keywords supported since 5.005
    (ABSTRACT_FROM  => 'lib/SPVM/Sys.pm',
     AUTHOR         => 'USER_NAME<USER_MAIL>') : ()),
  test => {TESTS => 't/*.t'},
  clean => {FILES => ['.spvm_build', 't/.spvm_build']},
  META_MERGE => {
    'meta-spec' => { version => 2 },
    resources => {
      repository => {
        type => 'git',
        url  => '',
        web  => '',
      },
    },
  },
  # SPVM::Builder::Util::API is needed for Makefile.PL
  CONFIGURE_REQUIRES => {
    'SPVM'              => '0.9649',
  },
  PREREQ_PM         => {
    'SPVM::Errno' => '0.04',
  },
);

sub MY::postamble {

  my $make_rule = '';
  
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::Constant');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::Fcntl');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::FileHandle');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::DirHandle');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::Dirent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO::Utimbuf');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Process');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::User');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::User::Passwd');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::User::Group');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Constant');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Hostent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Netent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Servent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Protoent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Addrinfo');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::Sockaddr');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::In_addr');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket::In6_addr');
  
  return $make_rule;
}

1;
