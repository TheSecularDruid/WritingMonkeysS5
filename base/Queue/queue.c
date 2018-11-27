#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>


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

struct cell* read_queue(struct queue* source)
{
    return source->first;
}

int is_queue_empty(struct queue* source)
{
    return (source->first == NULL);
}

void init_queue(struct queue* source)
{
    source->first = NULL;
    source->last = NULL;
}

struct cell pop_queue(struct queue* source) {
    struct cell popped;
    cell_cpy(read_queue(source),&popped);
    remove_in_queue(source);
    return popped;
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

int length_queue(struct queue* queue)
{
    struct cell* ptr = source->first;
    int prompter = 0;
    while(ptr != NULL){
        prompter++;
        ptr = ptr->next;
    }
    return prompter;
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

//
//----
// Stats functions
//----
//

void greatest_occurency(struct queue* source, struct queue* dest)
{
    struct cell* ptr = source->first;
    int max_occurency = 0;

    while(ptr != NULL){
        if(max_occurency < ptr->was_read_by_statistician){
            max_occurency = ptr->was_read_by_statistician;
            purge_queue(dest);
            struct cell* cell_of_max = malloc(sizeof(struct cell));
            cell_cpy(ptr,cell_of_max);
            add_in_queue(cell_of_max,dest);
            cell_of_max->was_read_by_statistician = ptr->was_read_by_statistician;
        }
        else{
            if(max_occurency == ptr->was_read_by_statistician){
                struct cell* cell_of_max = malloc(sizeof(struct cell));
                cell_cpy(ptr,cell_of_max);
                add_in_queue(cell_of_max,dest);
                cell_of_max->was_read_by_statistician = ptr->was_read_by_statistician;
            }
        }
        ptr = ptr->next;
    }
}

void minimal_occurency(struct queue* source, struct queue* dest)
{
    struct cell* ptr = source->first;
    int min_occurency = 0;
    if(ptr != NULL)
        min_occurency = ptr->was_read_by_statistician;

    while(ptr != NULL){
        if(min_occurency > ptr->was_read_by_statistician){
            min_occurency = ptr->was_read_by_statistician;
            purge_queue(dest);
            struct cell* cell_of_min = malloc(sizeof(struct cell));
            cell_cpy(ptr,cell_of_min);
            add_in_queue(cell_of_min,dest);
            cell_of_min->was_read_by_statistician = ptr->was_read_by_statistician;
        }
        else{
            if(min_occurency == ptr->was_read_by_statistician){
                struct cell* cell_of_min = malloc(sizeof(struct cell));
                cell_cpy(ptr,cell_of_min);
                add_in_queue(cell_of_min,dest);
                cell_of_min->was_read_by_statistician = ptr->was_read_by_statistician;
            }
        }
        ptr = ptr->next;
    }
}
