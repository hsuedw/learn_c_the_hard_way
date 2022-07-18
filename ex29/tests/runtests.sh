#!/bin/bash


function print_result() {
    if [ $1 -eq 0 ]
    then
        echo PASS
    else
        echo FAIL
    fi
}

echo "## Running unit tests:"

echo "#### Test print_a_message"
tests/ex29_tests build/libex29.so print_a_message "hello there"
print_result $?

echo "#### Test uppercase"
tests/ex29_tests build/libex29.so uppercase "hello there"
print_result $?

echo "#### Test lowercase"
tests/ex29_tests build/libex29.so lowercase "HELLO THERE"
print_result $?

echo "#### Test fail_on_purpose"
tests/ex29_tests build/libex29.so fail_on_purpose "I fail"
print_result $?

echo "#### Test fail_on_purpose without argument"
tests/ex29_tests build/libex29.so fail_on_purpose 
print_result $?

echo "#### Test a function that is not there"
tests/ex29_tests build/libex29.so adfasfasdf asdfadff
print_result $?

echo "#### Test a .so that is not there"
tests/ex29_tests build/libex.so adfasfasdf asdfadff
print_result $?
