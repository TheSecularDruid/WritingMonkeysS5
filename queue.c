#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void add_in_queue(struct cell* toAdd, struct queue* source)
{
  toAdd->next = NULL;
  source->last->next = toAdd;
  source->last = toAdd;
}

void remove_in_queue(struct queue* source)
{
  if(source->first != NULL){
    struct cell* c = source->first->next;
    free(source->first);
    source->first = c;;
  }
}

struct cell* read_first(struct queue source)
{
  return source.first;
}

int is_empty(struct queue source)
{
  return (source.first == NULL);
}
