#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include <stdlib.h>
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

struct node *getRRPrio(struct node *head, struct node *currentPriority){
	struct node *current;
	struct node *priority = malloc(sizeof(struct node));
	current = head;
	priority = currentPriority;
	struct node *lastPriority = currentPriority;
	int currPrio = 0;
	int sPrio = 0;

	while (current != NULL){

		sPrio = priority->task->priority;
		currPrio = current->task->priority;
		
		if (currPrio >= sPrio){
			
			if (strcmp(current->task->name, lastPriority->task->name) != 0) {
				priority = current;
				current = current->next;
			}
			else{
				current = current->next;
			}
		}
		else{
			current = current->next;
		}
	}
	return priority;
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

	printf("This scheduling algorithm is basically just round robin, and tries to things a bit at a time instead of one at a time. \n");
	printf("Obviously the big difference is instead of queing by order they come in you do it by priority which changes what finishes first\n");

	struct node* currNode = getBP(head);
	while (tasksLeft > 0)
	{
		Task *currTask = currNode->task;
		if (currTask->burst > 10)
		{
			printf("Current task could not finished in 10 so it was ran for a bit \n");
			run(currTask, 10);
			currTask->burst = currTask->burst - 10;

			printf("Traverse linked list for highest prio, but not repeating.\n");
			currNode = getRRPrio(head, currNode);
			if(currNode == NULL)
			{
				printf("Couldn't find another node left\n");
				return;
			}
			printf("Queue for next node\n");
			currTask = currNode->task;
		}
		else
		{
			printf("Current task can be finished in less than 10, so it will be ran to completion\n");
			int time_Remaining = currTask->burst;
			run(currTask, time_Remaining);
			currTask->burst = currTask->burst - time_Remaining;

			printf("Current task will be deleted\n");
			delete(&head, currTask);
			currNode = getBP(head);

			if(currNode == NULL)
			{
				printf("No more tasks remaining\n");
				return;
			}
			printf("Move onto next task\n");
			currTask = currNode->task;
			tasksLeft-= 1;
		}
	}
}