package Test::SPVM::Sys::Socket::Server::UNIX;

use base 'Test::SPVM::Sys::Socket::Server';

use strict;
use warnings;
use IO::Socket::UNIX;
use Carp ();
use File::Temp 'tempdir';
use Time::HiRes ();

# Fields
sub auto_start { ... }

sub max_wait { ... }

sub tmpdir { ... }

sub path { ... }

# Class Methods
sub new {
    my $class = shift;
    my %args = @_==1 ? %{$_[0]} : @_;
    Carp::croak("missing mandatory parameter 'code'") unless exists $args{code};
    my $self = bless {
        auto_start => 1,
        max_wait   => 10,
        _my_pid    => $$,
        %args,
    }, $class;
    unless (defined $self->{path}) {
        $self->{tmpdir} = tempdir( CLEANUP => 1 );
        $self->{path} = $self->{tmpdir} . "/test.sock";
    }
    $self->start()
      if $self->{auto_start};
    return $self;
}

# Instance Methods
sub start {
  my $self = shift;
  my $pid = fork();
  
  die "fork() failed: $!" unless defined $pid;
  
  if ( $pid ) { # parent process.
      $self->{pid} = $pid;
      &_wait_unix_sock({ path => $self->path, max_wait => $self->{max_wait} });
      return;
  } else { # child process
      $self->{code}->($self->path);
      # should not reach here
      if (kill 0, $self->{_my_pid}) { # warn only parent process still exists
          warn("[Test::SPVM::Sys::Socket::Server::UNIXet] Child process does not block(PID: $$, PPID: $self->{_my_pid})");
      }
      exit 0;
  }
}

sub _wait_unix_sock {
  my ($path, $max_wait);
  if (@_ && ref $_[0] eq 'HASH') {
      $path = $_[0]->{path};
      $max_wait = $_[0]->{max_wait};
  } elsif (@_ == 3) {
      # backward compat
      ($path, (my $sleep), (my $retry)) = @_;
      $max_wait = $sleep * $retry;
  } else {
      ($path, $max_wait) = @_;
  }
  $max_wait ||= 10;
  my $waiter = &_make_waiter($max_wait);
  while ( $waiter->() ) {
      IO::Socket::UNIX->new(
          Type => SOCK_STREAM,
          Peer => $path,
      ) && return 1;
  }
  return 0;
}

sub _make_waiter {
  my $max_wait = shift;
  my $waited = 0;
  my $sleep  = 0.001;
  
  return sub {
    return 0 if $max_wait >= 0 && $waited > $max_wait;
    
    Time::HiRes::sleep($sleep);
    $waited += $sleep;
    $sleep  *= 2;
    
    return 1;
  };
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
