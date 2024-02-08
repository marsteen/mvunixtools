#!/bin/sh
if ["$1" == ""]
then
echo "usage:   project_source <folder> <keyfile.txt>" 
echo "example: project_source . keyfile.txt"
else
find $1 \( -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) -exec ./projectheader $2 {} \;
fi

