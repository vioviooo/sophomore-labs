CC = gcc
# FLAGS = -Wall -Wextra -Werror -fsanitize=address
FLAGS = -Wall -Wextra -Werror
# FLAGS = -Wall

all: ../build/2

../build/2: main.o
	$(CC) $(FLAGS) main.o -o ../build/2

main.o: functions.c main.c main.h
	$(CC) $(FLAGS) -c main.c

clean:
	rm -rf *.o
	rm -rf ../build/2

beauty:
	clang-format -i *.c
	clang-format -i *.h

analyze:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

out:
	../build/2

rebuild: clean all