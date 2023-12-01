package SPVM::Sys::IO::FileStream;

1;

=head1 Name

SPVM::Sys::IO::FileStream - C<FILE> structure in the C language.

=head1 Description

The Sys::IO::FileStream of L<SPVM> represetns the L<FILE|https://linux.die.net/man/3/fopen> structure in the C language.

=head1 Usage
  
  use Sys::IO::FileStream;

=head1 Details

This class is a pointer class. The pointer of the instance is set to a C<FILE> object.

=head1 Fields

=head2 closed

C<has closed : ro byte;>

The file stream is closed.

=head2 no_destroy

C<has no_destroy : ro byte;>

Do not call the L</"DESTROY"> method.

=head1 Instance Methods

C<method DESTROY : void ();>

The destructor.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

