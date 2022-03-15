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
	struct node *temp;
	temp = head;
	printf("First come first serve is probably the easiest algorithm. As the textbook states it's just like a line \n");
	printf("In order to run this we just run the last element of the list since they entered in reverse and then delete it moving to the next in line\n");
	for(int i = tasksLeft; i > 0; i--){
		temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		Task *nod = temp->task;
		
		//run it
		run(nod, nod->burst);
		//delete it
		delete(&head, nod);
	}
	tasksLeft = 0;
	printf("After running all of the nodes it ends here \n");
} 