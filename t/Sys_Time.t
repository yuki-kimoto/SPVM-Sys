use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'Sys::Time';

use SPVM 'TestCase::Sys::Time';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(SPVM::TestCase::Sys::Time->gettimeofday);

ok(SPVM::TestCase::Sys::Time->clock);

ok(SPVM::TestCase::Sys::Time->clock_gettime);

ok(SPVM::TestCase::Sys::Time->clock_getres);

ok(SPVM::TestCase::Sys::Time->getitimer);

ok(SPVM::TestCase::Sys::Time->setitimer);

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Process->times(undef) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Time->times);
}

ok(SPVM::TestCase::Sys::Time->clock_nanosleep);

ok(SPVM::TestCase::Sys::Time->nanosleep);

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
