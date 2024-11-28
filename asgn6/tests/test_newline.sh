#!/bin/bash

# Test for ensuring every line of output ends with a newline.
./calc 5 7 > got.txt
CAT_EXIT_CODE=$?

# Create the expected output file.
echo "12" > expected.txt

# Check exit code. Expect exit code = 0.
if [ $CAT_EXIT_CODE -ne 0 ]; then
    echo "wrong exit code: $CAT_EXIT_CODE"
    rm expected.txt got.txt
    exit 1
fi

# Check program output. Ensure it matches and ends with a newline.
if ! diff expected.txt got.txt; then
    echo "wrong output"
    rm expected.txt got.txt
    exit 1
fi

# Check if the output ends with a newline.
if [ "$(tail -c 1 got.text)" != $"\n"; then
    echo "output does not end with newline"
    rm expected.txt got.txt
    exit 1
fi

# Test passed.
echo "PASS"

# Cleanup.
rm expected.txt got.txt
exit 0

