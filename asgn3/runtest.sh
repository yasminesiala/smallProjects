# Usage:    source runtest num_players seed
# Example:  source runtest 3 784

# Check that two command-line arguments are given.
if [ "$1" = "" ] || [ "$2" = "" ]
then
    echo 'Usage:    source runtest num_players seed'
    echo 'Example:  source runtest 3 784'
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
        EXEC='../../resources/asgn3/lcr_arm'
    else
        EXEC='../../resources/asgn3/lcr_x86'
    fi

    # Confirm that the executable file is where we expect it to be.
    if ! [ -f $EXEC ]
    then
        echo "Can't find reference program $EXEC"
    else
        # Run the executables.
        printf "%d\n%d\n" $1 $2 | $EXEC > expected.txt
        printf "%d\n%d\n" $1 $2 | ./lcr > got.txt

        # Print any difference.
        # The diff -s option reports when the files are identical.
        diff -s expected.txt got.txt
    fi
fi

