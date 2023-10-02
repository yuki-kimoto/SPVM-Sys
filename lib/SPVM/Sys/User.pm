package SPVM::Sys::User;

1;

=head1 Name

SPVM::Sys::User - User System Call

=head1 Usage
  
  use Sys::User;
  
  my $effective_user_id = Sys::User->geteuid;

=head1 Description

C<Sys::User> is the class for the user manipulation.

=head1 Class Methods

=head2 getuid

C<native static method getuid : int ()>

Get the real user ID.

=head2 geteuid

C<native static method geteuid : int ()>
  
Get the effective user ID.

=head2 getgid

C<native static method getgid : int ()>

Get the real group ID.

=head2 getegid

C<native static method getegid : int ()>
  
Get the effective group ID.

=head2 setuid

C<native static method setuid : int ($uid : int)>

Set the user ID.

=head2 seteuid

C<native static method seteuid : int ($euid : int)>

Set the effective user ID.

=head2 setgid

C<native static method setgid : int ($gid : int)>

Set the real user ID.

=head2 setegid

C<native static method setegid : int ($egid : int)>

Set the effective group ID.

=head2 setpwent

C<native static method setpwent : void ()>

Move to the head of the group database.

=head2 endpwent

C<native static method endpwent : void ()>

Close the group database.

=head2 getpwent

C<native static method getpwent : L<Sys::User::Passwd|SPVM::Sys::User::Passwd> ()>

Get a group entry. The group entry is a L<Sys::User::Passwd|SPVM::Sys::User::Passwd> object.

=head2 setgrent

C<native static method setgrent : void ()>

Move to the head of the group database.

=head2 endgrent

C<native static method endgrent : void ()>

Close the group database.

=head2 getgrent

C<native static method getgrent : L<Sys::User::Group|SPVM::Sys::User::Group> ()>

Get a group entry as L<Sys::User::Group|SPVM::Sys::User::Group>

=head2 getgroups

C<native static method getgroups : int[] ()>

Get group IDs.

=head2 setgroups

C<native static method setgroups : void ($groups : int[])>

Set group IDs.

=head2 getpwuid

C<native static method getpwuid : L<Sys::User::Passwd|SPVM::Sys::User::Passwd> ($id : int)>

Get a group entry by the user id. The group entry is a L<Sys::User::Passwd|SPVM::Sys::User::Passwd> object.

=head2 getpwnam

C<native static method getpwnam : L<Sys::User::Passwd|SPVM::Sys::User::Passwd> ($name : string)>

Get a group entry by the user name. The group entry is a L<Sys::User::Passwd|SPVM::Sys::User::Passwd> object.

=head2 getgrgid

C<native static method getgrgid : L<Sys::User::Group|SPVM::Sys::User::Group> ($id : int)>

Get a group entry by the user id. The group entry is a L<Sys::User::Group|SPVM::Sys::User::Group> object.

=head2 getgrnam

C<native static method getgrnam : L<Sys::User::Group|SPVM::Sys::User::Group> ($name : string)>

Get a group entry by the user id. The group entry is a L<Sys::User::Group|SPVM::Sys::User::Group> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

