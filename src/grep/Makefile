CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lpcre2-8

TARGET  = s21_grep
OBJS    = s21_grep.o flags_functions.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

s21_grep.o: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -c $< -o $@

flags_functions.o: flags_functions.c s21_grep.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)