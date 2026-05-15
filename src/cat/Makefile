CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

TARGET = s21_cat
SRCS = s21_cat.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean rebuild test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

test: $(TARGET)
	chmod +x test_cat.sh
	./test_cat.sh
