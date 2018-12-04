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

//NEW A3
void init_monkey(struct monkey* mon, struct queue* que, enum WORK_S work, FILE* source_text)
{
    mon->status = 1;
    mon->work = work;
    mon->read_words = 0;
    mon->printed_words = 0;
    mon->my_queue = que; //NULL if the monkey doesn't have HIS queue
    mon->my_source_text = source_text; //Same
}

void init_monkeys(struct monkey monkeyz[], int length, struct queue* writer_queue_a, struct queue* writer_queue_b, struct queue* reader_queue_a, struct queue* reader_queue_b, FILE* file1, FILE* file2)
{

    init_monkey(&(monkeyz[0]),reader_queue_a,READER_1, file1);
    init_monkey(&(monkeyz[1]),reader_queue_b,READER_2, file2);
    init_monkey(&(monkeyz[2]),NULL,STATISTICIAN, NULL);
    init_monkey(&(monkeyz[3]),NULL,PRINTER,NULL);
    init_monkey(&(monkeyz[4]),writer_queue_a,WRITER_1,NULL);
    init_monkey(&(monkeyz[5]),writer_queue_b,WRITER_2,NULL);
}

int read_already(struct cell cell) {
   return cell.was_read_by_statistician;
}

//
//--------------------
// Monkeyz selection
//--------------------
//

int should_statisician_strike(const struct monkey* mon_read_1, const struct monkey* mon_read_2)
{
    if(is_queue_empty(mon_read_1->my_queue) || read_already( *(read_queue(mon_read_1->my_queue)) ))
        if(is_queue_empty(mon_read_2->my_queue) || read_already( *(read_queue(mon_read_2->my_queue)) ))
            return 1;
    return 0;
}

int should_writer_work(const struct successors_queue* stats)
{
    return !(is_successors_queue_empty(*stats));
}

int should_reader_work(const struct monkey* mon)
{
    return mon->my_source_text != NULL && !(feof(mon->my_source_text) != 0);
}

int should_printer_work(const struct monkey* writer_one, const struct monkey* writer_two)
{
    return !(is_queue_empty(writer_one->my_queue) && is_queue_empty(writer_two->my_queue));
}

void filter_active_monkeys(struct monkey monkeyz[], int length, struct successors_queue stats){
    for (int i=0;i<length;i=i+1) {
        switch(monkeyz[i].work) {
            case READER_1 :
            case READER_2 :
                monkeyz[i].status = should_reader_work(&(monkeyz[i]));
                break;
            case STATISTICIAN :
                monkeyz[i].status = !should_statisician_strike(&(monkeyz[READER_1]),&(monkeyz[READER_2]));
                break;
            case PRINTER :
                monkeyz[i].status = should_printer_work(&(monkeyz[WRITER_1]),&(monkeyz[WRITER_2]));
                break;
            case WRITER_1 :
            case WRITER_2 :
                monkeyz[i].status = should_writer_work(&stats);
                break;
        }
    }
}

int is_all_on_strike(struct monkey monkeyz[], int length)
{
    for(int i = 0; i < length; i++){
        if(monkeyz[i].status == 1)
            return 0;
    }
    return 1;
}

void work(struct monkey* monkey, struct successors_queue* stats, struct cell* last_word_read, struct monkey monkeyz[])
{
    switch (monkey->work) {
        case READER_1 :
        case READER_2 :
            reader_work(monkey);
            break;
        case STATISTICIAN:
            statistician_work(*monkey, stats, last_word_read, monkeyz);
            break;
        case PRINTER:
            printer_work(monkey,monkeyz);
            break;
        case WRITER_1 :
        case WRITER_2 :
            writer_work(monkey,stats);
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

    return &monkeyz[active_monkeyz[rand()%nb_actives]];
}

void print_active_monkeyz(struct monkey monkeyz[], int length)
{
    for(int i = 0; i < length; i++){
        if(monkeyz[i].status == 1)
            print_monkey(monkeyz[i]);
    }
    printf("--------------------------\n");
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

int reader_work(struct monkey* reader_monkey)
{
    char word[MAX_WORD_LENGTH+1] = "";
    read_a_word(word,reader_monkey->my_source_text);
    if(strcmp(word,"") != 0){
        struct cell* cell_to_add = malloc(sizeof(struct cell));
        to_lower_string(word);
        strcpy(cell_to_add->word,word);
        add_in_queue(cell_to_add,reader_monkey->my_queue);
        reader_monkey->read_words = reader_monkey->read_words + 1;
    }
    return 0;
}

//
//--------
// Statistician Monkey
//--------
//

void statistician_work(struct monkey monkey, struct successors_queue* stats, struct cell* last_word_read, struct monkey monkeyz[])
{
    struct queue* chosen_queue;
    if(!is_queue_empty(monkeyz[READER_1].my_queue))
        chosen_queue = monkeyz[READER_1].my_queue;
    else
        chosen_queue = monkeyz[READER_2].my_queue;

    struct successors_cell* researched_cell = research_word_in_successors_queue(*stats, chosen_queue->first->word);
   if (researched_cell != NULL) //if the word exist in the stats queue
        researched_cell->nb_of_occ += 1;
   else {
        struct successors_cell* word_to_analyse = malloc(sizeof(struct successors_cell));
        strcpy(word_to_analyse->word,chosen_queue->first->word);
        add_in_successors_queue(word_to_analyse, stats);
        word_to_analyse->nb_of_occ = 1;
   }

   if(strcmp(last_word_read->word,"") != 0){ //Si on a lu un mot avant
       struct successors_cell* researched_ancestor = research_word_in_successors_queue(*stats, last_word_read->word);
       struct cell* researched_suc_in_anc  = research_in_queue(&(researched_ancestor->successors), chosen_queue->first->word);
       if(researched_suc_in_anc != NULL) //The ancestor had this successor already
           researched_suc_in_anc->was_read_by_statistician++;
       else{
           struct cell* cell_to_add = malloc(sizeof(struct cell));
           strcpy(cell_to_add->word,chosen_queue->first->word);
           add_in_queue(cell_to_add,&(researched_ancestor->successors));
           cell_to_add->was_read_by_statistician = 1;
       }
   }

   strcpy(last_word_read->word,chosen_queue->first->word);
   pop_queue(chosen_queue);
}


//
//-----------
// Printer Monkey
//-----------
//

int is_a_simple_punc_sign(char word[]) {
    return( ! ( strcmp(word,",") && strcmp(word, ".") ) );
}

int printer_work(struct monkey* monkey, struct monkey monkeyz[]){
    struct queue* writer_queue;

    if(!is_queue_empty(monkeyz[WRITER_1].my_queue))
        writer_queue = monkeyz[WRITER_1].my_queue;
    else
        writer_queue = monkeyz[WRITER_2].my_queue;

    struct cell read_word = pop_queue(writer_queue);
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

void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue)
{
    struct successors_cell* ptr = NULL;

    if (ispunct(writer_monkey->memorized_word[0])){
        int length = length_successors_queue(*stats_queue);
        ptr = research_successors_cell(stats_queue,rand()%length);
        struct cell* buffer = malloc(sizeof(struct cell));
        strcpy(buffer->word,ptr->word);
        add_in_queue(buffer,writer_monkey->my_queue);
        writer_monkey->sentence_length += 1;
    } else{
        ptr = research_word_in_successors_queue(*stats_queue, writer_monkey->memorized_word);
    }

    if( (rand()%10==0) || is_queue_empty(&(ptr->successors)) ){
    	generate_punctuation(writer_monkey->my_queue, writer_monkey->sentence_length);
        strcpy(writer_monkey->memorized_word,".");
    	writer_monkey->sentence_length = 0;
    } else{
    	int length_of_suc = total_multiplicity_of_queue(&(ptr->successors));
    	struct cell* successor = nth_queue_element_with_multiplicity(&(ptr->successors), rand()%length_of_suc);
    	struct cell* buffer = malloc(sizeof(struct cell));
    	cell_cpy(successor,buffer);
    	add_in_queue(buffer,writer_monkey->my_queue);
    	writer_monkey->sentence_length += 1;
        strcpy(writer_monkey->memorized_word,successor->word);
    }
}

// void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue)
// {
//     int length = length_successors_queue(*stats_queue);
//     struct successors_cell* ptr = research_successors_cell(stats_queue,rand()%length);
//     if(is_queue_empty(&(ptr->successors))){
//          char* ponctuation[] = {",",";",".","!","?"};
//          struct cell* buffer = malloc(sizeof(struct successors_cell));
//          strcpy(buffer->word,ponctuation[rand()%5]);
//          add_in_queue(buffer,writer_monkey->my_queue);
//     } else{
//         int length_of_suc = length_queue(&(ptr->successors));
//         struct cell* successor = research_cell(&(ptr->successors),rand()%length_of_suc);
//         struct cell* buffer = malloc(sizeof(struct cell));
//         cell_cpy(successor,buffer);
//         add_in_queue(buffer,writer_monkey->my_queue);
//      }
// }

//
//-----------------
// Debuggs functions
//-----------------
//

void print_monkey(struct monkey monkey) {
   printf("status = %d (work like a happy monkey = 1, on strike = 0) | work = %d (0 = Reader, 1 = Stat., 2 = Printer, 3 = Writer) | read_words = %d | printed_words = %d \n", monkey.status, monkey.work, monkey.read_words, monkey.printed_words);
}

void print_monkeys(struct monkey monkeyz[], int length) {
   for (int i = 0; i<length; i+=1) print_monkey(monkeyz[i]);
}
