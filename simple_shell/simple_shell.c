#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_LEN 1024
#define EXITCD "exit\n"


int main(int argc, char *argv[]){
	//variable stuff
	char line[BUFFER_LEN];
	char space[] = " ";
	pid_t retVal;
	int doYouRun = 1;
	int status;

	//first check if it was ran with arguments, if it was print error
	if(argc > 1 && *argv != NULL){
		fprintf( stderr, "it does not accept any command line arguments\n");
		return 0;
	}

	//loop till "exit" typed
	while(doYouRun){
		//prompt
		printf("thing>");
		fflush(stdout);
		//read
		if(!fgets(line, BUFFER_LEN, stdin)){ 
        	break;                                
    	}

		//exit check
		if (strcmp(line, EXITCD) == 0){
			doYouRun = 0;
		}else{
			//if not then run thing
			// goal is break into arg list, fork, then execvp, then wait
		
			//to do this first you have to break up the command by space
			
			// char *pnt = strtok(line, space);
			// while(pnt != NULL){
			// 	printf("%s \n", pnt);
			// 	pnt = strtok(NULL, space);
			// }

			//now you can fork
			retVal = fork();
			//check if you're in child
			if(retVal == 0){
				execvp(line, line);
				fprintf( stderr, "fail, Line56\n");
				exit(0);
			}else{
				//else wait
				while (wait(&status) != retVal);
			}
		}
		

	}
	
	return 0;
}

// int main(void)
// {
// 	char *string;
// 	char *args[MAX_LINE/2 + 1];
// 	size_t size = 10;
//     	int should_run = 1;
		
//     	while (should_run){   
//         	printf("What do you want:");
//         	char **string_pointer = &string;
// 			size_t command = getline(string_pointer,&size,stdin);
// 			if (strcmp(EXITCD, command) ==0){
// 				return 0;
// 			}
//     	}
    
// 	return 0;
// }