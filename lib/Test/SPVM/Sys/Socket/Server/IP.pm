package Test::SPVM::Sys::Socket::Server::IP;

use base 'Test::SPVM::Sys::Socket::Server';

use strict;
use warnings;
use Carp ();

use Test::SPVM::Sys::Socket::Util;

# Fields
sub port { shift->{port} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    auto_start => 1,
    my_pid => $$,
    @_,
  };
  
  bless $self, ref $class || $class;
  
  my $port = Test::SPVM::Sys::Socket::Util::get_empty_port;
  
  $self->{port} = $port;
  
  if ($self->{auto_start}) {
    $self->start;
  }
  
  return $self;
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
    
    Test::SPVM::Sys::Socket::Util::wait_port($port);
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
