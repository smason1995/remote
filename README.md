# REMOTE: SSH/SFTP Profile Manager   
#### Author: Sydney Ann Mason
#### Current version: 1.5
#### Last Revised Date: 04/16/2019
#### Branch: TESTING

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
### TODO (needs to be prioritized):
    - Encrypt profile list for added security
    - Allow remote to run ssh urls directly
    - Make distro packages (aiming to support Debian/Ubuntu, Arch, Fedora, Opensuse)
    - Add support for Remote Desktop Protocol (RDP)
    - Attempt to get support for Mac (if the reousrces to test it become available)
    - Add support for TAB completion
    - Use fakeroot instead of SUDO (to happen very soon)
