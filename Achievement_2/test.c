#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Monkeyz/monkeyz.h"
#include "Queue/queue.h"
#include "Queue/successors_queue.h"
#include <assert.h>

//For coloured output
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define QUEUE_LENGTH_TST_NB 6
#define CELL_MODIF_NB 2

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

int initialization_queue_test(struct queue* queue)
{
    if(queue->first != NULL)
        return 1;
    return 0;
}

void create_cells(int nb_of_cells, struct queue* queue)
{
    for(int i = 0 ; i < nb_of_cells; i++)
    {
        struct cell* cell = malloc(sizeof(struct cell));
        add_in_queue(cell,queue);
    }
}

int test_length(struct queue* queue, int nb_to_test)
{
    if(length_queue(queue) != nb_to_test)
        return 1;
    return 0;
}

void print_cell_stress_test_results(int nb_errors, int nb_test)
{
    int success = nb_test - nb_errors;
    printf(GRN "%d/%d success" RESET "\n", success, nb_test);
    printf(RED "%d" RESET " failed\n",nb_errors);
}

void delete_cells(int nb_to_del,struct queue* queue)
{
    for(int i = 0; i < nb_to_del; i++)
    {
        pop_queue(queue);
    }
}

int  cell_stress_test(int nb_of_cells)
{
    struct queue myqueue;
    init_queue(&myqueue);
    int er = initialization_queue_test(&myqueue);
    if(er)
        return 1;

    printf("Adding %d cells...\n", nb_of_cells);
    //Test if the length of the queue is correct
    create_cells(nb_of_cells,&myqueue);
    er = test_length(&myqueue,nb_of_cells);
    delete_cells(nb_of_cells/2,&myqueue);
    er += test_length(&myqueue,nb_of_cells/2);
    purge_queue(&myqueue);
    er += test_length(&myqueue,0);
    print_cell_stress_test_results(er,QUEUE_LENGTH_TST_NB);

    return 0;
}

int queue_test()
{
    printf("Stress Test : \n");
    int er = cell_stress_test(500);
    if(er)
        return 1;
    er = cell_stress_test(1500);
    if(er)
        return 1;
    er = cell_stress_test(2000);
    if(er)
        return 1;
    er = cell_stress_test(4000);
    if(er)
        return 1;
    er = cell_stress_test(8000);
    if(er)
        return 1;
    er = cell_stress_test(120000);
    if(er)
        return 1;

    return 0;
}

void pop_queue_test(struct queue* queue)
{
    printf("Testing pop queue...\n");

    struct cell* cellb = malloc(sizeof(struct cell));
    struct cell* cella = malloc(sizeof(struct cell));
    strcpy(cella->word,"A");
    strcpy(cellb->word,"B");
    add_in_queue(cella,queue);
    add_in_queue(cellb,queue);

    struct cell popped = pop_queue(queue);

    assert(strcmp(popped.word,"A") == 0);
    assert(strcmp(queue->first->word,"B") == 0);

    printf(GRN "OK\n" RESET);
}

void purge_queue_test(struct queue* queue)
{
    printf("Testing purge queue...\n");

    struct cell* cellb = malloc(sizeof(struct cell));
    struct cell* cella = malloc(sizeof(struct cell));
    add_in_queue(cella,queue);
    add_in_queue(cellb,queue);

    purge_queue(queue);

    assert(is_queue_empty(queue));
    assert(length_queue(queue) == 0);

    printf(GRN "OK\n" RESET);

}

void research_in_queue_test(struct queue* queue)
{
    printf("Testing research in queue...\n");

    struct cell* cella = malloc(sizeof(struct cell));
    struct cell* cellb = malloc(sizeof(struct cell));
    struct cell* cellc = malloc(sizeof(struct cell));
    struct cell* celld = malloc(sizeof(struct cell));
    struct cell* celle = malloc(sizeof(struct cell));
    strcpy(cella->word,"cella");
    strcpy(cellb->word,"cellb");
    strcpy(cellc->word,"cellc");
    strcpy(celld->word,"celld");
    strcpy(celle->word,"celld");

    add_in_queue(cella,queue);
    add_in_queue(cellb,queue);
    add_in_queue(cellc,queue);
    add_in_queue(celld,queue);
    add_in_queue(celle,queue);

    struct cell* result = research_in_queue(queue,"celld");

    assert(strcmp(result->word,"celld") == 0);

    printf(GRN "OK\n" RESET);
}

void reader_work_cond_test(FILE* filename,FILE* filename2)
{
    FILE* read_file_1 = filename;
    FILE* read_file_2 = filename2;

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

    struct monkey monkeyz[NUMBER_OF_MONKEYS];
    init_monkeys(monkeyz, NUMBER_OF_MONKEYS,&writer_queue_a,&writer_queue_b,&reader_queue_a,&reader_queue_b,read_file_1,read_file_2);

    strcpy(monkeyz[WRITER_1].memorized_word,".");
    monkeyz[WRITER_1].sentence_length = 0;
    monkeyz[WRITER_1].sentence_finished = 0;
    strcpy(monkeyz[WRITER_2].memorized_word,".");
    monkeyz[WRITER_2].sentence_length = 0;
    monkeyz[WRITER_2].sentence_finished = 0;
    monkeyz[WRITER_2].sentence_finished = 0;

    printf("Testing reader monkey working conditions...\n");
    assert(should_reader_work(&monkeyz[READER_1]) == 1);
    assert(should_reader_work(&monkeyz[READER_2]) == 1);
    struct cell* r_cla = malloc(sizeof(struct cell));
    struct cell* r_clb = malloc(sizeof(struct cell));
    add_in_queue(r_cla,monkeyz[READER_1].my_queue);
    add_in_queue(r_clb,monkeyz[READER_1].my_queue);
    add_in_queue(r_cla,monkeyz[READER_2].my_queue);
    add_in_queue(r_clb,monkeyz[READER_2].my_queue);
    assert(should_reader_work(&monkeyz[READER_1]) == 0);
    assert(should_reader_work(&monkeyz[READER_2]) == 0);
    purge_queue(monkeyz[READER_1].my_queue);
    purge_queue(monkeyz[READER_2].my_queue);
    char ch = ' ';
    while(ch = fgetc(monkeyz[READER_1].my_source_text) != EOF);
    ch = ' ';
    while(ch = fgetc(monkeyz[READER_2].my_source_text) != EOF);
    assert(should_reader_work(&monkeyz[READER_1]) == 0);
    assert(should_reader_work(&monkeyz[READER_2]) == 0);
    printf(GRN "OK\n" RESET);

    purge_queue(&reader_queue_a);
    purge_queue(&reader_queue_b);
    purge_queue(&writer_queue_a);
    purge_queue(&writer_queue_b);
    purge_successors_queue(&stats_queue);
}

void statistician_work_cond_test(FILE* filename,FILE* filename2)
{
    FILE* read_file_1 = filename;
    FILE* read_file_2 = filename2;

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

    struct monkey monkeyz[NUMBER_OF_MONKEYS];
    init_monkeys(monkeyz, NUMBER_OF_MONKEYS,&writer_queue_a,&writer_queue_b,&reader_queue_a,&reader_queue_b,read_file_1,read_file_2);

    strcpy(monkeyz[WRITER_1].memorized_word,".");
    monkeyz[WRITER_1].sentence_length = 0;
    monkeyz[WRITER_1].sentence_finished = 0;
    strcpy(monkeyz[WRITER_2].memorized_word,".");
    monkeyz[WRITER_2].sentence_length = 0;
    monkeyz[WRITER_2].sentence_finished = 0;
    monkeyz[WRITER_2].sentence_finished = 0;

    printf("Testing statistician monkey working conditions...\n");
    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 1);
    struct cell* r_cla = malloc(sizeof(struct cell));
    struct cell* r_clb = malloc(sizeof(struct cell));
    struct cell* r_claa = malloc(sizeof(struct cell));
    struct cell* r_clbb = malloc(sizeof(struct cell));
    add_in_queue(r_claa,monkeyz[READER_1].my_queue);
    add_in_queue(r_clbb,monkeyz[READER_1].my_queue);
    add_in_queue(r_cla,monkeyz[READER_2].my_queue);
    add_in_queue(r_clb,monkeyz[READER_2].my_queue);
    print_queue(monkeyz[READER_1].my_queue);

    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 0);
    printf("PASSED\n\n");

    remove_in_queue(monkeyz[READER_1].my_queue);
    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 0);
    remove_in_queue(monkeyz[READER_1].my_queue);
    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 1);

    char ch = ' ';
    while(ch = fgetc(monkeyz[READER_1].my_source_text) != EOF);
    ch = ' ';
    while(ch = fgetc(monkeyz[READER_2].my_source_text) != EOF);
    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 0);
    printf("\n\n\n");
    purge_queue(monkeyz[READER_1].my_queue);
    purge_queue(monkeyz[READER_2].my_queue);
    assert(should_statisician_strike(&monkeyz[READER_1],&monkeyz[READER_2]) == 1);
    printf(GRN "OK\n" RESET);

    purge_queue(&writer_queue_a);
    purge_queue(&writer_queue_b);
    purge_successors_queue(&stats_queue);
}

void research_cell_test(struct queue* queue)
{
    printf("Testing research cell...\n");

    struct cell* cella = malloc(sizeof(struct cell));
    struct cell* cellb = malloc(sizeof(struct cell));
    struct cell* cellc = malloc(sizeof(struct cell));
    struct cell* celld = malloc(sizeof(struct cell));
    struct cell* celle = malloc(sizeof(struct cell));
    strcpy(cella->word,"cella");
    strcpy(cellb->word,"cellb");
    strcpy(cellc->word,"cellc");
    strcpy(celld->word,"celld");
    strcpy(celle->word,"celld");

    struct cell* result = research_cell(queue,2);

    assert(strcmp(result->word,"cellc") == 0);
    printf(GRN "OK\n" RESET);
}

int main(int argc, char* argv[])
{
    struct queue my_queue;
    FILE* filename = fopen("../base/source.txt","r");
    FILE* filename2 = fopen("../base/source.txt","r");
    init_queue(&my_queue);

    printf("Queue part :\n\n");

    int er = queue_test();

    pop_queue_test(&my_queue);
    purge_queue_test(&my_queue);
    research_in_queue_test(&my_queue);
    research_cell_test(&my_queue);

    printf("Monkey part:\n\n");
    reader_work_cond_test(filename,filename2);
    //statistician_work_cond_test(filename,filename2);

    purge_queue(&my_queue);
    fclose(filename);
    fclose(filename2);

    if(er)
        printf(RED "Error" RESET "\n");
    return 0;
}
