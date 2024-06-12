package Test::SPVM::Sys::Socket::Server::IP;

use base 'Test::SPVM::Sys::Socket::Server';

use strict;
use warnings;
use Carp ();

use Test::SPVM::Sys::Socket::Util;

# Fields
sub port { shift->{port} }

# Instance Methods
sub init_fields {
  my ($self, %options) = @_;
  
  $self->SUPER::init_fields(%options);
  
  # port field
  my $port = Test::SPVM::Sys::Socket::Util::get_empty_port;
  
  $self->{port} = $port;
}

sub start {
  my ($self) = @_;
  
  my $port = $self->{port};
  
  my $pid = fork;
  
  unless (defined $pid) {
    Carp::confess("fork() failed: $!");
  }
  
  # Child
  if ($pid == 0) {
    my $code = $self->{code};
    
    $code->($port);
    
    if (kill 0, $self->{my_pid}) {
      warn("[Test::SPVM::Sys::Socket::Server::Socket::IP#start]Child process does not block(pid: $$, my_pid:$self->{my_pid}).");
    }
    
    exit 0;
  }
  # Parent
  else {
    $self->{pid} = $pid;
    
    $self->_wait_server_start;
  }
}

my $localhost = "127.0.0.1";

sub _wait_server_start {
  my ($self) = @_;
  
  my $port = $self->{port};
  
  my $max_wait = $self->{max_wait};
  
  $max_wait ||= 10;
  
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

1;

=head1 Name

Test::SPVM::Sys::Socket::Server::IP - Server Manager for IPv4/IPv6

=head1 Description

=head1 Usage

=head1 Details

This class is a L<Test::TCP> porting for tests for L<SPVM::Sys::Socket>.

=head1 Super Class

L<Test::SPVM::Sys::Socket::Server>

=head1 Fields

=head2 port

  my $port = $self->port;

The port number to which the server binds.

=head1 Class Methods

=head2 new


=head1 Instance Methods

=head2 start

  $server->start($code);

Starts a server process given an anon subroutine $code.

Call L<fork|https://perldoc.perl.org/functions/fork> function and starts the server specified by $code in the child process.

The parent process waits until the server starts.
