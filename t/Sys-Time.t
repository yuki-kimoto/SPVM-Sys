use Test::More;

use strict;
use warnings;
use FindBin;

use lib 't/lib';

use SPVM 'Sys::Time';
use SPVM 'Sys::OS';
use SPVM 'Sys';
use SPVM 'Int';

use SPVM 'TestCase::Sys::Time';

my $test_dir = "$FindBin::Bin";

my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Sys::Time::Tm
{
  my $time = SPVM::TestCase::Sys::Time->new_tm;
}

# time
{
  my $time = SPVM::TestCase::Sys::Time->time;
  my $perl_time = time;
  if ($time > $perl_time - 2 && $time < $perl_time + 2) {
    pass();
  }
  else {
    fail();
  }
}

# localtime
{
  my $time = time;
  my @perl_localtime = localtime($time);
  
  my $tm = SPVM::TestCase::Sys::Time->localtime_value($time);
  
  is($perl_localtime[0], $tm->tm_sec);
  is($perl_localtime[1], $tm->tm_min);
  is($perl_localtime[2], $tm->tm_hour);
  is($perl_localtime[3], $tm->tm_mday);
  is($perl_localtime[4], $tm->tm_mon);
  is($perl_localtime[5], $tm->tm_year);
  is($perl_localtime[6], $tm->tm_wday);
  is($perl_localtime[7], $tm->tm_yday);
  is($perl_localtime[8], $tm->tm_isdst);
  
  ok(SPVM::TestCase::Sys::Time->localtime);
}

# gmtime
{
  my $time = time;
  my @perl_gmtime = gmtime($time);
  
  my $tm = SPVM::TestCase::Sys::Time->gmtime_value($time);
  
  is($perl_gmtime[0], $tm->tm_sec);
  is($perl_gmtime[1], $tm->tm_min);
  is($perl_gmtime[2], $tm->tm_hour);
  is($perl_gmtime[3], $tm->tm_mday);
  is($perl_gmtime[4], $tm->tm_mon);
  is($perl_gmtime[5], $tm->tm_year);
  is($perl_gmtime[6], $tm->tm_wday);
  is($perl_gmtime[7], $tm->tm_yday);
  is($perl_gmtime[8], $tm->tm_isdst);
  
  ok(SPVM::TestCase::Sys::Time->gmtime);
}

ok(SPVM::TestCase::Sys::Time->clock);

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Time->getitimer(0, undef) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Time->getitimer);
}

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Time->setitimer(0, undef, undef) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Time->setitimer);
}

if ($^O eq 'MSWin32') {
  eval { SPVM::Sys::Time->times(undef) };
  like($@, qr/not supported/);
}
else {
  ok(SPVM::TestCase::Sys::Time->times);
}

ok(SPVM::TestCase::Sys::Time->utime("$test_dir"));

ok(SPVM::TestCase::Sys::Time->utimes("$test_dir"));

ok(SPVM::TestCase::Sys::Time->timespec);

ok(SPVM::TestCase::Sys::Time->timeval);

ok(SPVM::TestCase::Sys::Time->tzset);

{
  my $clock_nanosleep_supported;
  
  my $obj_major_version_ref = $api->new_int_array([0]);

  if (SPVM::Sys::OS->defined('_WIN32')) {
    $clock_nanosleep_supported = 0;
  }
  elsif (SPVM::Sys::OS->defined('__APPLE__')) {
    $clock_nanosleep_supported = 0;
  }
  elsif (SPVM::Sys::OS->defined('__FreeBSD__', $obj_major_version_ref)) {
    if ($obj_major_version_ref->[0] >= 13) {
      $clock_nanosleep_supported = 1;
    }
    else {
      $clock_nanosleep_supported = 0;
    }
  }
  else {
    $clock_nanosleep_supported = 1;
  }
  
  if (!$clock_nanosleep_supported) {
    eval { SPVM::Sys::Time->clock_nanosleep(0, 0, undef, undef) };
    like($@, qr/not supported/);
  }
  else {
    ok(SPVM::TestCase::Sys::Time->clock_nanosleep);
  }
}

ok(SPVM::TestCase::Sys::Time->nanosleep);

ok(SPVM::TestCase::Sys::Time->clock_getres);

ok(SPVM::TestCase::Sys::Time->clock_gettime);

ok(SPVM::TestCase::Sys::Time->gettimeofday);

# Sys
{
  # time
  {
    is(SPVM::Sys->time, time);
  }

  # localtime
  {
    my $time = time;
    
    #     0    1    2     3     4    5     6     7     8
    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime($time);
    
    my $tm = SPVM::Sys->localtime($time);
    
    is($tm->tm_sec, $sec);
    is($tm->tm_min, $min);
    is($tm->tm_hour, $hour);
    is($tm->tm_mday, $mday);
    is($tm->tm_mon, $mon);
    is($tm->tm_year, $year);
    is($tm->tm_wday, $wday);
    is($tm->tm_yday, $yday);
    is($tm->tm_isdst, $isdst);
  }

  # gmtime
  {
    my $time = time;
    
    #     0    1    2     3     4    5     6     7     8
    my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = gmtime($time);
    
    my $tm = SPVM::Sys->gmtime($time);
    
    is($tm->tm_sec, $sec);
    is($tm->tm_min, $min);
    is($tm->tm_hour, $hour);
    is($tm->tm_mday, $mday);
    is($tm->tm_mon, $mon);
    is($tm->tm_year, $year);
    is($tm->tm_wday, $wday);
    is($tm->tm_yday, $yday);
    is($tm->tm_isdst, $isdst);
  }
}

$api->destroy_runtime_permanent_vars;

my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
