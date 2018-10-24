#define MAX_WORD_LENGTH 64

struct cell{
  char word[MAX_WORD_LENGTH+1];
  struct cell* next;
};

struct queue{
  struct cell* first;
  struct cell* last;
};

void add_in_queue(struct cell* toAdd, struct queue* source); //Adding a cell to the queue
void remove_in_queue(struct queue* source); //Removing the oldest cell of the queue
struct cell* read_queue(struct queue source); //Reading the oldest cell of the queue
int is_queue_empty(struct queue source); //Checking if the queue is empty
void init_queue(struct queue* source); //Initializing the queue properly
