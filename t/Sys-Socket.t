use Test::More;

use strict;
use warnings;
use lib 't/lib';

use Socket;

use SPVM 'Sys::Socket';
use SPVM 'TestCase::Sys::Socket';
use SPVM 'TestCase::Sys';
use SPVM 'Sys::Socket::Constant';

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# The constant values
{
  is(SPVM::Sys::Socket::Constant->AF_INET, Socket::AF_INET);
  is(SPVM::Sys::Socket::Constant->AF_INET6, Socket::AF_INET6);
  
  eval { SPVM::Sys::Socket::Constant->AF_UNIX };
  if ($@) {
    warn "[Test Output]AF_UNIX is not supported";
  }
  else {
    is(SPVM::Sys::Socket::Constant->AF_INET6, Socket::AF_INET6);
  }
  is(SPVM::Sys::Socket::Constant->SOCK_STREAM, Socket::SOCK_STREAM);
  is(SPVM::Sys::Socket::Constant->SOCK_DGRAM, Socket::SOCK_DGRAM);
  is(SPVM::Sys::Socket::Constant->SOCK_RAW, Socket::SOCK_RAW);

  is(SPVM::Sys::Socket::Constant->SHUT_RD, Socket::SHUT_RD);
  is(SPVM::Sys::Socket::Constant->SHUT_RD, 0);
  is(SPVM::Sys::Socket::Constant->SHUT_WR, Socket::SHUT_WR);
  is(SPVM::Sys::Socket::Constant->SHUT_WR, 1);
  is(SPVM::Sys::Socket::Constant->SHUT_RDWR, Socket::SHUT_RDWR);
  is(SPVM::Sys::Socket::Constant->SHUT_RDWR, 2);
}

# The endian methods
{
  # htonl
  {
    ok(SPVM::TestCase::Sys::Socket->htonl);
    ok(SPVM::TestCase::Sys::Socket->ntohl);
    ok(SPVM::TestCase::Sys::Socket->htons);
    ok(SPVM::TestCase::Sys::Socket->ntohs);
  }
}

ok(SPVM::TestCase::Sys::Socket->inet_aton);
ok(SPVM::TestCase::Sys::Socket->inet_pton);
ok(SPVM::TestCase::Sys::Socket->inet_ntoa);
ok(SPVM::TestCase::Sys::Socket->inet_ntop);

ok(SPVM::TestCase::Sys::Socket->socket);

ok(SPVM::TestCase::Sys::Socket->sockaddr);

ok(SPVM::TestCase::Sys::Socket->connect);

ok(SPVM::TestCase::Sys::Socket->close);

ok(SPVM::TestCase::Sys::Socket->shutdown);

ok(SPVM::TestCase::Sys::Socket->send_and_recv);

ok(SPVM::TestCase::Sys::Socket->sendto_and_recvfrom);

ok(SPVM::TestCase::Sys::Socket->send_and_recv_udp);

ok(SPVM::TestCase::Sys::Socket->bind);

ok(SPVM::TestCase::Sys::Socket->listen);

ok(SPVM::TestCase::Sys::Socket->accept);

ok(SPVM::TestCase::Sys::Socket->getpeername);

ok(SPVM::TestCase::Sys::Socket->getsockname);

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Socket->socketpair(0, 0, 0, undef) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Socket->socketpair);
}

ok(SPVM::TestCase::Sys::Socket->setsockopt_int);

ok(SPVM::TestCase::Sys::Socket->getsockopt_int);

ok(SPVM::TestCase::Sys::Socket->sockaddr_un);

ok(SPVM::TestCase::Sys::Socket->sockaddr_strage);

ok(SPVM::TestCase::Sys::Socket->getaddrinfo);

ok(SPVM::TestCase::Sys::Socket->getnameinfo);

ok(SPVM::TestCase::Sys::Socket->set_tcp_keepalive);

ok(SPVM::TestCase::Sys::Socket->inet_socketpair);

ok(SPVM::TestCase::Sys::Socket->set_blocking);

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
