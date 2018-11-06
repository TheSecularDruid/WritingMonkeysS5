#include <stdio.h>
#include <stdlib.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"

int main(int argc, char** argv)
{
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
}
