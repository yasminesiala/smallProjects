
# Case 1: Check sum without leading spaces or zeroes.
./calc 5 6 > got.txt
CAT_EXIT_CODE=$?

# Expected output is "11", no leading spaces.
echo "11" > expected.txt

# Check if the exit code is 0.
if [ $CAT_EXIT_CODE -ne 0 ]; then
    echo "wrong exit code" $?
    rm expected.txt
    rm got.txt
    exit 1
fi

# Check program output.
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    echo "wrong output"
    rm expected.txt
    rm got.txt
    exit 1
fi

# Case 2: Check negative sum with no leading space and no unnecessary zero.
./calc -5 -6 > got.txt
CAT_EXIT_CODE=$?

# Expected output is "-11", no leading spaces or zero.
echo "-11" > expected.txt

# Check if the exit code is 0.
if [ $CAT_EXIT_CODE -ne 0 ]; then
    echo "wrong exit code" $?
    rm expected.txt
    rm got.txt
    exit 1
fi

# Check program output.
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    echo "wrong output"
    rm expected.txt
    rm got.txt
    exit 1
fi

# Case 3: Check if `0` is allowed to start with leading zero.
./calc 0 0 > got.txt
CAT_EXIT_CODE=$?

# Expected output is "0", no leading zeroes.
echo "0" > expected.txt

# Check if the exit code is 0.
if [ $CAT_EXIT_CODE -ne 0 ]; then
    echo "wrong exit code" $?
    rm expected.txt
    rm got.txt
    exit 1
fi

# Check program output.
diff expected.txt got.txt
if [ $? -ne 0 ]; then
    echo "wrong output"
    rm expected.txt
    rm got.txt
    exit 1
fi

echo "PASS"
rm expected.txt
rm got.txt
exit 0

