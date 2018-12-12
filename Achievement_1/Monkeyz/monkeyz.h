#ifndef MONKEYZ_H
#define MONKEYZ_H

#include "../Queue/queue.h"
#include "../Queue/successors_queue.h"

#define NUMBER_OF_MONKEYZ 4

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
void init_monkeys(struct monkey monkeyz[]);
int read_already(struct cell);
void filter_active_monkeys(struct monkey monkeyz[], struct queue* main_queue, FILE* filename, struct successors_queue stats, struct queue* writer_queue);
int are_all_on_strike(struct monkey monkeyz[]);
void work(struct monkey* monkeyz, struct queue* main_queue, struct successors_queue* stats, FILE* filename, struct queue* writer_queue, struct cell* last_word_read, int* writer_sentence_length, char memorized_word[]); // Principal work function for the monkeyz
struct monkey* random_select(struct monkey monkeyz[], int random);
//
//--------------------
//  Reader Monkey
//--------------------
//
int is_a_letter(char ch); //tests whether a given character is a letter or not
int is_a_number(char ch); //tests whether a given character is a number or not
void read_a_word(char* word, FILE* filename); //Read a single word (of a maximum length of MAX_WORD_LENGTH) from filename
void to_lower_string(char* str); //Changes the case of a character string to make it into a lower case string
int reader_work(struct monkey* reader_monkey, struct queue* main_queue, FILE* filename); //Does the work of a reader monkey
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
int is_a_simple_punc_sign(char word[]); //checks whether word is a standard word/a double ponctuation sign or a simple ponctuation sign
int printer_work(struct monkey* monkey, struct queue* main_queue);  //executes the work of a printer monkey
//
//--------------------
//  Writer Monkey
//--------------------
//
void generate_punctuation(struct queue* writer_queue, int writer_sentence_length); //Generates a punctuation mark (in a new cell added to the queue) when the writer monkey needs to end a sentence.
void new_sentence(struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[]);//Does the necessary to start a sentence in optimal conditions
void continue_sentence(struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[]); //Simply checks whether the sentence shall end, and if not adds a word following the random successors procedure
void end_sentence(struct queue* writer_queue, int* writer_sentence_length);//Does the necessary to end a sentence in optimal conditions
void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[]); //Does the work of the greatest monkey : The writer
//
//--------------------
//  Debuggs Functions
//--------------------
//
void print_monkey(struct monkey monkey); //Prints the data contained in a struct monkey
void print_monkeys(struct monkey monkeyz[]); //prints a table of monkeyz, one by line


#endif
