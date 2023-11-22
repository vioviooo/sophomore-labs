CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
# FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall

all: ../build/graph

../build/graph: graph.o stack.o stack_double.o
	$(CC) $(FLAGS) graph.o stack.o stack_double.o -o ../build/graph

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

stack.o: stack.c stack.h
	$(CC) $(FLAGS) -c stack.c

stack_double.o: stack_double.c stack_double.h
	$(CC) $(FLAGS) -c stack_double.c

clean:
	rm -rf *.o
	rm -rf ../build/graph

out:
	../build/graph

rebuild: clean all