#ifndef SUCCESSORS_QUEUE_H
#define SUCCESSORS_QUEUE_H

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

void init_successors_queue(struct successors_queue* succ_queue);
int is_successors_queue_empty(struct successors_queue succ_queue);
void add_in_successors_queue(struct successors_cell* to_add, struct successors_queue* source);
struct successors_cell* read_successors_queue(struct successors_queue source);
void remove_in_successors_queue(struct successors_queue* source);
struct successors_cell pop_successors_queue(struct successors_queue* source);
struct successors_cell* research_word_in_successors_queue(struct successors_queue source, char* word);
void purge_successors_queue(struct successors_queue* to_purge); //Purge an entire queue
struct successors_cell* research_successors_cell(struct successors_queue*, int position); //return the cell at the given position, NULL if doesn't exist
int length_successors_queue(struct successors_queue stats_queue); //Return the length of the queue (i.e the number of cells)
void successors_cell_cpy(struct successors_cell* source, struct successors_cell* dest); //Copy a successor cell properly
void print_successors_queue(struct successors_queue queue_to_print); //Print the whole queue


#endif
