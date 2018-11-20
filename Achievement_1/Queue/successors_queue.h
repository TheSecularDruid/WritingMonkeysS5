#ifndef SUCCESSORS_QUEUE_H
#define SUCCESSORS_QUEUE_H

#include "queue.h"

struct successors_cell {   //each cell contains a word, it's number of occurence and a pointer toward a standard queue containing it's successors and their number of occureces (attribute "was_read_by_statistician")
    char word[MAX_WORD_LENGTH+1];
    int nb_of_occ;
    struct queue successors;
    struct successors_cell* next;
};

struct successors_queue {
    struct successors_cell* first;
    struct successors_cell* last;
};

void init_successors_queue(struct successors_queue* succ_queue){
    succ_queue->first = NULL;
    succ_queue->last = NULL;
}

int is_successors_queue_empty(struct successors_queue succ_queue){
    return(succ_queue.first == NULL);
}

void add_in_successors_queue(struct successors_cell* toAdd, struct successors_queue* source) {
    if(is_successors_queue_empty(*source))
	source->first = toAdd;
    else
	source->last->next = toAdd;
    source->last = toAdd;
    toAdd->next = NULL;
    toAdd->nb_of_occ = 0;
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

#endif
