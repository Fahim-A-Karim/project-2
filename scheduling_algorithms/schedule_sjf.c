#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

//variables
int tasksLeft = 0;

struct node *head;

struct node* getSB(struct node *head){
	
	int currBurst = 0;
	int sBurst = 0;
	
	struct node *currNod = head;
	struct node *sNod = head;

	
	while(currNod != NULL)
	{
		sBurst = sNod->task->burst;
		currBurst = currNod->task->burst;

		if(currBurst < sBurst){
			sNod = currNod;
			currNod = currNod->next;

		}else{
			currNod = currNod->next;

		}
	}
	return sNod;
}


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
	
	printf("Shortest job first is also quite simple, you just run in order of smallest cpu burst to largest \n");
	printf("In order to do this first we get the smallest node by traversing the list and comparing each task \n");
	printf("Then it's just a matter of running, deleting and just looping back \n");
	for(int i = tasksLeft; i > 0; i--){
		//get the smallest node
		printf("Getting smallest\n");
		struct node *smallest = getSB(head);
		//get task from node
		Task *tmp = smallest->task;
		//run the task
		printf("running here\n");
		run(tmp, tmp->burst);
		//delete it
		printf("deleting current smallest node\n");
		delete(&head, tmp);
		
	}
	printf("After finishing this loop you're left with no more tasks left.\n");
	tasksLeft = 0;
} 