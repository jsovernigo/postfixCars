CC		=gcc
CFLAGS	=-Wall -std=c99 -g
OBJECTS	=q1.o q2.o linkedList.o stack.o pFix.o rental.o
EXEC1	=q1
EXEC2	=q2
COMP	=build
FILES	=./src/q1.c ./src/q2.c ./src/stack.c ./src/linkedList.c
INCLUDE	=./include


#
# This specifies which rules take no parameters.
#
.PHONY: all clean


all: $(COMP)


#
# This is the normal compilation rule.  Simply typing 'make' will run this
#
$(COMP): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC1) ./q1.o ./linkedList.o ./rental.o
	$(CC) $(CFLAGS) -o $(EXEC2) ./q2.o ./linkedList.o ./stack.o ./pFix.o -lm

#
# Object rules:
#

q1.o: ./src/q1.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/q1.c -I$(INCLUDE)

q2.o: ./src/q2.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/q2.c -I$(INCLUDE)

linkedList.o: ./src/linkedList.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/linkedList.c -I$(INCLUDE)

stack.o: ./src/stack.c ./src/linkedList.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/stack.c -I$(INCLUDE)	
	
pFix.o: ./src/pFix.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/pFix.c -I$(INCLUDE) -lm

rental.o: ./src/rental.c $(wildcard include/*.h)
	$(CC) -c $(CFLAGS) -o $@ ./src/rental.c -I$(INCLUDE)


#
# Clean-up rules.  Removes the executable and objects.
#

clean:
	rm $(EXEC1) $(EXEC2) $(OBJECTS)
