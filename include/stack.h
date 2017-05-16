/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *
 * 	This is a stack implimentation used to store post-fix operands
 * 	for the implimentation of a post-fix solver.  This is part of
 * 	a project for CIS*2520.
 * 	
 */

#ifndef __GSOVERNIGO_STACK_H__
#define __GSOVERNIGO_STACK_H__

#include "linkedList.h"
#include <stdlib.h>

struct vStack
{
	VNode* list;
};

typedef struct vStack VStack;

/**
 *	createStack
 *	creates a new stack that can be pushed and popped to/from
 *	IN:		none
 *	OUT:	stack	- a new stack that can be operated on.
 *	POST:	VStack has been allocated and should be destroyed.
 *	ERROR:	malloc fails
 */
VStack* createStack();

/**
 *	destroyStack
 *	destroys a stack and its data.
 *	IN:		stack	- the stack pointer to be destroyed and freed.
 *			del		- a function pointer to the freeing function for the data.
 *	OUT:	void
 *	POST:	stack has been destroyed and freed.  Use with caution.
 *	ERROR:	none.
 */
void destroyStack(VStack* stack, void (*del)(void*));

/**
 *	push
 *	pushes the value of node to the stack
 *	IN:		stack 	- a stack pointer (heh) that will be pushed to.
 *			node	- a node that will be pushed to stack
 *	OUT:	void
 *	POST:	node has been added to stack->list, which has been updated.
 *	ERROR:	node or stack is null
 */
void push(VStack* stack, VNode* node);

/**
 *	pop
 *	pops a value out of the stack, returning it to the caller.
 *	IN:		stack	- a stack pointer that will be popped from
 *	OUT:	head	- a pointer to the void node that was popped.
 *	POST:	stack->list has been updated to reflect this pop.
 *			since head was removed from the list, it should be freed
 *			by the caller.
 *	ERROR:	stack is null (null returned as a result)
 */
VNode* pop(VStack* stack);

#endif
