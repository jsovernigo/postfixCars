/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *	This file contains the function to be used to solve
 *	post fix expressions for the course CIS2520 in the
 *	University of Guelph.  Please note that the concept
 *	of solving postfix using a stack was presenteed to
 *	the author by Professor Fangju Wang, who teaches
 *	the same course.
 */

#ifndef __GSOVERNIGO_PFIX_H__
#define __GSOVERNIGO_PFIX_H__

#define DIVIDE_BY_ZERO_ERROR	-1
#define INVALID_OPERATOR_ERROR 	-2
#define PFIX_SYNTAX_ERROR		-3
#define VALID_PARAMETER_ERROR	-4

/**
 *	solve
 *	evaluates the passed in post fix expression by pushing operands
 *	to a stack, and popping and evaluating them when an operator is
 *	found.
 *	IN:		expression	- the expression that will be evaluated.
 *			err			- an integer pointer that should be updated.
 *	OUT:	answer		- the solution to the expression.
 *	POST:	err has been updated to reflect the error status of the
 *			calculation's success or failure.
 *	ERROR:	if expression is null, return 0 if err is valid
 *			but, if err is invalid, return INT_MIN
 *			because INT_MIN is a valid but unlikely possible solution,
 *			you must make sure to make err a valid integer pointer,
 *			so that the errors can be signaled, should they occur.
 */
double solve(char* expression, int* err);

/**
 *	operate
 *	actually operates and returns the operation specified by op as
 *	acted upon the two arguments, num1 and num2.
 *	IN:		num1		- the first number of the expression
 *			num2		- the second number of the expression
 *			op			- the operator that will be used to operate
 *						  upon num1 and num2.
 *			err			- an integer pointer to an integer that will
 *						  be used to store errors.
 *	OUT:	sol			- the solution to the passed in expressions
 *	POST:	err has been modified. possible values:
 *				- in case of div/0, err set to DIVIDE_BY_ZERO_ERROR
 *				- in case of an invalid operator, err set to INVALID_OPERATOR_ERROR
 *				- in case of success, err will be set to 0
 *	ERROR:	div by 0 or op is invalid. err flag will be set to code
 */
double operate(double num1, double num2, char op, int* err);

/**
 *	destroy
 *	takes a void pointer to an integer, and deletes it after casting
 *	it to an int pointer (this is used in order to utilize a void
 *	pointer linked list; it will be passed into another destroyNode
 *	function as a function pointer.
 *	INT:	num			- the number to be destroyed.
 *	OUT:	void
 *	POST:	num has been deallocated, and should be used with caution.
 *	ERROR:	none.
 */
void destroy(void* num);

/**
 *	getIntFromVoid
 *	returns the dereferenced (as a double) void pointer's data.  This is
 *	here just because it makes other code easier to read.
 *	IN:		num			- a void pointer to (hopefully) some double data.
 *	OUT:	val			- the value of the double
 *	POST:	none.
 *	ERROR:	num is NULL, or is not a double (uncatchable)
 */
double getDoubleFromVoid(void* num);

#endif
