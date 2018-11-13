main : queue.o monkeyz.o main.c
	gcc queue.o monkeyz.o main.c -std=c99 -g -o project

test : queue.o monkeyz.o test.c
	gcc queue.o monkeyz.o test.c -std=c99 -g -o project

queue.o : Queue/queue.h Queue/queue.c
	gcc Queue/queue.c -c -std=c99 -g

monkeyz.o : Monkeyz/monkeyz.h Monkeyz/monkeyz.c
	gcc Monkeyz/monkeyz.c -c -std=c99 -g

clean :
	rm project queue.o monkeyz.o
