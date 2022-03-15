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

struct node *RRPriority(struct node *head, struct node *currentPriority){
	struct node *temp;
	struct node *priority = malloc(sizeof(struct node));
	temp = head;
	priority = currentPriority;
	struct node *lastPriority = currentPriority;
	while (temp != NULL)
	{
		if (temp->task->priority >= priority->task->priority)
		{
			if (strcmp(temp->task->name, lastPriority->task->name) != 0) 
			{
				priority = temp;
				temp = temp->next;
			}
			else
			{
				temp = temp->next;
			}
		}
		else
		{
			temp = temp->next;
		}
	}
	return priority;
}

void add(char *name, int priority, int burst)
{
	Task *tmp = malloc(sizeof(struct node));
	tmp->name = name;
	tmp->priority = priority;
	tmp->burst = burst;
	insert(&head, tmp);
	tasksLeft+= 1;
}



void schedule()
{
	struct node* temp = getBP(head);
	while (tasksLeft > 0)
	{
		Task *tmp = temp->task;
		if (tmp->burst > 10)
		{
			run(tmp, 10);
			tmp->burst = tmp->burst - 10;
			//Get next task based on priority
			//priorityCheck = getByPriority(head);
			temp = RRPriority(head, temp);
			if(temp == NULL)
			{
				return;
			}
			tmp = temp->task;
		}
		else
		{
			int time_Remaining = tmp->burst;
			run(tmp, time_Remaining);
			tmp->burst = tmp->burst - time_Remaining;
			delete(&head, tmp);
			temp = getBP(head);
			if(temp == NULL)
			{
				return;
			}
			tmp = temp->task;
			tasksLeft-= 1;
		}
	}
}