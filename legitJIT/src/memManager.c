/*
===========================================================================================
Name         :  memManager.c
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014
Description  :  This is the implementation file that handles all the memory in the 
				legitJIT runtime
===========================================================================================
*/

#include <sys/mman.h> 	/** mmap, munmap 				**/
#include <string.h>   	/** memcpy 						**/
#include <stdlib.h>   	/** stdlib 						**/
#include <assert.h>   	/** assert 						**/

#include "memManager.h" /** The memManager header  **/

struct memManagerVars mMV;

/**
* Allocates writable/executable memory and then copies runtime code into allocated memory
* Note: real programs should not map memory both writable and executable because it is a 
* security risk.
**/
void* allocMem(void)
{
	void* ptrMem;

	ptrMem = mmap(NULL, sizeof(mMV.asmCode),  PROT_WRITE | PROT_EXEC, MAP_ANON | 
											  MAP_PRIVATE, -1, 0);

	if(ptrMem == (void*)-1) 
	{
		assert(ptrMem == (void*)-1);
		return NULL;
	}

	return ptrMem;
}

/**
*  Copies processor opcodes to the executable memory buffer
**/
bool copyExecutableCode(void)
{
	if(!mMV.memSpace || !mMV.asmCode)
		return false;

	memcpy(mMV.memSpace, mMV.asmCode, sizeof(mMV.asmCode));
	return true;
}

/**
*  Frees previously allocated memory allocated by allocMem()
*
*  Returns 1 if successful and 0 if it fails
**/
bool freeMem(void)
{
	if(mMV.memSpace && mMV.asmCode)
	{
		munmap(mMV.memSpace, sizeof(mMV.asmCode));
		return true;
	}
	return false;
}

/**
*  Executes memory buffer full of opcodes as a function.
*  Returns the function pointer func()
**/
int executeMem(void)
{
	JittedFunc func = mMV.memSpace;
	return func();
}
