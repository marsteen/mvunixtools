#!/bin/sh
if ["$1" == ""]
then
echo "usage:   project_source <keyfile.txt>" 
echo "example: project_source keyfile.txt"
else
find . \( -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) -exec projectheader $1 {} \;
fi

