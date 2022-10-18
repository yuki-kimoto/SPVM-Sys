use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }
use Time::HiRes 'usleep';

use Socket;
use IO::Socket;
use IO::Socket::INET;

use SPVM 'Sys::Ioctl';
use SPVM 'TestCase::Sys::Ioctl';

my $localhost = "127.0.0.1";

sub search_available_port {
  my $retry_port = 20000;
  
  my $port;
  my $retry_max = 10;
  my $retry_count = 0;
  while (1) {
    if ($retry_count > 0) {
      warn "[Test Output]Perform the ${retry_count} retry to search an available port $retry_port";
    }
    
    if ($retry_count > $retry_max) {
      die "Can't find an available port";
    }
    
    my $server_socket = IO::Socket::INET->new(
      LocalAddr => $localhost,
      LocalPort => $port,
      Listen    => SOMAXCONN,
      Proto     => 'tcp',
      Timeout => 5,
      Reuse => 1,
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

sub wait_port_prepared {
  my ($port) = @_;
  
  my $max_wait = 3;
  my $wait_time = 0.1;
  my $wait_total = 0;
  while (1) {
    if ($wait_total > $max_wait) {
      last;
    }
    
    sleep $wait_time;
    
    my $sock = IO::Socket::INET->new(
      Proto    => 'tcp',
      PeerAddr => $localhost,
      PeerPort => $port,
    );
    
    if ($sock) {
      last;
    }
    $wait_total += $wait_time;
    $wait_time *= 2;
  }
}

# Starts a echo server
# if "\0" is sent, the server will stop.
sub start_echo_server {
  my ($port) = @_;
  
  my $server_socket = IO::Socket::INET->new(
    LocalAddr => $localhost,
    LocalPort => $port,
    Listen    => SOMAXCONN,
    Proto     => 'tcp',
    Reuse => 1,
  );
  unless ($server_socket) {
    die "Can't create a server socket:$@";
  }
  
  my $server_close;
  while (1) {
    my $client_socket = $server_socket->accept;
    
    $client_socket->autoflush(1);
    
    my $data;
    while ($data = <$client_socket>) {
      print $client_socket $data;
    }
  }
}

sub kill_term_and_wait {
  my ($process_id) = @_;
  
  kill 'TERM', $process_id;
  
  # On Windows, waitpid never return. I don't understan yet this reason(maybe IO blocking).
  unless ($^O eq 'MSWin32') {
    waitpid $process_id, 0;
  }
}

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Port
my $port = &search_available_port;

ok(SPVM::TestCase::Sys::Ioctl->ioctl($port));

SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
