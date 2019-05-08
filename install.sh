mkdir ${HOME}/.config/remote
touch ${HOME}/.config/remote/remote_profiles
chmod +x remote
sudo cp remote /bin/
sudo cp man/remote.1.gz /usr/share/man/man1/
chmod -x remote
