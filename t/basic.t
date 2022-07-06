use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Cwd 'getcwd';

use SPVM 'TestCase::Sys';

ok(SPVM::TestCase::Sys->test);

# File tests
ok(SPVM::TestCase::Sys->ftest);

done_testing;
