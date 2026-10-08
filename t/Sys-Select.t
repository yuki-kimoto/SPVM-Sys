use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Sys::Select';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# FD_ZERO
# FD_SET
# FD_CLR
# FD_ISSET
ok(SPVM::TestCase::Sys::Select->select_utils);

ok(SPVM::TestCase::Sys::Select->select);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
