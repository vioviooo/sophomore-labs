CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall

all: ../build/7

../build/7: main.o
	$(CC) $(FLAGS) main.o -o ../build/7

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -rf *.o
	rm -rf ../build/7

out:
	../build/7

rebuild: clean all