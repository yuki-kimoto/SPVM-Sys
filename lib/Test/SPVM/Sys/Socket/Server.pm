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

sub pid { ... }

sub _my_pid { ... }

# Instance Methods
sub stop {
  my ($self) = @_;
  
  unless (defined $self->{pid}) {
    return;
  }
  
  unless ($self->{_my_pid} == $$) {
    return ;
  }
  
  Win32::Sleep(0) if $^O eq "MSWin32";
  
  kill $TERMSIG => $self->{pid};
  
  Win32::Sleep(0) if $^O eq "MSWin32";
  
  local $?;
  
  LOOP: while (1) {
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
      last LOOP;
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

Test::SPVM::Sys::Socket::Server - Server Manager

=head1 Description

=head1 Usage

=head1 Well Known Child Class

=over 2

=item * L<Test::SPVM::Sys::Socket::Server::IP>

=item * L<Test::SPVM::Sys::Socket::Server::UNIX>

=back
