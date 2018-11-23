#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "../Queue/queue.h"
#include "../Queue/successors_queue.h"

#define NUMBER_OF_MONKEYS 4

enum WORK_S { READER, STATISTICIAN, PRINTER, WRITER };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum WORK_S work;      //his activity/role
   int read_words;
   int printed_words;
};
//
//-----------------
//  Global Functions
//-----------------
//
void init_monkeys(struct monkey monkeyz[], int length);
int read_already(struct cell);
void filter_active_monkeys(struct monkey monkeyz[], int length, struct queue main_queue, FILE* filename, struct successors_queue stats);
int is_all_on_strike(struct monkey monkeyz[], int length);
void work(struct monkey* monkeyz, struct queue* main_queue, struct successors_queue* stats, FILE* filename, struct queue* writer_queue, struct cell* last_word_read); // Principal work function for the monkey
struct monkey* random_select(struct monkey monkeyz[], int length, int random);
//
//--------------------
//  Reader Monkey
//--------------------
//
int reader_work(struct monkey* reader_monkey, struct queue* main_queue, FILE* filename); //Does the work of a reader monkey
struct cell* create_cell(char* word, struct queue* main_queue); //Create a cell, put a word in and add it to the queue. Return the address of the queue newly created.
void read_a_word(char* word, FILE* filename); //Read a single word (of a maximum length of MAX_WORD_LENGTH) from filename
//
//--------------------
//  Statistician monkey
//--------------------
//
void statistician_work(struct monkey monkey, struct successors_queue* stats, struct queue* main_queue, struct cell* last_word_read);  //accomplish the work of a statistician monkey
//
//--------------------
//  Printer Monkey
//--------------------
//
int printer_work(struct monkey* monkey, struct queue* main_queue);  //execute the work of a printer monkey
//
//--------------------
//  Writer Monkey
//--------------------
//
void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue, struct queue* writer_queue); //Does the work of the greatest monkey : The writer
//
//--------------------
//  Debuggs Functions
//--------------------
//
void print_monkey(struct monkey monkey); //Print the data contained in a struct monkey
void print_monkeys(struct monkey monkeyz[], int length); //print a table of monkeyz, one by line


#endif
