CC = gcc
CFLAGS = -Wall -Werror -Wextra

TARGET = main

all: $(TARGET)

$(TARGET): test.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

check-leaks:
	valgrind --leak-check=full ./$(TARGET)