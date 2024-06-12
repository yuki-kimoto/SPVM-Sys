package Test::SPVM::Sys::Socket::Util;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;
use IO::Socket::UNIX;
use Errno qw/ECONNREFUSED/;

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
    V6Only    => 1,
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
          next if ($proto eq 'tcp' && &_check_port({ host => $host, port => $port }));
          return $port if &can_bind($host, $port, $proto);
      }
  } else {
      # kernel will select an unused port
      while ( my $sock = _listen_socket($host, undef, $proto) ) {
          $port = $sock->sockport;
          $sock->close;
          next if ($proto eq 'tcp' && &_check_port({ host => $host, port => $port }));
          return $port;
      }
  }
  
  Carp::confess("empty port not found");
}

sub _check_port {
    my ($host, $port, $proto) = @_ && ref $_[0] eq 'HASH' ? ($_[0]->{host}, $_[0]->{port}, $_[0]->{proto}) : (undef, @_);
    $host = '127.0.0.1'
        unless defined $host;
 
    return &_check_port_udp($host, $port)
        if $proto && lc($proto) eq 'udp';
 
    # TCP, check if possible to connect
    my $sock = IO::Socket::IP->new(
        Proto    => 'tcp',
        PeerAddr => $host,
        PeerPort => $port,
        V6Only    => 1,
    );
 
    if ($sock) {
        close $sock;
        return 1; # The port is used.
    }
    else {
        return 0; # The port is not used.
    }
 
}

sub _check_port_udp {
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
    my $up = defined($sock->recv(my $data, 1000)) || (
        ($^O eq 'MSWin32')
            ? ($^E != Errno::WSAECONNRESET() && $^E != Errno::WSAECONNREFUSED())
            : ($! != ECONNREFUSED)
    );
    close $sock;
    $up;
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

