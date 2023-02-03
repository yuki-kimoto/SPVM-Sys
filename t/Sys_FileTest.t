use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Cwd 'getcwd';

use SPVM 'TestCase::Sys::FileTest';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# File tests
ok(SPVM::TestCase::Sys::FileTest->e);
ok(SPVM::TestCase::Sys::FileTest->f);
ok(SPVM::TestCase::Sys::FileTest->d);
ok(SPVM::TestCase::Sys::FileTest->s);
ok(SPVM::TestCase::Sys::FileTest->z);

ok(SPVM::TestCase::Sys::FileTest->r);
ok(SPVM::TestCase::Sys::FileTest->R);
ok(SPVM::TestCase::Sys::FileTest->w);
ok(SPVM::TestCase::Sys::FileTest->W);
ok(SPVM::TestCase::Sys::FileTest->x);
ok(SPVM::TestCase::Sys::FileTest->X);
ok(SPVM::TestCase::Sys::FileTest->o);
ok(SPVM::TestCase::Sys::FileTest->O);

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
