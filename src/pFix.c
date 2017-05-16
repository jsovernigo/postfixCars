/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 * 	This file contains the code for the functions 
 *	defined in the h file of the same name.  They
 *	are to be used to evaluate postfix expressions
 *	provided at command line which are not space
 *	delimited.
 */

#include "pFix.h"
#include "stack.h"
#include "linkedList.h"
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

double solve(char* expression, int* err)
{
	VStack* stack;
	int i;
	double solution;


	if(expression == NULL) // if we cannot operate on NULL...
	{
		if(err == NULL) // and have no way of signalling an error.
		{
			return INT_MIN; 
		}
		else
		{
			*err = VALID_PARAMETER_ERROR; // assign an error code.
			return 0;
		}
	}
	else if(err == NULL) // there is no way to signal errors.
	{
		return INT_MIN; // so return an impossible value.
	}

	stack = createStack();

	for(i = 0; i < strlen(expression); i++) // loop through the string.
	{
		if(isdigit(expression[i]))
		{
			double* num;
			VNode* newNode;

			num = malloc(sizeof(double));
			*num = expression[i] - '0'; // store the value of the int we found.

			newNode = createNode((void*)num); // cast num to an int pointer, and add it to the list.
			push(stack, newNode);
		}
		else if(strchr("+-/*^",expression[i]) != NULL) // this is basically like matching to the regex "[+-/*\\^]+" for the record
		{
			double answer;
			double num1;
			double num2;

			int* eCode;
			VNode* node1;
			VNode* node2;

			num1 = 0;
			num2 = 0;

			eCode = malloc(sizeof(int)); // setup the ecode's memory.

			node1 = pop(stack);
			if(node1 == NULL) // there were not enough elements on the stack
			{
				*err = PFIX_SYNTAX_ERROR;
				return 0;
			}	
			else
			{
				num1 = getDoubleFromVoid(node1->data); // get the void pointer
				if(num1 == INT_MIN)
				{
					*err = PFIX_SYNTAX_ERROR;
					return 0;
				}
			}

			node2 = pop(stack); // there were not enough elements on the stack
			if(node2 == NULL)
			{
				*err = PFIX_SYNTAX_ERROR;
				return 0;
			}
			else
			{
				num2 = getDoubleFromVoid(node2->data); // convert the void pointer to an integer
				if(num2 == INT_MIN) // if there was an error
				{
					*err = PFIX_SYNTAX_ERROR; // set the flag
					return 0;
				}
			}
			answer = operate(num1, num2, expression[i], eCode);

			if(*eCode != 0) // some error was caught...
			{
				*err = *eCode; // reassign the code and return
				return 0;
			}
			else if(answer == INT_MIN) // something went horribly wrong. (this should never actually happen, except in extreme circumstances, like malloc failing.
			{
				*err = VALID_PARAMETER_ERROR;
				return 0;
			}
			else
			{	
				double* newVal;
				VNode* newNode;

				newVal = malloc(sizeof(double)); // get a storage container...
				*newVal = answer;
				newNode = createNode((void*)newVal); // cast the new value to a void pointer and create a new node to store it.
				push(stack, newNode); // push the new value to the stack
			}

			destroyNode(node1, &destroy);
			destroyNode(node2, &destroy);
		}
		else // bad input char... don't worry about it.
		{
			continue;
		}
	}

	if(size(stack->list) != 1) // there were too many arguments on the stack, so we have run into a syntax error.
	{
		*err = PFIX_SYNTAX_ERROR;
		return 0;
	}
	else
	{
		VNode* answer;
		answer = pop(stack);
		solution = getDoubleFromVoid(answer->data); // get the final data
		destroyNode(answer, &destroy); // destroy the node.
	}
	*err = 0; // report no errors.

	destroyStack(stack, &destroy);

	return solution;
}

double operate(double num1, double num2, char opp, int* err)
{
	double answer;

	if(err == NULL)
	{
		return INT_MIN;
	}

	if(opp == '+') // add
	{
		answer = num2 + num1;
	}
	else if(opp == '-') // subtract
	{
		answer = num2 - num1;
	}
	else if(opp == '*') // multiply
	{
		answer = num2 * num1;
	}
	else if(opp == '/') // divide, watch for div/0!
	{
		if(num1 == 0) // we have run into a divide by zero error
		{
			*err = DIVIDE_BY_ZERO_ERROR;
			return INT_MIN;
		}
		else
		{
			answer = num2 / num1;
		}
	}	
	else if(opp == '^') // exponential
	{
		answer = pow(num2, num1);
	}
	else // invalid operator.
	{
		*err = INVALID_OPERATOR_ERROR;
	}	
	*err = 0; // no errors reported!
	return answer;
}	

void destroy(void* num)
{
	double* d = (double*) num; // while this cast is not necessary, it simply shows integer explicitly.
	free(d);
}

double getDoubleFromVoid(void* num)
{
	double val;
	if(num == NULL)
	{
		return INT_MIN;
	}
	val = *((double*) num); // dereferrence as an int pointer.
	return val;
}
