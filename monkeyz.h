#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "queue/queue.h"
#define FIFO queue_name         //replace queue_name with the actual name of the queue when implemented
#define TEXTFILE filename.txt  //same, with the name of the file once it's created
//it is supposed that filename is opened in read mode for this program

enum work { READER, STATISTICIAN, WRITTEN };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum work work;      //his activity/role
};

void init_monkeys(struct monkey monkeyz[], int length);

int read_already(struct cell);
void filter_active_monkeys(struct monkey monkeyz[], int length);


#endif
