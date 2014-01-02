/*
 ===============================================================================================================================
 Name        : asmInstructions.h
 Author      : Vs37nX
 Version     : 0.2
 Copyright   : You can copy any part of this code AS LONG as you mention me somewhere in the projects credits or contributors
 Description : This is the header interface for writing to the executable memory space (mMV.memSpace)
 ===============================================================================================================================
 */

#ifndef ASMINSTRUCTIONS_H_
#define ASMINSTRUCTIONS_H_

#include "memManager.h"

void ret(void);
void movEaxNum(int x);
void pushEax(void);
void popEcx(void);
void popEax(void);
void addNum(int x);
extern inline void imul(int x, int y);
extern void oldImul(int x, int y);
extern void add(int x, int y);

#endif /* ASMINSTRUCTIONS_H_ */
