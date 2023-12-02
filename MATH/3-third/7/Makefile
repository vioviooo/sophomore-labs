CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall

all: ../build/7

../build/7: main.o stack.o stack_double.o
	$(CC) $(FLAGS) main.o stack.o stack_double.o -o ../build/7

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

stack_double.o: stack_double.c stack_double.h
	$(CC) $(FLAGS) -c stack_double.c

clean:
	rm -rf *.o
	rm -rf ../build/7

out:
	../build/7

rebuild: clean all