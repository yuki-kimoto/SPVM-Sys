use Test::More;

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
BEGIN { $ENV{SPVM_BUILD_DIR} = "$FindBin::Bin/.spvm_build"; }

use Config;
    
use POSIX q(:sys_wait_h);

use SPVM 'Sys::Signal';
use SPVM 'Sys::Signal::Constant';

use SPVM 'Fn';
use SPVM 'TestCase::Sys::Signal';

use File::Temp;

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Signal->kill(0, 0) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Signal->kill);
}

{
  my %signo;
  {
    my $i = 0;
    for my $name (split(' ', $Config{sig_name})) {
      $signo{$name} = $i;
      $i++;
    }
  }
  
  my @signal_names = qw(
    HUP INT QUIT ILL TRAP ABRT BUS FPE KILL USR1 SEGV USR2 PIPE ALRM TERM STKFLT CHLD CONT STOP TSTP TTIN TTOU URG XCPU XFSZ VTALRM PROF WINCH IO PWR SYS RTMIN RTMAX 
  );
  
  my $i = 0;
  for my $signal_name (@signal_names) {
    my $signal_number = $signo{$signal_name};
    if (defined $signal_number) {
      warn "[Test Output]SIG$signal_name";
      my $signal_method_name = "SIG$signal_name";
      
      if ($^O eq 'linux') {
        is($signal_number, SPVM::Sys::Signal::Constant->$signal_method_name);
      }
      else {
        eval { SPVM::Sys::Signal::Constant->$signal_method_name };
        if ($@) {
          warn "[Test Output]$signal_method_name is not defined";
        }
        else {
          is($signal_number, SPVM::Sys::Signal::Constant->$signal_method_name);
        }
      }
    }
  }
}

ok(SPVM::TestCase::Sys::Signal->signal);

{
  my $tmp_dir = File::Temp->newdir;
  
  ok(SPVM::TestCase::Sys::Signal->signal_go("$tmp_dir"));
}

SPVM::Fn->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
