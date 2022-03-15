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
	struct node *sNod = malloc(sizeof(struct node));

	sNod = head;
	
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
	

	for(int i = tasksLeft; i > 0; i--){
		struct node *smallest = getSB(head);
		Task *tmp = smallest->task;
		run(tmp, tmp->burst);
		delete(&head, tmp);
		
	}
	tasksLeft = 0;
} 