CFLAGS=-Wall -g3 -std=c99

main_base : queue.o monkeyz.o main.o
	gcc queue.o monkeyz.o main.o $(CFLAGS) -o project

test : queue.o monkeyz.o test.o
	gcc queue.o monkeyz.o test.o $(CFLAGS) -o test
	./test

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

clean_test :
	rm test queue.o monkeyz.o test.o
