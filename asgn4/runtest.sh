# Usage:    source runtest.sh "list of numbers"
# Example:  source runtest.sh "314 76 95064"

# Check that one command-line argument is given.
if [ "$1" = "" ]
then
    echo 'Usage:    source runtest.sh LIST OF NUMBERS'
    echo 'Example:  source runtest.sh 314 76 95064'
    echo 'Usage:    source runtest.sh -d LIST OF NUMBERS'
    echo 'Example:  source runtest.sh -d 314 76 95064'
else
    # Automatically determine if this laptop is running Apple silicon or x86.
    CPUTYPE=`lscpu | grep Architecture: | awk -e '{print $2;}'`

    # If the automation above doesn't work, then uncomment one of the lines
    # below to force the choice.
    #CPUTYPE=aarch64
    #CPUTYPE=x86

    # Set EXEC to the path of the appropriate executable file.
    if [ $CPUTYPE = 'aarch64' ]
    then
        EXEC='../../resources/asgn4/unique_arm'
    else
        EXEC='../../resources/asgn4/unique_x86'
    fi

    # Confirm that the executable file is where we expect it to be.
    if ! [ -f $EXEC ]
    then
        echo "Can't find reference program $EXEC"
    else
        # Run the executables.
        $EXEC $@ > expected.txt
        ./unique $@ > got.txt

        # Print any difference.
        # The diff -s option reports when the files are identical.
        diff -s expected.txt got.txt
    fi
fi

