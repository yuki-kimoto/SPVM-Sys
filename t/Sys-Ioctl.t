use Test::More;

use strict;
use warnings;
use lib 't/lib';
use Time::HiRes 'usleep';

use SPVM 'Sys::Ioctl';
use SPVM 'TestCase::Sys::Ioctl';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Sys::Ioctl->ioctl);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
