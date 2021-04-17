#!/usr/bin/fish --debug="env-*"

set SCRIPT_DIR (dirname (status --current-filename))

if test "$USE_EXPAND" = "true"
    fish $SCRIPT_DIR/expand_header.fish
end

set url (string sub -s 4 (head -n 1 $FILE))
set binary /tmp/(date +%s).out

echo "url: $url"
echo "bin: $binary"

g++ $FILE \
-std=c++17 \
-Wall \
-Wextra \
-o $binary

and rm $binary

and oj submit $url $FILE
