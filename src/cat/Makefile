CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

TARGET = s21_cat
SRCS = s21_cat.c

.PHONY: all clean rebuild test

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)

rebuild: clean all

test: $(TARGET)
	chmod +x test_cat.sh
	./test_cat.sh
