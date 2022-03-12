#include <stdio.h>
#include "utils.h"


#define MAX_LINE 80 
#define EXITCD "exit"
int main(void)
{
	char *args[MAX_LINE/2 + 1];
    	int should_run = 1;
		
    	while (should_run){   
        	printf("What do you want:");
        	command = getline()
			if(strcmp(EXITCD, command) ==0){
				return 0;
			}
        	/**
         	 * After reading user input, the steps are:
         	 * (1) fork a child process
         	 * (2) the child process will invoke execvp()
         	 * (3) if command included &, parent will invoke wait()
         	 */
    	}
    
	return 0;
}