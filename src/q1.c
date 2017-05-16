/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *	this file contains the main function, which will
 *	call the menu function from rental.c/h, causing
 *	the program to begin its primary function.
 */

#include "rental.h"
#include <stdio.h>

/**
 *	main
 *	this is the entry point for the car rental executable.
 *	it does not handle any error checking, other than to return 1.
 *	all error checking is done internally within menu.
 *	IN:		none.
 *	OUT:	0		- on success
 *		    1		- on failure.
 *	POST:	assets/inventory.txt will have been modified.
 *	ERROR:	various; see menu() in rental.h/c
 */
int main()
{
	int success;

	success = menu();

	if(success != 0)
	{
		printf("Uh oh!  An error occured.\nSorry...\n");
		return 1;
	}

	return 0;
}
