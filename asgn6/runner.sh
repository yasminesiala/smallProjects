#!/bin/bash

# This file tests all bird-counting binaries using student-provided test files.
#
#       Usage:  ./runtests
#               source runtests
#
# Place test files in the directory "tests".  The name of each test must
# start with "test_" and end with ".sh".
#
#       tests/test_anything_you_want.sh
#       \_________/\_______________/\_/
#        required     your choice    required
#
# Examples:  test_input_plus_511a.sh
#            test_input_plus_511b.sh
#            test_input_plus_512a.sh
#            test_input_512b.sh
#            test_input_with_two_minuses.sh
#
# Each of your tests must end with end with "exit 0" or "exit 1"


# Configure the test script.
REPORT_PASSING_TESTS=1
PRINT_TEST_OUTPUT=0
PRINT_USING_COLOR=1

# Automatically determine whether to run x86 or arm binaries.
cat_folder=compiled_cats_arm
if [ "$(uname -m)" = "x86_64" ]; then
    cat_folder=compiled_cats_x86
fi

# For all "cat" binaries
for cat in $(find $cat_folder -name '*cat'); do
    cp $cat calc

    # for all test scripts
    for script in $(find tests -name 'test_*' ); do
        cp $script current_test.sh
        scriptname=$(basename $script .sh)

        if [ "$1" = "" ] || [ "$1" = "$scriptname" ]
        then
            # run the test
            err=$(sh current_test.sh 2> /dev/null)

            if [ $? -eq 0 ]
            then
                if [ $REPORT_PASSING_TESTS -eq 1 ] ; then
                    if [ $PRINT_USING_COLOR -eq 1 ] ; then
                        /usr/bin/echo -e "\033[32mPASS\033[0m:\t$cat\twith $scriptname"
                        if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                            echo Message:
                            /usr/bin/echo -e "\033[33m$err\033[0m"
                        fi
                    else
                        /usr/bin/echo -e "PASS:\t$cat\twith $scriptname"
                        if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                            echo Message:
                            echo $err
                        fi
                    fi
                fi
            else
                if [ $PRINT_USING_COLOR -eq 1 ] ; then
                    /usr/bin/echo -e "\033[31mFAIL\033[0m:\t$cat\twith $scriptname"
                    if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                        echo Message:
                        /usr/bin/echo -e "\033[33m$err\033[0m"
                    fi
                else
                    /usr/bin/echo -e "FAIL\t$cat\twith $scriptname"
                    if [ $PRINT_TEST_OUTPUT -ne 0 ] ; then
                        echo Message:
                        echo $err
                    fi
                fi
            fi
        fi

        rm current_test.sh
    done
    
    rm calc
done
