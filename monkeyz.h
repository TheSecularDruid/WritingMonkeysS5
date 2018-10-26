#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "queue/queue.h"
#define TEXTFILE filename.txt  //same, with the name of the file once it's created
//it is supposed that filename is opened in read mode for this program

enum work { READER, STATISTICIAN, WRITTER };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum work work;      //his activity/role
   int read_words;      
   int printed_words;
};

void init_monkeys(struct monkey monkeyz[], int length);

int read_already(struct cell);
void filter_active_monkeys(struct monkey all_monkeyz[], struct monkey active_monkeyz[], int lengt, struct queue FIFO, );  //modifies status of monkeys and put active monkeys in the active_monkeyz table for later use in work
//be weary that both tables should have the same length in order to avoid segfault errors
int writter_work(struct monkey, struct queue FIFO);  //execute the work of a writter monkey

#endif
