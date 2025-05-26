package SPVM::Sys::IO::Windows;



1;

=head1 Name

SPVM::Sys::IO::Windows - IO System Call on Windows

=head1 Description

Sys::IO::Windows class in L<SPVM> has methods to manipulate IO system calls in Windows.

=head1 Usage

  use Sys::IO::Windows;

=head1 Class Methods

=head2 unlink

C<static method unlink : int ($pathname : string);>

Delete a file.

Note:

This method is implemented so that the beheivior is the same as L<Sys::IO#readlink|SPVM::Sys::IO/"readlink"> method as possible.

If the file given by the path name $pathname is read-only, the flag is disabled before the file deletion. If the file deletion failed, the flag is restored.

This method can delete both symlinks and directory junctions.

Error numbers in Windows are replaced with the ones in POSIX.

Exceptions:

$pathname must be defined. Otherwise an exception is thrown.

If the unlink function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 rename

C<static method rename : int ($oldpath : string, $newpath : string);>

Raname the file name from the old name $oldpath to the new name $newpath.

Note:

This method is implemented so that the beheivior is the same as L<Sys::IO#readlink|SPVM::Sys::IO/"readlink"> method as possible.

Error numbers in Windows are replaced with the ones in POSIX.

Exceptions:

$oldpath must be defined. Otherwise an exception is thrown.

$newpath must be defined. Otherwise an exception is thrown.

If the rename function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 symlink

C<static method symlink : int ($oldpath : string, $newpath : string);>

Creates a path $newpath symbolically linked to the path $oldpath.

Note:

This method is implemented so that the beheivior is the same as L<Sys::IO#symlink|SPVM::Sys::IO/"symlink"> method as possible.

Error numbers in Windows are replaced with the ones in POSIX.

=head2 win_readlink

C<static method win_readlink : string ($path : string);>

If the file $path is a symbolic link or directory junction, returns its link text.

Exceptions:

An exception is thrown if $path does not exist, if the process do not have the appropriate permission to open $path, or if $path is not a symbolic link or a directory junction.

=head2 realpath

C<static method realpath : mutable string ($path : string, $resolved_path : mutable string);>

Resolves symbolic link in the path $path and converts it to a canonical absolute path(but not long path format), and returns it.

$resolved_path must be undef.

=head2 is_symlink

C<static method is_symlink : int ($path : string);>

If the file $path is a symblic link or a directory junction, returns 1; otherwise returns 0.

Excepsitons:

The path $path must be defined. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

