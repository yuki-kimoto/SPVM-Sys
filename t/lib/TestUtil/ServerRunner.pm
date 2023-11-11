package TestUtil::ServerRunner;

use strict;
use warnings;
use Carp 'confess';

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
    @_
  };
  
  bless $self, ref $class || $class;
  
  my $port = $self->empty_port;
  
  $self->{port} = $port;
  
  my $code = $self->{code};
  
  my $process_id = fork;
  
  # Child
  if ($process_id == 0) {
    $code->($port);
  }
  else {
    $self->{process_id} = $process_id;
    
    $self->wait_port($port);
  }
  
  return $self;
}

sub can_bind {
    my ($host, $port, $proto) = @_;
    # The following must be split across two statements, due to
    # https://rt.perl.org/Public/Bug/Display.html?id=124248
    my $s = _listen_socket($host, $port, $proto);
    return defined $s;
}

sub _listen_socket {
    my ($host, $port, $proto) = @_;
    $port  ||= 0;
    $proto ||= 'tcp';
    IO::Socket::INET->new(
        (($proto eq 'udp') ? () : (Listen => 5)),
        LocalAddr => $host,
        LocalPort => $port,
        Proto     => $proto,
        # V6Only    => 1,
        (($^O eq 'MSWin32') ? () : (ReuseAddr => 1)),
    );
}

# get a empty port on 49152 .. 65535
# http://www.iana.org/assignments/port-numbers
sub empty_port {
    my ($host, $port, $proto) = @_ && ref $_[0] eq 'HASH' ? ($_[0]->{host}, $_[0]->{port}, $_[0]->{proto}) : (undef, @_);
    $host = '127.0.0.1'
        unless defined $host;
    $proto = $proto ? lc($proto) : 'tcp';
 
    if (defined $port) {
        # to ensure lower bound, check one by one in order
        $port = 49152 unless $port =~ /^[0-9]+$/ && $port < 49152;
        while ( $port++ < 65000 ) {
            # Remote checks don't work on UDP, and Local checks would be redundant here...
            next if ($proto eq 'tcp' && check_port({ host => $host, port => $port }));
            return $port if can_bind($host, $port, $proto);
        }
    } else {
        # kernel will select an unused port
        while ( my $sock = _listen_socket($host, undef, $proto) ) {
            $port = $sock->sockport;
            $sock->close;
            next if ($proto eq 'tcp' && check_port({ host => $host, port => $port }));
            return $port;
        }
    }
    die "empty port not found";
}

sub check_port {
    my ($host, $port, $proto) = @_ && ref $_[0] eq 'HASH' ? ($_[0]->{host}, $_[0]->{port}, $_[0]->{proto}) : (undef, @_);
    $host = '127.0.0.1'
        unless defined $host;
 
    return _check_port_udp($host, $port)
        if $proto && lc($proto) eq 'udp';
 
    # TCP, check if possible to connect
    my $sock = IO::Socket::INET->new(
        Proto    => 'tcp',
        PeerAddr => $host,
        PeerPort => $port,
        # V6Only   => 1,
    );
 
    if ($sock) {
        close $sock;
        return 1; # The port is used.
    }
    else {
        return 0; # The port is not used.
    }
 
}

sub wait_port {
  my ($class, $port) = @_;
  
  my $max_wait = 3;
  my $wait_time = 0.1;
  my $wait_total = 0;
  while (1) {
    if ($wait_total > $max_wait) {
      last;
    }
    
    sleep $wait_time;
    
    my $sock = IO::Socket::INET->new(
      Proto    => 'tcp',
      PeerAddr => $localhost,
      PeerPort => $port,
    );
    
    if ($sock) {
      last;
    }
    $wait_total += $wait_time;
    $wait_time *= 2;
  }
}

sub run_do_nothing_server {
  my ($class, $port) = @_;
  
  my $server_socket = IO::Socket::INET->new(
    LocalAddr => $localhost,
    LocalPort => $port,
    Listen    => SOMAXCONN,
    Proto     => 'tcp',
    Reuse => 1,
  );
  unless ($server_socket) {
    confess "Can't create a server socket:$@";
  }
  
  while (1) {
    my $client_socket = $server_socket->accept;
    
    $client_socket->close;
  }
}

# Starts a echo server
# if "\0" is sent, the server will stop.
sub run_echo_server {
  my ($class, $port) = @_;
  
  my $server_socket = IO::Socket::INET->new(
    LocalAddr => $localhost,
    LocalPort => $port,
    Listen    => SOMAXCONN,
    Proto     => 'tcp',
    Reuse => 1,
  );
  unless ($server_socket) {
    confess "Can't create a server socket:$@";
  }
  
  while (1) {
    my $client_socket = $server_socket->accept;
    
    $client_socket->autoflush(1);
    
    my $data;
    while ($data = <$client_socket>) {
      my $close = 0;
      if ($data =~ s/\0.*//) {
        $close = 1;
      }
      
      print $client_socket $data;
      
      if ($close) {
        $client_socket->close;
        last;
      }
    }
  }
}


# Instance Methods
sub stop {
  my ($self) = @_;
  
  my $process_id = $self->{process_id};
  
  kill $TERMSIG, $process_id;
  
  # On Windows, waitpid never return. I don't understan yet this reason(maybe IO blocking).
  unless ($^O eq 'MSWin32') {
    waitpid $process_id, 0;
  }
}

sub DESTROY {
  my ($self) = @_;
  
  $self->stop;
}
