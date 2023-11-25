CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall

all: ../build/2

../build/2: main.o
	$(CC) $(FLAGS) main.o -o ../build/2

main.o: main.c main.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -rf *.o
	rm -rf ../build/2

out:
	../build/2

rebuild: clean all