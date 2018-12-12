#ifndef QUEUE_H
#define QUEUE_H

#define MAX_WORD_LENGTH 20

struct cell{
  char word[MAX_WORD_LENGTH+1];
  int was_read_by_statistician;
  struct cell* next;
};

struct queue{
  struct cell* first;
  struct cell* last;
};

void init_queue(struct queue* source); //Initializes the queue properly (Initializes first and last to NULL)
int is_queue_empty(struct queue* source); //Checks whether the queue is empty
void add_in_queue(struct cell* toAdd, struct queue* source); //Adds a cell to the queue
struct cell* read_queue(struct queue* source); //Reads (WITHOUT DELETING IT) the oldest cell of the queue
void remove_in_queue(struct queue* source); //Removes the oldest cell of the queue
struct cell pop_queue(struct queue* source); //Removes the oldest cell from the queue and returns it
int length_queue(struct queue* queue); //Returns the length of a queue given in argument
void print_queue(struct queue* queue_to_print); //Prints the queue with every information
void print_queue_light(struct queue* queue);//Prints the words contained in the queue, separated by periods
void queue_cpy(struct queue* source, struct queue* dest); //Copy every cell of a queue to another one
void purge_queue(struct queue* queue_to_purge); //Purges (deletes every cell) the queue
struct cell* research_in_queue(struct queue* source, char* word_to_search); //Searches a cell in a queue with the word_to_search word as a criterion, returns NULL if the word of the cell isn't found, the adress of the cell otherwise
struct cell* research_cell(struct queue* source, int position); //Returns the cell at the given position, returns NULL if position is greater than the length of the queue
void cell_cpy(struct cell* source, struct cell* dest); //Copies a cell
void print_cell(struct cell* cell_to_print); //Prints a cell
int total_multiplicity_of_queue(const struct queue* source);//Returns the sum of the multiplicities of all cells in the queue
struct cell* nth_queue_element_with_multiplicity(const struct queue* source, int n);//Returns the nth cell, each cell being counted with its multiplicity (ex a cell having a multiplicity of 3 will be counted thrice), used for ponderated random choices

#endif
