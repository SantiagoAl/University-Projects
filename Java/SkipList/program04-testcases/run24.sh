#!/bin/bash

# Sean Szumlanski
# COP 3503, Summer 2019

# ==================
# SkipList: run24.sh
# ==================
# You can run this script at the command line like so:
#
#   bash run24.sh
#
# For more details, see the assignment PDF.


################################################################################
# Shell check.
################################################################################

# Running this script with sh instead of bash can lead to false positives on the
# test cases. Yikes! These checks ensure the script is not being run through the
# Bourne shell (or any shell other than bash).

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
NUM_TEST_CASES=24


################################################################################
# Check that all required files are present.
################################################################################

if [ ! -f SkipList.java ]; then
	echo ""
	echo " Error: You must place SkipList.java in this directory before we can"
	echo "        proceed. Aborting test script."
	echo ""
	exit
elif [ ! -f RNG.java ]; then
	echo ""
	echo " Error: You must place RNG.java in this directory before we can"
	echo "        proceed. Aborting test script."
	echo ""
	exit
elif [ ! -d sample_output ]; then
	echo ""
	echo " Error: You must place the sample_output folder in this directory"
	echo "        before we can proceed. Aborting test script."
	echo ""
	exit
fi

function check_test_case()
{
	local testcase_file=$1
	local output_file=$2

	if [ ! -f $testcase_file ]; then
		echo ""
		echo " Error: You must place $testcase_file in this directory before we"
		echo "        can proceed. Aborting test script."
		echo ""
		exit
	fi

	if [ ! -f sample_output/$output_file ]; then
		echo ""
		echo " Error: You must place $output_file in the sample_output directory"
		echo "        before we can proceed. Aborting test script."
		echo ""
		exit
	fi
}

for i in `seq -f "%02g" 1 2`;
do
	check_test_case "Bonus$i.java" "Bonus$i-output.txt"
done

for i in `seq -f "%02g" 1 16`;
do
	check_test_case "TestCase$i.java" "TestCase$i-output.txt"
done

for i in `seq -f "%02g" 17 22`;
do
	check_test_case "TestCaseNew$i.java" "TestCaseNew$i-output.txt"
done


################################################################################
# Run test cases with input specified at command line (standard test cases).
################################################################################

echo ""
echo "================================================================"
echo "Running test cases..."
echo "================================================================"
echo ""

function run_test_case()
{
	local testcase=$1

	echo -n "  [Test Case] $testcase.java ... "

	rm *.class 2> /dev/null

	# Attempt to compile.
	javac SkipList.java $testcase.java 2> /dev/null
	compile_val=$?
	if [[ $compile_val != 0 ]]; then
		echo "fail (failed to compile)"
		return
	fi

	# Run program. Capture return value to check whether it crashes.
	java $testcase > myoutput.txt 2> /dev/null
	execution_val=$?
	if [[ $execution_val != 0 ]]; then
		echo "fail (program crashed)"
		return
	fi

	# Run diff and capture its return value.
	diff myoutput.txt sample_output/$testcase-output.txt > /dev/null
	diff_val=$?
	
	# Output results based on diff's return value.
	if  [[ $diff_val != 0 ]]; then
		echo "fail (output does not match)"
	else
		echo "PASS!"
		PASS_CNT=`expr $PASS_CNT + 1`
	fi
}

for i in `seq -f "%02g" 1 2`;
do
	run_test_case "Bonus$i"
done

for i in `seq -f "%02g" 1 16`;
do
	run_test_case "TestCase$i"
done

for i in `seq -f "%02g" 17 22`;
do
	run_test_case "TestCaseNew$i"
done


################################################################################
# Special check for compile-time warnings and warning suppression annotations.
################################################################################

echo ""
echo "================================================================"
echo "Running Additional Tests and Safety Checks"
echo "================================================================"
echo ""

javac SkipList.java 2> SkipList__warning.err

warnings_flag=1
if [ -s SkipList__warning.err ]; then
	warnings_flag=0
fi

grep --silent unchecked SkipList__warning.err
unchecked_flag=$?

grep --silent "@Suppress" SkipList.java
suppress_flag=$?

if [[ $warnings_flag == 0 ]]; then
	echo "  [Additional Check] Compiles without warnings: ** fail **"
else
	echo "  [Additional Check] Compiles without warnings: PASS"
	PASS_CNT=`expr $PASS_CNT + 1`
fi

if [[ $unchecked_flag == 0 ]]; then
	echo "  [Additional Check] Compiles without unchecked ops: ** fail **"
else
	echo "  [Additional Check] Compiles without unchecked ops: PASS"
	PASS_CNT=`expr $PASS_CNT + 1`
fi

if [[ $suppress_flag == 0 ]]; then
	echo "  [Additional Check] No suppression annotations: ** fail **"
	supp_note=1
else
	echo "  [Additional Check] No suppression annotations: PASS"
	PASS_CNT=`expr $PASS_CNT + 1`
fi


############################################################################
# Check for tabs vs. spaces.
############################################################################

echo ""
echo "================================================================"
echo "Checking for tabs vs. spaces..."
echo "================================================================"
echo ""

if ! [ -x "$(command -v grep)" ]; then
	echo "  Skipping tabs vs. spaces check; grep not installed. You"
	echo "  might see this message if you're running this script on a"
	echo "  Mac. Please be sure to test your final code on Eustis."
elif ! [ -x "$(command -v awk)" ]; then
	echo "  Skipping tabs vs. spaces check; awk not installed. You"
	echo "  might see this message if you're running this script on a"
	echo "  Mac. Please be sure to test your final code on Eustis."
else
	num_spc_lines=`grep "^ " SkipList.java | wc -l | awk '{$1=$1};1'`
	num_tab_lines=`grep "$(printf '^\t')" SkipList.java | wc -l | awk '{$1=$1};1'`
	num_und_lines=`grep "$(printf '^[^\t ]')" SkipList.java | wc -l | awk '{$1=$1};1'`

	echo "  Number of lines beginning with spaces: $num_spc_lines"
	echo "  Number of lines beginning with tabs: $num_tab_lines"
	echo "  Number of lines with no indentation: $num_und_lines"

	if [ "$num_spc_lines" -gt 0 ] && [ "$num_tab_lines" -gt 0 ]; then
		echo ""
		echo "  Whoa, buddy! It looks like you're starting some lines of code with"
		echo "  tabs, and other lines of code with spaces. You'll need to choose"
		echo "  one or the other."
		echo ""
		echo "  Try running the following commands to see which of your lines begin"
		echo "  with spaces (the first command below) and which ones begin with tabs"
		echo "  (the second command below):"
		echo ""
		echo "     grep \"^ \" SkipList.java -n"
		echo "     grep \"\$(printf '^\t')\" SkipList.java -n"
	elif [ "$num_spc_lines" -gt 0 ]; then
		echo ""
		echo "  Looks like you're using spaces for all your indentation! (Yay!)"
	elif [ "$num_tab_lines" -gt 0 ]; then
		echo ""
		echo "  Looks like you're using tabs for all your indentation! (Yay!)"
	else
		echo ""
		echo "  Whoa, buddy! It looks like none of your lines of code are indented!"
	fi
fi


################################################################################
# Cleanup phase.
################################################################################

# Clean up any lingering .class files.
rm -f *.class

# Clean up the output files generated by this script.
rm -f myoutput.txt SkipList__warning.err


################################################################################
# Final thoughts.
################################################################################

echo ""
echo "================================================================"
echo "Final Thoughts"
echo "================================================================"
echo ""
echo "  Recall that these are not the same test cases released with"
echo "  the assignment PDF."
echo ""
echo "  Also, this script does not impose any runtime restrictions and"
echo "  therefore won't be able to detect any proccess timeouts that"
echo "  might be indicated in your official test case transcript."
echo ""
