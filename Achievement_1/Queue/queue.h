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

void add_in_queue(struct cell* toAdd, struct queue* source); //Adding a cell to the queue
void remove_in_queue(struct queue* source); //Removing the oldest cell of the queue
struct cell* read_queue(struct queue source); //Reading (AND NOT DELETE) the oldest cell of the queue
int is_queue_empty(struct queue source); //Checking if the queue is empty
void init_queue(struct queue* source); //Initializing the queue properly (Initializing first and last to NULL)
struct cell pop_queue(struct queue* source); //Just a pop goddamit (yet I couldn't do it properly)
void print_queue(struct queue queue_to_print); //print the queue
void purge_queue(struct queue* queue_to_purge); //Purge (delete all cells) the queue
struct cell* research_word_in_queue(struct queue source, char* word_to_search); //Search a cell in a queue with the word_to_search word, return NULL if the word of the cell isn't found, the adress to the cell otherwise
struct cell* research_cell(struct queue* source, int position); //Return the cell at the given position, if the cell doesn't exit, return NULL
void cell_cpy(struct cell* source, struct cell* dest); //Copy a cell
void print_cell(struct cell* cell_to_print); //Print a cell
int length_queue(struct queue queue); //Returns the length of a queue given in argument
void print_queue_light(struct queue queue);//Prints the words contained in the queue, separated by periods
void queue_cpy(struct queue* source, struct queue* dest); //Copy every cell of a queue to another one
//--
// Stats functions
//--
void greatest_occurency(struct queue source, struct queue* dest); //Put in the queue dest the maximum(s) Occurency(ies) (only usable with the stats queue)
void minimal_occurency(struct queue source, struct queue* dest); //Put in the queue dest the minimum(s) Occurency(ies) (only usable with the stats queue)

#endif
