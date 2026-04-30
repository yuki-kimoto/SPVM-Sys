package SPVM::Sys::IO::Glob;

1;

=head1 Name

SPVM::Sys::IO::Glob - BSD glob Porting

=head1 Description

L<Sys::IO::Glob> class in L<SPVM> is a port of BSD C<glob> function.

=head1 Usage

  use Sys::IO::Glob;
  
  my $files = Sys::IO::Glob->glob("path/*");
  
  my $files = Sys::IO::Glob->glob("path/?oo");

=head1 Class Methods

C<static method glob : string[] ($pattern : string);>

The L<bsd_glob|https://metacpan.org/pod/Sys::IO::Glob#bsd_glob> porting.

The C<~> expansion is not supported.

=head1 Copyright & License

Copyright (c) 2025 Yuki Kimoto

MIT License
