package SPVM::Sys::IO::Stat;

1;

=head1 Name

SPVM::Sys::IO::Stat - struct stat in the C language

=head1 Description

Sys::IO::Stat class in L<SPVM> represents C<struct stat> in the C language, and has utility methods for the structure.

=head1 Usage

  use Sys::IO::Stat;
  
  my $file = "foo.txt";
  my $stat = Sys::IO::Stat->new;
  
  Sys::IO::Stat->stat($file, $stat);
  
  Sys::IO::Stat->lstat($file, $stat);
  
  my $st_mode = $stat->mode;
  
  my $st_size = $stat->size;

=head1 Details

This class is a pointer class. The pointer the instance has is set to a C<struct stat> object.

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

Returns C<st_dev>.

=head2 st_ino

C<method st_ino : int ();>

Returns C<st_ino>.

=head2 st_mode

C<method st_mode : int ();>

Returns C<st_mode>.

=head2 st_nlink

C<method st_nlink : int ();>

Returns C<st_nlink>.

=head2 st_uid

C<method st_uid : int ();>

Returns C<st_uid>.

=head2 st_gid

C<method st_gid : int ();>

Returns C<st_gid>.

=head2 st_rdev

C<method st_rdev : int ();>

Returns C<st_rdev>.

=head2 st_size

C<method st_size : long ();>

Returns C<st_size>.

=head2 st_blksize

C<method st_blksize : long ();>

Returns C<st_blksize>.

=head2 st_blocks

C<method st_blocks : long ();>

Returns C<st_blocks>.

=head2 st_mtime

C<method st_mtime : long ();>

Returns C<st_mtime>.

=head2 st_atime

C<method st_atime : long ();>

Returns C<st_atime>.

=head2 st_ctime

C<method st_ctime : long ();>

Returns C<st_ctime>.

=head2 st_mtim_tv_nsec

C<method st_mtim_tv_nsec : long ();>

Returns C<st_mtim.tv_nsec>.

=head2 st_atim_tv_nsec

C<method st_atim_tv_nsec : long ();>

Returns C<st_atim.tv_nsec>.

=head2 st_ctim_tv_nsec

C<method st_ctim_tv_nsec : long ();>

Returns C<st_ctim.tv_nsec>.

=head2 A

C<method A : double ();>

The implementation of L<Sys#A|SPVM::Sys/"A"> method.

=head2 C

C<method C : double ();>

The implementation of L<Sys#C|SPVM::Sys/"C"> method.

=head2 M

C<method M : double ();>

The implementation of L<Sys#M|SPVM::Sys/"M"> method.

=head2 O

C<method O : int ();>

The implementation of L<Sys#O|SPVM::Sys/"O"> method.

=head2 S

C<method S : int ();>

The implementation of L<Sys#S|SPVM::Sys/"S"> method.

=head2 b

C<method b : int ();>

The implementation of L<Sys#b|SPVM::Sys/"b"> method.

=head2 c

C<method c : int ();>

The implementation of L<Sys#c|SPVM::Sys/"c"> method.

=head2 d

C<method d : int ();>

The implementation of L<Sys#d|SPVM::Sys/"d"> method.

=head2 e

C<method e : int ();>

The implementation of L<Sys#e|SPVM::Sys/"e"> method.

=head2 f

C<method f : int ();>

The implementation of L<Sys#f|SPVM::Sys/"f"> method.

=head2 g

C<method g : int ();>

The implementation of L<Sys#g|SPVM::Sys/"g"> method.

=head2 k

C<method k : int ();>

The implementation of L<Sys#k|SPVM::Sys/"k"> method.

=head2 l

C<method l : int ();>

The implementation of L<Sys#l|SPVM::Sys/"l"> method.

=head2 o

C<method o : int ();>

The implementation of L<Sys#o|SPVM::Sys/"o"> method.

=head2 p

C<method p : int ();>

The implementation of L<Sys#p|SPVM::Sys/"p"> method.

=head2 s

C<method s : long ();>

The implementation of L<Sys#s|SPVM::Sys/"s"> method.

=head2 u

C<method u : int ();>

The implementation of L<Sys#u|SPVM::Sys/"u"> method.

=head2 z

C<method z : int ();>

The implementation of L<Sys#z|SPVM::Sys/"z"> method.

=head2 r

C<method r : int ();>

The implementation of L<Sys#r|SPVM::Sys/"r"> method.

=head2 w

C<method w : int ();>

The implementation of the L<Sys#w|SPVM::Sys/"w"> method.

=head2 x

C<method x : int ();>

The implementation of L<Sys#x|SPVM::Sys/"x"> method.

=head2 R

C<method R : int ();>

The implementation of L<Sys#R|SPVM::Sys/"R"> method.

=head2 W

C<method W : int ();>

The implementation of L<Sys#W|SPVM::Sys/"W"> method.

=head2 X

C<method X : int ();>

The implementation of L<Sys#X|SPVM::Sys/"X"> method.

=head1 dev

C<method dev : long ();>

Same as L</"st_dev">.

=head1 ino

C<method ino : long ();>

Same as L</"st_ino">.

=head1 mode

C<method mode : int ();>

Same as L</"st_mode">.

=head1 nlink

C<method nlink : long ();>

Same as L</"st_nlink">.

=head1 uid

C<method uid : int ();>

Same as L</"st_uid">.

=head1 gid

C<method gid : int ();>

Same as L</"st_gid">.

=head1 rdev

C<method rdev : long ();>

Same as L</"st_rdev">.

=head1 size

C<method size : long ();>

Same as L</"st_size">.

=head1 blksize

C<method blksize : long ();>

Same as L</"st_blksize">.

=head1 blocks

C<method blocks : long ();>

Same as L</"st_blocks">.

=head1 mtime

C<method mtime : long ();>

Same as L</"st_mtime">.

=head1 atime

C<method atime : long ();>

Same as L</"st_atime">.

=head1 ctime

C<method ctime : long ();>

Same as L</"st_ctime">.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

