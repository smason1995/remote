# REMOTE: SSH/SFTP Profile Manager   
#### Author: Sydney Ann Mason
#### Current version: 1.0
#### Last Revised Date: 04/16/2019

### Desc:
    Remote is a CLI-based manager for SSH and SFTP connections via terminals while being terminal agnostic.

### Dependencies:
<b>pathlib</b> library for python3

### Setup:
```
$cd path/to/remote/repo
$chmod +x install.sh
$./install.sh
```

### DEVELOPMENT
    All changes/updates are made to the testing branch and moved into the master branch when known to work properly in most use cases.
### TODO (needs to be prioritized):
    - Allow adding and removal of multiple profiles at once
    - Make profiles easily editable via remote
    - Encrypt profile list for added security
    - Allow remote to run ssh urls directly
    - Make distro packages (aiming to support Debian/Ubuntu, Arch, Fedora, Opensuse)
    - Add support for Remote Desktop Protocol (RDP)
    - Attempt to get support for Mac (if the reousrces to test it become available)
    - Add support for TAB completion
    - Use fakeroot instead of SUDO (to happen very soon)
