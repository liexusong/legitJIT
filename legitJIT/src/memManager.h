/*
 ===============================================================================================================================
 Name        : memManager.h
 Author      : Vs37nX
 Version     : 0.2
 Copyright   : You can copy any part of this code AS LONG as you mention me somewhere in the projects credits or contributors
 Description : This is the header interface for all the memory management applications
 ===============================================================================================================================
 */

#ifndef MEMMANAGER_H_
#define MEMMANAGER_H_

typedef unsigned char byte;
typedef enum bool { false, true } bool;

typedef int (*JittedFunc)();

struct memManagerVars
{
	byte asmCode [255];
	void* memSpace;
};

void* allocMem();
bool  copyExecutableCode();
bool  freeMem();
int executeMem();

#endif /* MEMMANAGER_H_ */
