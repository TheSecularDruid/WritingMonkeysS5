#ifndef QUEUE_H
#define QUEUE_H

#define MAX_WORD_LENGTH 20

struct cell{
  char word[MAX_WORD_LENGTH+1];
  int was_read_by_statistician;
  struct cell* next;
};

struct queue{
  struct cell* first;
  struct cell* last;
};

void add_in_queue(struct cell* toAdd, struct queue* source); //Adding a cell to the queue
void remove_in_queue(struct queue* source); //Removing the oldest cell of the queue
struct cell* read_queue(struct queue source); //Reading the oldest cell of the queue
int is_queue_empty(struct queue source); //Checking if the queue is empty
void init_queue(struct queue* source); //Initializing the queue properly
struct cell pop_queue(struct queue source); //Just a pop goddamit

#endif
