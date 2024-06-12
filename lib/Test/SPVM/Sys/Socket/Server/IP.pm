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
    @_,
    my_pid => $$,
  };
  
  bless $self, ref $class || $class;
  
  my $port = Test::SPVM::Sys::Socket::Util::get_empty_port;
  
  $self->{port} = $port;
  
  my $code = $self->{code};
  
  my $pid = fork;
  
  # Child
  if ($pid == 0) {
    $code->($port);
  }
  else {
    $self->{pid} = $pid;
    
    Test::SPVM::Sys::Socket::Util::wait_port($port);
  }
  
  return $self;
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
