package SPVM::Sys::IO::Windows;



1;

=head1 Name

SPVM::Sys::IO::Windows - IO System Call on Windows

=head1 Description

C<SPVM::Sys::IO::Windows> is the C<Sys::IO::Windows> class in L<SPVM> language.

=head1 Usage

  use Sys::IO::Windows;

=head1 Class Methods

=head2 unlink

C<native static method unlink : int ($pathname : string);>

Delete a file.

Note:

If the file given by the path name $pathname does not exist, returns -1 and C<errno> is set to C<ENOENT>.

If the file given by the path name $pathname is read-only, the flag is disabled before the file deletion. If the file deletion failed, the flag is restored.

This method can delete both symlinks and directory junctions.

Exceptions:

$pathname must be defined. Otherwise an exception is thrown.

If the unlink function failed, an exception is thrown with C<eval_error_id> set to the basic type ID of the L<Error::System|SPVM::Error::System> class.

=head2 rename

C<static method rename : int ($oldpath : string, $newpath : string);>

The same as Perl L<rename|https://perldoc.perl.org/functions/rename> on Windows.

=head2 readlink

C<native static method readlink : int ($path : string, $buf : mutable string, $bufsiz : int);>

The same as Perl L<readlink|https://perldoc.perl.org/functions/readlink> on Windows.

=head2 get_readlink_buffer_size

C<native static method get_readlink_buffer_size : int ($path : string);>

Gets the L</"readlink"> needed buffer size.

=head2 is_symlink

C<native static method is_symlink : int ($path : string);>

If the file $path is symlinks or directory junctions, returns 1, othwerwise returns 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

