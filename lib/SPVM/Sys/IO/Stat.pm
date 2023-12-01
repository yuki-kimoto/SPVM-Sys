package SPVM::Sys::IO::Stat;

1;

=head1 Name

SPVM::Sys::IO::Stat - struct stat in the C language

=head1 Description

The Sys::IO::Stat class represents C<struct stat> in the C language, and has utility methods for the structure.

=head1 Usage

  use Sys::IO::Stat;
  
  my $file = "foo.txt";
  my $stat = Sys::IO::Stat->new;
  
  Sys::IO::Stat->stat($file, $stat);
  
  Sys::IO::Stat->lstat($file, $stat);
  
  my $st_mode = $stat->st_mode;
  my $st_size = $stat->st_size;

=head1 Details

This class is a pointer class. The pointer of the instance is set to a C<struct stat> object.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::IO::Stat|SPVM::Sys::IO::Stat> ();>

Creates a new L<Sys::IO::Stat|SPVM::Sys::IO::Stat> object.

=head2 stat

C<static method stat : int ($path : string, $stat : L<Sys::IO::Stat|SPVM::Sys::IO::Stat>);>

Calls the L<stat|https://linux.die.net/man/2/stat> function and returns its return value.

Exceptions:

$path must be defined. Otherwise an exception is thrown.

$stat must be defined. Otherwise an exception is thrown.

If the stat function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 lstat

C<static method lstat : int ($path : string, $stat : L<Sys::IO::Stat|SPVM::Sys::IO::Stat>);>

Calls the L<lstat|https://linux.die.net/man/2/lstat> function and returns its return value.

Exceptions:

$path must be defined. Otherwise an exception is thrown.

$stat must be defined. Otherwise an exception is thrown.

If the lstat function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 fstat

C<static method fstat : int ($fd : int, $stat : L<Sys::IO::Stat|SPVM::Sys::IO::Stat>);>

Calls the L<fstat|https://linux.die.net/man/2/fstat> function and returns its return value.

Exceptions:

The C<$stat> is a L<Sys::IO::Stat|SPVM::Sys::IO::Stat> object.

$stat must be defined. Otherwise an exception is thrown.

If the stat function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head2 st_dev

C<method st_dev : int ();>

Gets C<st_dev>.

=head2 st_ino

C<method st_ino : int ();>

Gets C<st_ino>.

=head2 st_mode

C<method st_mode : int ();>

Gets C<st_mode>.

=head2 st_nlink

C<method st_nlink : int ();>

Gets C<st_nlink>.

=head2 st_uid

C<method st_uid : int ();>

Gets C<st_uid>.

=head2 st_gid

C<method st_gid : int ();>

Gets C<st_gid>.

=head2 st_rdev

C<method st_rdev : int ();>

Gets C<st_rdev>.

=head2 st_size

C<method st_size : long ();>

Gets C<st_size>.

=head2 st_blksize

C<method st_blksize : long ();>

Gets C<st_blksize>.

=head2 st_blocks

C<method st_blocks : long ();>

Gets C<st_blocks>.

=head2 st_mtime

C<method st_mtime : long ();>

Gets C<st_mtime>.

=head2 st_atime

C<method st_atime : long ();>

Gets C<st_atime>.

=head2 st_ctime

C<method st_ctime : long ();>

Gets C<st_ctime>.

=head2 st_mtim_tv_nsec

C<method st_mtim_tv_nsec : long ();>

Gets C<st_mtim.tv_nsec>.

=head2 st_atim_tv_nsec

C<method st_atim_tv_nsec : long ();>

Gets C<st_atim.tv_nsec>.

=head2 st_ctim_tv_nsec

C<method st_ctim_tv_nsec : long ();>

Gets C<st_ctim.tv_nsec>.

=head2 A

C<method A : double ();>

=head2 C

C<method C : double ();>

=head2 M

C<method M : double ();>

=head2 O

C<method O : int ();>

=head2 S

C<method S : int ();>

=head2 b

C<method b : int ();>

=head2 c

C<method c : int ();>

=head2 d

C<method d : int ();>

=head2 e

C<method e : int ();>

=head2 f

C<method f : int ();>

=head2 g

C<method g : int ();>

=head2 k

C<method k : int ();>

=head2 l

C<method l : int ();>

=head2 o

C<method o : int ();>

=head2 p

C<method p : int ();>

=head2 s

C<method s : long ();>

=head2 u

C<method u : int ();>

=head2 z

C<method z : int ();>

=head2 cando

C<method cando : int ($mode : int, $effective : int);>

=head2 r

C<method r : int ();>

=head2 w

C<method w : int ();>

=head2 x

C<method x : int ();>

=head2 R

C<method R : int ();>

=head2 W

C<method W : int ();>

=head2 X

C<method X : int ();>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

