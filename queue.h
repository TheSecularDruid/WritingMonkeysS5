#define MAX_WORD_LENGTH 64

struct cell{
  char word[MAX_WORD_LENGTH];
  struct cell* next;
};

struct queue{
  struct cell* first;
  struct cell* last;
};

void add_in_queue(struct cell* toAdd, struct queue* source);
void remove_in_queue(struct queue* source);
struct cell* read_first(struct queue source);
int is_empty(struct queue source);
void init_queue(struct queue source);
