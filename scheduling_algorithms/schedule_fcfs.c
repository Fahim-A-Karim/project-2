#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

//variables
int numTasks = 0;

struct node *head;


void add(char *name, int priority, int burst)
{
    
	Task *nod = malloc(sizeof(struct node));
	
    //nothing of note, should be just assiging values and inserting
    nod->name = name;
	nod->priority = priority;
	nod->burst = burst;

    //then just insert the nodes
	insert(&head, nod);

	numTasks+= 1;
}

void schedule()
{
	

	while(numTasks > 0)
	{
		Task *nod = head->task;
		run(nod, nod->burst);
		delete(&head, nod);
		numTasks--;
	}
} 