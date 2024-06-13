package Test::SPVM::Sys::Socket::Server;

use strict;
use warnings;
use Carp ();

use Socket;
use IO::Socket::IP;
use IO::Socket::UNIX;

# Fields
sub socket_domain { shift->{socket_domain} }

sub socket_type { shift->{socket_type} }

sub socket_protocol { shift->{socket_protocol} }

sub io_socket { shift->{io_socket} }

sub listen_backlog { shift->{listen_backlog} }

sub host { shift->{host} }

sub port { shift->{port} }

sub path { shift->{path} }

sub loop_cb { shift->{loop_cb} }

sub server_options { shift->{server_options} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    listen_backlog => SOMAXCONN,
    server_options => {},
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub new_echo_server_ipv4_tcp {
  my $class = shift;
  
  my $loop_cb = \&_echo_server_accept_loop;
  
  my %options = (
    socket_domain => AF_INET,
    socket_type => SOCK_STREAM,
    host => '127.0.0.1',
    loop_cb => $loop_cb,
    @_,
  );
  
  my $self = $class->new(%options);
  
  my $host = $self->{host};
  
  my $port = $self->{port};
  unless (defined $port) {
    Carp::confess("\"port\" option must be defined.");
  }
  
  my $listen_backlog = $self->{listen_backlog};
  
  my $socket_domain = $self->{socket_domain};
  
  my $socket_type = $self->{socket_type};
  
  my $io_socket = IO::Socket::IP->new(
    LocalAddr => $host,
    LocalPort => $port,
    Listen    => $listen_backlog,
    Domain => $socket_domain,
    Type     => $socket_type,
    ReuseAddr => 1,
  );
  
  unless ($io_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  $self->{io_socket} = $io_socket;
  
  return $self;
}

sub new_echo_server_ipv6_tcp {
  my $class = shift;
  
  my $loop_cb = \&_echo_server_accept_loop;
  
  my %options = (
    socket_domain => AF_INET6,
    socket_type => SOCK_STREAM,
    host => '::1',
    loop_cb => $loop_cb,
    @_,
  );
  
  my $self = $class->new(%options);
  
  my $host = $self->{host};
  
  my $port = $self->{port};
  unless (defined $port) {
    Carp::confess("\"port\" option must be defined.");
  }
  
  my $listen_backlog = $self->{listen_backlog};
  
  my $socket_domain = $self->{socket_domain};
  
  my $socket_type = $self->{socket_type};
  
  my $io_socket = IO::Socket::IP->new(
    LocalAddr => $host,
    LocalPort => $port,
    Listen    => $listen_backlog,
    Domain => $socket_domain,
    Type     => $socket_type,
    ReuseAddr => 1,
    V6Only   => 1,
  );
  
  unless ($io_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  $self->{io_socket} = $io_socket;
  
  return $self;
}

sub new_echo_server_unix_tcp {
  my $class = shift;
  
  my $loop_cb = \&_echo_server_accept_loop;
  
  my %options = (
    socket_type => SOCK_STREAM,
    loop_cb => $loop_cb,
    @_,
  );
  
  my $self = $class->new(%options);
  
  my $host = $self->{host};
  
  my $path = $self->{path};
  unless (defined $path) {
    Carp::confess("\"path\" option must be defined.");
  }
  
  my $listen_backlog = $self->{listen_backlog};
  
  my $socket_type = $self->{socket_type};
  
  my $io_socket = IO::Socket::UNIX->new(
    Type => $socket_type,
    Local => $path,
    Listen => $listen_backlog,
  );
  
  unless ($io_socket) {
    Carp::confess("Can't create a server socket:$@");
  }
  
  $self->{io_socket} = $io_socket;
  
  return $self;
}

sub _echo_server_accept_loop {
  my ($server_manager) = @_;
  
  my $io_socket = $server_manager->{io_socket};
  
  my $read_buffer_length = $server_manager->{server_options}{read_buffer_length} // 1024;
  
  while (1) {
    my $client_socket = $io_socket->accept;
    
    while (1) {
      my $buffer;
      my $read_length = $client_socket->sysread($buffer, $read_buffer_length);
      
      if ($read_length) {
        $client_socket->syswrite($buffer, $read_length);
      }
      else {
        last;
      }
    }
  }
}

# Instance Methods
sub start {
  my ($self) = @_;
  
  my $loop_cb = $self->{loop_cb};
  
  $loop_cb->($self);
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Server - Servers for tests for SPVM::Sys::Socket

=head1 Description

Test::SPVM::Sys::Socket::Server class has methods to start servers for tests for L<SPVM::Sys::Socket>.

=head1 Usage

=head1 Fields

=head2 socket_domain

  my $socket_domain $self->socket_domain;

=head2 socket_type

  my $socket_type $self->socket_type;

=head2 socket_protocol

  my $socket_protocol $self->socket_protocol;

=head2 io_socket

  my $io_socket $self->io_socket;

=head2 listen_backlog

  my $listen_backlog $self->listen_backlog;

=head2 host

  my $host $self->host;

=head2 port

  my $port $self->port;

=head2 path

  my $path $self->path;

=head2 loop_cb

  my $loop_cb $self->loop_cb;

=head2 server_options

  my $server_options $self->server_options;

=head1 Class Methods

=head2 new

  my $server_manager = Test::SPVM::Sys::Socket::Server->new(%options);

Creates a new L<Test::SPVM::Sys::Socket::Server> object and returns it.

=head2 new_echo_server_ipv4_tcp

  my $server_manager = Test::SPVM::Sys::Socket::Server->new_echo_server_ipv4_tcp(%options);

Creates a new a new L<Test::SPVM::Sys::Socket::Server> object that has the features for an IPv4 TCP echo server and returns it.

=head1 Instance Methods

=head2 start

  $server_manager->start;

Starts the server.

This method call a subroutine stored in L</"loop_cb"> field with the L<Test::SPVM::Sys::Socket::Server> object at 1th argument.
