#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>


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

struct cell pop_queue(struct queue* source) {
   struct cell popped = *(read_queue(*source));
   remove_in_queue(source);
   return popped;
}

void print_queue(struct queue queue_to_print)
{
  if (!is_queue_empty(queue_to_print)){
    struct cell* ptr = queue_to_print.first;
    while(ptr != NULL){
      printf("cell %d : %s ; was read by statistician : %d | next : %d\n",ptr,ptr->word,ptr->was_read_by_statistician,ptr->next);
      ptr = ptr->next;
    }
  }
  else
    printf("The queue is empty \n");
}

void purge_queue(struct queue* queue_to_purge)
{
  while(!is_queue_empty(*queue_to_purge)){
    remove_in_queue(queue_to_purge);
  }
}

struct cell* research_in_queue(struct queue source, char* word_to_search)
{
  struct cell* ptr = source.first;
  if(!is_queue_empty(source)){
    while(ptr != NULL){
      if(strcmp(word_to_search,ptr->word) == 0)
        return ptr;
      ptr = ptr->next;
    }
  }
  return NULL;
}

void cell_cpy(struct cell* source, struct cell* dest)
{
  strcpy(dest->word,source->word);
  dest->was_read_by_statistician = source->was_read_by_statistician;
  dest->next = source->next;
}

void print_cell(struct cell cell_to_print)
{
  printf("Cell at %p (%d) : \n",&cell_to_print,&cell_to_print);
  printf("Word : %s\n",cell_to_print.word);
  printf("Was Read By Statistician : %d\n",cell_to_print.was_read_by_statistician);
  printf("Next : %p (%d)\n",cell_to_print.next,cell_to_print.next);
}