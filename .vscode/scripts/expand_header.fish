#!/usr/bin/fish --debug="env-*"

set SCRIPT_DIR (dirname (status --current-filename))

python3 $SCRIPT_DIR/util/resolve_includes.py $FILE $LIB
and clang-format -i $FILE
