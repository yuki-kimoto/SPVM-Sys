package SPVM::Sys::Ioctl::Constant;

1;

=head1 Name

SPVM::Sys::Ioctl::Constant - Constant values for ioctl.

=head1 Usage

  use Sys::Ioctl::Constant as Ioctl;
  
=head1 Description

C<Sys::Ioctl::Constant> is the class for the constant values for the C<ioctl> function in the C language.

=head1 Class Methods

=head2 FIONBIO

C<static method FIONBIO : int ();>

Gets the value of C<FIONBIO>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

