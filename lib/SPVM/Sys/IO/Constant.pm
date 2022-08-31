package SPVM::Sys::IO::Constant;

our $VERSION = '0.01';

1;

=head1 Name

SPVM::Sys::IO::Constant - IO constant values.

=head1 Usage

  use Sys::IO::Constant as IO;
  
  IOC->O_TRUNC;
  
=head1 Description

C<Sys::IO::Constant> is a L<SPVM> module.

=head1 Class Methods

=head2 AT_EMPTY_PATH

  static method AT_EMPTY_PATH : int ();

Get the error number of C<AT_EMPTY_PATH>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AT_FDCWD

  static method AT_FDCWD : int ();

Get the error number of C<AT_FDCWD>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AT_NO_AUTOMOUNT

  static method AT_NO_AUTOMOUNT : int ();

Get the error number of C<AT_NO_AUTOMOUNT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AT_SYMLINK_FOLLOW

  static method AT_SYMLINK_FOLLOW : int ();

Get the error number of C<AT_SYMLINK_FOLLOW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 AT_SYMLINK_NOFOLLOW

  static method AT_SYMLINK_NOFOLLOW : int ();

Get the error number of C<AT_SYMLINK_NOFOLLOW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_CHOWN

  static method CAP_CHOWN : int ();

Get the error number of C<CAP_CHOWN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_DAC_READ_SEARCH

  static method CAP_DAC_READ_SEARCH : int ();

Get the error number of C<CAP_DAC_READ_SEARCH>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_FOWNER

  static method CAP_FOWNER : int ();

Get the error number of C<CAP_FOWNER>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_FSETID

  static method CAP_FSETID : int ();

Get the error number of C<CAP_FSETID>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_LEASE

  static method CAP_LEASE : int ();

Get the error number of C<CAP_LEASE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 CAP_SYS_RESOURCE

  static method CAP_SYS_RESOURCE : int ();

Get the error number of C<CAP_SYS_RESOURCE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_ACCESS

  static method DN_ACCESS : int ();

Get the error number of C<DN_ACCESS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_ATTRIB

  static method DN_ATTRIB : int ();

Get the error number of C<DN_ATTRIB>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_CREATE

  static method DN_CREATE : int ();

Get the error number of C<DN_CREATE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_DELETE

  static method DN_DELETE : int ();

Get the error number of C<DN_DELETE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_MODIFY

  static method DN_MODIFY : int ();

Get the error number of C<DN_MODIFY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_MULTISHOT

  static method DN_MULTISHOT : int ();

Get the error number of C<DN_MULTISHOT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 DN_RENAME

  static method DN_RENAME : int ();

Get the error number of C<DN_RENAME>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 FD_CLOEXEC

  static method FD_CLOEXEC : int ();

Get the error number of C<FD_CLOEXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_ADD_SEALS

  static method F_ADD_SEALS : int ();

Get the error number of C<F_ADD_SEALS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_DUPFD

  static method F_DUPFD : int ();

Get the error number of C<F_DUPFD>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_DUPFD_CLOEXEC

  static method F_DUPFD_CLOEXEC : int ();

Get the error number of C<F_DUPFD_CLOEXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETFD

  static method F_GETFD : int ();

Get the error number of C<F_GETFD>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETFL

  static method F_GETFL : int ();

Get the error number of C<F_GETFL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETLEASE

  static method F_GETLEASE : int ();

Get the error number of C<F_GETLEASE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETLK

  static method F_GETLK : int ();

Get the error number of C<F_GETLK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETLK64

  static method F_GETLK64 : int ();

Get the error number of C<F_GETLK64>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETOWN

  static method F_GETOWN : int ();

Get the error number of C<F_GETOWN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETOWN_EX

  static method F_GETOWN_EX : int ();

Get the error number of C<F_GETOWN_EX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETPIPE_SZ

  static method F_GETPIPE_SZ : int ();

Get the error number of C<F_GETPIPE_SZ>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GETSIG

  static method F_GETSIG : int ();

Get the error number of C<F_GETSIG>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GET_FILE_RW_HINT

  static method F_GET_FILE_RW_HINT : int ();

Get the error number of C<F_GET_FILE_RW_HINT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GET_RW_HINT

  static method F_GET_RW_HINT : int ();

Get the error number of C<F_GET_RW_HINT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_GET_SEALS

  static method F_GET_SEALS : int ();

Get the error number of C<F_GET_SEALS>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_NOTIFY

  static method F_NOTIFY : int ();

Get the error number of C<F_NOTIFY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OFD_GETLK

  static method F_OFD_GETLK : int ();

Get the error number of C<F_OFD_GETLK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OFD_SETLK

  static method F_OFD_SETLK : int ();

Get the error number of C<F_OFD_SETLK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OFD_SETLKW

  static method F_OFD_SETLKW : int ();

Get the error number of C<F_OFD_SETLKW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OWNER_PGRP

  static method F_OWNER_PGRP : int ();

Get the error number of C<F_OWNER_PGRP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OWNER_PID

  static method F_OWNER_PID : int ();

Get the error number of C<F_OWNER_PID>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_OWNER_TID

  static method F_OWNER_TID : int ();

Get the error number of C<F_OWNER_TID>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_RDLCK

  static method F_RDLCK : int ();

Get the error number of C<F_RDLCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SEAL_FUTURE_WRITE

  static method F_SEAL_FUTURE_WRITE : int ();

Get the error number of C<F_SEAL_FUTURE_WRITE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SEAL_GROW

  static method F_SEAL_GROW : int ();

Get the error number of C<F_SEAL_GROW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SEAL_SEAL

  static method F_SEAL_SEAL : int ();

Get the error number of C<F_SEAL_SEAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SEAL_SHRINK

  static method F_SEAL_SHRINK : int ();

Get the error number of C<F_SEAL_SHRINK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SEAL_WRITE

  static method F_SEAL_WRITE : int ();

Get the error number of C<F_SEAL_WRITE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETFD

  static method F_SETFD : int ();

Get the error number of C<F_SETFD>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETFL

  static method F_SETFL : int ();

Get the error number of C<F_SETFL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETLEASE

  static method F_SETLEASE : int ();

Get the error number of C<F_SETLEASE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETLK

  static method F_SETLK : int ();

Get the error number of C<F_SETLK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETLK64

  static method F_SETLK64 : int ();

Get the error number of C<F_SETLK64>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETLKW

  static method F_SETLKW : int ();

Get the error number of C<F_SETLKW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETLKW64

  static method F_SETLKW64 : int ();

Get the error number of C<F_SETLKW64>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETOWN

  static method F_SETOWN : int ();

Get the error number of C<F_SETOWN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETOWN_EX

  static method F_SETOWN_EX : int ();

Get the error number of C<F_SETOWN_EX>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETPIPE_SZ

  static method F_SETPIPE_SZ : int ();

Get the error number of C<F_SETPIPE_SZ>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SETSIG

  static method F_SETSIG : int ();

Get the error number of C<F_SETSIG>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SET_FILE_RW_HINT

  static method F_SET_FILE_RW_HINT : int ();

Get the error number of C<F_SET_FILE_RW_HINT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_SET_RW_HINT

  static method F_SET_RW_HINT : int ();

Get the error number of C<F_SET_RW_HINT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_UNLCK

  static method F_UNLCK : int ();

Get the error number of C<F_UNLCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 F_WRLCK

  static method F_WRLCK : int ();

Get the error number of C<F_WRLCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_APPEND

  static method O_APPEND : int ();

Get the error number of C<O_APPEND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_ASYNC

  static method O_ASYNC : int ();

Get the error number of C<O_ASYNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_CLOEXEC

  static method O_CLOEXEC : int ();

Get the error number of C<O_CLOEXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_CREAT

  static method O_CREAT : int ();

Get the error number of C<O_CREAT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_DIRECT

  static method O_DIRECT : int ();

Get the error number of C<O_DIRECT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_DIRECTORY

  static method O_DIRECTORY : int ();

Get the error number of C<O_DIRECTORY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_DSYNC

  static method O_DSYNC : int ();

Get the error number of C<O_DSYNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_EXCL

  static method O_EXCL : int ();

Get the error number of C<O_EXCL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_EXEC

  static method O_EXEC : int ();

Get the error number of C<O_EXEC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_LARGEFILE

  static method O_LARGEFILE : int ();

Get the error number of C<O_LARGEFILE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_NDELAY

  static method O_NDELAY : int ();

Get the error number of C<O_NDELAY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_NOATIME

  static method O_NOATIME : int ();

Get the error number of C<O_NOATIME>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_NOCTTY

  static method O_NOCTTY : int ();

Get the error number of C<O_NOCTTY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_NOFOLLOW

  static method O_NOFOLLOW : int ();

Get the error number of C<O_NOFOLLOW>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_NONBLOCK

  static method O_NONBLOCK : int ();

Get the error number of C<O_NONBLOCK>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_PATH

  static method O_PATH : int ();

Get the error number of C<O_PATH>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_RDONLY

  static method O_RDONLY : int ();

Get the error number of C<O_RDONLY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_RDWR

  static method O_RDWR : int ();

Get the error number of C<O_RDWR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_RSYNC

  static method O_RSYNC : int ();

Get the error number of C<O_RSYNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_SYNC

  static method O_SYNC : int ();

Get the error number of C<O_SYNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_TMPFILE

  static method O_TMPFILE : int ();

Get the error number of C<O_TMPFILE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_TRUNC

  static method O_TRUNC : int ();

Get the error number of C<O_TRUNC>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 O_WRONLY

  static method O_WRONLY : int ();

Get the error number of C<O_WRONLY>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SEEK_CUR

  static method SEEK_CUR : int ();

Get the error number of C<SEEK_CUR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SEEK_DATA

  static method SEEK_DATA : int ();

Get the error number of C<SEEK_DATA>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SEEK_END

  static method SEEK_END : int ();

Get the error number of C<SEEK_END>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SEEK_HOLE

  static method SEEK_HOLE : int ();

Get the error number of C<SEEK_HOLE>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 SEEK_SET

  static method SEEK_SET : int ();

Get the error number of C<SEEK_SET>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Copyright & License

Copyright 2022-2022 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

