use Test::More;

use strict;
use warnings;
use File::Spec;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'Sys::IO::Glob';
use SPVM 'TestCase::Sys::IO::Glob';

my $test_dir = File::Spec->rel2abs("t/ftest/glob/basic");

is_deeply(SPVM::Sys::IO::Glob->glob("$test_dir/foo.txt")->to_strings, [glob("$test_dir/foo.txt")]);

is_deeply(SPVM::Sys::IO::Glob->glob("$test_dir/foo")->to_strings, [glob("$test_dir/foo")]);

is_deeply(SPVM::Sys::IO::Glob->glob("$test_dir/?oo")->to_strings, [glob("$test_dir/?oo")]);

is_deeply(SPVM::Sys::IO::Glob->glob("$test_dir/foo*")->to_strings, [glob("$test_dir/foo*")]);

is_deeply(SPVM::Sys::IO::Glob->glob("$test_dir/*")->to_strings, [glob("$test_dir/*")]);

done_testing;
