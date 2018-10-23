main : queue.o
	gcc queue.o main.c -std=c99  -o main

queue.o : queue.h
	gcc queue.c -c -std=c99

clean :
	rm main queue.o
