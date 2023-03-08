use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp;

use SPVM 'TestCase::Sys::IO::Stat';
use SPVM 'Sys::IO::Stat';

use IO::Poll;
use File::stat ();

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $test_dir = "$FindBin::Bin";

# Sys::IO::Stat->stat in SPVM is the same as MinGW stat function in Windows, not Perl.

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

{
  ok(SPVM::TestCase::Sys::IO::Stat->stat("$test_dir"));

  {
    my $file = "$test_dir/ftest/readline_long_lines.txt";
    my $stat_info = SPVM::Sys::IO::Stat->new();
    SPVM::Sys::IO::Stat->stat($file, $stat_info);
    my $stat_info_expected = File::stat::stat($file);
    use Data::Dumper;
    warn Dumper $stat_info_expected;
    
    is($stat_info->st_dev, $stat_info_expected->dev, "st_dev");
    is($stat_info->st_ino, $stat_info_expected->ino, "st_ino");
    is($stat_info->st_mode, $stat_info_expected->mode, "st_mode");
    is($stat_info->st_nlink, $stat_info_expected->nlink, "st_nlink");
    is($stat_info->st_uid, $stat_info_expected->uid, "uid");
    is($stat_info->st_gid, $stat_info_expected->gid, "gid");
    is($stat_info->st_rdev, $stat_info_expected->rdev, "rdev");
    is($stat_info->st_size, $stat_info_expected->size, "size");
    is($stat_info->st_atime, $stat_info_expected->atime, "atime);
    is($stat_info->st_mtime, $stat_info_expected->mtime, "mtime");
    is($stat_info->st_ctime, $stat_info_expected->ctime, "ctime");
    
    unless ($^O eq 'MSWin32') {
      is($stat_info->st_blksize, $stat_info_expected->blksize, "blksize");
      is($stat_info->st_blocks, $stat_info_expected->blocks, "blocks");
    }
  }
}

unless ($^O eq 'MSWin32') {
  ok(SPVM::TestCase::Sys::IO::Stat->lstat("$test_dir"));
  
  {
    my $file = "$test_dir/ftest/readline_long_lines.txt";
    my $stat_info = SPVM::Sys::IO::Stat->new();
    SPVM::Sys::IO::Stat->lstat($file, $stat_info);
    my $stat_info_expected = File::stat::lstat($file);
    use Data::Dumper;
    warn Dumper $stat_info_expected;
    
    is($stat_info->st_dev, $stat_info_expected->dev, "st_dev");
    is($stat_info->st_ino, $stat_info_expected->ino, "st_ino");
    is($stat_info->st_mode, $stat_info_expected->mode, "st_mode");
    is($stat_info->st_nlink, $stat_info_expected->nlink, "st_nlink");
    is($stat_info->st_uid, $stat_info_expected->uid, "stat[4]");
    is($stat_info->st_gid, $stat_info_expected->gid, "stat[5]");
    is($stat_info->st_rdev, $stat_info_expected->rdev, "stat[6]");
    is($stat_info->st_size, $stat_info_expected->size, "stat[7]");
    is($stat_info->st_atime, $stat_info_expected->atime, "stat[8]");
    is($stat_info->st_mtime, $stat_info_expected->mtime, "stat[9]");
    is($stat_info->st_ctime, $stat_info_expected->ctime, "stat[10]");
    
    unless ($^O eq 'MSWin32') {
      is($stat_info->st_blksize, $stat_info_expected->blksize, "blksize");
      is($stat_info->st_blocks, $stat_info_expected->blocks, "blocks");
    }
  }
}


SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
