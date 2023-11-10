use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use TestUtil::ServerRunner;

# Port
my $port = TestUtil::ServerRunner->search_available_port();

warn "[Test Output]Port:$port";

ok($port >= 20000);

{
  my $process_id = fork;

  # Child
  if ($process_id == 0) {
    TestUtil::ServerRunner->run_echo_server($port);
  }
  else {
    TestUtil::ServerRunner->wait_port_prepared($port);
    
    TestUtil::ServerRunner->kill_term_and_wait($process_id);
  }
}

ok(1);

done_testing;
