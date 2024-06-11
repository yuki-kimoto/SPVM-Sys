package Test::SPVM::Sys::Socket::Util;

use strict;
use warnings;
use Carp ();

use Socket;

my $localhost = "127.0.0.1";

# Starts a echo server
sub run_echo_server {
  my ($port) = @_;
  
  my $server_socket = IO::Socket::INET->new(
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

