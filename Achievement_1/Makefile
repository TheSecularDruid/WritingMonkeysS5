CFLAGS=-Wall -g3 -std=c99

main : queue.o monkeyz.o main.o successors_queue.o
	gcc queue.o monkeyz.o main.o successors_queue.o $(CFLAGS) -o project

test : queue.o monkeyz.o test.o successors_queue.o
	gcc queue.o monkeyz.o test.o successors_queue.o $(CFLAGS) -o test
	./test

main.o : main.c
	gcc -o main.o -c main.c $(CFLAGS)

test.o : test.c
	gcc -o test.o -c test.c $(CFLAGS)

queue.o : Queue/queue.h Queue/queue.c
	gcc -o queue.o -c Queue/queue.c $(CFLAGS)

monkeyz.o : Monkeyz/monkeyz.h Monkeyz/monkeyz.c
	gcc -o monkeyz.o -c Monkeyz/monkeyz.c  $(CFLAGS)

successors_queue.o : Queue/successors_queue.c Queue/successors_queue.h
	gcc -o successors_queue.o -c Queue/successors_queue.c $(CFLAGS)

clean :
	rm project queue.o monkeyz.o main.o successors_queue.o

clean_test :
	rm test queue.o monkeyz.o successors_queue.o test.o
