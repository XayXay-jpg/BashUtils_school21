CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRCS = s21_grep.c flags_functions.c
TARGET = s21_grep

.PHONY: all clean rebuild test

all: $(TARGET)

$(TARGET): $(SRCS) s21_grep.h
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)

rebuild: clean all

test: $(TARGET)
	chmod +x test_grep.sh
	./test_grep.sh