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

=head2 symlink

C<static method symlink : int ($old_path : string, $new_path : string);>

Creates a path $new_path symbolically linked to the path $old_path.

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

