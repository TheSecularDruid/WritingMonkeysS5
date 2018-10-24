#include <stdio.h>
#include <stdlib.h>
#include "queue/queue.h"

int main(int argc, char** argv)
{
  struct cell* c = malloc(sizeof(struct cell));
  struct cell* cc = malloc(sizeof(struct cell));
  struct cell* ccc = malloc(sizeof(struct cell));
  struct cell* cccc = malloc(sizeof(struct cell));

  struct queue main_queue;
  init_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  add_in_queue(cccc,&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  add_in_queue(ccc,&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  add_in_queue(cc,&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  remove_in_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  remove_in_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  remove_in_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  remove_in_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);
  remove_in_queue(&main_queue);
  printf("first : %d\n", main_queue.first);
  printf("last : %d\n", main_queue.last);


  return EXIT_SUCCESS;
}
