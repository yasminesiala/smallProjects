./calc 12 14 15 > got.txt 
CAT_EXIT_CODE=$?

echo "TOO MANY ARGUMENTS" > expected.txt

if [ $CAT_EXIT_CODE -eq 0 ]; then
    echo "wrong exit code"
    exit 1
fi

# Check program output
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    echo "wrong output"
    exit 1
fi

echo "PASS"

# Clean up
rm expected.txt got.txt
exit 0
