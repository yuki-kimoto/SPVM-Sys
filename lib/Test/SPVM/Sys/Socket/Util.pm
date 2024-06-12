package Test::SPVM::Sys::Socket::Util;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;
use IO::Socket::UNIX;
use Errno qw/ECONNREFUSED/;

my $localhost = "127.0.0.1";

sub get_empty_port {
  my %options = @_;
  
  # host option
  my $host = $options{host};
  unless (defined $host) {
    $host = '127.0.0.1';
  }
  
  # proto option
  my $proto = $options{proto};
  unless (defined $proto) {
    $proto = 'tcp';
  }
  $proto = lc $proto;
  
  # kernel will select an unused port
  while ( my $sock = _listen_socket($host, undef, $proto) ) {
    my $port = $sock->sockport;
    $sock->close;
    next if ($proto eq 'tcp' && &_can_use_port(host => $host, port => $port));
    return $port;
  }
  
  Carp::confess("empty port not found");
}

sub _listen_socket {
  my ($host, $port, $proto) = @_;
  
  my %options = (
    (($proto eq 'udp') ? () : (Listen => 5)),
    LocalAddr => $host,
    LocalPort => $port,
    Proto     => $proto,
    # In Windows, SO_REUSEADDR works differently In Linux. The feature that corresponds to SO_REUSEADDR in Linux is enabled by default in Windows.
    (($^O eq 'MSWin32') ? () : (ReuseAddr => 1)),
    V6Only    => 1,
  );
  
  my $socket = IO::Socket::IP->new(%options);
  
  return $socket;
}

sub _can_use_port {
  my %options = @_;
  
  my $host = $options{host};
  unless (defined $host) {
    $host = '127.0.0.1';
  }
  
  # port option
  my $port = $options{port};
  
  # proto option
  my $proto = $options{proto};
  unless (defined $proto) {
    $proto = 'tcp';
  }
  $proto = lc $proto;
  
  my $can_use = 0;
  if ($proto eq 'udp') {
    $can_use = &_can_use_port_udp($host, $port)
  }
  elsif ($proto eq 'tcp') {
    $can_use = &_can_use_port_tcp($host, $port)
  }
  else {
    Carp::confess("\"proto\" option does not support \"$proto\".");
  }
}

sub _can_use_port_tcp {
  my ($host, $port) = @_;
  
  my $sock = IO::Socket::IP->new(
    Proto    => 'tcp',
    PeerAddr => $host,
    PeerPort => $port,
    V6Only    => 1,
  );
  
  my $can_use = 0;
  
  if ($sock) {
    close $sock;
    $can_use = 1;
  }
  
  return $can_use;
}

sub _can_use_port_udp {
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
  my $can_use = defined($sock->recv(my $data, 1000)) || (
      ($^O eq 'MSWin32')
          ? ($^E != Errno::WSAECONNRESET() && $^E != Errno::WSAECONNREFUSED())
          : ($! != ECONNREFUSED)
  );
  close $sock;
  
  return $can_use;
}

sub run_echo_server {
  my ($port) = @_;
  
  my $server_socket = IO::Socket::IP->new(
    LocalAddr => $localhost,
    LocalPort => $port,
    Listen    => SOMAXCONN,
    Proto     => 'tcp',
    ReuseAddr => 1,
  );
  unless ($server_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  while (1) {
    my $client_socket = $server_socket->accept;
    
    while (1) {
      my $buffer;
      my $read_length = $client_socket->sysread($buffer, 1024);
      
      if ($read_length) {
        $client_socket->syswrite($buffer, $read_length);
      }
      else {
        last;
      }
    }
  }
}

sub run_echo_server_unix {
  my ($path) = @_;
  
  my $server_socket = IO::Socket::UNIX->new(
    Type => SOCK_STREAM(),
    Local => $path,
    Listen => 1,
  );
  
  unless ($server_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  while (1) {
    my $client_socket = $server_socket->accept;
    
    while (1) {
      my $buffer;
      my $read_length = $client_socket->sysread($buffer, 1024);
      
      if ($read_length) {
        $client_socket->syswrite($buffer, $read_length);
      }
      else {
        last;
      }
    }
  }
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Util - Socket Utility Functions for SPVM::Sys::Socket

=head1 Description

Test::SPVM::Sys::Socket::Util module has functions for socket utilities for SPVM::Sys::Socket.

=head1 Usage

