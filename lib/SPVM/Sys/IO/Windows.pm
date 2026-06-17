package SPVM::Sys::IO::Windows;



1;

=head1 Name

SPVM::Sys::IO::Windows - IO System Call on Windows

=head1 Description

Sys::IO::Windows class in L<SPVM> has methods to manipulate IO system calls in Windows.

=head1 Details

=head2 Symbolic Link

In this document, 'symbolic link' refers to both symbolic links and directory junctions.

=head1 Usage

  use Sys::IO::Windows;

=head1 Class Methods

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

=head1 See Also

=over 2

=item * L<Sys|SPVM::Sys>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

