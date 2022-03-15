
#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

//variables
int tasksLeft = 0;

struct node *head;

struct node* getBP(struct node *head){
	
	int currPrio = 0;
	int sPrio = 0;
	
	struct node *currNod = head;
	struct node *sNod = head;

	
	while(currNod != NULL)
	{
		sPrio = sNod->task->priority;
		currPrio = currNod->task->priority;

		if(currPrio < sPrio){
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

void schedule()
{
	//Priority
	printf("Scheduling by priority is similar to smallest job first. \n");
	printf("The only read difference is just that you run in order of priority instead of burst time /n");
	for(int i = tasksLeft; i > 0; i--){
		printf("Traversing for smallest prio\n");
		struct node *priority = getBP(head);

		Task *currNode = priority->task;
		printf("Run current task\n");
		run(currNode, currNode->burst);
		printf("Deleting current task\n");
		delete(&head, currNode);
		
	}
	printf("No more tasks left\n");
	tasksLeft = 0;
}

