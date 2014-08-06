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

int main(int argc, char **argv)
{
	int res;

	char o;
  int num1, num2;

	initTiming();

	printf("[?] Enter the sum, like this \"NUM2 OPERAND NUM2\": ");
	scanf("%i %c %i", &num1, &o, &num2);

	movEaxNum(0);

	switch(o)
	{
	case '*':
		imul(num1, num2);
		break;
	case '/':
		idiv(num1, num2);
		break;
	case '+':
		add (num1, num2);
		break;
	case '-':
		sub (num1, num2);
		break;
	default:
		printf("default\n");
	}

	popEax();
	ret();

	checkVal(allocMem(), 		       "memory allocation failed!"      );
	checkVal(copyExecutableCode(), "copying executable code failed!");

	startTimer();
	/* Execute the JIT'ted function pointer containing opcodes */
  res = executeMem();
	finishTimer();

  fprintf(stderr, "JIT result   = %d\n",   res);
  fprintf(stderr, "multiplier   = %u / %u\n",   getTimebaseNumer(), getTimebaseDenom());
  fprintf(stderr, "elapsed time = %llu nanos\n", getElapsedTime());

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
		fprintf(stderr, "ERROR: %s\n", msg);
		exit(EXIT_FAILURE);
	}
}
