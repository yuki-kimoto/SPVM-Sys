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

rmdir() deletes a directory, which must be empty.

See the detail of the L<rmdir|https://linux.die.net/man/2/rmdir> function in the case of Linux.

=head2 unlink

  static method unlink : int ($path : string);

unlink() deletes a name from the file system. If that name was the last link to a file and no processes have the file open the file is deleted and the space it was using is made available for reuse.

See the detail of the L<unlink|https://linux.die.net/man/2/unlink> function in the case of Linux.

=head2 close

  static method close : int ($fd : int);

close() closes a file descriptor, so that it no longer refers to any file and may be reused. Any record locks (see fcntl(2)) held on the file it was associated with, and owned by the process, are removed (regardless of the file descriptor that was used to obtain the lock).

See the detail of the L<close|https://linux.die.net/man/2/close> function in the case of Linux.

=head2 fclose

  static method fclose : int ($stream : Sys::IO::FileHandle);

The fclose() function flushes the stream pointed to by fp (writing any buffered output data using fflush(3)) and closes the underlying file descriptor.

See the detail of the L<fclose|https://linux.die.net/man/3/fclose> function in the case of Linux.

=head2 clearerr

  static method clearerr : void ($stream : Sys::IO::FileHandle);

The function clearerr() clears the end-of-file and error indicators for the stream pointed to by stream.

See the detail of the L<clearerr|https://linux.die.net/man/3/clearerr> function in the case of Linux.

=head2 feof

  static method feof : int ($stream : Sys::IO::FileHandle);

The function feof() tests the end-of-file indicator for the stream pointed to by stream, returning nonzero if it is set. The end-of-file indicator can only be cleared by the function clearerr().

See the detail of the L<feof|https://linux.die.net/man/3/feof> function in the case of Linux.

=head2 ferror

  static method ferror : int ($stream : Sys::IO::FileHandle);

The function ferror() tests the error indicator for the stream pointed to by stream, returning nonzero if it is set. The error indicator can only be reset by the clearerr() function.

See the detail of the L<ferror|https://linux.die.net/man/3/ferror> function in the case of Linux.

=head2 fileno

  static method fileno : int ($stream : Sys::IO::FileHandle);

The function fileno() examines the argument stream and returns its integer descriptor.

See the detail of the L<fileno|https://linux.die.net/man/3/fileno> function in the case of Linux.

=head2 open

  static method open : int ($path : string, $flags : int, $mode = 0 : int);

Given a pathname for a file, open() returns a file descriptor, a small, nonnegative integer for use in subsequent system calls (read(2), write(2), lseek(2), fcntl(2), etc.). The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process.

See the detail of the L<open|https://linux.die.net/man/2/open> function in the case of Linux.

=head2 fopen

  static method fopen : Sys::IO::FileHandle ($path : string, $mode : string);

The fopen() function opens the file whose name is the string pointed to by path and associates a stream with it.

See the detail of the L<fopen|https://linux.die.net/man/3/fopen> function in the case of Linux.

=head2 fdopen

  static method fdopen : Sys::IO::FileHandle ($fd : int, $mode : string);

The fdopen() function associates a stream with the existing file descriptor, fd. The mode of the stream (one of the values "r", "r+", "w", "w+", "a", "a+") must be compatible with the mode of the file descriptor. The file position indicator of the new stream is set to that belonging to fd, and the error and end-of-file indicators are cleared. Modes "w" or "w+" do not cause truncation of the file. The file descriptor is not dup'ed, and will be closed when the stream created by fdopen() is closed. The result of applying fdopen() to a shared memory object is undefined.

See the detail of the L<fdopen|https://linux.die.net/man/3/fdopen> function in the case of Linux.

=head2 freopen

  static method freopen : Sys::IO::FileHandle ($path : string, $mode : string, $stream : Sys::IO::FileHandle);

The freopen() function opens the file whose name is the string pointed to by path and associates the stream pointed to by stream with it. The original stream (if it exists) is closed. The mode argument is used just as in the fopen() function. The primary use of the freopen() function is to change the file associated with a standard text stream (stderr, stdin, or stdout).

See the detail of the L<freopen|https://linux.die.net/man/3/freopen> function in the case of Linux.

=head2 fread

  static method fread : int ($buffer : mutable string, $size : int, $data_length : int, $stream : Sys::IO::FileHandle);

The function fread() reads nmemb elements of data, each size bytes long, from the stream pointed to by stream, storing them at the location given by ptr.

See the detail of the L<fread|https://linux.die.net/man/3/fread> function in the case of Linux.

=head2 fwrite

  static method fwrite : int ($buffer : mutable string, $size : int, $data_length : int, $stream : Sys::IO::FileHandle);

The function fwrite() writes nmemb elements of data, each size bytes long, to the stream pointed to by stream, obtaining them from the location given by ptr.

See the detail of the L<fread|https://linux.die.net/man/3/fwrite> function in the case of Linux.

=head2 read

  static method read : int ($fd : int, $buffer : mutable string, $count : int);

read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

See the detail of the L<read|https://linux.die.net/man/2/read> function in the case of Linux.

=head2 write

  static method write : int ($fd : int, $buffer : mutable string, $count : int);

write() writes up to count bytes from the buffer pointed buf to the file referred to by the file descriptor fd.

See the detail of the L<write|https://linux.die.net/man/2/write> function in the case of Linux.

=head2 getc

  static method getc : int ($stream : Sys::IO::FileHandle);

getc() is equivalent to fgetc() except that it may be implemented as a macro which evaluates stream more than once.

See the detail of the L<getc|https://linux.die.net/man/3/getc> function in the case of Linux.

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

=pod

fflush

=cut
