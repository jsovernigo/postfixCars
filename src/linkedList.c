/**
 *	Copyright (c) Julian Sovernigo 2016
 *
 *	This is a linked list module which uses void pointers such
 *	that all data can be abstracted or generalized, being 
 *	operated on by function pointers to preserve the generalization.
 *	The model of list and functions was presented originally to the
 *	writer by Justin Carvalho, during a lecture.  The interfaces
 *	have since been modified by the writer to include void data
 *	types so as to be generally useful.
 *
 *	This software was written with the full intenetion of being
 *	reused and shared, and implimenting general usefulness.
 *	However, this software is not to be used without express
 *	permission of the copyright holder, in written form, for
 *	any other use other than personal interest projects.
 *
 *	Use for academic projects is strictly prohibited.
 */

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>


VNode* createNode(void* data)
{
	VNode* newNode;

	newNode = malloc(sizeof(VNode)); // malloc for the new node
	if(newNode == NULL)
	{
		return NULL; // our malloc failed.
	}
	else
	{
		newNode->data = data; // set our pointer.
		newNode->next = NULL;
	}
	return newNode;
}

char* printNode(VNode* node, char* (*print)(void*))
{
	char* message;
	if(node == NULL)
	{
		return NULL;
	}
	message = print(node->data);
	return message;
}

void destroyNode(VNode* node, void (*del)(void*))
{
	if(node != NULL)
	{
		del(node->data); // calls the function pointer to the specific delete function.
	}
	free(node);

	return;
}

VNode* addToFront(VNode* list, VNode* tba)
{
	if(list == NULL)//isEmpty(list)) // the list we are adding to is empty!
	{
		tba->next = NULL;
		return tba;
	}
	else
	{
		tba->next = list; // we are now the head, so point to the old one.
	}
	return tba; // return our new head: us.
}

VNode* addToBack(VNode* list, VNode* tba)
{
	VNode* current;

	if(isEmpty(list)) // we should just add our new item to the list; its empty anyway
	{
		tba->next = NULL;
		return tba;
	}
	else
	{
		current = list;
		while(current->next != NULL) // loop through until we find the end
		{
			current = current->next;
		}
		current->next = tba; // add our node to the end
		tba->next = NULL;
	}
	return list; // return the head
}

VNode* addSort(VNode* list, VNode* tba, int (*equals)(void*, void*))
{
	VNode* previous;
	int i;

	if(tba == NULL)
	{
		return list;
	}

	if(list == NULL)
	{
		tba->next = NULL;
		return tba;
	}

	if(equals(tba->data, list->data) <= 0) // the list we have comes AFTER, or IS tba 
	{
		tba->next = list;
		return tba;
	}

	for(i = 1; i < size(list); i++)
	{
		previous = get(list, i - 1);	
		if( equals(tba->data, get(list, i)->data) <= 0) // if tba is before current, or equal to it.
		{
			tba->next = get(list, i); // I now point to the current.
			previous->next = tba; // the previous now points to me.
			return list;
		}
	}

	if(equals(tba->data, get(list, size(list) -1)->data) > 0) // if tba comes after the last index
	{
		tba->next = NULL;
		get(list, size(list) -1)->next = tba; // set the last one to point to our new last one.
	}

	return list;
}

VNode* removeFromFront(VNode* list)
{
	VNode* nHead;

	if(isEmpty(list)) // nothing to remove
	{
		return NULL;
	}
	nHead = list->next;

	return nHead;
}

VNode* removeFromBack(VNode* list)
{
	VNode* current;
	VNode* previous;

	if(isEmpty(list))
	{
		return NULL;
	}
	current = list;

	while(current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	previous->next = NULL;

	return list;
}

VNode* removeAt(VNode* list, int index)
{
	VNode* prev;

	if(list == NULL)
	{
		return NULL;
	}	
	if(index < 0 || index >= size(list)) // if the index is not valid.
	{
		return list;
	}

	if(index == 0)
	{
		return removeFromFront(list); // returns head->next essentially.  DONT FORGET TO GET THE ITEM WITH get() TO FREE/USE IT
	}
	else if(index == size(list) -1)
	{
		return removeFromBack(list); // returns the list head after removing from the back
	}

	prev = get(list, index - 1); // get the previous item 
	prev->next = get(list, index)->next; // set the previous.next to the current->next

	return list;
}

VNode* getLastNode(VNode* list)
{
	VNode* current;

	if(isEmpty(list)) // we are an empty list
	{
		return NULL;
	}

	current = list;
	while(current->next != NULL) // loop until we find the end
	{
		current = current->next;
	}
	
	return current; // return our last node
}

VNode* getFirstNode(VNode* list)
{
	if(isEmpty(list)) // no items left
	{
		return NULL;
	}
	
	return list; // return the list; it is the first item anyway.
}

int isEmpty(VNode* list)
{
	return (list == NULL) ? 1 : 0;
}

void printList(VNode* list, char* (*print)(void*))
{
	VNode* current;
	current = list;

	while(current != NULL) // loops through the whole list, printing each
	{
		char* msg;
		msg = printNode(current, print);
		printf("%s\n",msg);
		free(msg);
		current = current->next;
	}
	return;
}

void destroyList(VNode* list, void (*del)(void*))
{
	VNode* next;
	VNode* current;

	current = list;

	while(current != NULL) // loops until the end.
	{
		next = current->next;
		destroyNode(current, del); // deletes the node, using del
		current = next;
	}
	return;
}

int size(VNode* list)
{
	int size = 0;
	VNode* current;

	if(isEmpty(list)) // empty, return 0.
	{
		return 0;
	}

	current = list;

	while(current != NULL) // loop until we hit the end, then stop.
	{
		size ++;
		current = current->next;
	}

	return size;

}

VNode* get(VNode* list, int index)
{
	int cDex;
	VNode* current;
	VNode* tbr;

	cDex = 0;
	tbr = NULL;

	if(index >= size(list) || index < 0) // if we are outside of the range already.
	{
		return NULL;
	}

	current = list;

	while(current != NULL) // while we have not hit the end.
	{
		if(cDex == index)
		{
			return current;
		}
		else
		{
			cDex++; // increment the current index
		}
		current = current->next;
	}

	return tbr;
}
