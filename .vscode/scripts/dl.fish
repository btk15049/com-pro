#!/usr/bin/fish --debug="env-*"

set url (string sub -s 4 (head -n 1 $FILE))

echo "url: $URL"
echo "directry: $TEST_DIR"

oj dl $url -d $TEST_DIR
