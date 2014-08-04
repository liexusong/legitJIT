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

#include "timer.h"
#include "memManager.h"
#include "asmInstructions.h"

void checkVal (bool func, char* msg);

int main()
{
	int res;

	initTiming();

	/* Sets up the data for the JIT function*/
	movEaxNum(0);
	imul(5, 7);
	popEax();
	ret();

	checkVal(allocMem(), 		       "memory allocation failed!"      );
	checkVal(copyExecutableCode(), "copying executable code failed!");

	startTimer();
	/* Execute the JIT'ted function pointer containing opcodes */
  res = executeMem();
	finishTimer();

  fprintf(stderr, "JIT imul result = %d\n",   res);
  fprintf(stderr, "multiplier   %u / %u\n",   getTimebaseNumer(), getTimebaseDenom());
  fprintf(stderr, "elapsed time    = %llu nanos\n", getElapsedTime());

  /*
  * Frees the memory... Because if I dont clean up people tend to yell at me
  * over IRC when i ask for help.
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
