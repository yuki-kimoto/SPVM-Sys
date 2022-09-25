use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use POSIX q(:sys_wait_h);

use SPVM 'Sys::Process';

use SPVM 'TestCase::Sys::Process';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(SPVM::TestCase::Sys::Process->alarm);
ok(SPVM::TestCase::Sys::Process->fork);
ok(SPVM::TestCase::Sys::Process->sleep);
ok(SPVM::TestCase::Sys::Process->getpriority);

# The exit status
{
  is(WIFEXITED(0), SPVM::Sys::Process->WIFEXITED(0));
  is(WEXITSTATUS(0), SPVM::Sys::Process->WEXITSTATUS(0));
  is(WIFSIGNALED(0), SPVM::Sys::Process->WIFSIGNALED(0));
  is(WTERMSIG(0), SPVM::Sys::Process->WTERMSIG(0));
  is(WIFSTOPPED(0), SPVM::Sys::Process->WIFSTOPPED(0));
  is(WSTOPSIG(0), SPVM::Sys::Process->WSTOPSIG(0));
  
  # Non-POSIX
  SPVM::Sys::Process->WIFCONTINUED(0);
  SPVM::Sys::Process->WCOREDUMP(0);
}

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
