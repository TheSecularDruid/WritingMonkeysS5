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
  printf("Usage : ./main [-s] FILE\n");
}


void total_print(struct monkey monkeyz[], struct queue stats, struct queue max_occ, struct queue min_occ) {
   printf("Nombre de mots lus : %d \n", monkeyz[0].read_words);
   printf("Nombre de mots imprimés : %d \n", monkeyz[2].printed_words);
   printf("Nombre de mots différents : %d \n", length_queue(stats));
   printf("Multiplicité la plus grande : %d \n", max_occ.first->was_read_by_statistician);
   printf("atteinte par les mots : ");
   print_queue_light(max_occ);
   printf("Multiplicité la plus petite : %d \n", min_occ.first->was_read_by_statistician);
   printf("atteinte par les mots : ");
   print_queue_light(min_occ);
}

int main(int argc, char* argv[])
{
  //Initialization
  FILE* read_file = NULL;
  int seed_rng = 0;
  if(argc != 2 && argc != 4){
    print_usage();
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
  struct queue words_of_max_occurency;
  struct queue words_of_min_occurency;
  init_queue(&main_queue);
  init_queue(&stats_queue);
  init_queue(&words_of_max_occurency);
  init_queue(&words_of_min_occurency);
  struct monkey monkeyz[3];
  init_monkeys(monkeyz, 3);
  //End of Initialization

  //---
  // Main Algorithm
  //---
  filter_active_monkeys(monkeyz, 3, main_queue, read_file);
  while(!all_on_strike(monkeyz,3)){
    struct monkey* happy_selected_monkey = random_select(monkeyz, 3, seed_rng);
    if(happy_selected_monkey->work == 0)
      printf("Read words : %d\n",happy_selected_monkey->read_words);
    work(happy_selected_monkey, &main_queue, &stats_queue, read_file);

    filter_active_monkeys(monkeyz, 3, main_queue, read_file);
  }
  //---
  // End of Main Algorithm
  //---

  //Printing the result
  printf("\nWords Read : %d\n",monkeyz[0].read_words);
  struct queue max_occurency_queue;
  struct queue min_occurency_queue;
  init_queue(&max_occurency_queue);
  init_queue(&min_occurency_queue);

  greatest_occurency(stats_queue,&max_occurency_queue);
  minimal_occurency(stats_queue,&min_occurency_queue);
  printf("Maximum Occurency : \n");
  print_queue(max_occurency_queue);
  printf("Minimum Occurency : \n");
  print_queue(min_occurency_queue);
  //End Printing the result

  //Purge
  purge_queue(&main_queue);
  purge_queue(&stats_queue);
  purge_queue(&words_of_max_occurency);
  purge_queue(&words_of_min_occurency);
  fclose(read_file);
  //End-Purge

  return EXIT_SUCCESS;
}
