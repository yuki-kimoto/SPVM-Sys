package SPVM::Sys::Select::Constant;

1;

=head1 Name

SPVM::Sys::Select::Constant - Constant Values for Select.

=head1 Description

Sys::Select::Constant class in L<SPVM> has methods to get constant values for the select system call.

=head1 Usage

  use Sys::Select::Constant;

=head1 Class Methods

=head2 FD_SETSIZE

C<static method FD_SETSIZE : int ();>

Gets the value of C<FD_SETSIZE>. If the value is not defined in this system, an L<Error::NotSupported|SPVM::Error::NotSupported> exception is thrown.

=head1 See Also

=over 2

=item * L<Sys|SPVM::Sys>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

