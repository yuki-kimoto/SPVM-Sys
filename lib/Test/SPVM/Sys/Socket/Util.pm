package Test::SPVM::Sys::Socket::Util;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;

my $localhost = "127.0.0.1";

sub can_bind {
  my ($host, $port, $proto) = @_;
  
  my $socket = &_listen_socket($host, $port, $proto);
  
  my $can_bind = defined $socket;
  
  return $can_bind;
}

sub _listen_socket {
  my ($host, $port, $proto) = @_;
  
  $port  ||= 0;
  
  $proto ||= 'tcp';
  
  my %options = (
    (($proto eq 'udp') ? () : (Listen => 5)),
    LocalAddr => $host,
    LocalPort => $port,
    Proto     => $proto,
    # In Windows, SO_REUSEADDR works differently In Linux. The feature that corresponds to SO_REUSEADDR in Linux is enabled by default in Windows.
    (($^O eq 'MSWin32') ? () : (ReuseAddr => 1)),
  );
  
  my $socket = IO::Socket::IP->new(%options);
  
  return $socket;
}

sub get_empty_port {
  my ($host, $port, $proto) = @_;
  
  $host = '127.0.0.1'
      unless defined $host;
  $proto = $proto ? lc($proto) : 'tcp';
  
  if (defined $port) {
      # to ensure lower bound, check one by one in order
      $port = 49152 unless $port =~ /^[0-9]+$/ && $port < 49152;
      while ( $port++ < 65000 ) {
          # Remote checks don't work on UDP, and Local checks would be redundant here...
          next if ($proto eq 'tcp' && check_port({ host => $host, port => $port }));
          return $port if &can_bind($host, $port, $proto);
      }
  } else {
      # kernel will select an unused port
      while ( my $sock = _listen_socket($host, undef, $proto) ) {
          $port = $sock->sockport;
          $sock->close;
          next if ($proto eq 'tcp' && check_port({ host => $host, port => $port }));
          return $port;
      }
  }
  
  Carp::confess("empty port not found");
}

sub check_port {
    my ($host, $port, $proto) = @_ && ref $_[0] eq 'HASH' ? ($_[0]->{host}, $_[0]->{port}, $_[0]->{proto}) : (undef, @_);
    $host = '127.0.0.1'
        unless defined $host;
 
    return _check_port_udp($host, $port)
        if $proto && lc($proto) eq 'udp';
 
    # TCP, check if possible to connect
    my $sock = IO::Socket::IP->new(
        Proto    => 'tcp',
        PeerAddr => $host,
        PeerPort => $port,
    );
 
    if ($sock) {
        close $sock;
        return 1; # The port is used.
    }
    else {
        return 0; # The port is not used.
    }
 
}

sub wait_port {
  my ($port) = @_;
  
  my $max_wait = 3;
  my $wait_time = 0.1;
  my $wait_total = 0;
  while (1) {
    if ($wait_total > $max_wait) {
      last;
    }
    
    sleep $wait_time;
    
    my $sock = IO::Socket::IP->new(
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

sub run_echo_server {
  my ($port) = @_;
  
  my $server_socket = IO::Socket::IP->new(
    LocalAddr => $localhost,
    LocalPort => $port,
    Listen    => SOMAXCONN,
    Proto     => 'tcp',
    Reuse => 1,
  );
  unless ($server_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  while (1) {
    my $client_socket = $server_socket->accept;
    
    while (my $data = <$client_socket>) {
      print $client_socket $data;
    }
  }
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Util - Socket Utility Functions for SPVM::Sys::Socket

=head1 Description

Test::SPVM::Sys::Socket::Util module has functions for socket utilities for SPVM::Sys::Socket.

=head1 Usage

