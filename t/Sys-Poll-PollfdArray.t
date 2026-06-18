use Test::More;

use strict;
use warnings;
use lib 't/lib';
use Time::HiRes 'usleep';

use SPVM 'TestCase::Sys::Poll::PollfdArray';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::Sys::Poll::PollfdArray->fields);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->new);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->fd);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->set_fd);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->events);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->set_events);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->revents);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->set_revents);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->push);

ok(SPVM::TestCase::Sys::Poll::PollfdArray->remove);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
