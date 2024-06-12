use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use Test::SPVM::Sys::Socket::ServerManager::UNIX;
use Test::SPVM::Sys::Socket::Util;

{
  my $server = Test::SPVM::Sys::Socket::ServerManager::UNIX->new(
    code => sub {
      my ($path) = @_;
      
      Test::SPVM::Sys::Socket::Util::run_echo_server_unix($path);
    },
  );
}

ok(1);

done_testing;
