#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>

void init_queue(struct queue* source)
{
    source->first = NULL;
    source->last = NULL;
}

int is_queue_empty(struct queue* source)
{
    return (source->first == NULL);
}

void add_in_queue(struct cell* toAdd, struct queue* source)
{
    if(is_queue_empty(source))
        source->first = toAdd;
    else
        source->last->next = toAdd;
    source->last = toAdd;
    toAdd->next = NULL;
    toAdd->was_read_by_statistician = 0;
}

struct cell* read_queue(struct queue* source)
{
    return source->first;
}

void remove_in_queue(struct queue* source)
{
    if(!is_queue_empty(source)){
        struct cell* c = source->first->next;
        free(source->first);
        source->first = c;
        if(is_queue_empty(source))
            source->last = NULL;
    }
}

struct cell pop_queue(struct queue* source) {
    struct cell popped;
    cell_cpy(read_queue(source),&popped);
    remove_in_queue(source);
    return popped;
}

int length_queue(struct queue* source)
{
    struct cell* ptr = source->first;
    int prompter = 0;
    while(ptr != NULL){
        prompter++;
        ptr = ptr->next;
    }
    return prompter;
}

void print_queue(struct queue* queue_to_print)
{
    if (!is_queue_empty(queue_to_print)){
        struct cell* ptr = queue_to_print->first;
        while(ptr != NULL){
            printf("cell %p : %s ; was read by statistician : %d | next : %p\n",ptr,ptr->word,ptr->was_read_by_statistician,ptr->next);
            ptr = ptr->next;
        }
    }
    else
        printf("The queue is empty \n");
}

void print_queue_light(struct queue* queue)
{
    if (!is_queue_empty(queue)){
        struct cell* ptr = queue->first;
        while(ptr != NULL){
            printf("%s (%d); ", ptr->word,ptr->was_read_by_statistician);
            ptr = ptr->next;
        }
        printf("\n");
    }
    else
        printf("The queue is empty \n");
}

void queue_cpy(struct queue* source, struct queue* dest)
{
    struct cell* ptr = source->first;
    while(ptr != NULL){
        struct cell* buffer = malloc(sizeof(struct cell));
        cell_cpy(ptr,buffer);
        buffer->next = NULL;
        add_in_queue(buffer,dest);
        ptr = ptr->next;
    }
}

void purge_queue(struct queue* queue_to_purge)
{
    while(!is_queue_empty(queue_to_purge)){
        remove_in_queue(queue_to_purge);
    }
}

struct cell* research_in_queue(struct queue* source, char* word_to_search)
{
    struct cell* ptr = source->first;
    if(!is_queue_empty(source)){
        while(ptr != NULL){
            if(strcmp(word_to_search,ptr->word) == 0)
                return ptr;
            ptr = ptr->next;
        }
    }
    return NULL;
}

struct cell* research_cell(struct queue* source, int position)
{
    struct cell* ptr = source->first;
    int i  = 0;
    while(ptr != NULL && i != position)
    {
        i++;
        ptr = ptr->next;
    }
    return ptr;
}

void cell_cpy(struct cell* source, struct cell* dest)
{
    strcpy(dest->word,source->word);
    dest->was_read_by_statistician = source->was_read_by_statistician;
    dest->next = source->next;
}

void print_cell(struct cell* cell_to_print)
{
  printf("Cell at %p : \n",cell_to_print);
  printf("Word : %s\n",cell_to_print->word);
  printf("Was Read By Statistician : %d\n",cell_to_print->was_read_by_statistician);
  printf("Next : %p \n",cell_to_print->next);
}

int total_multiplicity_of_queue(const struct queue* source) {
    int total_multiplicity = 0;
    struct cell* ptr = source->first;
    while (ptr!=NULL) {
	total_multiplicity += ptr->was_read_by_statistician;
	ptr = ptr->next;
    }
    return total_multiplicity;
    
}

struct cell* nth_queue_element_with_multiplicity(const struct queue* source, int n) {
    struct cell* ptr = source->first;
    while( ptr!=NULL&&n>0 ) {
	n -= ptr->was_read_by_statistician;
	ptr = ptr->next;
    }
    if (ptr==NULL)
	return source->last;
    return ptr;
} 
