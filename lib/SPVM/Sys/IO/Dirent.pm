package SPVM::Sys::IO::Dirent;

1;

=head1 Name

SPVM::Sys::IO::Dirent - struct dirent in C language

=head1 Usage
  
  use Sys::IO::Dirent;

=head1 Description

C<Sys::IO::Dirent> is the class for C<struct dirent> in C<C language>.

=head1 Pointer Class

This class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Class Methods

=head2 d_ino

C<method d_ino : int ();>

Gets C<d_ino>.

=head2 d_reclen

C<method d_reclen : int ();>

Gets C<d_reclen>.

=head2 d_name

C<method d_name : string ();>

Gets C<d_name>. This value is copied.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

