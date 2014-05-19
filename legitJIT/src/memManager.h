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

typedef unsigned char byte;
typedef enum bool {false, true} bool;

typedef int (*JittedFunc)();

struct memManagerVars
{
	byte asmCode [255];
	void* memSpace;
};

bool allocMem();
bool copyExecutableCode();
bool freeMem();
int  executeMem();

#endif /* MEMMANAGER_H_ */
