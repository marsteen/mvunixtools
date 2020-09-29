#!/bin/sh
#
# Parameter: 1. Ordner, wo gesucht wird
# 2. Dateien, in denen gesucht wird (nur Kennung). z.B. cpp
# 3. Was gesucht wird (Suchwort)
#
# Parameter fuer grep:
#
# -F: in Dateien suchen
# -H: Dateinamen ausgeben
# -n: Zeilennummer ausgeben
#
if [ -z "$1" ]
then
echo "usage: findinfiles <where> <filetype> <what>" 
echo "example: findinfiles . cpp Color"
else
find $1 -name "*.$2" -exec grep -F -H -n $3 {} \;
fi

