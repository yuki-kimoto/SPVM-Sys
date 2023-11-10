package TestUtil::ServerRunner;

use strict;
use warnings;
use Carp 'confess';

use Socket;
use IO::Socket;
use IO::Socket::INET;

my $localhost = "127.0.0.1";

# Fields
sub port { shift->{port} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    @_
  };
  
  bless $self, ref $class || $class;
  
  my $port = $self->search_available_port;
  
  $self->{port} = $port;
  
  my $code = $self->{code};
  
  my $process_id = fork;
  
  # Child
  if ($process_id == 0) {
    $code->($port);
    exit;
  }
  else {
    $self->{process_id} = $process_id;
    
    $self->wait_port_prepared($port);
  }
  
  return $self;
}

sub search_available_port {
  my ($class) = @_;
  
  my $try_port = 20000;
  
  my $available_port;
  my $retry_max = 10;
  my $retry_count = 0;
  while (1) {
    if ($retry_count > 0) {
      warn "[Test Output]Perform the ${retry_count} retry to search an available port $try_port";
    }
    
    if ($retry_count > $retry_max) {
      confess "Can't find an available port";
    }
    
    my $server_socket = IO::Socket::INET->new(
      PeerAddr => $localhost,
      PeerPort => $try_port,
      Timeout => 5,
    );
    
    unless ($server_socket) {
      $available_port = $try_port;
      last;
    }
    
    $try_port++;
    $retry_count++;
  }
  
  return $available_port;
}

sub wait_port_prepared {
  my ($class, $port) = @_;
  
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

sub kill_term_and_wait {
  my ($class, $process_id) = @_;
  
  kill 'TERM', $process_id;
  
  # On Windows, waitpid never return. I don't understan yet this reason(maybe IO blocking).
  unless ($^O eq 'MSWin32') {
    waitpid $process_id, 0;
  }
}

# Instance Methods
sub DESTROY {
  my $self = shift;
  
  my $process_id = $self->{process_id};
  
  $self->kill_term_and_wait($process_id);
}
