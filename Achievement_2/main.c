#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue/queue.h"
#include "Monkeyz/monkeyz.h"
#include <time.h>
#include <getopt.h>

#define MAX_NUMBER_OF_ROUNDS 600


int reading_arguments(int* seed_rng, FILE** read_file_1, FILE** read_file_2, int argc, char* argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                *seed_rng = atoi(optarg);
                break;
        }
    }
    if(argc == 4 || argc == 2){
        *read_file_1 = fopen(argv[argc - 1],"r");
        *read_file_2 = fopen(argv[argc - 1],"r");
    }else{
        *read_file_1 = fopen(argv[argc - 1],"r");
        *read_file_2 = fopen(argv[argc - 2],"r");
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
    FILE* read_file_1 = NULL;
    FILE* read_file_2 = NULL;
    int seed_rng = 0;

    //Args number test. Quit the program if it doesn't have enough args.
    if(argc > 6 || argc == 1){
        print_usage();
        exit(EXIT_SUCCESS);
    }

    //Reading arguments...
    int error_code = reading_arguments(&seed_rng, &read_file_1, &read_file_2, argc, argv);
    if(error_code == 1){
        printf("Erreur lors de la lecture des arguments\n");
        exit(EXIT_FAILURE);
    }
    if(read_file_1 == NULL){
        printf("Nom de fichier incorrect ou manquant\n");
        exit(EXIT_FAILURE);
    }
    if(seed_rng == 0) //If no -s option has been declared
        srand(time(NULL));
    else
        srand(seed_rng);

    //Queue Initializing
    struct queue reader_queue_a;
    struct queue reader_queue_b;
    struct queue writer_queue_a;
    struct queue writer_queue_b;
    struct successors_queue stats_queue;
    init_queue(&reader_queue_a);
    init_queue(&reader_queue_b);
    init_queue(&writer_queue_a);
    init_queue(&writer_queue_b);
    init_successors_queue(&stats_queue);

    //Monkey initializing
    struct monkey monkeyz[NUMBER_OF_MONKEYS]; //Number of Monkeys is defined in monkeyz.h
    init_monkeys(monkeyz, NUMBER_OF_MONKEYS,&writer_queue_a,&writer_queue_b,&reader_queue_a,&reader_queue_b,read_file_1,read_file_2);

    //Initializing the writers
    strcpy(monkeyz[WRITER_1].memorized_word,".");
    monkeyz[WRITER_1].sentence_length = 0;
    monkeyz[WRITER_1].sentence_finished = 0;
    strcpy(monkeyz[WRITER_2].memorized_word,".");
    monkeyz[WRITER_2].sentence_length = 0;
    monkeyz[WRITER_2].sentence_finished = 0;
    monkeyz[WRITER_2].sentence_finished = 0;
    //End of Initialization

    //---
    // Main Algorithm
    //---
    int i = 0;
    filter_active_monkeys(monkeyz, NUMBER_OF_MONKEYS, stats_queue);
    while(!is_all_on_strike(monkeyz,NUMBER_OF_MONKEYS) && i < MAX_NUMBER_OF_ROUNDS){
        struct monkey* happy_selected_monkey = random_select(monkeyz, NUMBER_OF_MONKEYS, seed_rng);

        if(happy_selected_monkey->work != WRITER_1 && happy_selected_monkey->work != WRITER_2)
            happy_selected_monkey->work_function(happy_selected_monkey, &stats_queue, monkeyz);
        else
            if(i >= 100)
                happy_selected_monkey->work_function(happy_selected_monkey, &stats_queue, monkeyz);

        filter_active_monkeys(monkeyz, NUMBER_OF_MONKEYS, stats_queue);
        i++;
    }
    //---
    // End of Main Algorithm
    //---

    // // print_queue_light(monkeyz[READER_1].my_queue);
    // // print_queue_light(monkeyz[READER_2].my_queue);
    // print_successors_queue(stats_queue);
    // print_queue_light(monkeyz[WRITER_1].my_queue);
    // print_queue_light(monkeyz[WRITER_2].my_queue);
    // // printf("\nRead words : %d \n",monkeyz[READER_1].read_words+monkeyz[READER_2].read_words);

    //Purge
    purge_queue(&reader_queue_a);
    purge_queue(&reader_queue_b);
    purge_queue(&writer_queue_a);
    purge_queue(&writer_queue_b);
    purge_successors_queue(&stats_queue);
    fclose(read_file_1);
    fclose(read_file_2);
    //End-Purge

    return EXIT_SUCCESS;
}
