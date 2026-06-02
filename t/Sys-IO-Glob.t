use Test::More;

use strict;
use warnings;
use File::Spec;
use FindBin;
use lib "$FindBin::Bin/lib";
use File::Temp;

use SPVM 'Sys';
use SPVM 'Sys::IO::Glob';
use SPVM 'TestCase::Sys::IO::Glob';

my $test_dir = "t/ftest/glob/basic";

my $tmp_dir = File::Temp->newdir;

# Exact match file
{
  my $pattern = "$test_dir/foo.txt";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 1);
  is_deeply($got, $expected);
}

# Path without extension
{
  my $pattern = "$test_dir/foo";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 1);
  is_deeply($got, $expected);
}

# Wildcard '?'
{
  my $pattern = "$test_dir/?oo.txt";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 2); # foo.txt and boo.txt
  is_deeply($got, $expected);
}

# Wildcard '*' at end
{
  my $pattern = "$test_dir/foo*";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 2);
  is_deeply($got, $expected);
}

# Wildcard '*' all
{
  my $pattern = "$test_dir/*";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  # Ensure we have at least 2 files (foo.txt, boo.txt)
  ok(@$got >= 2);
  is_deeply($got, $expected);
}

# Sys glob method
{
  my $pattern = "$test_dir/*";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys->glob($pattern)->to_strings;
  
  ok(@$got >= 2);
  is_deeply($got, $expected);
}

# Non-existent file (No meta-chars)
{
  my $pattern = "$test_dir/not_exists.txt";
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys->glob($pattern)->to_strings;
  
  is(@$got, 1);
  is_deeply($got, $expected);
}

# {fo,bo}
{
  my $pattern = "$test_dir/{fo,bo}o.txt";
  
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 2);
  is_deeply($got, $expected);
}

# [fb]
{
  my $pattern = "$test_dir/[fb]oo.txt";
  
  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;
  
  is(@$got, 2);
  is_deeply($got, $expected);
}

# Quote special chars
{
  my $special_file = "$tmp_dir/foo-bar.txt";
  open my $fh, '>', $special_file; close $fh;

  my $pattern = "$tmp_dir/foo\\-bar.txt";

  my $expected = [glob($pattern)];
  my $got = SPVM::Sys::IO::Glob->bsd_glob($pattern)->to_strings;

  is(@$got, 1);
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
