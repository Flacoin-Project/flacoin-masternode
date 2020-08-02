
Debian
====================
This directory contains files used to package flacoind/flacoin-qt
for Debian-based Linux systems. If you compile flacoind/flacoin-qt yourself, there are some useful files here.

## flacoin: URI support ##


flacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install flacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your flacoinqt binary to `/usr/bin`
and the `../../share/pixmaps/flacoin128.png` to `/usr/share/pixmaps`

flacoin-qt.protocol (KDE)

