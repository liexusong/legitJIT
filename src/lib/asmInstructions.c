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
  *position++ = 0xb8;
  pint = (void*)position;
  *pint++ = x;
  position = (void*)pint;
}

void movEbxNum(int x)
{
  int* pint;
  *position++ = 0xbb;
  pint = (void*)position;
  *pint++ = x;
  position = (void*)pint;
}

void pushEax(void)
{
    *position++ = PUSHAX;
}

void pushEdx(void)
{
    *position++ = PUSHDX;
}

void pushEbx(void)
{
    *position++ = 0x53;
}

void popEcx(void)
{
    *position++ = POPCX;
}

void popEbx(void)
{
    *position++ = 0x5b;
}

void popEax(void)
{
    *position++ = POPAX;
}

void popEdx(void)
{
    *position++ = POPDX;
}

void addNum(int x)
{
    movEaxNum(x);
    pushEax();
}

void addNumEbx(int x)
{
    movEbxNum(x);
    pushEbx();
}

void imul(int x, int y)
{
	addNum(x);
	addNum(y);

  popEcx();
  popEax();

	*position++ = 0xf7;
	*position++ = 0xe9;

	pushEax();
}

void idiv(int x, int y)
{
  addNum(x);
  addNum(y);

  popEcx();
  popEax();

  *position++ = 0xf7;
  *position++ = 0xf3;

  pushEax();
}


void sub(int x, int y)
{
  addNum(x);
  addNum(y);
  popEcx();
  popEax();

  *position++ = 0x29;
  *position++ = 0xc8;

  pushEax();
}

void add(int x, int y)
{
	addNum(x);
	addNum(y);
	popEcx();
	popEax();

	*position++ = 0x01;
	*position++ = 0xc8;

	pushEax();
}
