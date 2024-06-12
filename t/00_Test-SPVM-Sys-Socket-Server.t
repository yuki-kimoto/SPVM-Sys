use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use Test::SPVM::Sys::Socket::ServerManager::UNIX;
use Test::SPVM::Sys::Socket::ServerManager::IP;
use Test::SPVM::Sys::Socket::Util;

# Port
my $port = Test::SPVM::Sys::Socket::Util::get_empty_port;

warn "[Test Output]Port:$port";

ok($port >= 20000);

{
  my $server = Test::SPVM::Sys::Socket::ServerManager::IP->new(
    code => sub {
      my ($port) = @_;
      
      Test::SPVM::Sys::Socket::Util::start_echo_server_ipv4_tcp(port => $port);
    },
  );
}

{
  my $server = Test::SPVM::Sys::Socket::ServerManager::IP->new(
    code => sub {
      my ($port) = @_;
      
      Test::SPVM::Sys::Socket::Util::start_echo_server_ipv4_tcp(port => $port);
    },
  );
}

{
  my $server = Test::SPVM::Sys::Socket::ServerManager::UNIX->new(
    code => sub {
      my ($path) = @_;
      
      Test::SPVM::Sys::Socket::Util::start_echo_server_unix_tcp(path => $path);
    },
  );
}

ok(1);

done_testing;
