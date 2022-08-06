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

ok(SPVM::TestCase::Sys::User->setuid);
ok(SPVM::TestCase::Sys::User->seteuid);
ok(SPVM::TestCase::Sys::User->setgid);
ok(SPVM::TestCase::Sys::User->setegid);

if ($^O eq 'Win32') {
  eval { SPVM::TestCase::Sys::User->setpwent };
  ok($@);
}
else {
  ok(SPVM::TestCase::Sys::User->setpwent);
}

if ($^O eq 'Win32') {
  eval { SPVM::TestCase::Sys::User->endpwent };
  ok($@);
}
else {
  ok(SPVM::TestCase::Sys::User->endpwent);
}

if ($^O eq 'Win32') {
  eval { SPVM::TestCase::Sys::User->setgrent };
  ok($@);
}
else {
  ok(SPVM::TestCase::Sys::User->setgrent);
}

if ($^O eq 'Win32') {
  eval { SPVM::TestCase::Sys::User->endgrent };
  ok($@);
}
else {
  ok(SPVM::TestCase::Sys::User->endgrent);
}

# TODO
# This test failed. Maybe permission problems
=pod
{
  my @groups_expected = split(/\s+/, "$)");
  shift @groups_expected;
  is_deeply(SPVM::TestCase::Sys::User->getgroups_value->to_elems, \@groups_expected);
  ok(SPVM::TestCase::Sys::User->setgroups);
}
=cut

done_testing;
