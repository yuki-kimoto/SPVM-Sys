use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp;

use SPVM 'Fn';
use SPVM 'TestCase::Sys';
use SPVM 'TestCase::Sys::IO::Stat';
use SPVM 'Sys::IO::Stat';
use SPVM 'Sys';
use SPVM 'Sys::IO';
use SPVM 'Sys::OS';

use IO::Poll;
use File::stat ();

use Data::Dumper;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $test_dir = "$FindBin::Bin";

my $test_tmp_dir = File::Temp->newdir;
{
  SPVM::TestCase::Sys->SET_TEST_TMP_DIR("$test_tmp_dir");
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

{
  # stat
  {
    my $test_dir = "$FindBin::Bin";
    {
      my $file = "$test_dir/ftest/readline_long_lines.txt";
      my $stat = SPVM::Sys->stat($file);
      my $stat_expected = SPVM::Sys::IO::Stat->new;
      SPVM::Sys::IO::Stat->stat($file, $stat_expected);
      
      is($stat->st_dev, $stat_expected->st_dev, "st_dev");
      is($stat->st_ino, $stat_expected->st_ino, "st_ino");
      is($stat->st_mode, $stat_expected->st_mode, "st_mode");
      is($stat->st_nlink, $stat_expected->st_nlink, "st_nlink");
      is($stat->st_uid, $stat_expected->st_uid, "uid");
      is($stat->st_gid, $stat_expected->st_gid, "gid");
      is($stat->st_rdev, $stat_expected->st_rdev, "rdev");
      is($stat->st_size, $stat_expected->st_size, "size");
      is($stat->st_atime, $stat_expected->st_atime, "atime");
      is($stat->st_mtime, $stat_expected->st_mtime, "mtime");
      is($stat->st_ctime, $stat_expected->st_ctime, "ctime");
      
      unless ($^O eq 'MSWin32') {
        is($stat->st_blksize, $stat_expected->st_blksize, "blksize");
        is($stat->st_blocks, $stat_expected->st_blocks, "blocks");
      }
    }
  }

  {
    my $file_not_exists = "t/ftest/not_exists.txt";
    my $file_empty = "t/ftest/file_empty.txt";
    my $file_bytes8 = "t/ftest/file_bytes8.txt";
    my $file_myexe_exe = "t/ftest/myexe.exe";
    my $file_myexe_bat = "t/ftest/myexe.bat";
    my $file_myexe_cmd = "t/ftest/myexe.cmd";

    # File tests
    {
      ok(SPVM::TestCase::Sys->A);
      is(sprintf("%.14g", SPVM::Sys->A($file_empty)), sprintf("%.14g", -A $file_empty));
    }
    {
      ok(SPVM::TestCase::Sys->C);
      is(sprintf("%.14g", SPVM::Sys->C($file_empty)), sprintf("%.14g", -C $file_empty));
    }
    {
      ok(SPVM::TestCase::Sys->M);
      is(sprintf("%.14g", SPVM::Sys->M($file_empty)), sprintf("%.14g", -M $file_empty));
    }
    
    if (SPVM::Sys::OS->is_windows) {
      warn "[Test Skip]Sys#O method is not supported in this system"
    }
    else {
      ok(SPVM::TestCase::Sys->O);
      is(!!SPVM::Sys->O($file_not_exists), !!-O $file_not_exists);
      is(!!SPVM::Sys->O($file_empty), !!-O $file_empty);
      is(!!SPVM::Sys->O($file_bytes8), !!-O $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->R);
      is(!!SPVM::Sys->R($file_not_exists), !!-R $file_not_exists);
      is(!!SPVM::Sys->R($file_empty), !!-R $file_empty);
      is(!!SPVM::Sys->R($file_bytes8), !!-R $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->S);
      is(!!SPVM::Sys->S($file_empty), !!-S $file_empty);
      is(!!SPVM::Sys->S($file_bytes8), !!-S $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->W);
      is(!!SPVM::Sys->W($file_not_exists), !!-W $file_not_exists);
      is(!!SPVM::Sys->W($file_empty), !!-W $file_empty);
      is(!!SPVM::Sys->W($file_bytes8), !!-W $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->X);
      is(!!SPVM::Sys->X($file_not_exists), !!-X $file_not_exists);
      is(!!SPVM::Sys->X($file_empty), !!-X $file_empty);
      ok(SPVM::Sys->X($file_myexe_exe));
      ok(SPVM::Sys->X($file_myexe_bat));
      ok(SPVM::Sys->X($file_myexe_cmd));
      is(!!SPVM::Sys->X($file_myexe_exe), !!-X $file_myexe_exe);
      is(!!SPVM::Sys->X($file_myexe_bat), !!-X $file_myexe_bat);
      is(!!SPVM::Sys->X($file_myexe_cmd), !!-X $file_myexe_cmd);
    }
    {
      ok(SPVM::TestCase::Sys->d);
      is(!!SPVM::Sys->d($file_not_exists), !!-d $file_not_exists);
      is(!!SPVM::Sys->d($file_empty), !!-d $file_empty);
      is(!!SPVM::Sys->d($file_bytes8), !!-d $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->f);
      is(!!SPVM::Sys->f($file_not_exists), !!-f $file_not_exists);
      is(!!SPVM::Sys->f($file_empty), !!-f $file_empty);
      is(!!SPVM::Sys->f($file_bytes8), !!-f $file_bytes8);
    }
    if (SPVM::Sys::OS->is_windows) {
      warn "[Test Skip]Sys#g method is not supported in this system"
    }
    else {
      ok(SPVM::TestCase::Sys->g);
      is(!!SPVM::Sys->g($file_not_exists), !!-g $file_not_exists);
      is(!!SPVM::Sys->g($file_empty), !!-g $file_empty);
      is(!!SPVM::Sys->g($file_bytes8), !!-g $file_bytes8);
    }
    if (SPVM::Sys::OS->is_windows) {
      warn "[Test Skip]Sys#k method is not supported in this system"
    }
    else {
      ok(SPVM::TestCase::Sys->k);
      is(!!SPVM::Sys->k($file_not_exists), !!-k $file_not_exists);
      is(!!SPVM::Sys->k($file_empty), !!-k $file_empty);
      is(!!SPVM::Sys->k($file_bytes8), !!-k $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->b);
      is(!!SPVM::Sys->b($file_not_exists), !!-b $file_not_exists);
      is(!!SPVM::Sys->b($file_empty), !!-b $file_empty);
      is(!!SPVM::Sys->b($file_bytes8), !!-b $file_bytes8);
    }
    if (SPVM::Sys::OS->is_windows) {
      warn "[Test Skip]Sys#o method is not supported in this system"
    }
    else {
      ok(SPVM::TestCase::Sys->o);
      is(!!SPVM::Sys->o($file_not_exists), !!-o $file_not_exists);
      is(!!SPVM::Sys->o($file_empty), !!-o $file_empty);
      is(!!SPVM::Sys->o($file_bytes8), !!-o $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->p);
      is(!!SPVM::Sys->p($file_not_exists), !!-p $file_not_exists);
      is(!!SPVM::Sys->p($file_empty), !!-p $file_empty);
      is(!!SPVM::Sys->p($file_bytes8), !!-p $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->r);
      is(!!SPVM::Sys->r($file_not_exists), !!-r $file_not_exists);
      is(!!SPVM::Sys->r($file_empty), !!-r $file_empty);
      is(!!SPVM::Sys->r($file_bytes8), !!-r $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->s);
      is(!!SPVM::Sys->s($file_empty), !!-s $file_empty);
      is(!!SPVM::Sys->s($file_bytes8), !!-s $file_bytes8);
    }
    if (SPVM::Sys::OS->is_windows) {
      warn "[Test Skip]Sys#u method is not supported in this system"
    }
    else {
      ok(SPVM::TestCase::Sys->u);
      is(!!SPVM::Sys->u($file_not_exists), !!-u $file_not_exists);
      is(!!SPVM::Sys->u($file_empty), !!-u $file_empty);
      is(!!SPVM::Sys->u($file_bytes8), !!-u $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->z);
      is(!!SPVM::Sys->z($file_empty), !!-z $file_empty);
      is(!!SPVM::Sys->z($file_bytes8), !!-z $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->w);
      is(!!SPVM::Sys->w($file_not_exists), !!-w $file_not_exists);
      is(!!SPVM::Sys->w($file_empty), !!-w $file_empty);
      is(!!SPVM::Sys->w($file_bytes8), !!-w $file_bytes8);
    }
    {
      ok(SPVM::TestCase::Sys->x);
      is(!!SPVM::Sys->x($file_not_exists), !!-x $file_not_exists);
      is(!!SPVM::Sys->x($file_empty), !!-x $file_empty);
      ok(SPVM::Sys->x($file_myexe_exe));
      ok(SPVM::Sys->x($file_myexe_bat));
      ok(SPVM::Sys->x($file_myexe_cmd));
      is(!!SPVM::Sys->x($file_myexe_exe), !!-x $file_myexe_exe);
      is(!!SPVM::Sys->x($file_myexe_bat), !!-x $file_myexe_bat);
      is(!!SPVM::Sys->x($file_myexe_cmd), !!-x $file_myexe_cmd);
    }
  }
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
