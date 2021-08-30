#!/bin/sh
find . -name "*.cpp" -exec sed -e 's/\t/ /g' {} > {} \;
