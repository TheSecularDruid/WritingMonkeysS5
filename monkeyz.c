#include <stdio.h>

void init_monkeys(struct monkey monkeyz[], int length){
   for (int i=0;i<length;i=i+1) {
      monkeyz[i].status = 1;
      monkeyz[i].work = i ;      //each monkey is initialized with a different activity, granted there is as much or more activities than there are monkeys
   }
}
int read_already(struct cell cell) {
   return cell.was_read_by_statistician;
}

void filter_active_monkeys(struct monkey all_monkeyz[], struct monkey active_monkeyz[], int length, struct queue FIFO, struct cell mot){
   int j = 0;
   for (int i=0;i<length;i=i+1) {
      switch(all_monkeyz[i].work) {
      case READER :
	 if (fgets("",0,TEXTFILE)==NULL)
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
	    j = j + 1}
      }
   }
}

int writter_work(struct monkey monkey, struct queue FIFO){
   if (monkey.work != READER)
      return 1;
   struct cell read_word = pop_queue(FIFO);
   printf("%s", read_word.word)
   monkey.printed_words += 1;   
}

