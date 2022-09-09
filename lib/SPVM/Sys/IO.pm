package SPVM::Sys::IO;

1;

=head1 Name

SPVM::Sys::IO - File IO

=head1 Usage
  
  use Sys::IO;

=head1 Description

C<Sys::IO> is the class for the file IO.

=head1 Class Methods

=head2 rmdir

  static method rmdir : int ($path : string);

=head2 unlink

  static method unlink : int ($file : string);

=head2 close

  static method close : int ($fd : int);

=head2 fclose

  static method fclose : int ($stream : Sys::IO::FileHandle);

=head2 clearerr

  static method clearerr : void ($stream : Sys::IO::FileHandle);

=head2 feof

  static method feof : int ($stream : Sys::IO::FileHandle);

=head2 ferror

  static method ferror : int ($stream : Sys::IO::FileHandle);

=head2 fileno

  static method fileno : int ($stream : Sys::IO::FileHandle);

=head2 open

  static method open : int ($path : string, $flags : int, $mode = 0 : int);

=head2 fopen

  static method fopen : Sys::IO::FileHandle ($path : string, $mode : string);

=head2 fdopen

  static method fdopen : Sys::IO::FileHandle ($fd : int, $mode : string);

=head2 freopen

  static method freopen : Sys::IO::FileHandle ($path : string, $mode : string, $stream : Sys::IO::FileHandle);

=head2 fread

  static method fread : int ($buffer : mutable string, $size : int, $data_length : int, $stream : Sys::IO::FileHandle);

=head2 fwrite

  static method fwrite : int ($buffer : mutable string, $size : int, $data_length : int, $stream : Sys::IO::FileHandle);

=head2 read

  static method read : int ($fd : int, $buffer : mutable string, $count : int);

=head2 write

  static method write : int ($fd : int, $buffer : mutable string, $count : int);

=head2 getc

  static method getc : int ($stream : Sys::IO::FileHandle);

=head2 EOF

  static method EOF : int ();

=head2 chdir

  static method chdir : int ($path : string);

=head2 chmod

  static method chmod : int ($path : string, $mode :int);

=head2 chown

  static method chown : int ($path : string, $owner : int, $group : int);

=head2 mkdir

  static method mkdir : int ($path : string, $mode : int);

=head2 fseek

  static method fseek : int ($stream : Sys::IO::FileHandle, $offset : long, $whence : int);

=head2 ftell

  static method ftell : long ($stream : Sys::IO::FileHandle);

=head2 opendir

  static method opendir : Sys::IO::DirHandle ($dir : string);

=head2 closedir

  static method closedir : int ($dh : Sys::IO::DirHandle);

=head2readdir

  static method readdir : Sys::IO::Dirent ($dh : Sys::IO::DirHandle); # Non-thead safe

=head2rewinddir

  static method rewinddir : void ($dh : Sys::IO::DirHandle);

=head2 telldir

  static method telldir : long ($dh : Sys::IO::DirHandle);

=head2 seekdir

  static method seekdir : void ($dh : Sys::IO::DirHandle, $offset : long);

=head2 truncate

  static method truncate : long ($path : string, $offset : long);

=head2 lseek

  static method lseek : long ($fd : int, $offset : long, $whence : int);

=head2 umask

  static method umask : int ($mode : int);

=head2 rename

  static method rename : int ($old_path : string, $new_path : string);

=head2 readlink

  static method readlink : int ($path : string, $buffer : mutable string);

=head2 symlink

  static method symlink : int ($target : string, $link_path : string);

=head2 ioctl

  static method ioctl : int ($fd : int, $request : int, $arg_ref : string[]);

=head2 ioctl_int

  static method ioctl_int : int ($fd : int, $request : int, $arg_ref : int*);

=head2 utime

  static method utime : int ($file : string, $buffer : Sys::IO::Utimbuf);

=head2access

  static method access : int ($path : string, $mode : int);

=head2 stat

  static method stat : int ($path : string, $stat : Sys::IO::Stat);

=head2 lstat

  static method lstat : int ($path : string, $stat : Sys::IO::Stat);
  
=head2 fcntl

  static method fcntl : int ($fd : int, $command : int, $arg = undef : object of Int|Sys::IO::Flock|object);

=head2 poll

  static method poll : int ($fds : Sys::IO::PollfdArray, $nfds : int, $timeout : int);

=head2 flock

  static method flock : int ($fd : int, $operation : int);

