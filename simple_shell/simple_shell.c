#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_LEN 1024
#define EXITCD "exit\n"
#define PROCD "proc"


void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

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
	char procPath[] = "/proc/";
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
				fil = fopen(argument, "r");

				//2. read from it
				fgetc(fil);
    			while (ind != EOF){
					//3. print out it's output to stdout
        			printf ("%c", ind);
        			ind = fgetc(fil);
    			}
				


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

