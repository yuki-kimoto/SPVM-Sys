package SPVM::Sys::Fcntl;

our $VERSION = '0.01';

1;

=head1 Name

SPVM::Sys::Fcntl - Sys::Fcntl is a SPVM module

=head1 Usage

  use Sys::Fcntl;
  
=head1 Description

C<Sys::Fcntl> is a L<SPVM> module.

=head1 Class Methods

=head2 DN_ACCESS

  native static method DN_ACCESS : int ();


=head2 DN_ATTRIB

  native static method DN_ATTRIB : int ();


=head2 DN_CREATE

  native static method DN_CREATE : int ();


=head2 DN_DELETE

  native static method DN_DELETE : int ();


=head2 DN_MODIFY

  native static method DN_MODIFY : int ();


=head2 DN_MULTISHOT

  native static method DN_MULTISHOT : int ();


=head2 DN_RENAME

  native static method DN_RENAME : int ();


=head2 FD_CLOEXEC

  native static method FD_CLOEXEC : int ();


=head2 F_ADD_SEALS

  native static method F_ADD_SEALS : int ();


=head2 F_DUPFD

  native static method F_DUPFD : int ();


=head2 F_DUPFD_CLOEXEC

  native static method F_DUPFD_CLOEXEC : int ();


=head2 F_GETFD

  native static method F_GETFD : int ();


=head2 F_GETFL

  native static method F_GETFL : int ();


=head2 F_GETLEASE

  native static method F_GETLEASE : int ();


=head2 F_GETLK

  native static method F_GETLK : int ();


=head2 F_GETLK64

  native static method F_GETLK64 : int ();


=head2 F_GETOWN

  native static method F_GETOWN : int ();


=head2 F_GETOWN_EX

  native static method F_GETOWN_EX : int ();


=head2 F_GETPIPE_SZ

  native static method F_GETPIPE_SZ : int ();


=head2 F_GETSIG

  native static method F_GETSIG : int ();


=head2 F_GET_FILE_RW_HINT

  native static method F_GET_FILE_RW_HINT : int ();


=head2 F_GET_RW_HINT

  native static method F_GET_RW_HINT : int ();


=head2 F_GET_SEALS

  native static method F_GET_SEALS : int ();


=head2 F_NOTIFY

  native static method F_NOTIFY : int ();


=head2 F_OFD_GETLK

  native static method F_OFD_GETLK : int ();


=head2 F_OFD_SETLK

  native static method F_OFD_SETLK : int ();


=head2 F_OFD_SETLKW

  native static method F_OFD_SETLKW : int ();


=head2 F_OWNER_PGRP

  native static method F_OWNER_PGRP : int ();


=head2 F_OWNER_PID

  native static method F_OWNER_PID : int ();


=head2 F_OWNER_TID

  native static method F_OWNER_TID : int ();


=head2 F_RDLCK

  native static method F_RDLCK : int ();


=head2 F_SEAL_FUTURE_WRITE

  native static method F_SEAL_FUTURE_WRITE : int ();


=head2 F_SEAL_GROW

  native static method F_SEAL_GROW : int ();


=head2 F_SEAL_SEAL

  native static method F_SEAL_SEAL : int ();


=head2 F_SEAL_SHRINK

  native static method F_SEAL_SHRINK : int ();


=head2 F_SEAL_WRITE

  native static method F_SEAL_WRITE : int ();


=head2 F_SETFD

  native static method F_SETFD : int ();


=head2 F_SETFL

  native static method F_SETFL : int ();


=head2 F_SETLEASE

  native static method F_SETLEASE : int ();


=head2 F_SETLK

  native static method F_SETLK : int ();


=head2 F_SETLKW

  native static method F_SETLKW : int ();


=head2 F_SETOWN

  native static method F_SETOWN : int ();


=head2 F_SETOWN_EX

  native static method F_SETOWN_EX : int ();


=head2 F_SETPIPE_SZ

  native static method F_SETPIPE_SZ : int ();


=head2 F_SETSIG

  native static method F_SETSIG : int ();


=head2 F_SET_FILE_RW_HINT

  native static method F_SET_FILE_RW_HINT : int ();


=head2 F_SET_RW_HINT

  native static method F_SET_RW_HINT : int ();


=head2 F_UNLCK

  native static method F_UNLCK : int ();


=head2 F_WRLCK

  native static method F_WRLCK : int ();


=head2 O_APPEND

  native static method O_APPEND : int ();


=head2 O_ASYNC

  native static method O_ASYNC : int ();


=head2 O_CLOEXEC

  native static method O_CLOEXEC : int ();


=head2 O_CREAT

  native static method O_CREAT : int ();


=head2 O_DIRECT

  native static method O_DIRECT : int ();


=head2 O_DIRECTORY

  native static method O_DIRECTORY : int ();


=head2 O_DSYNC

  native static method O_DSYNC : int ();


=head2 O_EXCL

  native static method O_EXCL : int ();


=head2 O_LARGEFILE

  native static method O_LARGEFILE : int ();


=head2 O_NOATIME

  native static method O_NOATIME : int ();


=head2 O_NOCTTY

  native static method O_NOCTTY : int ();


=head2 O_NOFOLLOW

  native static method O_NOFOLLOW : int ();


=head2 O_NONBLOCK

  native static method O_NONBLOCK : int ();


=head2 O_PATH

  native static method O_PATH : int ();


=head2 O_RDONLY

  native static method O_RDONLY : int ();


=head2 O_RDWR

  native static method O_RDWR : int ();


=head2 O_SYNC

  native static method O_SYNC : int ();


=head2 O_TMPFILE

  native static method O_TMPFILE : int ();


=head2 O_TRUNC

  native static method O_TRUNC : int ();


=head2 O_WRONLY

  native static method O_WRONLY : int ();

