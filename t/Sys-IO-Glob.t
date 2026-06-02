use Test::More;

use strict;
use warnings;
use File::Spec;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'Sys';
use SPVM 'Sys::IO::Glob';
use SPVM 'TestCase::Sys::IO::Glob';

my $test_dir = "t/ftest/glob/basic";

is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$test_dir/foo.txt")->to_strings, [glob("$test_dir/foo.txt")]);

is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$test_dir/foo")->to_strings, [glob("$test_dir/foo")]);

is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$test_dir/?oo")->to_strings, [glob("$test_dir/?oo")]);

is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$test_dir/foo*")->to_strings, [glob("$test_dir/foo*")]);

is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$test_dir/*")->to_strings, [glob("$test_dir/*")]);

is_deeply(SPVM::Sys->glob("$test_dir/*")->to_strings, [glob("$test_dir/*")]);

is_deeply(SPVM::Sys->glob("$test_dir/not_exists.txt")->to_strings, [glob("$test_dir/not_exists.txt")]);

{
  my $pattern = "$test_dir/{f,b}oo.txt";
  
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 2);
  is_deeply($got, $expected);
}

if ($^O eq 'MSWin32') {
  my $win_test_dir = $test_dir;
  $win_test_dir =~ s/\//\\/g;
  
  is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$win_test_dir\\foo.txt")->to_strings, [glob("$win_test_dir\\foo.txt")]);
  is_deeply(SPVM::Sys::IO::Glob->bsd_glob("$win_test_dir\\*")->to_strings, [glob("$win_test_dir\\*")]);
}
else {
  diag("[Test Skip]Skipping Windows-specific separator tests on $^O");
}

done_testing;
