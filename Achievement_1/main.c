#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"
#include <time.h>

#define MAX_NUMBER_OF_ROUNDS 300


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
        printf("YO\n");
        return 1;
    }
    struct queue main_queue;
    struct successors_queue stats_queue;
    struct queue writer_queue;
    struct queue words_of_max_occurency;
    struct queue words_of_min_occurency;
    init_queue(&main_queue);
    init_queue(&writer_queue);
    init_successors_queue(&stats_queue);
    init_queue(&words_of_max_occurency);
    init_queue(&words_of_min_occurency);
    struct monkey monkeyz[NUMBER_OF_MONKEYZ]; //Number of Monkeys is defined in monkeyz.h
    init_monkeys(monkeyz);
    struct cell last_word_read;
    strcpy(last_word_read.word,"");
    if(seed_rng == 0) //If no -s option has been declared
        srand(time(NULL));
    else
        srand(seed_rng);

    char memorized_word[MAX_WORD_LENGTH] = {'.'};
    int writer_sentence_length = 0;
    //End of Initialization

    //---
    // Main Algorithm
    //---
    int i = 0;
    filter_active_monkeys(monkeyz, &main_queue, read_file, stats_queue, &writer_queue);
    while(!are_all_on_strike(monkeyz) && i < MAX_NUMBER_OF_ROUNDS){
        struct monkey* happy_selected_monkey = random_select(monkeyz, seed_rng);
        if(happy_selected_monkey->work != WRITER || i > 100){
	    work(happy_selected_monkey, &main_queue, &stats_queue, read_file, &writer_queue, &last_word_read, &writer_sentence_length, memorized_word);
        }
      filter_active_monkeys(monkeyz, &main_queue, read_file, stats_queue, &writer_queue);
      i++;
    }
    //---
    // End of Main Algorithm
    //---

    printf("\nRead words : %d \n",monkeyz[0].read_words);
    //Purge
    purge_queue(&main_queue);
    purge_queue(&writer_queue);
    purge_successors_queue(&stats_queue);
    purge_queue(&words_of_max_occurency);
    purge_queue(&words_of_min_occurency);
    fclose(read_file);
    //End-Purge

    return EXIT_SUCCESS;
}
