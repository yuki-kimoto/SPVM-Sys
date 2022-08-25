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
    'SPVM'              => '0.9641',
  },
  PREREQ_PM         => {
    'SPVM::Errno' => '0.04',
  },
);

sub MY::postamble {

  my $make_rule = '';
  
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::FileTest');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::IO');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Net');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Process');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Socket');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::User');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Fcntl');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::FileHandle');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::DirHandle');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Passwd');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Group');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Dir');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Hostent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Netent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Servent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Ent::Protoent');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Utimbuf');
  $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Sys::Addrinfo');
  
  return $make_rule;
}

1;
