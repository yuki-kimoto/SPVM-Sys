use Test::More;

use strict;
use warnings;
use utf8;
use FindBin;
use File::Temp;

use lib "t/lib";
use SPVM 'TestCase::Sys::IO';
use SPVM 'TestCase::Sys';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $test_dir = "$FindBin::Bin";
SPVM::TestCase::Sys->SET_TEST_DIR($test_dir);

my $test_tmp_dir = File::Temp->newdir;
SPVM::TestCase::Sys->SET_TEST_TMP_DIR("$test_tmp_dir");

{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys::IO->open("$tmp_dir"));
}
ok(SPVM::TestCase::Sys::IO->chdir);

SPVM::TestCase::Sys->SET_TEST_DIR(undef);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
