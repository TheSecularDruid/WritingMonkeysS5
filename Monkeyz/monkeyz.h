#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "../Queue/queue.h"


enum WORK_S { READER, STATISTICIAN, WRITTER };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum WORK_S work;      //his activity/role
   int read_words;
   int printed_words;
};

void init_monkeys(struct monkey monkeyz[], int length);
int read_already(struct cell);
void filter_active_monkeys(struct monkey all_monkeyz[], struct monkey active_monkeyz[], int length, struct queue FIFO, FILE* filename);
int writter_work(struct monkey monkey, struct queue* FIFO);  //execute the work of a writter monkey

//
//--------------------
//  Reader Monkey
//--------------------
//
int reader_work(struct monkey reader_monkey, struct queue* main_queue, FILE* filename); //Does the work of a reader monkey
void create_cell(char* word, struct queue* main_queue); //Create a cell, put a word in and add it to the queue
void read_a_word(char* word, FILE* filename); //Read a single word (of a maximum length of MAX_WORD_LENGTH) from filename
void print_monkey(struct monkey monkey); //Print the data contained in a struct monkey
void print_monkeys(struct monkey monkeyz[], int length); //print a table of monkeyz, one by line


#endif

