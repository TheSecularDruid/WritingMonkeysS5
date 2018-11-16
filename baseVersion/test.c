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
   struct monkey test_monkeyz[3];
   init_monkeys(test_monkeyz, 3);
   filter_active_monkeys(test_monkeyz, 3, main_queue, read_file);

   //effective main
   reader_work(&test_monkeyz[0], &main_queue, read_file);
   printer_work(&test_monkeyz[2], &main_queue);
   


   //Purge
   purge_queue(&main_queue);
   purge_queue(&stats_queue);
   fclose(read_file);
}
