#include <stdio.h>
#include "../Queue/queue.h"
#include "../Queue/successors_queue.h"
#include "monkeyz.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//
//-------------------------
// Monkeyz global functions
//-------------------------
//

void init_monkeys(struct monkey monkeyz[]){
   for (int i=0;i<NUMBER_OF_MONKEYZ;i=i+1) {
      monkeyz[i].status = 1;
      monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
      monkeyz[i].read_words = 0;
      monkeyz[i].printed_words = 0;
   }
}

int read_already(struct cell cell) {
   return cell.was_read_by_statistician;
}

void filter_active_monkeys(struct monkey monkeyz[], struct queue* main_queue, FILE* filename, struct successors_queue stats, struct queue* writer_queue){
    for (int i=0;i<NUMBER_OF_MONKEYZ;i=i+1) {
        switch(monkeyz[i].work) {
            case READER :
                if (feof(filename)!=0)
                   monkeyz[i].status = 0;
                else
                   monkeyz[i].status = 1;
                break;
            case STATISTICIAN :
                if (is_queue_empty(main_queue) || read_already( *(read_queue(main_queue)) ))
                   monkeyz[i].status = 0;
                else
                   monkeyz[i].status = 1;
                break;
            case PRINTER :
                if (is_queue_empty(writer_queue))
                   monkeyz[i].status = 0;
                else
                   monkeyz[i].status = 1;
                break;
            case WRITER :
                if(is_successors_queue_empty(stats))
                    monkeyz[i].status = 0;
                else
                    monkeyz[i].status = 1;
                break;
        }
    }
}


int are_all_on_strike(struct monkey monkeyz[])
{
    for(int i = 0; i < NUMBER_OF_MONKEYZ; i++){
        if(monkeyz[i].status == 1)
            return 0;
    }
    return 1;
}

void work(struct monkey* monkey, struct queue* main_queue, struct successors_queue* stats, FILE* filename, struct queue* writer_queue, struct cell* last_word_read, int* writer_sentence_length, char memorized_word[])
{
    switch (monkey->work) {
        case READER:
            reader_work(monkey, main_queue, filename);
            break;
        case STATISTICIAN:
            statistician_work(*monkey,stats, main_queue, last_word_read);
            break;
        case PRINTER:
            printer_work(monkey, writer_queue);
            break;
        case WRITER:
            writer_work(monkey,stats,writer_queue, writer_sentence_length, memorized_word);
            break;
    }
}

struct monkey* random_select(struct monkey monkeyz[], int random) {
    int nb_actives = 0;
    int active_monkeyz[NUMBER_OF_MONKEYZ];
    for (int i=0;i<NUMBER_OF_MONKEYZ; i++) {
        if (monkeyz[i].status==1) {
          active_monkeyz[nb_actives] = i;
          nb_actives += 1;
        }
    }

    return &monkeyz[active_monkeyz[rand()%nb_actives]];
}

//
//--------------------------
// Reader Monkey
//--------------------------
//
int is_a_letter(char ch) {
    return ( (ch > 64 && ch < 91)||( ch > 96 && ch < 123) );
}

int is_a_number(char ch) {
    return ( ch > 47 && ch < 58 );
}

void read_a_word(char word[], FILE* filename)
{
    int i = 0;
    int ch = 0;
    while( ((ch = fgetc(filename)) != EOF)   //we're in word while the end of file is not reached
	   && ( is_a_letter(ch) || is_a_number(ch) || ch==45 || ch==39 ) //and the character read is either a letter or a hyphen (ch==45) or an apostrophe (ch==39)
	   && (i < MAX_WORD_LENGTH) ) //and the word isn't longer than supposed possible

	{
	    word[i] = ch;
	    i++;
	}
    word[i] = 0;
}

void to_lower_string(char* str)
{
    while(*str) {
    	*str = tolower(*str);
    	str++;
    }
}

int reader_work(struct monkey* reader_monkey, struct queue* main_queue, FILE* filename)
{
    char word[MAX_WORD_LENGTH+1] = "";
    read_a_word(word,filename);
    if(strcmp(word,"") != 0){
        struct cell* cell_to_add = malloc(sizeof(struct cell));
        to_lower_string(word);
        strcpy(cell_to_add->word,word);
        add_in_queue(cell_to_add,main_queue);
        reader_monkey->read_words = reader_monkey->read_words + 1;
    }
    return 0;
}

//
//--------
// Statistician Monkey
//--------
//

void statistician_work(struct monkey monkey, struct successors_queue* stats, struct queue* main_queue, struct cell* last_word_read)
{


   struct successors_cell* researched_cell = research_word_in_successors_queue(stats, main_queue->first->word);
   if (researched_cell != NULL) //if the word exist in the stats queue
        researched_cell->nb_of_occ += 1;
   else {
        struct successors_cell* word_to_analyse = malloc(sizeof(struct successors_cell));
        strcpy(word_to_analyse->word,main_queue->first->word);
        add_in_successors_queue(word_to_analyse, stats);
        word_to_analyse->nb_of_occ = 1;
   }

   if(strcmp(last_word_read->word,"") != 0){ //Si on a lu un mot avant
       struct successors_cell* researched_ancestor = research_word_in_successors_queue(stats, last_word_read->word);
       struct cell* researched_suc_in_anc  = research_in_queue(&(researched_ancestor->successors), main_queue->first->word);
       if(researched_suc_in_anc != NULL) //The ancestor had this successor already
           researched_suc_in_anc->was_read_by_statistician++;
       else{
           struct cell* cell_to_add = malloc(sizeof(struct cell));
           strcpy(cell_to_add->word,main_queue->first->word);
           add_in_queue(cell_to_add,&(researched_ancestor->successors));
           cell_to_add->was_read_by_statistician = 1;
       }
   }

   strcpy(last_word_read->word,main_queue->first->word);
   pop_queue(main_queue);
}


//
//-----------
// Printer Monkey
//-----------
//

int is_a_simple_punc_sign(char word[]) {
    return( ! ( strcmp(word,",") && strcmp(word, ".") ) );
}

int printer_work(struct monkey* monkey, struct queue* writter_queue){
    struct cell read_word = pop_queue(writter_queue);
    if (is_a_simple_punc_sign(read_word.word))
	   printf("\b%s ", read_word.word);
    else
	   printf("%s ", read_word.word);
    monkey->printed_words += 1;
    return 0;
}

//
//--------
// Writer Monkey
//--------
//

void generate_punctuation(struct queue* writer_queue, int writer_sentence_length) {
    if (writer_sentence_length==1) {
	struct cell* buffer = malloc(sizeof(struct cell));
	strcpy(buffer->word,"!");
	add_in_queue(buffer,writer_queue);
    }
    else {
	char* punctuation[] = {"...",".","!","?"};
	struct cell* buffer = malloc(sizeof(struct cell));
	strcpy(buffer->word,punctuation[rand()%4]);
	add_in_queue(buffer,writer_queue);
    }
}

void new_sentence(struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[]) {
    int length = length_successors_queue(*stats_queue);
    struct successors_cell* random_word = research_successors_cell(stats_queue, rand()%length);
    struct cell* new_word = malloc(sizeof(struct cell));
    strcpy(new_word->word,random_word->word);
    add_in_queue(new_word, writer_queue);
    strcpy(memorized_word,random_word->word);
    *writer_sentence_length = 1;
}

void continue_sentence(struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[]) {
    struct successors_cell* selected_word = research_word_in_successors_queue(stats_queue, memorized_word);
    if ( (rand()%10!=0) && !is_queue_empty(&(selected_word->successors)) ){ //for the 10% chance to randomly interrupt a sentence, ie 90% chance to normally continue it
	struct cell* successor = random_successor(selected_word);
	struct cell* written_word = malloc(sizeof(struct cell));
	cell_cpy(successor,written_word);
	add_in_queue(written_word,writer_queue);
	*writer_sentence_length+=1;
	strcpy(memorized_word,written_word->word);
    }
    else
	end_sentence(writer_queue, writer_sentence_length);
}

void end_sentence(struct queue* writer_queue, int* writer_sentence_length){
    generate_punctuation(writer_queue, *writer_sentence_length);
    *writer_sentence_length = 0;
}

void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue, struct queue* writer_queue, int* writer_sentence_length, char memorized_word[])
{
    if (*writer_sentence_length==0){
	new_sentence(stats_queue, writer_queue, writer_sentence_length, memorized_word);
    } else {
	continue_sentence(stats_queue, writer_queue, writer_sentence_length, memorized_word);
    }
}

//
//-----------------
// Debuggs functions
//-----------------
//

void print_monkey(struct monkey monkey) {
   printf("status = %d (work like a happy monkey = 1, on strike = 0) | work = %d (0 = Reader, 1 = Stat., 2 = Printer, 3 = Writer) | read_words = %d | printed_words = %d \n", monkey.status, monkey.work, monkey.read_words, monkey.printed_words);
}

void print_monkeys(struct monkey monkeyz[]) {
   for (int i = 0; i<NUMBER_OF_MONKEYZ; i+=1) print_monkey(monkeyz[i]);
}
