#!/bin/sh
mkdir small
find . -maxdepth 1 -iname "*.jpg" -exec convert {} -resize 50% small/{} \;
