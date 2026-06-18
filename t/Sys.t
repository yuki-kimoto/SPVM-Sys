use Test::More;

use strict;
use warnings;
use utf8;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Sys';
use SPVM 'Int';
use SPVM 'Long';
use SPVM 'Double';

use SPVM 'TestCase::Sys';
use SPVM 'Sys::OS';
use File::stat ();

use SPVM 'Fn';
use SPVM 'Sys::IO::Stat';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $test_dir = "$FindBin::Bin";

SPVM::TestCase::Sys->SET_TEST_DIR($test_dir);

my $test_tmp_dir = File::Temp->newdir;
{
  SPVM::TestCase::Sys->SET_TEST_TMP_DIR("$test_tmp_dir");
}

ok(SPVM::TestCase::Sys->rand);

# _getcwd
{
  my $expected = Cwd::getcwd();
  is(SPVM::Sys->_getcwd, $expected);
}

{
  my $test_dir = "$FindBin::Bin";
  ok(SPVM::TestCase::Sys->chdir("$test_dir"));
}

SPVM::TestCase::Sys->SET_TEST_DIR(undef);

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
