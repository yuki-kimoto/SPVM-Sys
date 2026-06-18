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

# env
{
  is(SPVM::Sys->env("PATH"), $ENV{PATH});
}

ok(SPVM::TestCase::Sys->ioctl);

ok(SPVM::TestCase::Sys->set_tcp_keepalive);

ok(SPVM::TestCase::Sys->env);

ok(SPVM::TestCase::Sys->set_env);

ok(SPVM::TestCase::Sys->rand);

# _getcwd
{
  my $expected = Cwd::getcwd();
  is(SPVM::Sys->_getcwd, $expected);
}

# _getdcwd
if (SPVM::Sys::OS->is_windows) {
  {
    my $expected = Cwd::getdcwd();
    is(SPVM::Sys->_getdcwd, $expected);
  }
  
  {
    my $expected = Cwd::getdcwd('C:');
    is(SPVM::Sys->_getdcwd('C:'), $expected);
  }
  
  {
    my $expected = Cwd::getdcwd('c:');
    is(SPVM::Sys->_getdcwd('c:'), $expected);
  }
  
}

# _realpath
{
  {
    my $file_empty = "t/ftest/file_empty.txt";
    is(SPVM::Sys->_realpath($file_empty), Cwd::realpath($file_empty));
  }
  
  {
    my $dir = "t/ftest";
    is(SPVM::Sys->_realpath($dir), Cwd::realpath($dir));
  }
  {
    my $file_not_exists = "t/ftest/not_exists.txt";
    eval { SPVM::Sys->_realpath($file_not_exists); };
    ok($@);
  }
  
  {
    my $path = 't/Sys.t';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = 't/lib/../Sys.t';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = 't';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = 't/';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = 't//';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = '/';
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  {
    my $path = "$FindBin::Bin";
    my $ret = SPVM::Sys->_realpath($path);
    my $expected = Cwd::realpath($path);
    is($ret, $expected);
  }
  
  if ($^O eq 'MSWin32') {
    {
      my $path = "t\\Sys.t";
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
    {
      my $path = "t\\lib\\..\\Sys.t";
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
    {
      my $path = "t";
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
    {
      my $path = "t\\";
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
    {
      my $path = "t\\\\";
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
    {
      my $path = '\\';
      my $ret = SPVM::Sys->_realpath($path);
      my $expected = Cwd::realpath($path);
      is($ret, $expected);
    }
  }
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
