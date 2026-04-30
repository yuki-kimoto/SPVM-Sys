package SPVM::Sys::IO::Glob;

1;

=head1 Name

SPVM::Sys::IO::Glob - BSD bsd_glob Porting

=head1 Description

L<Sys::IO::Glob> class in L<SPVM> is a port of BSD C<bsd_glob> function.

=head1 Usage

  use Sys::IO::Glob;
  
  my $files = Sys::IO::Glob->bsd_glob("path/*");
  
  my $files = Sys::IO::Glob->bsd_glob("path/?oo");

=head1 Class Methods

=head2 bsd_glob

C<static method bsd_glob : string[] ($pattern : string);>

Perl's L<bsd_glob|https://metacpan.org/pod/File::Glob#bsd_glob> porting.

The C<~> expansion is not supported.

=head1 Copyright & License

Copyright (c) 2025 Yuki Kimoto

MIT License
