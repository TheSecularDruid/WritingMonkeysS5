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
    init_queue(&my_queue);

    printf("Queue part :\n\n");

    int er = queue_test();

    pop_queue_test(&my_queue);
    purge_queue_test(&my_queue);
    research_in_queue_test(&my_queue);
    research_cell_test(&my_queue);

    printf("Monkey part:\n\n");
    //reader_work_cond_test(filename,filename2);
    //statistician_work_cond_test(filename,filename2);
    printf("The Achievement 1 version doesn't test the monkey part. To test the monkey part, please compile the Achievement 2 version.\n");

    purge_queue(&my_queue);

    if(er)
        printf(RED "Error" RESET "\n");
    return 0;
}
