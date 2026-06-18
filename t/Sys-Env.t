use Test::More;

use strict;
use warnings;
use utf8;

use lib 't/lib';
use SPVM 'TestCase::Sys';
use SPVM 'Sys';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Sys
{
  # env
  {
    is(SPVM::Sys->env("PATH"), $ENV{PATH});
  }

  ok(SPVM::TestCase::Sys->env);

  ok(SPVM::TestCase::Sys->set_env);
}

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
