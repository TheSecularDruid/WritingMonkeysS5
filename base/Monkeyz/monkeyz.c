#include <stdio.h>
#include "../Queue/queue.h"
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

void init_monkeys(struct monkey monkeyz[], int length){
    for (int i=0;i<length&&i<NUMBER_OF_MONKEYZ;i=i+1) {
    	monkeyz[i].status = 1;
    	monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
    	monkeyz[i].read_words = 0;
    	monkeyz[i].printed_words = 0;
    }
}

int read_already(struct cell cell) {
    return cell.was_read_by_statistician;
}

void filter_active_monkeys(struct monkey monkeyz[], int length, struct queue FIFO, FILE* filename){
    for (int i=0;i<length;i=i+1) {
    switch(monkeyz[i].work) {
        case READER :
            if (feof(filename)!=0)
                monkeyz[i].status = 0;
            else
                monkeyz[i].status = 1;
            break;
        case STATISTICIAN :
            if (is_queue_empty(&FIFO)||read_already( *(read_queue(&FIFO)) ))
                monkeyz[i].status = 0;
            else
                monkeyz[i].status = 1;
            break;
        case PRINTER :
            if (is_queue_empty(&FIFO)||!read_already( *(read_queue(&FIFO)) ))
                monkeyz[i].status = 0;
            else
                monkeyz[i].status = 1;
            break;
        }
    }
}


int all_on_strike(struct monkey monkeyz[])
{
    for(int i = 0; i < NUMBER_OF_MONKEYZ; i++){
	if(monkeyz[i].status == 1)
	    return 0;
    }
    return 1;
}

void work(struct monkey* monkey, struct queue* main_queue, struct queue* stats, FILE* filename)
{
    switch (monkey->work) {
    case READER:
    	reader_work(monkey, main_queue, filename);
    	break;
    case STATISTICIAN:
    	statistician_work(stats, main_queue);
    	break;
    case PRINTER:
    	printer_work(monkey, main_queue);
    	break;
    }
}

struct monkey* random_select(struct monkey monkeyz[], int length, int random) {
    int nb_actives = 0;
    int active_monkeyz[length];
    for (int i=0;i<length; i++) {
    	if (monkeyz[i].status==1) {
    	    active_monkeyz[nb_actives] = i;
    	    nb_actives += 1;
    	}
    }
    if(random == 0)
	   srand(time(NULL));
    else
	   srand(random);

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

void statistician_work(struct queue* stats, struct queue* main_queue) {
    struct cell* cell_to_inc = research_in_queue(stats, main_queue->first->word);
    if (cell_to_inc != NULL){ //if the word exist in the stats queue
        cell_to_inc->was_read_by_statistician += 1;
    }
    else {
        struct cell* first_word = malloc(sizeof(struct cell));
        struct cell* ptr = main_queue->first;
        cell_cpy(ptr,first_word);
        add_in_queue (first_word, stats);
        stats->last->was_read_by_statistician += 1;
    }
    main_queue->first->was_read_by_statistician = 1;
}


//
//-----------
// Printer Monkey
//-----------
//

int printer_work(struct monkey* monkey, struct queue* main_queue){
    struct cell read_word = pop_queue(main_queue);
    printf("%s ", read_word.word);
    monkey->printed_words += 1;
    return 0;
}


//
//-----------------
// Debuggs functions
//-----------------
//

void print_monkey(struct monkey monkey) {
    printf("status = %d, work = %d (0 = reader, 1 = statistician, 2 = printer, more = error, read_words = %d, printed_words = %d \n", monkey.status, monkey.work, monkey.read_words, monkey.printed_words);
}

void print_monkeys(struct monkey monkeyz[], int length) {
    for (int i = 0; i<length; i+=1) print_monkey(monkeyz[i]);
}
