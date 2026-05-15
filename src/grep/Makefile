CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRCS = s21_grep.c flags_functions.c
OBJS = $(SRCS:.c=.o)
TARGET = s21_grep

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c s21_grep.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

test: $(TARGET)
	chmod +x test_grep.sh
	./test_grep.sh