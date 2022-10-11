#include <stdlib.h>
#include <stdio.h>
#include "fim.h"

/*------------------------------------------------------------------------------------------------------------------*/
/*
 * This function takes a char array, removes spaces and seperates words with '\0' instead
 */ 
void parseCommand(char* pu8CommandArr)
{
    char * scanner, *reference;
    reference = pu8CommandArr;
    scanner   = pu8CommandArr + 1;
    while( *scanner != '\0')
    {
    	if( (*reference == ' ') && ( *scanner == ' ') )
    	{
    		scanner++;
    	}
    	else if( ( *reference == ' ') && ( *scanner != ' ') )
    	{
    		*reference = *scanner;
    		*scanner = ' ';
    		reference++;
    		scanner++;
    		if( *scanner == ' ')
    		{
    			*reference = '\0';
    			reference++;
    		}
    	}
    	else if( ( *reference != ' ') && ( *scanner != ' ') )
    	{
    		reference++;
    		scanner++;
    	}
    	else if ( ( *reference != ' ') && ( *scanner == ' ') )
    	{
    		reference++;
    		scanner++;
    		*reference = '\0';
    	}
    }
    if( *reference == ' ')
    {
    	*(reference) = '\0';
    }
}

/*------------------------------------------------------------------------------------------------------------------*/
/*
 * This functions takes char array, with its length "length" and an int var reference, that if the received array is
 * not full empty it alloactes the command with its argument in the heap.
 *
 * RETURNS a pointer that points to both the command and its arguments, else it frees the space (received all space 
 * array). 
 */

char** getCommand(char* commandsArr, int length ,int* numberOfCommands)
{
	int nullCounter = 0;
	int i = 0;
	char** commandsPtr = (char**)malloc( sizeof(char*) * length );
	if( ( commandsArr[0] != '\0') && ( commandsArr[0] != ' '))
	{
		*numberOfCommands = 1;
		commandsPtr[0]    = commandsArr;
		while( i < length)
		{
			if( commandsArr[i] == '\0' )
			{
				nullCounter++;
			}
			else
			{
				if( ( nullCounter > 0 ) && (commandsArr[i] != ' ') )
				{
					commandsPtr[*numberOfCommands] = commandsArr + i;
					(*numberOfCommands)++;
					nullCounter = 0;
				}
			}
			i++;
		}
	}
	else
	{
		free(commandsPtr);
		commandsPtr = NULL;
		(*numberOfCommands) = 0;
	}
	return commandsPtr;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*
 * RETURNS 1 if there is assignment operator in the command recieved else return 0
 */
char   commandAssignmentCheck(char* command)
{
	char returnVal = 0;
	int i = 0;
	while(command[i] != '\0')
	{
		if( command[i] == '=' )
		{
			returnVal = 1;
			break;
		}
		i++;
	}
	return returnVal;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*
 * Recieves the variable assignment array "command" saves it using the realloc function in the heap to keep both the
 * variable and its value saved contiguously in memory seperated by '\0' operator.
 * 
 * RETURNS: pointer to 2 pointers; firts is the variable, second is the value
 */
char**  assignmentParseCommand(char* command)
{
        char* expressionPtr = NULL;
	char** returnPtr = NULL;
	int  expressionLength = 1;
	int  valLength = 0;
	int i = 0;
	while(command[i] != '\0')
	{
		if( ( command[i] != '=' ) && (command[i] != ' ') )
		{
			expressionPtr = (char*)realloc(expressionPtr, expressionLength);
			*(expressionPtr + expressionLength - 1) = command[i];
		        expressionLength++;
		}
		else if(command[i] == '=')
		{
			valLength = expressionLength;
			*(expressionPtr + expressionLength - 1) = '\0';
			expressionLength++;
		}
		i++;
	}
	*(expressionPtr + expressionLength - 1) = '\0';
	returnPtr = (char**)malloc(2 * sizeof(char*));
	
	returnPtr[0] = expressionPtr;
	returnPtr[1] = expressionPtr + valLength;
	
	return returnPtr ;
}
