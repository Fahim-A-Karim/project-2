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



void schedule()
{
	struct node* currNod = head;
	while (numTasks > 0)
	{
		Task *currTas = currNod->task;
		if (currTas->burst > 10)
		{
			run(currTas, 10);
			currTas->burst = currTas->burst - 10;
			currNod = currNod->next;
			if (currNod != NULL)
			{
				currTas = currNod->task;
			}
			else
			{
				currNod = head;
				if (currNod == NULL)
				{
					return;
				}
				else
				{
					currTas = currNod->task;
				}
			}
		}
		else
		{
			int time_Remaining = currTas->burst;
			run(currTas, time_Remaining);
			currTas->burst = currTas->burst - time_Remaining;
			currNod = currNod->next;
			delete(&head, currTas);
			if (currNod != NULL)
			{
				currTas = currNod->task;
			}
			else
			{
				currNod = head;
				if (currNod == NULL)
				{
					return;
				}
				else
				{
					currTas = currNod->task;
				}
			}
		}
	}
}