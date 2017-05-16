/**
 * 	Giuliano Sovernigo			0948924
 * 	CIS*2520					A2: cars and postfix
 * 	Due October 24, 2016
 *	This file contains the code for the rental car
 *	inventory menu which was defined in the header
 *	file of the same name as this.  It will be used
 *	in CIS2520 A2.
 */

#include "rental.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Car* createCar(int miles, char* lPlate)
{
	Car* newCar;
	newCar = malloc(sizeof(Car));

	if(newCar == NULL)
	{
		return NULL;
	}
	newCar->lPlate = malloc(sizeof(char) * 24);

	newCar->miles = miles;
	strcpy(newCar->lPlate, lPlate); // assign the car's new fields to the passed in values.

	return newCar;
}

void destroyCar(void* car)
{
	if(car != NULL)
	{
		free(((Car*)car)->lPlate); // free the contents
	}
	free(car);
	return;
}

int compareCar(void* car, void* otherCar)
{
	if(car == NULL)
	{
		return -1;
	}
	if(otherCar == NULL)
	{
		return 1;
	}

	return ((Car*)car)->miles - ((Car*)otherCar)->miles; // return the miles of the first, minus the miles of the second (produces a "larger int means first is greater" behaviour specified by the linked list module.
}

char* printCar(void* car)
{
	char* msg;
	if(car == NULL)
	{
		return NULL;
	}
	else if (((Car*)car)->lPlate == NULL) // if the contents of the struct are null
	{
		return NULL;
	}	

	msg = malloc(sizeof(char) * 50); // make a new message

	snprintf(msg, 49, "License Plate: %s\nMileage: %d", ((Car*)car)->lPlate, ((Car*)car)->miles);
	return msg;
}

int menu()
{

	int tCode;

	int numCars;

	VNode* available;
	VNode* rented;
	VNode* repair;

	available = NULL;
	rented = NULL;
	repair = NULL;

	printf("Reading in cars from database... ");
	numCars = readFromFile(&available, &rented, &repair);
	printf("Success.\nA total of %d cars were read in.\n\n",numCars);


	do
	{
		printf("Welcome to the Car Inventory system.\n1. Add a new car.\n2. Return a rented car.\n3. Return a car to be repaired.\n4. Transfer from repairs to available.\n5. Rent the first available car.\n6. Print all inventory lists.\n7. Quit.\n");
		tCode = getChoice();
		
		if(tCode == 1) // add a new car
		{
			int miles;
			int success;
			char* lp;
			char input[20];
			char* msg;
			VNode* new;

			miles = 50000; // default value

			lp = getLPlate(); // get the user input license plate
			if(getCarByPlate(available, lp) != NULL || getCarByPlate(rented, lp) != NULL || getCarByPlate(repair, lp) != NULL) // if we found a car with this license plate already in the system.
			{
				printf("A car with that license plate was already found.\n");
				continue;
			}
			
			do
			{
				printf("Please enter the mileage:\n");
				fgets(input, 20, stdin);
				success = sscanf(input, "%d", &miles);
				if(success == EOF)
				{
					miles = -1;
				}
				
			}while(success == EOF || miles < 0); // get input until a valid int appears

			new = createNode((void*)createCar(miles, lp));
			available = addSort(available, new, &compareCar);
			msg = printNode(new, &printCar);

			printf("Car \n%s\nhas been added to the inventory.\n", msg);
			free(msg);
			prompt();
		}
		else if(tCode == 2) // return a Car
		{
			char* lp;
			int i;
			char* msg;
			VNode* trans;

			trans = NULL;

			printf("Searching for a car in rented...\n");
			lp = getLPlate();

			for(i = 0; i < size(rented); i++) // loop through rented
			{
				VNode* cur;
				cur = get(rented, i);
				if(strcmp(((Car*)cur->data)->lPlate, lp) == 0) // if the two license plates are the same
				{
					trans = cur;
					rented = removeAt(rented, i); // remove trans from rented
					break;
				}
			}
			available = addSort(available, trans, &compareCar); // add trans to the available list
			if(trans != NULL)
			{
				double price;

				price = getPrice(trans);
				msg = printNode(trans, &printCar);
				printf("Car \n%s\nhas been transfered to available cars.\nThe charge will be $%.2lf\n", msg, price);
				free(msg);
			}
			else
			{
				printf("No car was found with that plate.\n");
			}
			prompt();
		}
		else if(tCode == 3) // send car to repair from rented
		{
			char* lp;
			char* msg;
			int i;
			VNode* trans;

			trans = NULL;

			printf("Searching for a car in rented...\n");
			lp = getLPlate();

			for(i = 0; i < size(rented); i++) // loop through rented
			{
				VNode* cur;
				cur = get(rented, i);
				if(strcmp(((Car*)cur->data)->lPlate, lp) == 0) // if the two license plates are the same
				{
					trans = cur;
					rented = removeAt(rented, i); // remove trans from rented
					break;
				}
			}
			repair = addSort(repair, trans, &compareCar); // add trans to the repairs list
			if(trans != NULL)
			{
				double price;
				msg = printNode(trans, &printCar);
				price = getPrice(trans);
				printf("Car \n%s\nhas been transfered to cars under repair.\nThe charge will be $%.2lf\n", msg, price);
				free(msg);
			}
			else
			{
				printf("No car was found with that plate.\n");
			}
			prompt();
		}
		else if(tCode == 4) // repair a car
		{
			char* lp;
			int i;
			char* msg;
			VNode* trans;

			trans = NULL;

			printf("Searching for a car in repairs...\n");
			lp = getLPlate();

			for(i = 0; i < size(repair); i++) // loop through repairs
			{
				VNode* cur;
				cur = get(repair, i);
				if(strcmp(((Car*)cur->data)->lPlate, lp) == 0) // if the two license plates are the same
				{
					trans = cur;
					repair = removeAt(repair, i); // remove trans from repairs
					break;
				}
			}
			available = addSort(available, trans, &compareCar); // add trans to the avail list
			if(trans != NULL)
			{
				msg = printNode(trans, &printCar);
				printf("Car \n%s\nhas been transfered to the available list.\n", msg);
				free(msg);
			}
			else
			{
				printf("No car was found with that plate.\n");
			}
			prompt();
		}
		else if(tCode == 5) // rent a car
		{
			int returnDate;
			VNode* rent;
			char* msg;

			printf("Please enter an anticipated return date: (yymmdd)\n");
			scanf("%d", &returnDate); // get the user defined return date.

			rent = get(available, 0);
			available = removeFromFront(available);
			rented = addSort(rented, rent, &compareCar);
			if(rent != NULL)
			{
				msg = printNode(rent, &printCar);
				printf("Car:\n%s\nhas been rented.\n", msg);
				free(msg);
			}
			else
			{
				printf("No cars are available to rent.\n");
			}
			prompt();

		}
		else if(tCode == 6) // print the list
		{
			printf("Available cars:\n");
			printList(available, &printCar);
			printf("\nRented Cars:\n");
			printList(rented, &printCar);
			printf("\nCars under repair:\n");
			printList(repair, &printCar);
			printf("\n");
		}
		else if(tCode == 7) // quit
		{
			printf("Goodbye!\n");
		}

	}while(tCode != 7);

	numCars = writeToFile(available, rented, repair); // write to the file.
	if(numCars < 0)
	{
		return -1;
	}

	return 0;
}

int getChoice()
{
	char* in;

	in = malloc(sizeof(char) * 10);
	if(in == NULL)
	{
		return -1;
	}

	do // repeat until valid number has been entered.
	{
		printf("Please enter a transaction code:\n");
		fgets(in, 10, stdin);
	}while(strchr("1234567", in[0]) < 0); // while the first character is not a valid transaction code.
	return (in[0] - '0');
}

char* getLPlate()
{
	char* ulp; // user license plate
	char in[20];

	ulp = malloc(sizeof(char)*20);
	if(ulp == NULL)
	{
		return NULL;
	}

	do // while nothing has been entered (basically just \n has been entered.)
	{
		printf("Please enter a license plate number:\n");
		fgets(in, 19, stdin); // gets the string from stdin
	}while(strlen(in) <= 1);
	sscanf(in, "%s", ulp);

	return ulp;
}

VNode* getCarByPlate(VNode* list, char* lPlate)
{
	int i;

	for(i = 0; i < size(list); i++) // loops through the cars
	{
		Car* car;

		car = (Car*)get(list, i)->data; // get the list at i's data, then cast it to a Car*
		if(strcmp(lPlate, car->lPlate) == 0) 
		{
			return get(list, i);
		}
	}
	return NULL;
}

int writeToFile(VNode* avail, VNode* rented, VNode* repair)
{
	FILE* outFile;
	int i;

	int cars;

	cars = 0;

	outFile = fopen("assets/inventory.txt","w"); // open the file for writing
	if(outFile == NULL)
	{
		return -1;
	}

	/*
	 *	Please note that while the linked lists are not explicitly
	 *	checked for null here, size(null) returns 0, and therefore
	 *	would prevent the list from being accessed in the loop.
	 */

	//go throught available cars first.
	for(i = 0; i < size(avail); i++)
	{
		int miles;
		char* lp;

		Car* car;

		car = (Car*)get(avail, i)->data; // gets the next car in the list
		miles = car->miles;
		lp = car->lPlate; // its fine to assign the refernce, since we are just printing it.

		fprintf(outFile, "%s,%d\n", lp, miles); // print the csv version of the car.
		cars++;
	}
	fprintf(outFile, "%s\n", END_OF_SECTION); // prints the end of section tag

	//next go through the rented cars.
	for(i = 0; i < size(rented); i++)
	{
		int miles;
		char* lp;

		Car* car;

		car = (Car*)get(rented, i)->data; // gets the next car in the list
		miles = car->miles;
		lp = car->lPlate; // its fine to assign the refernce, since we are just printing it.

		fprintf(outFile, "%s,%d\n", lp, miles); // print the csv version of the car.
		cars++;
	}
	fprintf(outFile, "%s\n", END_OF_SECTION); // prints the end of section tag

	//finally the repaired ones
	for(i = 0; i < size(repair); i++)
	{
		int miles;
		char* lp;

		Car* car;

		car = (Car*)get(repair, i)->data; // gets the next car in the list
		miles = car->miles;
		lp = car->lPlate; // its fine to assign the refernce, since we are just printing it.

		fprintf(outFile, "%s,%d\n", lp, miles); // print the csv version of the car.
		cars++;
	}
	fprintf(outFile, "%s\n", END_OF_SECTION);

	return cars;
}

int readFromFile(VNode** avail, VNode** rented, VNode** repair)
{
	char line[50];
	FILE* inFile;

	int cars;

	cars = 0;

	inFile = fopen("assets/inventory.txt", "r");
	if(inFile == NULL)
	{
		return -1;
	}

	while(fgets(line, 49, inFile) != NULL) // reads the available cars.
	{
		if(strstr(line, END_OF_SECTION) != NULL) // this means we have gotten to a new list
		{
			break;
		}
		else
		{
			char lp[50];
			int miles;
			Car* nc;

			sscanf(line, "%[^,],%d", lp, &miles); // gets the miles and license plate from the string.
			nc = createCar(miles, lp);

			*avail = addSort(*avail, createNode((void*)nc), &compareCar); // adds the new car, in its sorted location.
			cars++;
		}
	}

	while(fgets(line, 49, inFile) != NULL) // reads the rented cars.
	{
		if(strstr(line, END_OF_SECTION) != NULL) // this means we have gotten to a new list
		{
			break;
		}
		else
		{
			char lp[50];
			int miles;
			Car* nc;

			sscanf(line, "%[^,],%d", lp, &miles); // gets the miles and license plate from the string.
			nc = createCar(miles, lp);

			*rented = addSort(*rented, createNode((void*)nc), &compareCar); // adds the new car, in its sorted location.
			cars++;
		}
	}

	while(fgets(line, 49, inFile) != NULL) // reads the cars that are in for repair.
	{
		if(strstr(line, END_OF_SECTION) != NULL) // this means we have gotten to a new list
		{
			break;
		}
		else
		{
			char lp[50];
			int miles;
			Car* nc;

			sscanf(line, "%[^,],%d", lp, &miles); // gets the miles and license plate from the string.
			nc = createCar(miles, lp);

			*repair = addSort(*repair, createNode((void*)nc), &compareCar); // adds the new car, in its sorted location.
			cars++;
		}
	}
	return cars;
}

void prompt()
{
	printf("Strike any key to continue.\n");
	getchar();
	return;
}

double getPrice(VNode* current)
{
	int newMiles;
	char input[20];
	double price;
	int diff;
	int success;

	price = 40.00; // default rate

	if(current == NULL) // if input is invalid
	{
		return 0;
	}
	do // keep going until we get a valid int
	{
		printf("Please enter the returned mileage:\n");
		fgets(input, 19, stdin);
		success = sscanf(input, "%d", &newMiles);
		if(success == EOF)
		{
			newMiles = -1;
		}

	}while(success == EOF || newMiles < ((Car*)current->data)->miles);

	diff = newMiles - ((Car*)current->data)->miles;
	diff -= 100;

	price += (diff * 0.15);
	((Car*)current->data)->miles = newMiles; // update the miles.

	return price;

}
