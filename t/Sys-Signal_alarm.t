use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use POSIX q(:sys_wait_h);

use SPVM 'Sys::Signal';

use SPVM 'Fn';
use SPVM 'TestCase::Sys::Signal';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Signal->alarm(0) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Signal->alarm);
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
