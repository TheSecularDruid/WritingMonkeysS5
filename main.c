#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"

int main(int argc, char** argv)
{
   /* that is Kais' main
  FILE* ptr = fopen("source_text.txt","r");
  struct monkey monkeyz[3];
  printf("succes at opening file\n");
  init_monkeys(monkeyz,3);
  struct queue main_queue;
  init_queue(&main_queue);
  printf("success whiled initializing the queue\n");
  int error = reader_work(monkeyz[0],&main_queue,ptr);
  if(error)
    printf("Error : Monkey not a reader\n");
  else
    printf("success : reader work compiles\n");
  error = reader_work(monkeyz[0],&main_queue,ptr);
  if(error)
    printf("Error : Monkey not a reader\n");
  else
    printf("success : reader work compiles\n");
  print_queue(main_queue);
  purge_queue(&main_queue);
  fclose(ptr);
  return EXIT_SUCCESS;
   */

   /* that is Raph's main */
   FILE* read_file = fopen("source_text.txt", "r");
   struct queue main_queue;
   init_queue(&main_queue);
   struct monkey test_monkeyz[3];
   init_monkeys(test_monkeyz, 3);
   struct monkey test_active_monkeyz[3];
   filter_active_monkeys(test_monkeyz, test_active_monkeyz, 3, main_queue, read_file);
   struct cell* test_cell = malloc(sizeof(struct cell));
   struct cell* test_cell2 = malloc(sizeof(struct cell));
   strcpy(test_cell->word,"youhou");
   strcpy(test_cell2->word, "second");
   printf("jusqu'ici tout va bien\n");
   test_cell->was_read_by_statistician = 1;
   test_cell2->was_read_by_statistician = 1;
   add_in_queue(test_cell, &main_queue);
   add_in_queue(test_cell2, &main_queue);
   printf("la queue est chargée\n");
   print_queue(main_queue);
   printf("le singe selectionné est un %d", test_monkeyz[2].work);
   int error1 = writter_work(test_monkeyz[2], &main_queue);
   print_queue(main_queue);
   int error2 = writter_work(test_monkeyz[2], &main_queue);
   print_queue(main_queue);
   fclose(read_file);
   printf("tout s'est bien passé \n");
   printf("mais les erreurs sont %d et %d", error1, error2);
   print_queue(main_queue);
}
