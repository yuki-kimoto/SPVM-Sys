package Test::SPVM::Sys::Socket::Server;

use strict;
use warnings;
use Carp ();
use Config;

use Test::SPVM::Sys::Socket::Util;
use IO::Socket::INET;

# process does not die when received SIGTERM, on win32.
my $TERMSIG = $^O eq 'MSWin32' ? 'KILL' : 'TERM';

my $localhost = "127.0.0.1";

# Fields
sub port { shift->{port} }

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    @_,
    _my_pid => $$,
  };
  
  bless $self, ref $class || $class;
  
  my $port = Test::SPVM::Sys::Socket::Util::empty_port;
  
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

# Instance Methods
sub stop {
    my ($self) = @_;
 
    return unless defined $self->{pid};
    return unless $self->{_my_pid} == $$;
 
    # This is a workaround for win32 fork emulation's bug.
    #
    # kill is inherently unsafe for pseudo-processes in Windows
    # and the process calling kill(9, $pid) may be destabilized
    # The call to Sleep will decrease the frequency of this problems
    #
    # SEE ALSO:
    #   http://www.gossamer-threads.com/lists/perl/porters/261805
    #   https://rt.cpan.org/Ticket/Display.html?id=67292
    Win32::Sleep(0) if $^O eq "MSWin32"; # will relinquish the remainder of its time slice
 
        kill $TERMSIG => $self->{pid};
 
    Win32::Sleep(0) if $^O eq "MSWin32"; # will relinquish the remainder of its time slice
 
 
    local $?; # waitpid modifies original $?.
    LOOP: while (1) {
        my $kid = waitpid( $self->{pid}, 0 );
        if ($^O ne 'MSWin32') { # i'm not in hell
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

