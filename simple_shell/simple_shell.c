#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_LEN 1024
#define EXITCD "exit\n"
#define PROCD "proc"




int main(int argc, char *argv[]){
	//variable stuff
	char line[BUFFER_LEN];
	pid_t retVal;
	int doYouRun = 1;
	int status;
	//char file_path[50];
	//char* path= "/bin/";
	//int spaceCount = 0;
	char* argument[BUFFER_LEN];
	FILE *fil;
	char fileName[BUFFER_LEN];
	char procPath[BUFFER_LEN] = "/proc/";
	char ind;

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
		
			//1. remove /n
			line[strcspn(line, "\n")] = 0;
			
			//2. split into init comm
			argument[0] = strtok(line, " ");
			
			//3. split rest of spaces
			int i = 0;
			while(argument[i] != NULL){
				argument[++i] = strtok(NULL, " ");
			}
			
			//check if arg 0 is proc or not
			if (strcmp(argument[0], PROCD) == 0){
				
				/////////////////////////////////////////////work on from here
				//1. figure out how to read specifically from the proc filesystem
				
				argument[0] = procPath;
				//strcat(procPath, p);
				//printf(procPath);
				//printf("\n");
				int x = 0;

				while(argument[x] != NULL){
					strcat(fileName, argument[x]);
					x+= 1;
				}
				printf(fileName);
				fil = fopen(fileName, "r");

				 //2. read from it
				do {
        			ind = fgetc(fil);
        		 	printf("%c", ind);
 
        		 	// Checking if character is not EOF.
        		 	// If it is EOF stop eading.
    			 	} while (ind != EOF);
				
				fclose(fil);


			}else{

				//now you can fork
				retVal = fork();
				//check if you're in child
				if(retVal == 0){
					//execute
					execvp(argument[0], argument);
					fprintf( stderr, "fail, in child\n");
					doYouRun = 0;
				}else{
					//else wait
					while (wait(&status) != retVal);
				}
			}

			
		}
		
		//spaceCount = 0;
	}
	
	return 0;
}

