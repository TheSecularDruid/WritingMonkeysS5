CFLAGS=-Wall -g3 -std=c99

main : Achievement_1/queue.o Achievement_1/monkeyz.o Achievement_1/main.o Achievement_1/successors_queue.o
	gcc Achievement_1/queue.o Achievement_1/monkeyz.o Achievement_1/main.o Achievement_1/successors_queue.o $(CFLAGS) -o project

Achievement_1/queue.o : Achievement_1/Queue/queue.h Achievement_1/Queue/queue.c
	gcc -o Achievement_1/queue.o -c Achievement_1/Queue/queue.c $(CFLAGS)

Achievement_1/monkeyz.o : Achievement_1/Monkeyz/monkeyz.h Achievement_1/Monkeyz/monkeyz.c
	gcc -o Achievement_1/monkeyz.o -c Achievement_1/Monkeyz/monkeyz.c  $(CFLAGS)

Achievement_1/successors_queue.o : Achievement_1/Queue/successors_queue.c Achievement_1/Queue/successors_queue.h
	gcc -o Achievement_1/successors_queue.o -c Achievement_1/Queue/successors_queue.c $(CFLAGS)

Achievement_1/main.o : Achievement_1/main.c
	gcc -o Achievement_1/main.o -c Achievement_1/main.c $(CFLAGS)

main_base : queue.o monkeyz.o main.o
	gcc queue.o monkeyz.o main.o $(CFLAGS) -o project

test : queue.o monkeyz.o test.o
	gcc queue.o monkeyz.o test.o $(CFLAGS) -o test

main.o : main.c
	gcc -o main.o -c main.c $(CFLAGS)

test.o : test.c
	gcc -o test.o -c test.c $(CFLAGS)

queue.o : Queue/queue.h Queue/queue.c
	gcc -o queue.o -c Queue/queue.c $(CFLAGS)

monkeyz.o : Monkeyz/monkeyz.h Monkeyz/monkeyz.c
	gcc -o monkeyz.o -c Monkeyz/monkeyz.c  $(CFLAGS)

clean :
	rm project queue.o monkeyz.o main.o
