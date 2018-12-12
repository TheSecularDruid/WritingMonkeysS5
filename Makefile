CFLAGS=-Wall -g3 -std=c99
CURRENT_GOAL=Achievement_1


main : queue.o successors_queue.o monkeyz.o main.o
	gcc $(CURRENT_GOAL)/queue.o $(CURRENT_GOAL)/monkeyz.o $(CURRENT_GOAL)/main.o $(CURRENT_GOAL)/successors_queue.o $(CFLAGS) -o project

successors_queue.o : $(CURRENT_GOAL)/Queue/successors_queue.c $(CURRENT_GOAL)/Queue/successors_queue.h
	gcc -o $(CURRENT_GOAL)/successors_queue.o -c $(CURRENT_GOAL)/Queue/successors_queue.c $(CFLAGS)

test : queue.o monkeyz.o test.o successors_queue.o
	gcc $(CURRENT_GOAL)/queue.o $(CURRENT_GOAL)/monkeyz.o $(CURRENT_GOAL)/test.o $(CURRENT_GOAL)/successors_queue.o $(CFLAGS) -o test

main.o : $(CURRENT_GOAL)/main.c
	gcc -o $(CURRENT_GOAL)/main.o -c $(CURRENT_GOAL)/main.c $(CFLAGS)

test.o : $(CURRENT_GOAL)/test.c
	gcc -o $(CURRENT_GOAL)/test.o -c $(CURRENT_GOAL)/test.c $(CFLAGS)

queue.o : $(CURRENT_GOAL)/Queue/queue.h $(CURRENT_GOAL)/Queue/queue.c
	gcc -o $(CURRENT_GOAL)/queue.o -c $(CURRENT_GOAL)/Queue/queue.c $(CFLAGS)

monkeyz.o : $(CURRENT_GOAL)/Monkeyz/monkeyz.h $(CURRENT_GOAL)/Monkeyz/monkeyz.c
	gcc -o $(CURRENT_GOAL)/monkeyz.o -c $(CURRENT_GOAL)/Monkeyz/monkeyz.c  $(CFLAGS)

clean_test:
	rm test $(CURRENT_GOAL)/successors_queue.o $(CURRENT_GOAL)/queue.o $(CURRENT_GOAL)/test.o $(CURRENT_GOAL)/monkeyz.o

clean:
	rm project $(CURRENT_GOAL)/successors_queue.o $(CURRENT_GOAL)/queue.o $(CURRENT_GOAL)/main.o $(CURRENT_GOAL)/monkeyz.o
