#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include "fim.h"

void main()
{
    char command[100] = { };
    char *const argv[] = { NULL };
    char *const envp[] = { NULL };
    int status;
    int commandCounter = 0;
    char **cPtr;
    char **expressionPtr = NULL;
    char *varPtr = NULL;
    int len;
    int i = 0;
    int ret_pid;
    char assignmentCheck;
    int envVarsCount = 0;
    char*** envVars = NULL;
    while (1) {
	printf("Please type your command> ");
	fgets(command, 100, stdin);
	if (strcmp(command, "\n")) 
	{
	    len = strlen(command);
	    command[len - 1] = 0;
	    
	    if( !( strcmp(command, "set") ) )
	    {
			for(int i = 0; i < envVarsCount; i++)
	        	{
	        		printf("local_vars[%d]: %s = %s\n",i,envVars[i][0],envVars[i][1]);	
	        	}
            }
	    else if( !( strcmp(command, "export") ) )
	    {
	
	    }
	    else
	    {
	        assignmentCheck = commandAssignmentCheck(command);
	        if(assignmentCheck != 1)
	        {

	            parseCommand(command);
	            cPtr = getCommand(command, len, &commandCounter);
	            cPtr[commandCounter] = NULL;
	            ret_pid = fork();

	            if(ret_pid == -1)
		        printf("Forking failed\n");
	            else if (ret_pid > 0) 
	            {
		        wait(&status);
	            } 
	            else if (ret_pid == 0) 
	            {
		        execvp(cPtr[0], cPtr);
		        printf("Failed to execute command\n");
              	    }
	    	}
	    	else
	    	{
	        	expressionPtr = assignmentParseCommand(command);
	        	envVars       = (char***)realloc(envVars, envVarsCount+1);
	        	envVars[envVarsCount++] = expressionPtr;
	    	}
	    }
	} 
    }
}
