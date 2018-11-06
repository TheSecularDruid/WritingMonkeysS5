#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void add_in_queue(struct cell* toAdd, struct queue* source)
{
  if(is_queue_empty(*source))
    source->first = toAdd;
  else
    source->last->next = toAdd;
  source->last = toAdd;
  toAdd->next = NULL;
  toAdd->was_read_by_statistician = 0;
}

void remove_in_queue(struct queue* source)
{
  if(!is_queue_empty(*source)){
    struct cell* c = source->first->next;
    free(source->first);
    source->first = c;
    if(is_queue_empty(*source))
      source->last = NULL;
  }
}

struct cell* read_queue(struct queue source)
{
  return source.first;
}

int is_queue_empty(struct queue source)
{
  return (source.first == NULL);
}

void init_queue(struct queue* source)
{
  source->first = NULL;
  source->last = NULL;
}

struct cell pop_queue(struct queue source) {
   struct cell popped = *(read_queue(source));
   remove_in_queue(&source);
   return popped;
}

void print_queue(struct queue queue_to_print)
{
  struct cell* ptr = queue_to_print.first;
  while(ptr != queue_to_print.last){
    printf("cell %d : %s | next : %d\n",ptr,ptr->word,ptr->next);
    ptr = ptr->next;
  }
  printf("cell %d : %s | next : %d\n",ptr,ptr->word,ptr->next);
}

void purge_queue(struct queue* queue_to_purge)
{
  while(!is_queue_empty(*queue_to_purge)){
    remove_in_queue(queue_to_purge);
  }
}
