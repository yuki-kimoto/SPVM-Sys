package Test::SPVM::Sys::Socket::Server;

use strict;
use warnings;
use Carp ();
use Config;
use POSIX ();

use Test::SPVM::Sys::Socket::Util;

# process does not die when received SIGTERM in Windows
my $TERMSIG = $^O eq 'MSWin32' ? 'KILL' : 'TERM';

# Fields

sub pid  { $_[0]->{pid} }

sub my_pid { shift->{my_pid} }

sub auto_start { shift->{auto_start} }

# Instance Methods
sub stop {
  my ($self) = @_;
  
  unless (defined $self->{pid}) {
    return;
  }
  
  unless ($self->{my_pid} == $$) {
    return ;
  }
  
  Win32::Sleep(0) if $^O eq "MSWin32";
  
  kill $TERMSIG => $self->{pid};
  
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

=head1 Instance Methods

=head2 stop

Stop the server process.

=head2 DESTROY

The destructor, which call L</"stop"> method.

=head1 Well Known Child Class

=over 2

=item * L<Test::SPVM::Sys::Socket::Server::IP>

=item * L<Test::SPVM::Sys::Socket::Server::UNIX>

=back
