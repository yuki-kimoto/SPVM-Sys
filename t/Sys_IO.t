use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp;

use SPVM 'TestCase::Sys::IO';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $test_dir = "$FindBin::Bin";
ok(SPVM::TestCase::Sys::IO->fopen($test_dir));
ok(SPVM::TestCase::Sys::IO->open($test_dir));
ok(SPVM::TestCase::Sys::IO->close($test_dir));
ok(SPVM::TestCase::Sys::IO->fdopen($test_dir));
ok(SPVM::TestCase::Sys::IO->fclose($test_dir));
{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys::IO->mkdir("$tmp_dir"));
}

{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys::IO->rmdir("$tmp_dir"));
}

{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys::IO->unlink("$tmp_dir"));
}

{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys::IO->fileno("$tmp_dir"));
}
ok(SPVM::TestCase::Sys::IO->fread($test_dir));
ok(SPVM::TestCase::Sys::IO->feof($test_dir));
ok(SPVM::TestCase::Sys::IO->ferror($test_dir));
ok(SPVM::TestCase::Sys::IO->clearerr($test_dir));
ok(SPVM::TestCase::Sys::IO->getc($test_dir));
ok(SPVM::TestCase::Sys::IO->fgets($test_dir));

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
