use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }
use Time::HiRes 'usleep';

use SPVM 'Sys::Socket::Errno';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count();

# The constant values
{
  ok(1);
}

my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
