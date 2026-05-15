#!/bin/bash

# Create test files
TEST1="test1.txt"
TEST2="test2.txt"

# Some complex text with empty lines, tabs, and Windows CR (\r) characters
echo -e "Hello world!\n\nThis is a simple test.\nTesting cat utility.\n\n\nhello again!\n\t123 numbers 456\nAnother Line" > "$TEST1"
echo -e "Just another file\n\n\n\nHello there\nBye!\n" > "$TEST2"

# Append some \r for the -e test
printf "Line with CR\r\n" >> "$TEST1"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

FAIL_COUNT=0
SUCCESS_COUNT=0

run_test() {
    local args="$@"

    ./s21_cat $args > s21_output.txt
    cat $args > sys_output.txt

    if cmp -s s21_output.txt sys_output.txt; then
        echo -e "${GREEN}SUCCESS:${NC} cat $args"
        ((SUCCESS_COUNT++))
    else
        echo -e "${RED}FAIL:${NC} cat $args"
        echo "Expected:"
        cat sys_output.txt
        echo "Got:"
        cat s21_output.txt
        echo "-----------------------"
        ((FAIL_COUNT++))
    fi
}

echo "Running tests for s21_cat..."
echo "============================"

# Test without flags
run_test "$TEST1"
run_test "$TEST2"

# Test with flags
run_test "-b" "$TEST1"
run_test "-e" "$TEST1"
run_test "-n" "$TEST1"
run_test "-s" "$TEST1"
run_test "-t" "$TEST1"

run_test "-b" "$TEST2"
run_test "-e" "$TEST2"
run_test "-n" "$TEST2"
run_test "-s" "$TEST2"
run_test "-t" "$TEST2"

echo "============================"
echo "Tests completed."
echo -e "${GREEN}Successful: $SUCCESS_COUNT${NC}"
if [ $FAIL_COUNT -gt 0 ]; then
    echo -e "${RED}Failed: $FAIL_COUNT${NC}"
    exit 1
fi

rm -f s21_output.txt sys_output.txt "$TEST1" "$TEST2"
exit 0
