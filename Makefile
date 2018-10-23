main : queue.o
	gcc queue.o main.c -std=c99  -o main

queue.o : queue.h
	gcc queue.c -c -std=c99

clean :
	rm main queue.o queue.h.gch

test_monkeyz :
	cc monkeyz.c -std=c99 -Werror -o test_monkeyz
	rm test_monkeyz
