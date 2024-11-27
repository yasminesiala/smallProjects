./calc 4 "abc" > got.txt 
CAT_EXIT_CODE=$?

echo "BAD INPUT" > expected.txt

# Expect exit code != 0.
# Complain if exit code = 0.
if [ $CAT_EXIT_CODE -eq 0 ]; then
    echo "wrong exit code" $?
    rm expected.txt
    rm got.txt

    # Report failure to the calling script and exit.
    exit 1
fi

# Check program output
# Complain if it's unexpected.
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    # message on failure
    echo "wrong output"
    rm expected.txt
    rm got.txt

    # Report failure to the calling and exit.cript.
    exit 1
fi

# We made it this far.
# Celebrate!
echo "PASS"

# Remove temporary files.
rm expected.txt
rm got.txt

# Report success to the calling and exit.cript.
exit 0
