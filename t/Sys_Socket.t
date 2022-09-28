use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Socket;
use IO::Socket::INET;

use SPVM 'Sys::Socket';
use SPVM 'TestCase::Sys::Socket';

sub search_available_port {
  my $retry_port = 20000;
  
  my $port;
  my $retry_max = 10;
  my $retry_count = 0;
  while (1) {
    if ($retry_count > $retry_max) {
      die "Can't find an available port";
    }
    
    my $server_socket = IO::Socket::INET->new(
      LocalPort => $port,
      Listen    => SOMAXCONN,
      Proto     => 'tcp',
      Reuse     => 1,
      Timeout => 5,
    );
    
    if ($server_socket) {
      $port = $retry_port;
      last;
    }

    $retry_port++;
    $retry_count++;
  }
  
  return $port;
}

my $port = 20000;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

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
}

ok(SPVM::TestCase::Sys::Socket->socket);

# Sys::Socket::Sockaddr
{
  my $port = &search_available_port;
  ok(SPVM::TestCase::Sys::Socket->sockaddr($port));
}

# connect
{
  my $process_id = fork;

  my $port = &search_available_port;
  
  # Child
  if ($process_id == 0) {
    my $server_socket = IO::Socket::INET->new(
      LocalPort => $port,
      Listen    => SOMAXCONN,
      Proto     => 'tcp',
      Reuse     => 1,
    );
    
    unless ($server_socket) {
      die "Can't create a server socket";
    }
    
    while (1) {
      $server_socket->accept;
    }
  }
  else {
    SPVM::TestCase::Sys::Socket->connect($port);
    
    kill 'HUP', $process_id;
  }
}

# close
{
  my $process_id = fork;

  my $port = &search_available_port;
  
  # Child
  if ($process_id == 0) {
    my $server_socket = IO::Socket::INET->new(
      LocalPort => $port,
      Listen    => SOMAXCONN,
      Proto     => 'tcp',
      Reuse     => 1,
    );
    
    unless ($server_socket) {
      die "Can't create a server socket";
    }
    
    while (1) {
      $server_socket->accept;
    }
  }
  else {
    SPVM::TestCase::Sys::Socket->close($port);
    
    kill 'HUP', $process_id;
  }
}

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
