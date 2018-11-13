#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"


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
  printf("Usage : ./project [-s] FILE\n");
}


int main(int argc, char* argv[])
{
  //Init
  FILE* read_file = NULL;
  int seed_rng;
  if(argc != 2 && argc != 4){
    usage();
    return EXIT_SUCCESS;
  }
  int error_code = reading_arguments(&seed_rng, &read_file, argc, argv);
  if(error_code == 1){
    printf("Erreur lors de la lecture des arguments\n");
    return 3;
  }
  if(read_file == NULL){
    printf("Nom de fichier incorrect ou manquant\n");
    return 1;
  }
  struct queue main_queue;
  struct queue stats_queue;
  init_queue(&main_queue);
  init_queue(&stats_queue);
  struct monkey monkeyz[3];
  init_monkeys(monkeyz, 3);
  //End-Init


  filter_active_monkeys(monkeyz, 3, main_queue, read_file);
  while(!all_on_strike(monkeyz,3)){
    struct monkey happy_selected_monkey = random_select(monkeyz, 3);
    work(&happy_selected_monkey, &main_queue, &stats_queue, read_file);
    filter_active_monkeys(monkeyz, 3, main_queue, read_file);
  }

  //Purge
  purge_queue(&main_queue);
  purge_queue(&stats_queue);
  fclose(read_file);
  return EXIT_SUCCESS;
  //End-Purge
}
