#!/bin/sh
pacman -Fy
pacman -S mingw-w64-x86_64-gcc
pacman -S make
echo 'PATH="${PATH}:/mingw64/bin"' >> .bash_profile

