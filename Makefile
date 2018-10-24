test : queue.o
	gcc queue.o main.c -std=c99 -o project

queue.o : queue/queue.h
	gcc queue/queue.c -c -std=c99

clean :
	rm project queue.o	


test_monkeyz :
	cc monkeyz.c -std=c99 -Werror -o test_monkeyz
	rm test_monkeyz
