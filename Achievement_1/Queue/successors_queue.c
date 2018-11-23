#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "successors_queue.h"

void init_successors_queue(struct successors_queue* succ_queue){
    succ_queue->first = NULL;
    succ_queue->last = NULL;
}

int is_successors_queue_empty(struct successors_queue succ_queue){
    return(succ_queue.first == NULL);
}

void add_in_successors_queue(struct successors_cell* to_add, struct successors_queue* source) {
    if(is_successors_queue_empty(*source))
	   source->first = to_add;
    else
    	source->last->next = to_add;

    source->last = to_add;
    to_add->next = NULL;
    to_add->nb_of_occ = 0;
}

struct successors_cell* read_successors_queue(struct successors_queue source) {
    return source.first;
}

void remove_in_successors_queue(struct successors_queue* source) {
    if(!is_successors_queue_empty(*source)){
	struct successors_cell* c = source->first->next;
	free(source->first);
	source->first = c;
    }
    if(is_successors_queue_empty(*source))
	source->last = NULL;
}

struct successors_cell pop_successors_queue(struct successors_queue* source) {
    struct successors_cell result = *(read_successors_queue(*source));
    remove_in_successors_queue(source);
    return(result);
}

void print_successors_queue(struct successors_queue queue_to_print)
{
    if (!is_successors_queue_empty(queue_to_print)){
      struct successors_cell* ptr = queue_to_print.first;
      while(ptr != NULL){
        printf("cell %p : %s ; nb of occ : %d | next : %p\n",ptr,ptr->word,ptr->nb_of_occ,ptr->next);
        printf("Successors of this word : ----------------------------------- \n");
        print_queue_light(ptr->successors);
        printf("End of successors --------------------------------------------\n");
        ptr = ptr->next;
      }
    }
    else
      printf("The successors queue is empty \n");
}

struct successors_cell* research_word_in_successors_queue(struct successors_queue source, char* word)
{
    struct successors_cell* ptr = source.first;
    if(!is_successors_queue_empty(source)){
      while(ptr != NULL){
        if(strcmp(word,ptr->word) == 0)
          return ptr;
        ptr = ptr->next;
      }
    }
    return NULL;
}

//NEW TO TEST
struct successors_cell* research_successors_cell(struct successors_queue* source, int position)
{
    struct successors_cell* ptr = source->first;
    int i  = 1;
    while(ptr != NULL && i != position)
    {
        i++;
        ptr = ptr->next;
    }
    return ptr;
}

//NEW TO TEST
int length_successors_queue(struct successors_queue source)
{
    struct successors_cell* ptr = source.first;
    int i = 0;
    while(ptr != NULL){
        i++;
        ptr = ptr->next;
    }
    return i;
}

//NEW TO TEST
void successors_cell_cpy(struct successors_cell* source, struct successors_cell* dest)
{
    strcpy(dest->word,source->word);
    dest->nb_of_occ = source->nb_of_occ;
    dest->next = source->next;
    queue_cpy(&(source->successors),&(dest->successors));
}

void purge_successors_queue(struct successors_queue* to_purge)
{
    while(!(is_successors_queue_empty(*to_purge))){
        purge_queue(&(to_purge->first->successors));
        remove_in_successors_queue(to_purge);
    }
}
