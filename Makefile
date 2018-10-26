main : queue.o monkeyz.o main.c
	gcc queue.o monkeyz.o main.c -std=c99 -o project

test : queue.o monkeyz.o main.c
	gcc queue.o monkeyz.o main.c -std=c99 -o project

queue.o : Queue/queue.h Queue/queue.c
	gcc Queue/queue.c -c -std=c99

monkeyz.o : Monkeyz/monkeyz.h Monkeyz/monkeyz.c
	gcc Monkeyz/monkeyz.c -c -std=c99

clean :
	rm project queue.o monkeyz.o


test_monkeyz :
	cc monkeyz.c -std=c99 -Werror -o test_monkeyz
	rm test_monkeyz
