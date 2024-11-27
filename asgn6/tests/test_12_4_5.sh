./calc 12 4 5 > got.txt 
CAT_EXIT_CODE=$?

if [ $CAT_EXIT_CODE -eq 0 ]; then
    echo "wrong exit code" $CAT_EXIT_CODE
    rm expected.txt
    rm got.txt
    exit 1
fi

# Check program output
echo "TOO MANY ARGUMENTS" > expected.txt
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    # message on failure
    echo "wrong output"
    rm expected.txt
    rm got.txt
    exit 1
fi

# Celebrate
echo "PASS"

rm expected.txt
rm got.txt
exit 0
