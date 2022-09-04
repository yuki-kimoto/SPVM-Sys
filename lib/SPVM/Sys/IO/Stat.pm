package SPVM::Sys::IO::Stat;

1;

=head1 NAME

SPVM::Sys::IO::Stat - Dir Handle

=head1 SYNOPSYS
  
  use Sys::IO::Stat;

=head1 DESCRIPTION

C<Sys::IO::Stat> is directory handle object that represent C<DIR> structure of C<C language>.

=head1 Class Methods

=head2 S_CDF

  native static method S_CDF : int ();


=head2 S_ENFMT

  native static method S_ENFMT : int ();


=head2 S_IF

  native static method S_IF : int ();


=head2 S_IFBLK

  native static method S_IFBLK : int ();


=head2 S_IFCHR

  native static method S_IFCHR : int ();


=head2 S_IFCMP

  native static method S_IFCMP : int ();


=head2 S_IFDIR

  native static method S_IFDIR : int ();


=head2 S_IFDOOR

  native static method S_IFDOOR : int ();


=head2 S_IFIFO

  native static method S_IFIFO : int ();


=head2 S_IFLNK

  native static method S_IFLNK : int ();


=head2 S_IFMPB

  native static method S_IFMPB : int ();


=head2 S_IFMPC

  native static method S_IFMPC : int ();


=head2 S_IFMT

  native static method S_IFMT : int ();


=head2 S_IFNAM

  native static method S_IFNAM : int ();


=head2 S_IFNWK

  native static method S_IFNWK : int ();


=head2 S_IFREG

  native static method S_IFREG : int ();


=head2 S_IFSHAD

  native static method S_IFSHAD : int ();


=head2 S_IFSOCK

  native static method S_IFSOCK : int ();


=head2 S_IFWHT

  native static method S_IFWHT : int ();


=head2 S_INSEM

  native static method S_INSEM : int ();


=head2 S_INSHD

  native static method S_INSHD : int ();


=head2 S_IREAD

  native static method S_IREAD : int ();


=head2 S_IRGRP

  native static method S_IRGRP : int ();


=head2 S_IROTH

  native static method S_IROTH : int ();


=head2 S_IRUSR

  native static method S_IRUSR : int ();


=head2 S_IRWXG

  native static method S_IRWXG : int ();


=head2 S_IRWXO

  native static method S_IRWXO : int ();


=head2 S_IRWXU

  native static method S_IRWXU : int ();


=head2 S_ISBLK

  native static method S_ISBLK : int ($mode : int);


=head2 S_ISCHR

  native static method S_ISCHR : int ($mode : int);


=head2 S_ISDIR

  native static method S_ISDIR : int ($mode : int);


=head2 S_ISFIFO

  native static method S_ISFIFO : int ($mode : int);


=head2 S_ISGID

  native static method S_ISGID : int ();


=head2 S_ISLNK

  native static method S_ISLNK : int ($mode : int);


=head2 S_ISREG

  native static method S_ISREG : int ($mode : int);


=head2 S_ISSOCK

  native static method S_ISSOCK : int ($mode : int);


=head2 S_ISUID

  native static method S_ISUID : int ();


=head2 S_ISVTX

  native static method S_ISVTX : int ();


=head2 S_IWGRP

  native static method S_IWGRP : int ();


=head2 S_IWOTH

  native static method S_IWOTH : int ();


=head2 S_IWUSR

  native static method S_IWUSR : int ();


=head2 S_IXGRP

  native static method S_IXGRP : int ();


=head2 S_IXOTH

  native static method S_IXOTH : int ();


=head2 S_IXUSR

  native static method S_IXUSR : int ();