#!/usr/bin/fish --debug="env-*"

set binary /tmp/(date +%s).out

echo "directry: $TEST_DIR"
echo "bin: $binary"

g++ $FILE \
-DBTK \
-D_GLIBCXX_DEBUG \
-std=c++17 \
-Wall \
-Wextra \
-I $LIB \
-o $binary

and oj test -c $binary -d $TEST_DIR
