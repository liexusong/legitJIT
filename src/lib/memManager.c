#include "memManager.h"

#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct memManagerVars mMV;

void dump(void)
{
	int i;
	for (i = 0; i < 255; ++i)
	{
  	printf("asmCode[%d] %c", i, mMV.asmCode[i]);
  }
}

/**
* Allocates writable/executable memory and then copies runtime code into allocated memory
* Note: real programs should not map memory both writable and executable because it is a
* security risk.
**/
bool allocMem(void)
{
	void* ptrMem;

	ptrMem = mmap(NULL, sizeof(mMV.asmCode), PROT_WRITE | PROT_EXEC,
											 MAP_ANON   | MAP_PRIVATE,
											 -1, 0);

	if(ptrMem == (void*)-1)
	{
		assert(ptrMem == (void*)-1);
		return false;
	}

	mMV.memSpace = ptrMem;

	return true;
}

/**
* Copies processor opcodes to the executable memory buffer
**/
bool copyExecutableCode(void)
{
	if(!mMV.memSpace || !mMV.asmCode)
		return false;

	memcpy(mMV.memSpace, mMV.asmCode, sizeof(mMV.asmCode));
	return true;
}

/**
* Frees previously allocated memory allocated by allocMem().
*
* Returns 1 if successful and 0 if it fails.
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
* Executes memory buffer full of opcodes.
*
* Returns the function pointer func().
**/
int executeMem(void)
{
	JittedFunc func = mMV.memSpace;
	return func();
}

float executeMemFloat(void)
{
	FloatJittedFunc func = mMV.memSpace;
	return func();
}
