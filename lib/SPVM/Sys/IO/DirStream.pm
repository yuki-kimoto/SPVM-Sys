package SPVM::Sys::IO::DirStream;

1;

=head1 Name

SPVM::Sys::IO::DirStream - the class for the C<DIR> type in the C language.

=head1 Usage
  
  use Sys::IO::DirStream;
  use Sys::IO;
  
  my $dir = "foo";
  
  # Sys::IO::DirStream
  my $dir_stream = Sys::IO->opendir($dir);

=head1 Description

C<Sys::IO::DirStream> is the class for the C<DIR> type in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Fields

=head2 closed

C<has closed : ro byte;>

The directory stream is closed.

=head1 Instance Methods

C<method DESTROY : void ();>

The destructor.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

