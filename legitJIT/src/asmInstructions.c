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
    *position++  = RET;
}

void movEaxNum(int x)
{
	int* pint;
    *position++ = MOVAX;
    pint = (void*)position;
    *pint++ = x;
    position = (void*)pint;
}


void pushEax(void)
{
    *position++ = PUSHAX;
}


void popEcx(void)
{
    *position++ = POPCX;
}


void popEax(void)
{
    *position++ = POPAX;
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

    *position++ = POPCX;
    *position++ = POPAX;

	*position++ = IMULRMW;
	*position++ = JMPNP;

	*position++ = PUSHAX;
}


void add(int x, int y)
{
	addNum(x);
	addNum(y);
	popEcx();
	popEax();

	*position++ = ADDRW;
	*position++ = ROTATE;

	pushEax();
}

