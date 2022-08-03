#!/bin/sh
#
# Parameter: 
# 1. Ordner, wo gesucht wird
# 2. Dateien, in denen gesucht wird (nur Kennung). z.B. cpp
# 3. Was gesucht wird (Suchwort)
# 4. Zusaetzliche Options, z.B. -i (case-insensitive)
#
# Parameter fuer grep:
#
# -F: in Dateien suchen
# -H: Dateinamen ausgeben
# -n: Zeilennummer ausgeben
#
if [ -z "$1" ]
then
echo "usage: findinfiles <where> <filetype> <what> [options]" 
echo "  example: findinfiles . cpp Color"
echo "  example: findinfiles . h color -i"
echo "version 1.1"
else
find $1 -name "*.$2" -exec grep $4 -F -H -n $3 {} \;
fi

