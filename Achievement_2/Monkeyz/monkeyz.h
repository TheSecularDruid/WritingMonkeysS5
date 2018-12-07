#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "../Queue/queue.h"
#include "../Queue/successors_queue.h"

enum WORK_S { READER_1, READER_2, STATISTICIAN, PRINTER, WRITER_1, WRITER_2, NUMBER_OF_MONKEYS };

struct monkey {
   int status ;         //boolean, equals 0 if on strike, 1 if active
   enum WORK_S work;      //his activity/role
   int read_words;
   int printed_words;
   struct queue* my_queue; //NEW A3
   FILE* my_source_text;
   char memorized_word[MAX_WORD_LENGTH];
   int sentence_length;
   int sentence_finished;
};
//
//-----------------
//  Global Functions
//-----------------
//
void init_monkey(struct monkey* mon, struct queue* que, enum WORK_S work, FILE* source_text); //Init only one monkey
void init_monkeys(struct monkey monkeyz[], int length, struct queue* writer_queue_a, struct queue* writer_queue_b, struct queue* reader_queue_a, struct queue* reader_queue_b, FILE* file1, FILE* file2);
int read_already(struct cell);
//
//----------------
//  Monkeyz Selection
//----------------
//
int should_statisician_work(const struct monkey* mon_read_1, const struct monkey* mon_read_2);
int should_writer_work(const struct successors_queue* stats, struct monkey* writer_monkey);
int should_reader_work(const struct monkey* mon);
int should_printer_work(const struct monkey* writer_one, const struct monkey* writer_two);
void filter_active_monkeys(struct monkey monkeyz[], int length, struct successors_queue stats);
int is_all_on_strike(struct monkey monkeyz[], int length);
void work(struct monkey* monkey, struct successors_queue* stats, struct cell* last_word_read, struct monkey monkeyzz[]); // Principal work function for the monkey
struct monkey* random_select(struct monkey monkeyz[], int length, int random);
//
//--------------------
//  Reader Monkey
//--------------------
//
int reader_work(struct monkey* reader_monkey); //Does the work of a reader monkey
void read_a_word(char* word, FILE* filename); //Read a single word (of a maximum length of MAX_WORD_LENGTH) from filename
int is_a_letter(char ch); //tests whether a given character is a letter or not
int is_a_number(char ch); //tests whether a given character is a number or not
//
//--------------------
//  Statistician monkey
//--------------------
//
void statistician_work(struct monkey monkey, struct successors_queue* stats, struct cell* last_word_read, struct monkey monkeyz[]);  //accomplish the work of a statistician monkey
//
//--------------------
//  Printer Monkey
//--------------------
//
int is_a_simple_punc_sign(char word[]); //check wether word is a standard word/a double ponctuation sign or a simple ponctuation sign
int printer_work(struct monkey* monkey, struct monkey monkeyz[]);  //execute the work of a printer monkey
//
//--------------------
//  Writer Monkey
//--------------------
//
void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue); //Does the work of the greatest monkey : The writer
//
//--------------------
//  Debuggs Functions
//--------------------
//
void print_monkey(struct monkey monkey); //Print the data contained in a struct monkey
void print_monkeys(struct monkey monkeyz[], int length); //print a table of monkeyz, one by line


#endif
