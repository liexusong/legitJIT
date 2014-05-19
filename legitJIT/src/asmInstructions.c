/*
===========================================================================================
Name         :  asmInstructions.c
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014
Description  :  This is the header interface for writing to the executable memory space 
				(mMV.memSpace)
===========================================================================================
*/

#include "asmInstructions.h"

struct memManagerVars mMV;
byte* position = mMV.asmCode;

void ret(void)
{
    *position++  = 0xc3;
}

void movEaxNum(int x)
{
	int* pint;
    *position++ = 0xb8;
    pint = (void*)position;
    *pint++ = x;
    position = (void*)pint;
}


void pushEax(void)
{
    *position++ = 0x50;
}


void popEcx(void)
{
    *position++ = 0x59;
}


void popEax(void)
{
    *position++ = 0x58;
}


void addNum(int x)
{
    movEaxNum(x);
    pushEax();
}

inline void imul(int x, int y)
{
	addNum(x);
	addNum(y);

    *position++ = 0x59;
    *position++ = 0x58;

	*position++ = 0xF7;
	*position++ = 0xE9;

	*position++ = 0x50;
}


void add(int x, int y)
{
	addNum(x);
	addNum(y);
	popEcx();
	popEax();

	*position++ = 0x03;
	*position++ = 0xC1;

	pushEax();
}

