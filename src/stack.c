/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *
 * 	This is a stack implimentation which uses void node
 *	liked lists in order to be fully modular.
 *	it is used in this program to store post-fix operands
 * 	for the implimentation of a post-fix solver.  This is part of
 * 	a project for CIS*2520.
 * 	
 */

#include "stack.h"
#include "linkedList.h"

VStack* createStack()
{
	VStack* new;

	new = malloc(sizeof(VStack));
	new->list = NULL;

	return new;
}

void destroyStack(VStack* stack, void (*del)(void*))
{
	destroyList(stack->list, del);
	free(stack);
	return;
}

void push(VStack* stack, VNode* node)
{
	if(stack == NULL || node == NULL) // if either parameter cannot be operated on...
	{
		return;
	}
	else
	{
		stack->list = addToFront(stack->list, node); // add the node to the front
	}
	return;
}

VNode* pop(VStack* stack)
{
	VNode* head;

	if(stack == NULL) // stack is inoperable
	{
		return NULL;
	}

	if(stack->list != NULL)
	{
		head = getFirstNode(stack->list);
		stack->list = removeFromFront(stack->list); // set the list to the next available value.
	}
	else
	{
		return NULL;
	}

	return head;
}
