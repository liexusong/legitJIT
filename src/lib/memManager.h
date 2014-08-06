/*
===============================================================================================
Name         :  memManager.h
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014 Description : This is the header interface for all the
				memory management applications
===============================================================================================
*/

#ifndef MEMMANAGER_H_
#define MEMMANAGER_H_

#include "timer.h"

typedef unsigned char byte;
typedef enum bool {false, true} bool;

typedef int (*JittedFunc)(void);

struct memManagerVars
{
	byte asmCode [255];
	void* memSpace;
};

extern bool allocMem(void);
extern bool copyExecutableCode(void);
extern bool makeMemoryExecutable(void);
extern bool freeMem(void);
extern inline int executeMem(void);

//void outputToFile(char* filename);

#endif /* MEMMANAGER_H_ */
