CFLAGS=-Wall -g3 -std=c99


main_achievement_1 : Achievement_1/queue.o Achievement_1/monkeyz.o Achievement_1/main.o Achievement_1/successors_queue.o
	gcc queue.o monkeyz.o main.o successors_queue.o $(CFLAGS) -o project

main_base : queue.o monkeyz.o main.o
	gcc queue.o monkeyz.o main.o $(CFLAGS) -o project

Achievement_1/queue.o : Achievement_1/Queue/queue.h Achievement_1/Queue/queue.c
	gcc -o queue.o -c Achievement_1/Queue/queue.c $(CFLAGS)

Achievement_1/monkeyz.o : Achievement_1/Monkeyz/monkeyz.h Achievement_1/Monkeyz/monkeyz.c
	gcc -o monkeyz.o -c Achievement_1/Monkeyz/monkeyz.c  $(CFLAGS)

Achievement_1/successors_queue.o : Achievement_1/Queue/successors_queue.c Achievement_1/Queue/successors_queue.h
	gcc -o successors_queue.o -c Achievement_1/Queue/successors_queue.c $(CFLAGS)

Achievement_1/main.o : Achievement_1/main.c
	gcc -o main.o -c Achievement_1/main.c $(CFLAGS)

test : queue.o monkeyz.o test.o
	gcc queue.o monkeyz.o test.o $(CFLAGS) -o test

main.o : base/main.c
	gcc -o main.o -c base/main.c $(CFLAGS)

test.o : base/test.c
	gcc -o test.o -c base/test.c $(CFLAGS)

queue.o : base/Queue/queue.h base/Queue/queue.c
	gcc -o queue.o -c base/Queue/queue.c $(CFLAGS)

monkeyz.o : base/Monkeyz/monkeyz.h base/Monkeyz/monkeyz.c
	gcc -o monkeyz.o -c base/Monkeyz/monkeyz.c  $(CFLAGS)

clean :
	rm project queue.o monkeyz.o main.o
