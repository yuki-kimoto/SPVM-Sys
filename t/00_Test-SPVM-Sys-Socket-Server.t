use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use Test::SPVM::Sys::Socket::Server;

# Port
my $port = Test::SPVM::Sys::Socket::Server->empty_port;

warn "[Test Output]Port:$port";

ok($port >= 20000);

{
  my $server = Test::SPVM::Sys::Socket::Server->new(
    code => sub {
      my ($port) = @_;
      
      Test::SPVM::Sys::Socket::Server->run_echo_server($port);
    },
  );
}

ok(1);

done_testing;
