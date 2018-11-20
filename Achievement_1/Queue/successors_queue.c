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

struct successors_cell* research_in_successors_queue(struct successors_queue source, char word[]) {
    struct successors_cell* ptr = source.first;
    while(ptr!=NULL&&strcmp(ptr->word,word)) {
	printf("%s | %p", ptr->word, ptr);
  	ptr = ptr->next;
    }
    return(NULL);
    
}
