use Test::More;

use strict;
use warnings;
use lib 't/lib';

use SPVM 'TestCase::Sys::Socket';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

ok(SPVM::TestCase::Sys::Socket->connect_ipv6);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
