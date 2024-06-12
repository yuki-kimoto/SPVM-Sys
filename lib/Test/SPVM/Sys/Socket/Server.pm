package Test::SPVM::Sys::Socket::Server;

use strict;
use warnings;
use Carp ();
use Config;
use POSIX ();

use Test::SPVM::Sys::Socket::Util;

# Fields
sub pid  { shift->{pid} }

sub my_pid { shift->{my_pid} }

sub auto_start { shift->{auto_start} }

sub max_wait { shift->{max_wait} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = bless {}, ref $class || $class;
  
  $self->init_fields(@_);
  
  if ($self->{auto_start}) {
    $self->start;
  }
  
  return $self;
}

# Instance Methods
sub init_fields {
  my ($self, %options) = @_;
  
  # auto_start field
  my $auto_start = $options{auto_start};
  unless (defined $auto_start) {
    $auto_start = 1;
  }
  $self->{auto_start} = $auto_start;
  
  # max_wait field
  my $max_wait = $options{max_wait};
  unless (defined $max_wait) {
    $max_wait = 10;
  }
  $self->{max_wait} = $max_wait;
  
  # my_pid field
  my $my_pid = $options{my_pid};
  unless (defined $my_pid) {
    $my_pid = $$;
  }
  $self->{my_pid} = $my_pid;
  
  # code field
  my $code = $options{code};
  unless (defined $code) {
    Carp::confess("\"code\" option must be deinfed.") ;
  }
  $self->{code} = $code;
}

sub start { Carp::confess("Not implemented.") }

sub stop {
  my ($self) = @_;
  
  unless (defined $self->{pid}) {
    return;
  }
  
  unless ($self->{my_pid} == $$) {
    return ;
  }
  
  Win32::Sleep(0) if $^O eq "MSWin32";
  
  # process does not die when received SIGTERM in Windows
  my $termsig = $^O eq 'MSWin32' ? 'KILL' : 'TERM';
  
  kill $termsig, $self->{pid};
  
  Win32::Sleep(0) if $^O eq "MSWin32";
  
  local $?;
  
  while (1) {
    my $kid = waitpid( $self->{pid}, 0 );
    if ($^O ne 'MSWin32') {
      if (POSIX::WIFSIGNALED($?)) {
        my $signame = (split(' ', $Config{sig_name}))[POSIX::WTERMSIG($?)];
        if ($signame =~ /^(ABRT|PIPE)$/) {
          Test::More::diag("your server received SIG$signame");
        }
      }
    }
    if ($kid == 0 || $kid == -1) {
      last;
    }
  }
  undef $self->{pid};
}

sub DESTROY {
  my ($self) = @_;
  
  $self->stop;
}

1;

=head1 Name

Test::SPVM::Sys::Socket::Server - Server Manager Base Class

=head1 Description

Test::SPVM::Sys::Socket::Server is a base class for server managers.

=head1 Fields

=head2 pid

  my $pid = $self->pid;

The child process ID created by L<fork|https://perldoc.perl.org/functions/fork> function.

=head2 my_pid

  my $my_pid = $self->my_pid;

The parent process ID created by L<fork|https://perldoc.perl.org/functions/fork> function.

=head2 auto_start

  my $auto_start = $self->auto_start;

If this field is a true value, L</"new"> method call L</"start"> method, otherwise does not call it.

=head2 max_wait

  my $max_wait = $self->max_wait;

The maximum number of times to wait to check that a server has been started by a child process created by L<fork|https://perldoc.perl.org/functions/fork> function..

=head1 Class Methods

=head2 new

  my $server = Test::SPVM::Sys::Socket::Server->new(%options);

Creates a new L<Test::SPVM::Sys::Socket::Server> object and returns it.

L</"pid"> field is set to the current process ID.

L</"max_wait"> field is set to 10 if C<max_wait> option is not specified.

L</"auto_start"> field is set to 1 if C<auto_start> option is not specified.

This method is planed to be implemented in child classes.

Options:

=over 2

=item * C<auto_start>

Sets L</"auto_start"> field to this value.

=item * C<max_wait>

Sets L</"max_wait"> field to this value.

=back

=head1 Instance Methods

=head2 start

  $server->start($code);

Starts a server process given an anon subroutine $code.

Call L<fork|https://perldoc.perl.org/functions/fork> function and starts the server specified by $code in the child process.

The parent process waits until the server starts.

This method is planed to be implemented in child classes.

=head2 stop

  $server->stop;

Stops the server process stared by L</"start"> method.

=head2 DESTROY

The destructor.

This method calls L</"stop"> method.

=head1 Well Known Child Class

=over 2

=item * L<Test::SPVM::Sys::Socket::Server::IP>

=item * L<Test::SPVM::Sys::Socket::Server::UNIX>

=back
