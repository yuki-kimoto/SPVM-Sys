use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use SPVM 'TestCase::Sys::User';

is(SPVM::TestCase::Sys::User->getuid_value, "$<");
is(SPVM::TestCase::Sys::User->geteuid_value, "$>");
is(SPVM::TestCase::Sys::User->getgid_value, (split(/\s+/, "$("))[0]);
is(SPVM::TestCase::Sys::User->getegid_value, (split(/\s+/, "$)"))[0]);

done_testing;
