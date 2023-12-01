CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall

all: ../build/5

../build/5: main.o stack.o stack_double.o
	$(CC) $(FLAGS) main.o stack.o stack_double.o -o ../build/5

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

stack_double.o: stack_double.c stack_double.h
	$(CC) $(FLAGS) -c stack_double.c

clean:
	rm -rf *.o
	rm -rf ../build/5

out:
	../build/5

rebuild: clean all