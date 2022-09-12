package SPVM::Sys::IO::DirStream;

1;

=head1 Name

SPVM::Sys::IO::DirStream - the class for the C<DIR> type in C<C language>.

=head1 Usage
  
  use Sys::IO::DirStream;
  use Sys::IO;
  
  my $dir = "foo";
  
  # Sys::IO::DirStream
  my $dir_stream = Sys::IO->opendir($dir);

=head1 Description

C<Sys::IO::DirStream> is the class for the C<DIR> type in C<C language>.

=head1 Instance Methods

  method DESTROY : void ();

The destructor.
