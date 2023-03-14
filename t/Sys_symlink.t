use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use File::Temp ();

use Errno;
use Cwd qw(getcwd);
use File::Basename;

use SPVM 'Sys';

use SPVM 'TestCase::Sys';

my $symlink_supported;
eval { SPVM::Sys->symlink('', '') };
if ($@ && $@ !~ /not permitted/) {
  $symlink_supported = 1;
}
plan skip_all => "no symlink available on this system"
    if !$symlink_supported;

# readlink
{
  my $tmp_dir = File::Temp->newdir;
  ok(SPVM::TestCase::Sys->readlink("$tmp_dir"));
}

done_testing();
