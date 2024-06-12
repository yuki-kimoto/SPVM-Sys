package Test::SPVM::Sys::Socket::Server::UNIX;

use base 'Test::SPVM::Sys::Socket::Server';

use strict;
use warnings;
use Carp ();

use IO::Socket::UNIX;
use File::Temp ();
use Time::HiRes ();

# Fields
sub max_wait { shift->{max_wait} }

sub tmpdir { shift->{tmpdir} }

sub path { shift->{path} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    auto_start => 1,
    max_wait   => 10,
    my_pid    => $$,
    @_,
  };
  
  bless $self, ref $class || $class;
  
  unless (defined $self->{code}) {
    Carp::confess("The anon subroutine \$code must be defined.") ;
  }
  
  unless (defined $self->{path}) {
    $self->{tmpdir} = File::Temp->newdir;
    $self->{path} = $self->{tmpdir} . "/test.sock";
  }
  
  if ($self->{auto_start}) {
    $self->start;
  }
  
  return $self;
}

# Instance Methods
sub start {
  my ($self) = @_;
  
  my $path = $self->path;
  
  my $pid = fork();
  
  unless (defined $pid) {
    Carp::confess("fork() failed: $!");
  }
  
  # Child
  if ($pid == 0) {
    
    my $code = $self->{code};
    
    $code->($path);
    
    if (kill 0, $self->{my_pid}) {
      warn("[Test::SPVM::Sys::Socket::Server::Socket::UNIX#start]Child process does not block(pid: $$, my_pid:$self->{my_pid}).");
    }
    
    exit 0;
  }
  # Parent
  else {
    $self->{pid} = $pid;
    $self->_wait_server_start;
    return;
  }
}

sub _wait_server_start {
  my ($self) = @_;
  
  my $path = $self->path;
  
  my $max_wait = $self->{max_wait};
  
  $max_wait ||= 10;
  
  my $waiter = &_make_waiter($max_wait);
  
  while ($waiter->()) {
    my $socket = IO::Socket::UNIX->new(
      Type => SOCK_STREAM,
      Peer => $path,
    );
    
    if ($socket) {
      return 1;
    }
  }
  
  return 0;
}

sub _make_waiter {
  my ($max_wait) = @_;
  
  my $waited = 0;
  
  my $sleep  = 0.001;
  
  my $waiter = sub {
    return 0 if $max_wait >= 0 && $waited > $max_wait;
    
    Time::HiRes::sleep($sleep);
    $waited += $sleep;
    $sleep  *= 2;
    
    return 1;
  };
  
  return $waiter;
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Server::IP - Server Manager for UNIX Domain Sockets

=head1 Description

=head1 Usage

=head1 Details

This class is a L<Test::UNIXSock> porting for tests for L<SPVM::Sys::Socket>.

=head1 Super Class

L<Test::SPVM::Sys::Socket::Server>
