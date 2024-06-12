package Test::SPVM::Sys::Socket::Server::UNIX;

use base 'Test::SPVM::Sys::Socket::Server';

use strict;
use warnings;
use Carp ();

use IO::Socket::UNIX;
use File::Temp ();
use Time::HiRes ();

# Fields
sub auto_start { shift->{auto_start} }

sub max_wait { shift->{max_wait} }

sub tmpdir { shift->{tmpdir} }

sub path { shift->{path} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    auto_start => 1,
    max_wait   => 10,
    _my_pid    => $$,
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
    $self->start();
  }
  
  return $self;
}

# Instance Methods
sub start {
  my ($self) = @_;
  
  my $pid = fork();
  
  unless (defined $pid) {
    Carp::confess("fork() failed: $!");
  }
  
  # Parent process
  if ($pid) {
    $self->{pid} = $pid;
    &_wait_unix_sock($self->path, $self->{max_wait});
    return;
  }
  # Child process
  else {
    $self->{code}->($self->path);
    if (kill 0, $self->{_my_pid}) {
      warn("[Test::SPVM::Sys::Socket::Server::UNIXet] Child process does not block(PID: $$, PPID: $self->{_my_pid})");
    }
    exit 0;
  }
}

sub _wait_unix_sock {
  my ($path, $max_wait) = @_;
  
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
