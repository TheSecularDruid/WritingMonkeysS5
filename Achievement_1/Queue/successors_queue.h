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
struct successors_cell* research_in_successors_queue(struct successors_queue source, char* word);


#endif
