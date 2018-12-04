#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Monkeyz/monkeyz.h"
#include "Queue/queue.h"
#include "Queue/successors_queue.h"

int reading_arguments(int* seed_rng, FILE** read_file, int argc, char* argv[])
{
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i],"-s") == 0){
      if(i == argc - 1)
        return 1; //Error
      *seed_rng = atoi(argv[i+1]);
    }
    if( (strcmp(argv[i-1],"-s") != 0) && (strcmp(argv[i],"-s") != 0) ){
      *read_file = fopen(argv[i],"r");
    }
  }
  return 0;
}

void print_args(int argc, char* argv[])
{
  for(int i = 0; i < argc; i++)
  {
    printf("%s \n",argv[i]);
  }
}

void print_usage()
{
  printf("Usage : ./main [-s] FILE\n");
}


int main(int argc, char* argv[])
{

}
