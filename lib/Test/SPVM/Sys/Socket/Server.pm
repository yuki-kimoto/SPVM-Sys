package Test::SPVM::Sys::Socket::Server;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;
use IO::Socket::UNIX;
use Errno qw/ECONNREFUSED/;

my $localhost = "127.0.0.1";

# Class Methods
sub start_echo_server {
  my %options = @_;
  
  my $io_socket_options = $options{io_socket_options};
  
  unless ($io_socket_options) {
    Carp::confess("io_socket_options option must be defined.");
  }
  
  my $port = 
  
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

sub start_echo_server_unix {
  my ($path) = @_;
  
  my $server_socket = IO::Socket::UNIX->new(
    Type => SOCK_STREAM(),
    Local => $path,
    Listen => SOMAXCONN,
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

Test::SPVM::Sys::Socket::Server - Server Utility Functions for SPVM::Sys::Socket

=head1 Description

Test::SPVM::Sys::Socket::Server module has functions for server utilities for SPVM::Sys::Socket.

=head1 Usage

