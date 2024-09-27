.PHONY: build run clean valgrind-test

tema1: Implementation.o List.o Stacks.o
	gcc Implementation.o List.o Stacks.o -o tema1 -Wall

Implementation.o: Implementation.c ExecuteQueue.h ListSort.h UndoStack.h
	gcc -c Implementation.c

List.o: List.c ListSort.h
	gcc -c List.c

Stacks.o: Stacks.c UndoStack.h
	gcc -c Stacks.c

run: tema1
	./tema1

clean:
	rm -f Implementation.o List.o Stacks.o tema1

valgrind-test:
	valgrind --leak-check=full ./tema1 < tema1.in