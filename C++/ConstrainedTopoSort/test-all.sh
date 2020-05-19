#!/bin/bash

if [ "$BASH" != "/bin/bash" ]; then
    echo ""
    echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
    echo ""
    exit
fi

if [ -z "$BASH_VERSION" ]; then
    echo ""
    echo " Bloop! Please use bash to run this script, like so: bash test-all.sh"
    echo ""
    exit
fi


################################################################################
# Initialization.
################################################################################

PASS_CNT=0
NUM_TEST_CASES=4
TOTAL_TEST_CNT=`expr $NUM_TEST_CASES + $NUM_TEST_CASES`


# Ensure that obnoxious glibc errors are piped to stderr.
export LIBC_FATAL_STDERR_=1

# Now redirect all local error messages to /dev/null (like "process aborted").
exec 2> /dev/null

if [ ! -f ConstrainedTopoSort.cpp ]; then
    echo ""
    echo " Error: You must place ConstrainedTopoSort.cpp in this directory before"
    echo " we can proceed. Aborting test script"
    echo ""
    exit
fi

if [ ! -f ConstrainedTopoSort.h ]; then
    echo ""
    echo " Error: You must place ConstrainedTopoSort.h in this directory before"
    echo " we can proceed. Aborting test script"
    echo ""
    exit
fi

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	if [ ! -f TestCase$i.cpp ]; then
		echo ""
		echo " Error: You must place TestCase$i.cpp in this directory before we"
		echo "        can proceed. Aborting test script."
		echo ""
		exit
	fi
done


################################################################################
# Run test cases.
################################################################################

echo ""
echo "================================================================"
echo "Running test cases..."
echo "================================================================"
echo ""

# Function for running a single test case.
function testScript()
{
    local TestCase=$1;

    echo -n "[Test Case] $TestCase ... "

    # Attemp to compile.
    g++ -std=c++14 ConstrainedTopoSort.cpp $TestCase 2> /dev/null
    compile_val=$?
    if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

    # Run program. Capture return value to check whether it crashes.
    ./a.out 2> /dev/null
    execution_val=$?
    if [[ $execution_val != 0 ]]; then
        echo "fail (program crashed)"
        return
    fi
}

for i in `seq -f "%02g" 1 $NUM_TEST_CASES`;
do
	testScript "TestCase$i.cpp"
done

# Clean up the executable and output files created by this script.
rm -f ./a.out
