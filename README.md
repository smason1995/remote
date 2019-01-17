#------------------------------#
| REMOTE:                      |
|   SSH/SFTP Profile Manager   |
|                              |
| Written by: Sydney Ann Mason |
| Version date: 11/27/2018     |
#------------------------------#

Remote is a CLI-based manager for SSH and SFTP connections via terminals.

It allows you to save, view, and execute profiles via the command line.
Following are the commands that remote will understand:

ssh                 will execute a secure-shell protocol via the command line

sftp                will execute secure-file-transfer-protocol via the command line

save                will write a new profile to the remote session storage

remove              will remove an existing profile from remote session storage

print-profiles      will display all known profiles to the screen

help                will print out the command available to execute

If you want to use the latest stable version of remote, then you can find it in
the Prod directory. If you want to use the version in development, then you can
find it in the Dev directory.

TODO (in no particular order):
     -Expand to cover most remoting needs
