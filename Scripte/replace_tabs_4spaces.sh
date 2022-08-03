#!/bin/sh
find . \( -name "*.cpp" -or -name "*.h" -or -name "*.html" \) -exec sed -e 's/\t/ /g' {} > {} \;
