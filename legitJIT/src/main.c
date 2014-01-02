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
#include "timer.h"

#define debug

struct memManagerVars mMV;

void setupData(void){

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

int stdMul(void){
	int x,y;

#ifdef debug
	startTimer();
#endif

	x = 5;
	y = 7;

	return x*y;
}

/** int argc, char *argv[] **/
int main()
{	
	long res;
	
#ifdef debug
	startTimer();
#endif

	setupData();
	
#ifdef debug
	stopTimer();
	reportTime("setupData", time_elapsed_nanos);
	time_elapsed_nanos = 0.0;
	startTimer();
#endif
	
	res = executeMem();
	
#ifdef debug
	stopTimer();
	reportTime("imul", time_elapsed_nanos);
#endif
	
	printf("JIT imul result = %d\n", res);

	res = 0;

	freeMem();

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/

#ifdef debug
	startTimer();
#endif
	
	res = stdMul();

#ifdef debug
	stopTimer();
	reportTime("std c imul", time_elapsed_nanos);
#endif
	
	printf("std c imul result = %ld\n", res);
	res = 0;

	return 0;
}

