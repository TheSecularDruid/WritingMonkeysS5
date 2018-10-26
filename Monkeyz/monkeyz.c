#include <stdio.h>
#include "../Queue/queue.h"
#include "monkeyz.h"
#include <string.h>
#include <stdlib.h>

void init_monkeys(struct monkey monkeyz[], int length){
   for (int i=0;i<length;i=i+1) {
      monkeyz[i].status = 1;
      monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
   }
}
int read_already(struct cell cell) {
   return cell.was_read_by_statistician;
}

void filter_active_monkeys(struct monkey all_monkeyz[], struct monkey active_monkeyz[], int length, struct queue FIFO, struct cell mot, FILE* filename){
   int j = 0;
   for (int i=0;i<length;i=i+1) {
      switch(all_monkeyz[i].work) {
      case READER :
	 if (fgets("",0,filename)==NULL)
	    all_monkeyz[i].status = 0;
	 else {
	    active_monkeyz[j] = all_monkeyz[i];
	    j = j+1; }
	 break;
      case STATISTICIAN :
	 if (is_queue_empty(FIFO)||read_already( *(read_queue(FIFO)) ))
	    all_monkeyz[i].status = 0;
	 else {
	    active_monkeyz[j] = all_monkeyz[i];
	    j = j+1; }
	 break;
      case WRITTER :
	 if (is_queue_empty(FIFO)||!read_already( *(read_queue(FIFO)) ))
	    all_monkeyz[i].status = 0;
	 else {
	    active_monkeyz[j] = all_monkeyz[i];
	    j = j + 1; }
    }
  }
}

int writter_work(struct monkey monkey, struct queue FIFO){
   if (monkey.work != READER)
      return 1;
   struct cell read_word = pop_queue(FIFO);
   printf("%s", read_word.word);
   monkey.printed_words += 1;
   return 0;
}



void read_a_word(char* word, FILE* filename)
{
  for(int i = 0; i < MAX_WORD_LENGTH; i++){
    char* buffer = malloc(sizeof(char*));
    fgets(buffer, 1, filename);
    printf("%s\n",buffer);
    if(*buffer ==  ' ')
      break;
    else
      word[i] = *buffer;
    free(buffer);
    }
    word[MAX_WORD_LENGTH+1] = 0;
}

void create_cell(char* word, struct queue* main_queue)
{
  struct cell* cell_to_add = malloc(sizeof(struct cell));
  strcpy(cell_to_add->word,word);
  add_in_queue(cell_to_add,main_queue);
  printf("cell_to_add word : %s\n",cell_to_add->word);
}

int reader_work(struct monkey reader_monkey, struct queue* main_queue, FILE* filename)
{
  if(reader_monkey.work != READER)
    return 1;

  char word[MAX_WORD_LENGTH+1];
  read_a_word(word,filename);
  create_cell(word,main_queue);
  return 0;
}
