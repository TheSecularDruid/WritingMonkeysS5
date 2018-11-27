CFLAGS=-Wall -g3 -std=c99
ACTUAL_GOAL=Achievement_1



main_A1 : queue.o monkeyz.o main.o successors_queue.o
	gcc Achievement_1/queue.o Achievement_1/monkeyz.o Achievement_1/main.o Achievement_1/successors_queue.o $(CFLAGS) -o project

main_base : queue.o monkeyz.o main.o
	gcc base/queue.o base/monkeyz.o base/main.o $(CFLAGS) -o project

successors_queue.o : $(ACTUAL_GOAL)/Queue/successors_queue.c $(ACTUAL_GOAL)/Queue/successors_queue.h
	gcc -o $(ACTUAL_GOAL)/successors_queue.o -c $(ACTUAL_GOAL)/Queue/successors_queue.c $(CFLAGS)

test : queue.o monkeyz.o test.o
	gcc $(ACTUAL_GOAL)/queue.o $(ACTUAL_GOAL)/monkeyz.o $(ACTUAL_GOAL)/test.o $(CFLAGS) -o test

main.o : $(ACTUAL_GOAL)/main.c
	gcc -o $(ACTUAL_GOAL)/main.o -c $(ACTUAL_GOAL)/main.c $(CFLAGS)

test.o : $(ACTUAL_GOAL)/test.c
	gcc -o $(ACTUAL_GOAL)/test.o -c $(ACTUAL_GOAL)/test.c $(CFLAGS)

queue.o : $(ACTUAL_GOAL)/Queue/queue.h $(ACTUAL_GOAL)/Queue/queue.c
	gcc -o $(ACTUAL_GOAL)/queue.o -c $(ACTUAL_GOAL)/Queue/queue.c $(CFLAGS)

monkeyz.o : $(ACTUAL_GOAL)/Monkeyz/monkeyz.h $(ACTUAL_GOAL)/Monkeyz/monkeyz.c
	gcc -o $(ACTUAL_GOAL)/monkeyz.o -c $(ACTUAL_GOAL)/Monkeyz/monkeyz.c  $(CFLAGS)

clean_Ach :
	rm project $(ACTUAL_GOAL)/successors_queue.o $(ACTUAL_GOAL)/queue.o $(ACTUAL_GOAL)/monkeyz.o $(ACTUAL_GOAL)/main.o

clean :
	rm project queue.o monkeyz.o main.o
