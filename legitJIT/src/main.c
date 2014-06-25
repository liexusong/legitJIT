/*
==============================================================================================
Name         :  main.c
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014
Description  :  The main file for the legitJIT project... controls all operations that occur 
				in the system
==============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "memManager.h"
#include "asmInstructions.h"

void checkVal (bool func, char* msg);
void setupData(void);

int main()
{
	/* Sets up the data for the JIT function*/
	movEaxNum(0);
	imul(5, 7);
	popEax();
	ret();

	checkVal(allocMem(), 		   "memory allocation failed!"      );
	checkVal(copyExecutableCode(), "copying executable code failed!");

	/* Execute the JIT'ted function pointer containing opcodes */
    fprintf(stderr, "JIT imul result = %d\n", executeMem());

    /*
    * Frees the memory... Because if I dont people tend to yell at me
    * over IRC (Cough #c Cough).
    */
	checkVal(freeMem(), "freeing memory failed!");

	exit(EXIT_SUCCESS);
}

/**
* Checks the return value from a statement and prints the associated error
* message if it is false
**/
void checkVal(bool func, char* msg)
{
	if(!func)
	{
		fprintf(stderr, "ERROR: %s", msg);
		exit(EXIT_FAILURE);
	}
}
