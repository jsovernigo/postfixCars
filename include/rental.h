/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *	this file contains the declarations for functions
 *	used in the menu of the Car rental program for
 *	CIS2520.
 *	All functions here are instantiated in the c file
 *	of the same name.
 */
#ifndef __GSOVERNIGO_RENTAL_H__
#define __GSOVERNIGO_RENTAL_H__

#include "linkedList.h"

#define END_OF_SECTION "EOS"

typedef struct car
{
	int miles;
	char* lPlate;
}Car;

/**
 *	createCar
 *	creates a new car struct, all fields allocated and populated
 *	IN:		miles	- the mileage of the car
 *			lPlate	- the license plate of the car.
 *	OUT:	a new Car struct pointer.
 *	POST:	car has been allocated and returned, and should be
 *			freed when its usefulness expires.
 *	ERROR:	lPlate is null.
 */
Car* createCar(int miles, char* lPlate);

/**
 *	destroyCar
 *	destroys the car struct after deallocating its fields.
 *	IN:		car		- the car struct that will be deallocated.
 *	OUT:	void
 *	POST:	car has been deallocated and should be handled with care.
 *	ERROR:	none.
 */
void destroyCar(void* car);

/**
 *	compareCar
 *	compares two void poiners referring to Car structs.  This is
 *	used as a function pointer that will be passed into a sorted
 *	add method in a void linked list (hence the void pointers)
 *	IN:		car		- the car we are checking against another.
 *			otherCar- the car being checked against.
 *	OUT:	0		- if the two pointer's contents are equal.
 *			<0		- if otherCar is AFTER car
 *			>0		- if otherCar is BEFORE car.
 *	POST:	none.
 *	ERROR:	either pointer is null. (null is considered LESS than
 *			valid input)
 */
int compareCar(void* car, void* otherCar);

/**
 *	printCar
 *	prints a car struct, returning the string representation of the car.
 *	IN:		car		- the car to be printed.
 *	OUT:	msg		- the string representation of the car struct.
 *	POST:	msg has been allocated and should be freed by the caller.
 *	ERROR:	malloc failes (return NULL) car is null (return NULL)
 */
char* printCar(void* car);

/**
 *	menu
 *	this is the main command loop of the program.  It returns 0 on
 *	success (no errors) or an error code on failure.
 *	IN:		void
 *	OUT:	0 on success, error code on failure.
 *	POST:	a number has been returned!
 *	ERROR:	several.  Fileio fails, malloc fails... the list is 
 *			extensive, believe me.
 */
int menu();

/**
 *	getChoice
 *	returns the user input integer transaction code (thats a mouthful)
 *	IN:		none.
 *	OUT:	a user-entered VALID transaction code, or -1 on (fatal) error
 *	POST:	an integer has been returned.
 *	ERROR:	none.
 */
int getChoice();

/**
 *	getLPlate
 *	gets user input for a license plate, and returns the malloc'd string.
 *	IN:		void
 *	OUT:	a user-input license plate.
 *	POST:	returned string has been alloced so free it when youre done.
 *	ERROR:	malloc fails.
 */
char* getLPlate();

/**
 *	getCarByPlate
 *	returns a VNode that contains a car* that has the same lPlate that
 *	was passed in as a parameter.
 *	IN:		lPlate	- the license plate to search by
 *	OUT:	car		- the VNode that contains a car struct with the same
 *					  license plate as lPlate.
 *			NULL	- if no such car was found.
 *	POST:	VNode has been returned, lPlate should be deallocated if it
 *			is no longer of any use to the caller.
 *	ERROR:	lPlate is NULL: returns null.
 */
VNode* getCarByPlate(VNode* list, char* lPlate);

/**
 *	writeToFile
 *	writes the contents of the lists to a predefined file.  Note that
 *	the contenst of the linked lists are printed in the order they 
 *	appear in this function, meaning they should be read in that order.
 *	They will be separated each by a Delimiter.
 *	IN:		avail	- the available cars linked list
 *			rented 	- the rented cars linked list
 *			repair	- the for-repair cars linked list.
 *	OUT:	number of cars printed, or negative error code on failure.
 *	POST:	all the files in assets/ have been updated.
 *	ERROR:	FILEIO error, any of the lists are null.
 */
int writeToFile(VNode* avail, VNode* rented, VNode* repair);

/**
 *	readFromFile 
 *	the inverse of the above function, this function should be invoked
 *	immediately upon launching the program.  It will populate the linked
 *	lists with data, such that they contain valid car structs.  The lists
 *	are stored in their respective order as parameters in this function,
 *	and will be separated by a delimiter.
 *	IN:		avail	- the available cars
 *			rented 	- the rented cars
 *			repair	- the broken cars
 *	OUT:	0 on sucecss or error code on failure
 *	POST:	
 */
int readFromFile(VNode** avail, VNode** rented, VNode** repair);

/**
 *	prompt
 *	prompts the user with a message to strike any key.
 *	IN:		3 pointer-pointers to the lists that will be populated.
 *	OUT:	void
 *	POST:	a message has been printed to the screen
 *	ERROR:	none
 */
void prompt();

/**
 *	getPrice
 *	finds the price that will be charged to the user.
 *	IN:		the car to be updated
 *	OUT:	price	- the price
 *	POST:	current->miles has been updated
 *	ERROR:	current is null. 
 */
double getPrice(VNode* current);

#endif
