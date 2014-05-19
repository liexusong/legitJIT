/*
 ===============================================================================================================================
 Name        : main.c
 Author      : Vs37nX
 Version     : 0.2
 Copyright   : You can copy any part of this code AS LONG as you mention me somewhere in the projects credits or contributors
 Description : The main file for the legitJIT project... controls all operations
 ===============================================================================================================================
 */

#include <stdio.h>    			/** Printf 				**/
#include <stdlib.h>   			/** Stdlib 				**/
#include <assert.h>   			/** Assert 				**/

#include "memManager.h"       /** MemoryManagement **/
#include "asmInstructions.h"  /** The actual logic **/

struct memManagerVars mMV;

void setupData(void)
{
	movEaxNum(0); /** padding for awnser **/
	imul(5, 7);
	popEax();
	ret();

	mMV.memSpace = allocMem();
	if(copyExecutableCode() == false)
	{
		printf("copying executable code failed...");
	}

}

/** int argc, char *argv[] **/
int main()
{	
	long res;

	setupData();
	res = executeMem();
	
	printf("JIT imul result = %d\n", res);

	res = 0;
	freeMem();

	return 0;
}

