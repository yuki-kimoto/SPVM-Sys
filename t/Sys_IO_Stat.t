use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp;

use SPVM 'TestCase::Sys::IO::Stat';

use IO::Poll;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $test_dir = "$FindBin::Bin";

{
  ok(SPVM::TestCase::Sys::IO::Stat->stat("$test_dir"));
  
  my $stat_info = SPVM::TestCase::Sys::IO::Stat->stat_info("$test_dir");
  my $stat_info_expected = [stat "$test_dir/ftest/file_bytes8.txt"];
  use Data::Dumper;
  warn Dumper $stat_info->to_elems;
  warn Dumper $stat_info_expected;
  
  is_deeply($stat_info->to_elems, $stat_info_expected);
}

unless ($^O eq 'MSWin32') {
  ok(SPVM::TestCase::Sys::IO::Stat->lstat("$test_dir"));
  
  my $lstat_info = SPVM::TestCase::Sys::IO::Stat->lstat_info("$test_dir");
  my $lstat_info_expected = [lstat "$test_dir/ftest/file_bytes8.txt"];
  is_deeply($lstat_info->to_elems, $lstat_info_expected);
}

{
  ok(SPVM::TestCase::Sys::IO::Stat->fstat("$test_dir"));
  
  my $stat_info = SPVM::TestCase::Sys::IO::Stat->fstat_info("$test_dir");
  my $stat_info_expected = [stat "$test_dir/ftest/file_bytes8.txt"];
  is_deeply($stat_info->to_elems, $stat_info_expected);
}

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
