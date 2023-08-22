package SPVM::Sys::Poll::Constant;

1;

=head1 Name

SPVM::Sys::Poll::Constant - Constant values for Poll.

=head1 Usage

  use Sys::Poll::Constant as Poll;
  
  my $o_trunc = Poll->O_TRUNC;

=head1 Description

C<Sys::Poll::Constant> is the class for the constant values for the poll function.

=head1 Class Methods

=head2 POLLERR

  static method POLLERR : int ();

Gets the value of C<POLLERR>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLHUP

  static method POLLHUP : int ();

Gets the value of C<POLLHUP>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLIN

  static method POLLIN : int ();

Gets the value of C<POLLIN>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLNVAL

  static method POLLNVAL : int ();

Gets the value of C<POLLNVAL>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLOUT

  static method POLLOUT : int ();

Gets the value of C<POLLOUT>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLPRI

  static method POLLPRI : int ();

Gets the value of C<POLLPRI>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDBAND

  static method POLLRDBAND : int ();

Gets the value of C<POLLRDBAND>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDNORM

  static method POLLRDNORM : int ();

Gets the value of C<POLLRDNORM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRBAND

  static method POLLWRBAND : int ();

Gets the value of C<POLLWRBAND>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRNORM

  static method POLLWRNORM : int ();

Gets the value of C<POLLWRNORM>. If the value is not defined in the system, an exception is thrown with the error code set to the basic type ID of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

