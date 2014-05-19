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
	setupData();
	fprintf(stderr, "JIT imul result = %d\n", executeMem());

	checkVal(freeMem(), "freeing memory failed!");

	exit(EXIT_SUCCESS);
}

void setupData(void)
{
	movEaxNum(0); /** Answer for the imul **/
	imul(5, 7);
	popEax();
	ret();

	checkVal(allocMem(), 		   "memory allocation failed!"      );
	checkVal(copyExecutableCode(), "copying executable code failed!");
}

void checkVal(bool func, char* msg)
{
	if(!func)
	{
		fprintf(stderr, "ERROR: %s", msg);
		exit(EXIT_FAILURE);
	}
}


