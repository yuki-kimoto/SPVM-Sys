use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Cwd 'getcwd';

use SPVM 'TestCase::Sys::FileTest';
use SPVM 'Sys::FileTest';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $file_not_exists = "t/ftest/not_exists.txt";
my $file_empty = "t/ftest/file_empty.txt";
my $file_bytes8 = "t/ftest/file_bytes8.txt";
my $file_myexe_exe = "t/ftest/myexe.exe";
my $file_myexe_bat = "t/ftest/file_myexe.bat";

my $proc_start_time = $^T;

# File tests
{
  ok(SPVM::TestCase::Sys::FileTest->A);
  is(SPVM::Sys::FileTest->A($file_empty, $proc_start_time), -A $file_empty);
}
{
  ok(SPVM::TestCase::Sys::FileTest->C);
  is(SPVM::Sys::FileTest->C($file_empty, $proc_start_time), -C $file_empty);
}
{
  ok(SPVM::TestCase::Sys::FileTest->M);
  is(SPVM::Sys::FileTest->M($file_empty, $proc_start_time), -M $file_empty);
}
ok(SPVM::TestCase::Sys::FileTest->O);
{
  ok(SPVM::TestCase::Sys::FileTest->R);
  is(!!SPVM::Sys::FileTest->R($file_not_exists), !!-R $file_not_exists);
  is(!!SPVM::Sys::FileTest->R($file_empty), !!-R $file_empty);
  is(!!SPVM::Sys::FileTest->R($file_bytes8), !!-R $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->S);
  is(!!SPVM::Sys::FileTest->S($file_empty), !!-S $file_empty);
  is(!!SPVM::Sys::FileTest->S($file_bytes8), !!-S $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->W);
  is(!!SPVM::Sys::FileTest->W($file_not_exists), !!-W $file_not_exists);
  is(!!SPVM::Sys::FileTest->W($file_empty), !!-W $file_empty);
  is(!!SPVM::Sys::FileTest->W($file_bytes8), !!-W $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->X);
  is(!!SPVM::Sys::FileTest->X($file_not_exists), !!-X $file_not_exists);
  is(!!SPVM::Sys::FileTest->X($file_empty), !!-X $file_empty);
  is(!!SPVM::Sys::FileTest->X($file_myexe_exe), !!-X $file_myexe_exe);
  is(!!SPVM::Sys::FileTest->X($file_myexe_bat), !!-X $file_myexe_bat);
}
{
  ok(SPVM::TestCase::Sys::FileTest->d);
  is(!!SPVM::Sys::FileTest->d($file_not_exists), !!-d $file_not_exists);
  is(!!SPVM::Sys::FileTest->d($file_empty), !!-d $file_empty);
  is(!!SPVM::Sys::FileTest->d($file_bytes8), !!-d $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->f);
  is(!!SPVM::Sys::FileTest->f($file_not_exists), !!-f $file_not_exists);
  is(!!SPVM::Sys::FileTest->f($file_empty), !!-f $file_empty);
  is(!!SPVM::Sys::FileTest->f($file_bytes8), !!-f $file_bytes8);
}
ok(SPVM::TestCase::Sys::FileTest->g);
ok(SPVM::TestCase::Sys::FileTest->k);
ok(SPVM::TestCase::Sys::FileTest->l);
ok(SPVM::TestCase::Sys::FileTest->b);
ok(SPVM::TestCase::Sys::FileTest->o);
ok(SPVM::TestCase::Sys::FileTest->p);
{
  ok(SPVM::TestCase::Sys::FileTest->r);
  is(!!SPVM::Sys::FileTest->r($file_not_exists), !!-r $file_not_exists);
  is(!!SPVM::Sys::FileTest->r($file_empty), !!-r $file_empty);
  is(!!SPVM::Sys::FileTest->r($file_bytes8), !!-r $file_bytes8);
}
ok(SPVM::TestCase::Sys::FileTest->s);
ok(SPVM::TestCase::Sys::FileTest->u);
{
  ok(SPVM::TestCase::Sys::FileTest->z);
  is(!!SPVM::Sys::FileTest->z($file_not_exists), !!-z $file_not_exists);
  is(!!SPVM::Sys::FileTest->z($file_empty), !!-z $file_empty);
  is(!!SPVM::Sys::FileTest->z($file_bytes8), !!-z $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->w);
  is(!!SPVM::Sys::FileTest->w($file_not_exists), !!-w $file_not_exists);
  is(!!SPVM::Sys::FileTest->w($file_empty), !!-w $file_empty);
  is(!!SPVM::Sys::FileTest->w($file_bytes8), !!-w $file_bytes8);
}
{
  ok(SPVM::TestCase::Sys::FileTest->x);
  is(!!SPVM::Sys::FileTest->x($file_not_exists), !!-x $file_not_exists);
  is(!!SPVM::Sys::FileTest->x($file_empty), !!-x $file_empty);
  is(!!SPVM::Sys::FileTest->x($file_myexe_exe), !!-x $file_myexe_exe);
  is(!!SPVM::Sys::FileTest->x($file_myexe_bat), !!-x $file_myexe_bat);
}

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
