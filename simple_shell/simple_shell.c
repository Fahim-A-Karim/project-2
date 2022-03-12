#include <stdio.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>

#define BUFFER_LEN 1024
#define EXITCD "exit\n"


int main(int argc, char *argv[]){
	char line[BUFFER_LEN];
	int doYouRun = 1;

	//first check if it was ran with arguments, if it was print error
	if(argc > 1 && *argv != NULL){
		fprintf( stderr, "it does not accept any command line arguments\n");
		return 0;
	}
	//loop till exit
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
		}
		//if not then run thing
		
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