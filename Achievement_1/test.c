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
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  printf("lecture\n");
  char word[] = ";";
  create_cell(word, &main_queue);
  printf("creat_cell \n");
  reader_work(&monkeyz[0], &main_queue, read_file);
  reader_work(&monkeyz[0], &main_queue, read_file);
  printf("lecture 2\n");
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);
  printer_work(&monkeyz[2], &main_queue);

  printf("printer\n");
  
  print_monkeys(monkeyz, 3);
  //Purge
  purge_queue(&main_queue);
  purge_queue(&stats_queue);
  purge_queue(&words_of_max_occurency);
  purge_queue(&words_of_min_occurency);
  fclose(read_file);
  //End-Purge
}
