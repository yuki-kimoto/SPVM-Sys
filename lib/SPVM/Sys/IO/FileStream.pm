package SPVM::Sys::IO::FileStream;

1;

=head1 Name

SPVM::Sys::IO::FileStream - the class for the C<FILE> type in the C language.

=head1 Usage
  
  use Sys::IO::FileStream;
  use Sys::IO;
  
  my $file = "foo.txt";
  
  # Sys::IO::FileStream
  my $file_stream = Sys::IO->fopen($file, "rb");

=head1 Description

C<Sys::IO::FileStream> is the class for the C<FILE> type in the C language.

This is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

=head1 Fields

=head2 closed

C<has closed : ro byte;>

The file stream is closed.

=head2 no_destroy

C<has no_destroy : ro byte;>

If this field is set to a true value, the file stream must not be closed.

=head1 Instance Methods

C<method DESTROY : void ();>

The destructor.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

