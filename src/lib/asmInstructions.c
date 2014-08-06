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

void clearEax(void)
{
  *position++  = 0x31;
  *position++  = 0xc0;
}

void clearEbx(void)
{
  *position++  = 0x31;
  *position++  = 0xdb;
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

void movEcxNum(int x)
{
  int* pint;
  *position++ = 0xb9;
  pint = (void*)position;
  *pint++ = x;
  position = (void*)pint;
}

void movEdxNum(int x)
{
  int* pint;
  *position++ = 0xba;
  pint = (void*)position;
  *pint++ = x;
  position = (void*)pint;
}

void pushEax(void)
{
    *position++ = PUSHAX;
}

void popEax(void)
{
    *position++ = POPAX;
}

void imul(int x, int y)
{
  movEaxNum(x);
  movEbxNum(y);

	*position++ = 0xf7;
	*position++ = 0xe3;

	pushEax();
}

void idiv(int x, int y)
{
  movEaxNum(x);
  *position++ = 0x99; // cdq
  movEcxNum(y);

  *position++ = 0xf7;
  *position++ = 0xf9;

  pushEax();
}


void sub(int x, int y)
{
  movEaxNum(x);
  movEbxNum(y);

  *position++ = 0x29;
  *position++ = 0xd8;

  pushEax();
}

void add(int x, int y)
{
  movEaxNum(x);
  movEbxNum(y);

	*position++ = 0x01;
	*position++ = 0xd8;

	pushEax();
}
