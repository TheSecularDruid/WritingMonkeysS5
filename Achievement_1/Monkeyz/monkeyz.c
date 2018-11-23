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

void init_monkeys(struct monkey monkeyz[], int length){
   for (int i=0;i<length;i=i+1) {
      monkeyz[i].status = 1;
      monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
      monkeyz[i].read_words = 0;
      monkeyz[i].printed_words = 0;
   }
}

int read_already(struct cell cell) {
   return cell.was_read_by_statistician;
}

//TO MODIFY
void filter_active_monkeys(struct monkey monkeyz[], int length, struct queue main_queue, FILE* filename, struct successors_queue stats){
    for (int i=0;i<length;i=i+1) {
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
                if (is_queue_empty(main_queue) || !read_already( *(read_queue(main_queue)) ))
                   monkeyz[i].status = 0;
                else
                   monkeyz[i].status = 1;
                break;
            case WRITER :
                //TODO
                monkeyz[i].status = 0;
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

void work(struct monkey* monkey, struct queue* main_queue, struct successors_queue* stats, FILE* filename, struct queue* writer_queue, struct cell* last_word_read)
{
    switch (monkey->work) {
        case READER:
            reader_work(monkey, main_queue, filename);
            break;
        case STATISTICIAN:
            statistician_work(*monkey,stats, main_queue, last_word_read);
            break;
        case PRINTER:
            printer_work(monkey, main_queue);
            break;
        case WRITER:
            //TO TEST
            // writer_work(monkey,stats,writer_queue);
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

    if(random == 0) //If no -s option has been declared
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

void read_a_word(char word[], FILE* filename)
{
    int i = 0;
    int ch = 0;
    while( ((ch = fgetc(filename)) != EOF) && ((strcmp(word, "") == 0) || (!isspace(ch) && !ispunct(ch)) || (ch==39)) ){
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

struct cell* create_cell(char* word, struct queue* main_queue)
{
  struct cell* cell_to_add = malloc(sizeof(struct cell));
  to_lower_string(word);
  strcpy(cell_to_add->word,word);
  add_in_queue(cell_to_add,main_queue);
  return cell_to_add;
}

int reader_work(struct monkey* reader_monkey, struct queue* main_queue, FILE* filename)
{
  char word[MAX_WORD_LENGTH+1] = "";
  read_a_word(word,filename);
  if(strcmp(word,"") != 0){ //Si on a lu quelque chose
    create_cell(word,main_queue);
    reader_monkey->read_words = reader_monkey->read_words + 1;
  }
  return 0;
}

//
//--------
// Statistician Monkey
//--------
//

//TO MODIFY
void statistician_work(struct monkey monkey, struct successors_queue* stats, struct queue* main_queue, struct cell* last_word_read)
{
   struct successors_cell* word_to_analyse = malloc(sizeof(struct successors_cell));
   strcpy(word_to_analyse->word,main_queue->first->word);


   struct successors_cell* researched_cell = research_word_in_successors_queue(*stats, word_to_analyse->word);
   if (researched_cell != NULL) //if the word exist in the stats queue
      researched_cell->nb_of_occ += 1;
   else {
      add_in_successors_queue(word_to_analyse, stats);
      word_to_analyse->nb_of_occ = 1;
   }

   if(strcmp(last_word_read->word,"") != 0){ //Si on a lu un mot avant
       struct successors_cell* researched_ancestor = research_word_in_successors_queue(*stats, last_word_read->word);
       struct cell* researched_suc_in_anc  = research_word_in_queue(researched_ancestor->successors, word_to_analyse->word);
       if(researched_suc_in_anc != NULL) //The ancestor had this successor already
           researched_suc_in_anc->was_read_by_statistician++;
       else{
           struct cell* created_cell = create_cell(word_to_analyse->word, &(researched_ancestor->successors));
           created_cell->was_read_by_statistician = 1;
       }
   }

   strcpy(last_word_read->word,word_to_analyse->word);
   main_queue->first->was_read_by_statistician = 1;
}


//
//-----------
// Printer Monkey
//-----------
//

int printer_work(struct monkey* monkey, struct queue* main_queue){
   if (monkey->work != PRINTER)
      return 1;
   struct cell read_word = pop_queue(main_queue);
   printf("%s ", read_word.word);
   monkey->printed_words += 1;
   return 0;
}

//
//--------
// Writer Monkey
//--------
//

//NEW TO TEST
void writer_work(struct monkey* writer_monkey, struct successors_queue* stats_queue, struct queue* writer_queue)
{
    int length = length_successors_queue(*stats_queue);
    srand(time(NULL));
    struct successors_cell* ptr = research_successors_cell(stats_queue,rand()%length);
    if(is_queue_empty(ptr->successors)){
         char* ponctuation[] = {",",";",".","!","?"};
         struct cell* buffer = malloc(sizeof(struct successors_cell));
         strcpy(buffer->word,ponctuation[rand()%5]);
         add_in_queue(buffer,writer_queue);
    } else{
         struct cell* successor = research_cell(&(ptr->successors),rand()%length);
         struct cell* buffer = malloc(sizeof(struct cell));
         cell_cpy(successor,buffer);
         add_in_queue(buffer,writer_queue);
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

void print_monkeys(struct monkey monkeyz[], int length) {
   for (int i = 0; i<length; i+=1) print_monkey(monkeyz[i]);
}
