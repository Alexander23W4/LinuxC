#!/bin/bash
echo "Running unit tests:"

# base on bash command line, run all test.c files, do automatic testing in batch
# each of the test.c file is a dependent test process
# redirect all test logs to LOG FILE
LIB_SOURCE=
TEST_FUNCTION=
PARAMETER=

# batch-execute test files, put output log into log file
for i in tests/*_tests
do
    if test -f $i
    then      # redirect output to log file (useful)
        if $VALGRIND ./$i $LIB_SOURCE $TEST_FUNCTION $PARAMETER 2>> tests/tests.log    # main operator, execute test file  
        then
            echo $i $TEST_FUNCTION PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done

echo ""


