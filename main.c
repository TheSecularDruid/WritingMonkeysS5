#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"

int main(int argc, char** argv)
{
   //Init
   FILE* read_file = fopen("source_text.txt", "r");
   struct queue main_queue;
   struct queue stats_queue;
   init_queue(&main_queue);
   init_queue(&stats_queue);
   struct monkey monkeyz[3];
   init_monkeys(monkeyz, 3);
   //End-Init

   while(!all_on_strike(monkeyz)){
        filter_active_monkeys(monkeyz, 3, main_queue, read_file);
        struct monkey* happy_selected_monkey = random_select(struct monkey monkeyz[], int length);
        work(happy_selected_monkey);
   }


   //Purge
   purge_queue(&main_queue);
   purge_queue(&stats_queue);
   fclose(read_file);
   //End-Purge
}
