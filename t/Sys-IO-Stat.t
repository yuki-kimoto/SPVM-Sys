use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp;

use SPVM 'Fn';
use SPVM 'TestCase::Sys::IO::Stat';
use SPVM 'Sys::IO::Stat';
use SPVM 'Sys::IO';

use IO::Poll;
use File::stat ();

use Data::Dumper;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $test_dir = "$FindBin::Bin";

my $test_tmp_dir = File::Temp->newdir;
{
  SPVM::TestCase::Sys::IO::Stat->SET_TEST_TMP_DIR("$test_tmp_dir");
}

=pod

  0 dev      device number of filesystem
  1 ino      inode number
  2 mode     file mode  (type and permissions)
  3 nlink    number of (hard) links to the file
  4 uid      numeric user ID of file's owner
  5 gid      numeric group ID of file's owner
  6 rdev     the device identifier (special files only)
  7 size     total size of file, in bytes
  8 atime    last access time in seconds since the epoch
  9 mtime    last modify time in seconds since the epoch
 10 ctime    inode change time in seconds since the epoch (*)
 11 blksize  preferred I/O size in bytes for interacting with the
             file (may vary from file to file)
 12 blocks   actual number of system-specific blocks allocated
             on disk (often, but not always, 512 bytes each)

=cut

sub ulong_to_long {
  my ($ulong_value) = @_;
  
  my ($long_value) = unpack('q', pack('Q', $ulong_value));
  
  return $long_value;
}

{
  ok(SPVM::TestCase::Sys::IO::Stat->stat("$test_dir"));
  
  my $file = "$test_dir/ftest/readline_long_lines.txt";
  my $stat = SPVM::Sys::IO::Stat->new();
  SPVM::Sys::IO::Stat->stat($file, $stat);
  my $stat_expected = File::stat::stat($file);
  
  if ($stat_expected->ino == 0) {
    warn "[Test Skip]This version of Perl does not support emulations of st_dev, st_ino, st_rdev, st_nlink.";
    warn "[Test Output]st_dev:" . $stat->dev;
    warn "[Test Output]st_ino:" . $stat->ino;
    warn "[Test Output]st_rdev:" . $stat->rdev;
    warn "[Test Output]st_nlink:" . $stat->nlink;
  }
  else {
    is($stat->dev, &ulong_to_long($stat_expected->dev), "st_dev");
    is($stat->ino, $stat_expected->ino, "st_ino");
    is($stat->rdev, $stat_expected->rdev, "rdev");
  }
  is($stat->nlink, $stat_expected->nlink, "st_nlink");
  is($stat->mode, $stat_expected->mode, "st_mode");
  is($stat->uid, $stat_expected->uid, "uid");
  is($stat->gid, $stat_expected->gid, "gid");
  is($stat->size, $stat_expected->size, "size");
  is($stat->atime, $stat_expected->atime, "atime");
  is($stat->mtime, $stat_expected->mtime, "mtime");
  is($stat->ctime, $stat_expected->ctime, "ctime");
  
  unless ($^O eq 'MSWin32') {
    is($stat->blksize, $stat_expected->blksize, "blksize");
    is($stat->blocks, $stat_expected->blocks, "blocks");
  }
}

ok(SPVM::TestCase::Sys::IO::Stat->lstat("$test_dir"));

{
  my $file = "$test_dir/ftest/readline_long_lines.txt";
  my $stat = SPVM::Sys::IO::Stat->new();
  SPVM::Sys::IO::Stat->lstat($file, $stat);
  my $stat_expected = File::stat::lstat($file);
  
  if ($stat_expected->ino == 0) {
    warn "[Test Skip]This version of Perl does not support emulations of st_dev, st_ino, st_rdev, st_nlink.";
    warn "[Test Output]st_dev:" . $stat->dev;
    warn "[Test Output]st_ino:" . $stat->ino;
    warn "[Test Output]st_rdev:" . $stat->rdev;
    warn "[Test Output]st_nlink:" . $stat->nlink;
  }
  else {
    is($stat->dev, &ulong_to_long($stat_expected->dev), "st_dev");
    is($stat->ino, $stat_expected->ino, "st_ino");
    is($stat->rdev, $stat_expected->rdev, "rdev");
    is($stat->nlink, $stat_expected->nlink, "st_nlink");
  }
  is($stat->mode, $stat_expected->mode, "st_mode");
  is($stat->uid, $stat_expected->uid, "uid");
  is($stat->gid, $stat_expected->gid, "gid");
  is($stat->size, $stat_expected->size, "size");
  is($stat->atime, $stat_expected->atime, "atime");
  is($stat->mtime, $stat_expected->mtime, "mtime");
  is($stat->ctime, $stat_expected->ctime, "ctime");
  
  unless ($^O eq 'MSWin32') {
    is($stat->blksize, $stat_expected->blksize, "blksize");
    is($stat->blocks, $stat_expected->blocks, "blocks");
  }
}

{
  ok(SPVM::TestCase::Sys::IO::Stat->fstat("$test_dir"));
  
  my $stat_info = SPVM::TestCase::Sys::IO::Stat->fstat_info("$test_dir");
  my $stat_info_expected = [stat "$test_dir/ftest/readline_long_lines.txt"];
  
  {
    my $file = "$test_dir/ftest/readline_long_lines.txt";
    my $fh_spvm = SPVM::Sys::IO->fopen($file, "rb");
    my $stat = SPVM::Sys::IO::Stat->new();
    SPVM::Sys::IO::Stat->fstat(SPVM::Sys::IO->fileno($fh_spvm), $stat);
    
    open my $fh_perl, '<', $file
      or die;
    my $stat_expected = File::stat::stat($fh_perl);
    
    if ($stat_expected->ino == 0) {
      warn "[Test Skip]This version of Perl does not support emulations of st_dev, st_ino, st_rdev, st_nlink.";
      warn "[Test Output]st_dev:" . $stat->dev;
      warn "[Test Output]st_ino:" . $stat->ino;
      warn "[Test Output]st_rdev:" . $stat->rdev;
      warn "[Test Output]st_nlink:" . $stat->nlink;
    }
    else {
      is($stat->dev, &ulong_to_long($stat_expected->dev), "st_dev");
      is($stat->ino, $stat_expected->ino, "st_ino");
      is($stat->rdev, $stat_expected->rdev, "rdev");
    }
    is($stat->mode, $stat_expected->mode, "st_mode");
    is($stat->uid, $stat_expected->uid, "uid");
    is($stat->gid, $stat_expected->gid, "gid");
    is($stat->size, $stat_expected->size, "size");
    is($stat->atime, $stat_expected->atime, "atime");
    is($stat->mtime, $stat_expected->mtime, "mtime");
    is($stat->ctime, $stat_expected->ctime, "ctime");
    unless ($^O eq 'MSWin32') {
      is($stat->blksize, $stat_expected->blksize, "blksize");
      is($stat->blocks, $stat_expected->blocks, "blocks");
    }
  }
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
