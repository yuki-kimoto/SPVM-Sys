package SPVM::Sys::IO::Utimbuf;

1;

=head1 Name

SPVM::Sys::IO::Utimbuf - struct utimbuf in the C language

=head1 Description

The Sys::IO::Utimbuf represents the C<struct utimbuf> in the C language.

=head1 Usage

  use Sys::IO::Utimbuf;
  
  my $utimbuf = Sys::IO::Utimbuf->new;
  
  my $actime = $utimbuf->actime;
  my $modtime = $utimbuf->modtime;
  
  $utimbuf->set_actime($actime);
  $utimbuf->set_modtime($modtime);

=head1 Details

This is a pointer class. The pointer of the instance is set to a C<struct utimbuf> object.

=head1 Class Methods

=head2 new

C<static method new : L<Sys::IO::Utimbuf|SPVM::Sys::IO::Utimbuf> ();>

Create a new L<Sys::IO::Utimbuf|SPVM::Sys::IO::Utimbuf> object.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

The destructor.

=head2 actime

C<method actime : long ();>

Get C<actime>.

=head2 set_actime

C<method set_actime : long ($actime : long);>

Set C<actime>.

=head2 modtime

C<method modtime : long ();>

Get C<modtime>.

=head2 set_modtime

C<method set_modtime : long ($modtime : long);>

Set C<modtime>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

