#!/usr/bin/fish --debug="env-*"

set SCRIPT_DIR (dirname (status --current-filename))

echo "// $URL" > $FILE
cat $TEMPLATE >> $FILE

if test "$URL" = ""
    echo '"oj dl" is skipped'
else
    fish $SCRIPT_DIR/dl.fish
end

