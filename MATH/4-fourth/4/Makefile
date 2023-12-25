CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall

all: ../build/4

../build/4: main.o stack.o
	$(CC) $(FLAGS) main.o stack.o -o ../build/4

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

clean:
	rm -rf *.o
	rm -rf ../build/4

out:
	../build/4

rebuild: clean all