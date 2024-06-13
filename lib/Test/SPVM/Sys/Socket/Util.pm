package Test::SPVM::Sys::Socket::Util;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;
use IO::Socket::UNIX;
use Errno qw/ECONNREFUSED/;

sub get_empty_port {
  
  # System will select an unused port
  my $socket = IO::Socket::IP->new(
    Listen => 5,
    # In Windows, SO_REUSEADDR works differently In Linux. The feature that corresponds to SO_REUSEADDR in Linux is enabled by default in Windows.
    (($^O eq 'MSWin32') ? () : (ReuseAddr => 1)),
  );
  my $port = $socket->sockport;
  
  $socket->close;
  
  return $port;
}

sub _is_available_port {
  my ($host, $port, $proto) = @_;
  
  my $is_available_port = 0;
  if ($proto eq 'udp') {
    $is_available_port = &_is_available_port_udp($host, $port)
  }
  elsif ($proto eq 'tcp') {
    $is_available_port = &_is_available_port_tcp($host, $port)
  }
  else {
    Carp::confess("\"proto\" option does not support \"$proto\".");
  }
  
  return $is_available_port;
}

sub _is_available_port_tcp {
  my ($host, $port) = @_;
  
  my $sock = IO::Socket::IP->new(
    Proto    => 'tcp',
    PeerAddr => $host,
    PeerPort => $port,
    V6Only    => 1,
  );
  
  my $used = 0;
  
  if ($sock) {
    close $sock;
    $used = 1;
  }
  
  my $is_available_port = !$used;
  
  return $is_available_port;
}

sub _is_available_port_udp {
  my ($host, $port) = @_;
  
  # send some UDP data and see if ICMP error is being sent back (i.e. ECONNREFUSED)
  my $sock = IO::Socket::IP->new(
      Proto    => 'udp',
      PeerAddr => $host,
      PeerPort => $port,
      V6Only   => 1,
      Blocking => 0,
  ) or die "failed to create bound UDP socket:$!";
  
  $sock->send("0", 0)
      or die "failed to send a UDP packet:$!";
  
  my ($rfds, $efds) = ('', '');
  vec($rfds, fileno($sock), 1) = 1;
  vec($efds, fileno($sock), 1) = 1;
  select $rfds, undef, $efds, 0.1;
  
  # after 0.1 second of silence, we assume that the server is up
  my $used = defined($sock->recv(my $data, 1000)) || (
      ($^O eq 'MSWin32')
          ? ($^E != Errno::WSAECONNRESET() && $^E != Errno::WSAECONNREFUSED())
          : ($! != ECONNREFUSED)
  );
  close $sock;
  
  my $is_available_port = !$used;
  
  return $is_available_port;
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Util - Socket Utility Functions for SPVM::Sys::Socket

=head1 Description

Test::SPVM::Sys::Socket::Util module has functions for socket utilities for SPVM::Sys::Socket.

=head1 Usage

