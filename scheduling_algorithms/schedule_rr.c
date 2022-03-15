#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

//variables
int tasksLeft = 0;

struct node *head;



void add(char *name, int priority, int burst){
    //increment tasks
	tasksLeft+= 1;

	Task *nod = malloc(sizeof(struct node));
	//assign parameters
	nod->priority = priority;
	nod->name = name;
	nod->burst = burst;

    //then just insert the nodes
	insert(&head, nod);
	
	
}



void schedule(){
	printf("At a high level this algorithm tries to run everything a bit at a time instead of one at a time. \n");
	printf("In this implementation I ran to completion if the burst time was less than 10 otherwise after 10 I moved onto the next. \n");
	printf("This process loops until you run work your way through all the tasks and finish them all.\n");

	struct node* currNod = head;
	while (tasksLeft > 0){
		printf("Moved onto the next task\n");
		Task *currTas = currNod->task;

		if (currTas->burst > 10){
			printf("Current task burst length was greater than 10\n");
			printf("Ran current task for 10\n");
			run(currTas, 10);
			currTas->burst = currTas->burst - 10;
			currNod = currNod->next;

			if (currNod != NULL){
				printf("Moved onto the next node \n");
				currTas = currNod->task;

			}else{
				printf("Cycled back \n");
				currNod = head;
				if (currNod == NULL){
					printf("Finished all tasks\n");
					return;

				}else{
					printf("Continue task\n");
					currTas = currNod->task;
				}
			}
		}
		else{
			printf("Ran current task to completion.\n");
			int time_Remaining = currTas->burst;
			run(currTas, time_Remaining);
			currTas->burst = currTas->burst - time_Remaining;
			currNod = currNod->next;
			printf("Deleted completed node.\n");
			delete(&head, currTas);

			if (currNod != NULL){
				printf("Moved onto the next node \n");
				currTas = currNod->task;
			}
			else{
				printf("Cycled back \n");
				currNod = head;
				if (currNod == NULL){
					printf("Finished all tasks\n");
					return;
				}
				else{
					printf("Continue task\n");
					currTas = currNod->task;
				}
			}
		}
	}
}