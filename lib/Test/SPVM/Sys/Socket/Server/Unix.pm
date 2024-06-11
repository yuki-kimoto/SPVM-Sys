package Test::SPVM::Sys::Socket::Server::UNIX;
use strict;
use warnings;
use 5.00800;
our $VERSION = '0.4';
use base qw/Exporter/;
use IO::Socket::UNIX;
use Test::SharedFork 0.12;
use Test::More ();
use Config;
use POSIX;
use Time::HiRes ();
use Carp ();
use File::Temp qw/ tempdir /;
use Net::EmptyPort ();
 
our @EXPORT = qw/ test_unix_sock wait_unix_sock /;
 
my $TERMSIG = 'TERM';
 
sub test_unix_sock {
    my %args = @_;
    for my $k (qw/client server/) {
        die "missing madatory parameter $k" unless exists $args{$k};
    }
    my $server_code = delete $args{server};
    my $client_code = delete $args{client};
 
    my $server = Test::SPVM::Sys::Socket::Server::UNIX->new(
        code => $server_code,
        %args,
    );
    $client_code->($server->path, $server->pid);
    undef $server; # make sure
}
 
sub wait_unix_sock {
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
    my $waiter = Net::EmptyPort::_make_waiter($max_wait);
    while ( $waiter->() ) {
        IO::Socket::UNIX->new(
            Type => SOCK_STREAM,
            Peer => $path,
        ) && return 1;
    }
    return 0;
}
 
# ------------------------------------------------------------------------- 
# OO-ish interface
 
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
 
sub pid  { $_[0]->{pid} }
sub path { $_[0]->{path} }
 
sub start {
    my $self = shift;
    my $pid = fork();
    die "fork() failed: $!" unless defined $pid;
 
    if ( $pid ) { # parent process.
        $self->{pid} = $pid;
        Test::SPVM::Sys::Socket::Server::UNIX::wait_unix_sock({ path => $self->path, max_wait => $self->{max_wait} });
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
 
sub stop {
    my $self = shift;
 
    return unless defined $self->{pid};
    return unless $self->{_my_pid} == $$;
 
    kill $TERMSIG => $self->{pid};
 
    local $?; # waitpid modifies original $?.
    LOOP: while (1) {
        my $kid = waitpid( $self->{pid}, 0 );
        if (POSIX::WIFSIGNALED($?)) {
            my $signame = (split(' ', $Config{sig_name}))[POSIX::WTERMSIG($?)];
            if ($signame =~ /^(ABRT|PIPE)$/) {
                Test::More::diag("your server received SIG$signame");
            }
        }
        if ($kid == 0 || $kid == -1) {
            last LOOP;
        }
    }
    undef $self->{pid};
}
 
sub DESTROY {
    my $self = shift;
    local $@;
    $self->stop();
}
 
1;

=head1 Name

Test::SPVM::Sys::Socket::Server::IP - Server Manager for UNIX Domain Sockets

=head1 Description

=head1 Usage

