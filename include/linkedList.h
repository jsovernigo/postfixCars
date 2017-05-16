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

#ifndef __GSOVERNIGO_LINKEDLIST_H__
#define __GSOVERNIGO_LINKEDLIST_H__

struct voidN
{
	void* data;
	struct voidN* next;
};

typedef struct voidN VNode;

/**
 *	createNode
 *	creates a new node, assigning the pointer of data to the passed 
 *	in data void pointer.
 *	IN:		data 	- a void pointer to the data to be stored
 *	OUT:	newNode - a new VNode pointer, initialized by the function.
 *			NULL	- on error
 *	POST:	newNode has been allocated, and should be freed by the
 *			caller.
 *  ERROR:	Malloc fails to allocated memory (returns null)
 */
VNode* createNode(void* data);

/**
 *	printNode
 *	prints an individual node, using the function pointer to operate
 *	on the data.
 *	IN:		node	- a node to be printed out.
 *			print	- a function pointer to the function that will
 *					  print a string representation of data
 *	OUT:	message - a string representation of the data that was
 *					  passed in.
 *	POST:	message has been allocated and should be freed by the
 *			caller.
 *	ERROR:	node or print are null, or garbage.
 */
char* printNode(VNode* node, char* (*print)(void*));

/**
 *	destroyNode
 *	this function destroys a specific node, deallocating it based
 *	on the function pointer passed in (del)
 *	IN:		node 	- a node that will be deleted.
 *			del		- a function pointer that is used to free the
 *					  memory for the data node.
 *	OUT:	void
 *	POST:	node has been deallocated, and should be handled with caution.
 *	ERROR:	none.
 */
void destroyNode(VNode* node, void (*del)(void*));

/**
 *	addToFront
 *	adds a passed in node to the front of the list.
 *	IN:		list	- the list head pointer that will have data added.
 *			tba		- the node that will be added as a new head.
 *	OUT:	tba		- returns the new head of the list
 *			list	- tba was null, so return the old head
 *	POST:	list has been updated, either being returned or being changed
 *			to tba by return.  CATCH THAT RETURN!!
 *	ERROR:	list is null, or tba is null (if list is null, add it anyway)
 */
VNode* addToFront(VNode* list, VNode* tba);

/**
 *	addToBack
 *	adds the node to the end of the list
 *	IN:		list	- the list that will be appended to.
 *			tba		- the node to be added
 *	OUT:	list	- returns the head of the list
 *			tba		- if list is null
 *	POST:	list has had an item added to it (hopefully)
 *	ERROR:	tba is null ( do not add, return list )
 */
VNode* addToBack(VNode* list, VNode* tba);

/**
 *	addSort
 *	adds a new element in its sorted location.  To determine where it
 *	will go, the function pointer equals should provide a means of 
 *	comparing the two datas.
 *	IN:		list	- the list that will be added to.
 *			tba		- the node that will be added.
 *			equals	- a function pointer that compares two of the data
 *					  types of this list, returning the integer value
 *					  of their "difference".  This function should
 *					  return 0 if the two datas are equal, <0 if the
 *					  first data is before the second, or >0 if the first
 *					  data is after the second.
 *	OUT:	the new head of the list (if its been changed)
 *	POST:	list could have changed value, tba will be added.
 *	ERROR:	list is null or tba is null.
 */
VNode* addSort(VNode* list, VNode* tba, int (*equals)(void*, void*));

/**
 *	removeFromFront
 *	removes a node from the front of the list and returns the new head
 *	IN:		list	- the list that will have a piece of it removed
 *	OUT:	head	- the new head of the list (or null)
 *	POST:	the head of list has been updated, and the old head should
 *			be freed (dont forget to get it before calling this using
 *			getFirstNode())
 *	ERROR:	list is null (just return null)
 */
VNode* removeFromFront(VNode* list);

/**
 *	removeFromBack
 *	removes a node from the end of the list, and returns the new head.
 *	IN:		list	- the list that will be de-ended.
 *	OUT:	head	- returns the new head of the list
 *	POST:	list should be one shorter, and the tail of the list should
 *			be freed (dont forget to use getLastNode() to get it and
 *			free it using destroyNode())
 *	ERROR:	list is null (returns null anyway)
 */
VNode* removeFromBack(VNode* list);

/**
 *	removeAt
 *	removes a particular element from the list, safely redirecting the
 *	previous and next pointers to ensure continuity of the list.
 *	IN:		list	- the list to be de-elemented.
 *			index	- the index that will be removed.
 *	OUT:	returns the head of the list.
 *	POST:	the internal reference to the element removed has been 
 *			essentially deleted.  Make sure to free its contents 
 *			seperately, aquiring it using get().
 *	ERROR:	index is out of range or list is invald.
 */
VNode* removeAt(VNode* list, int index);

/**
 *	getLastNode
 *	returns the last element in the list
 *	IN:		list	- the list pointer that we will return the end of.
 *	OUT:	tail	- returns the tail of the list.
 *	POST:	tail has been returned.
 *	ERROR:	list is null (returns null anyway)
 */
VNode* getLastNode(VNode* list);

/**
 *	getFirstNode
 *	returns the head of the list.
 *	IN:		list	- the head of the list we will return.
 *	OUT:	head	- returns the head of the list.
 *	POST:	the head of the list has been returned.
 *	ERROR:	list is null (return null anyway)
 */
VNode* getFirstNode(VNode* list);

/**
 *	isEmpty
 *	this function checks if the list is empty, and returns 1 or 0.
 *	IN:		list	- a list pointer that will be checked for emptiness
 *	OUT:	1		- if the list is empty
 *			0		- if the list is not empty
 *	POST:	none.
 *	ERROR:	none.
 */
int isEmpty(VNode* list);

/**
 *	printList
 *	prints the list, using print as the procedure for doing so.
 *	IN:		list	- the list that we will print
 *			print	- a function pointer that should return the string
 *					  representation of the node's data.
 *	OUT:	void
 *	POST:	the string representation of the data has been printed to the
 *			screen
 *	ERROR:	list is null
 */
void printList(VNode* list, char* (*print)(void*));

/**
 *	destroyList
 *	destroys each node in the list, using del as a means of destroying each
 *	node
 *	IN:		list	- the list to be deleted.
 *			del		- a function pointer to the destroying method for the
 *					  data type recoreded in each node.
 *	OUT:	void
 *	POST:	list has been deallocated, and should be treated with caution.
 *	ERROR:	list is null
 */
void destroyList(VNode* list, void (*del)(void*));

/**
 *	size
 *	returns the number of elements in the list.
 *	IN:		list 	- the list that we will measure
 *	OUT:	size	- the number of elements that are in the list
 *	POST:	an integer has been returned.
 *	ERROR:	list is null (returns 0 anyway)
 */
int size(VNode* list);

/**
 *	get
 *	returns a node at the index specified, or return null.
 *	IN:		list 	- the list that will be searched and taken from
 *			index	- the index to be returned (hopefully in range)
 *	OUT:	the node that will be accessed, or null.
 *	POST:	a vnode has been returned.  DO NOT DELETE.
 *	ERROR:	list is null, or index is out of range.
 */
VNode* get(VNode* list, int index);


#endif
