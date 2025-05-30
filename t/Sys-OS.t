use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Sys';
use SPVM 'Sys::OS';
use SPVM 'Int';
use SPVM 'Long';
use SPVM 'Double';

use SPVM 'Fn';
use SPVM 'TestCase::Sys::IO';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# is_windows
{
  if ($^O eq 'MSWin32') {
    ok(SPVM::Sys::OS->is_windows);
  }
  else {
    ok(!SPVM::Sys::OS->is_windows);
  }
}

# defined
{
  if ($^O eq 'MSWin32') {
    ok(SPVM::Sys::OS->defined('_WIN32'));
  }
  else {
    ok(!SPVM::Sys::OS->defined('_WIN32'));
  }
  
  # value
  if ($^O eq 'linux') {
    {
      my $value_ref = $api->new_int_array([0]);
      SPVM::Sys::OS->defined('__linux', $value_ref);
      ok($value_ref->[0]);
    }
    {
      my $value_ref = $api->new_long_array([0]);
      SPVM::Sys::OS->defined('__linux', $value_ref);
      ok($value_ref->[0]);
    }
    {
      my $value_ref = $api->new_double_array([0]);
      SPVM::Sys::OS->defined('__linux', $value_ref);
      ok($value_ref->[0]);
    }
  }
  
  {
    SPVM::Sys::OS->defined('__GNUC__');
    SPVM::Sys::OS->defined('__clang__');
    SPVM::Sys::OS->defined('__BORLANDC__');
    SPVM::Sys::OS->defined('__INTEL_COMPILER');
    SPVM::Sys::OS->defined('__unix');
    SPVM::Sys::OS->defined('__unix__');
    SPVM::Sys::OS->defined('__linux');
    SPVM::Sys::OS->defined('__linux__');
    SPVM::Sys::OS->defined('__FreeBSD__');
    SPVM::Sys::OS->defined('__NetBSD__');
    SPVM::Sys::OS->defined('__OpenBSD__');
    SPVM::Sys::OS->defined('_WIN32');
    SPVM::Sys::OS->defined('_WIN64');
    SPVM::Sys::OS->defined('_WINDOWS');
    SPVM::Sys::OS->defined('_CONSOLE');
    SPVM::Sys::OS->defined('_WIN32_WINDOWS');
    SPVM::Sys::OS->defined('_WIN32_WINNT');
    SPVM::Sys::OS->defined('__CYGWIN__');
    SPVM::Sys::OS->defined('__CYGWIN32__');
    SPVM::Sys::OS->defined('__MINGW32__');
    SPVM::Sys::OS->defined('__MINGW64__');
    SPVM::Sys::OS->defined('__APPLE__');
    SPVM::Sys::OS->defined('__MACH__');
    SPVM::Sys::OS->defined('__solaris');
  }
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
