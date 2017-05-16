/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *
 *	This file contains the main function for a post-fix solving
 *	stack-based evaluation engine.  It will be used for CIS2520
 *	A2.  Please note that the concept of using a stack to solve
 *	postfix input was provided by Professor Fangju Wang who
 *	teaches the same course.
 */
#include "pFix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv)
{
	double answer;
	char* expression;
	int* err;


	if(argc != 2)
	{
		printf("Error in invoking program.  Arguments were invalid.\nPlease use as:\n\t%s <postfix expression>\n\n", argv[0]);
		return 1;
	}
	else
	{
		expression = malloc(sizeof(char) * 512);
		if(expression == NULL) // malloc failed
		{
			return 1;
		}
		strcpy(expression, argv[1]);
	}	

	err = malloc(sizeof(int));
	if(err == NULL)
	{
		printf("Malloc failed to reserve memory.\n");
		return 1;
	}

	answer = solve(expression, err);


	if(*err != 0)
	{
		printf("An Error caused execution to halt.\nError code is: %d\n\n", *err);
		return *err;
	}
	else
	{
		printf("Answer to %s is: %.2lf\n", argv[1], answer);
	}

	return 0;
}
