package SPVM::Sys::Poll::Constant;

1;

=head1 Name

SPVM::Sys::Poll::Constant - Poll Constant Values

=head1 Usage

  use Sys::Poll::Constant;
  
=head1 Description

C<Sys::Poll::Constant> is a L<SPVM> module.

=head1 Class Methods

=head2 POLLERR

  static method POLLERR : int ();

Get the error number of C<POLLERR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLHUP

  static method POLLHUP : int ();

Get the error number of C<POLLHUP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLIN

  static method POLLIN : int ();

Get the error number of C<POLLIN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLNORM

  static method POLLNORM : int ();

Get the error number of C<POLLNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLNVAL

  static method POLLNVAL : int ();

Get the error number of C<POLLNVAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLOUT

  static method POLLOUT : int ();

Get the error number of C<POLLOUT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLPRI

  static method POLLPRI : int ();

Get the error number of C<POLLPRI>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDBAND

  static method POLLRDBAND : int ();

Get the error number of C<POLLRDBAND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDNORM

  static method POLLRDNORM : int ();

Get the error number of C<POLLRDNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRBAND

  static method POLLWRBAND : int ();

Get the error number of C<POLLWRBAND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRNORM

  static method POLLWRNORM : int ();

Get the error number of C<POLLWRNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

kimoto@tk2-259-39003:~/labo/modules/SPVM-Sys$ perl ~/poll_constant.pl
=head2 POLLERR

  static method POLLERR : int ();

Get the constant value of C<POLLERR>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLHUP

  static method POLLHUP : int ();

Get the constant value of C<POLLHUP>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLIN

  static method POLLIN : int ();

Get the constant value of C<POLLIN>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLNORM

  static method POLLNORM : int ();

Get the constant value of C<POLLNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLNVAL

  static method POLLNVAL : int ();

Get the constant value of C<POLLNVAL>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLOUT

  static method POLLOUT : int ();

Get the constant value of C<POLLOUT>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLPRI

  static method POLLPRI : int ();

Get the constant value of C<POLLPRI>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDBAND

  static method POLLRDBAND : int ();

Get the constant value of C<POLLRDBAND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLRDNORM

  static method POLLRDNORM : int ();

Get the constant value of C<POLLRDNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRBAND

  static method POLLWRBAND : int ();

Get the constant value of C<POLLWRBAND>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

=head2 POLLWRNORM

  static method POLLWRNORM : int ();

Get the constant value of C<POLLWRNORM>. If the system doesn't define this constant, an exception will be thrown. The error code is set to the class id of the L<Error::NotSupported|SPVM::Error::NotSupported> class.

