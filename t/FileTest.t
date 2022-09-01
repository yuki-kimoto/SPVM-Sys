use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Cwd 'getcwd';

use SPVM 'TestCase::Sys::FileTest';

# File tests
ok(SPVM::TestCase::Sys::FileTest->e);
ok(SPVM::TestCase::Sys::FileTest->f);
ok(SPVM::TestCase::Sys::FileTest->d);
ok(SPVM::TestCase::Sys::FileTest->s);

done_testing;
