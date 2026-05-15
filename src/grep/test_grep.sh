#!/bin/bash

# Create a temporary file for testing
TEST_FILE="test_file.txt"
TEST_FILE2="test_file2.txt"

echo -e "Hello world!\nThis is a simple test.\nTesting grep utility.\nhello again!\n123 numbers 456\nAnother Line" > "$TEST_FILE"
echo -e "Just another file\nHello there\nBye!" > "$TEST_FILE2"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

FAIL_COUNT=0
SUCCESS_COUNT=0

run_test() {
    local flag=$1
    local pattern=$2
    local files=$3

    ./s21_grep -$flag "$pattern" $files > s21_output.txt
    grep -$flag "$pattern" $files > sys_output.txt

    if cmp -s s21_output.txt sys_output.txt; then
        echo -e "${GREEN}SUCCESS:${NC} grep -$flag \"$pattern\" $files"
        ((SUCCESS_COUNT++))
    else
        echo -e "${RED}FAIL:${NC} grep -$flag \"$pattern\" $files"
        echo "Expected:"
        cat sys_output.txt
        echo "Got:"
        cat s21_output.txt
        echo "-----------------------"
        ((FAIL_COUNT++))
    fi
}

echo "Running tests for s21_grep..."
echo "============================="

# Test single files
run_test "e" "Hello" "$TEST_FILE"
run_test "i" "hello" "$TEST_FILE"
run_test "v" "Hello" "$TEST_FILE"
run_test "c" "Hello" "$TEST_FILE"
run_test "l" "Hello" "$TEST_FILE"
run_test "n" "Hello" "$TEST_FILE"

run_test "e" "test" "$TEST_FILE"
run_test "i" "TEST" "$TEST_FILE"
run_test "v" "test" "$TEST_FILE"
run_test "c" "test" "$TEST_FILE"
run_test "l" "test" "$TEST_FILE"
run_test "n" "test" "$TEST_FILE"

# Test missing pattern
run_test "e" "nonexistent" "$TEST_FILE"
run_test "c" "nonexistent" "$TEST_FILE"
run_test "v" "nonexistent" "$TEST_FILE"

echo "============================="
echo "Tests completed."
echo -e "${GREEN}Successful: $SUCCESS_COUNT${NC}"
if [ $FAIL_COUNT -gt 0 ]; then
    echo -e "${RED}Failed: $FAIL_COUNT${NC}"
    exit 1
fi

rm -f s21_output.txt sys_output.txt "$TEST_FILE" "$TEST_FILE2"
exit 0
