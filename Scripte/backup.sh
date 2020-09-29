#!/bin/bash
tar cvf D1digipad.tar D1digipad
tar cvf libd1digipad2.tar libd1digipad2
tar cvf map3dlib.tar map3dlib
#
#
source ./backupcounter.txt
backupcount=$((backupcount+1))
echo "backupcount="$backupcount > backupcounter.txt
#
#
#
#fbase="/media/steen/TOSHIBA EXT/Backup/Android/"
fbase="/Volumes/TOSHIBA EXT/Backup/iOS"
newfolder=$fbase$backupcount
#
#
mkdir "$newfolder"
#
#
cp D1digipad.tar libd1digipad2.tar map3dlib.tar "$newfolder"


