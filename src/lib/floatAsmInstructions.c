/*
===========================================================================================
Name         :  FloatAsmInstructions.c
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014
Description  :  This is the header interface for writing to the executable memory space
        (mMV.memSpace)
===========================================================================================
*/

#include "floatAsmInstructions.h"

struct memManagerVars mMV;
byte* position = mMV.asmCode;

void ret(void)
{
    *position++  = 0xc3;
}

void leave(void)
{
    *position++  = 0xc9;
}

void pushEax(void)
{
    *position++ = 0x50;
}

void pushEcx(void)
{
    *position++ = 0x51;
}

// Works only if the memory you want isn't more than 256
// TODO: add a facility for numbers bigger then one byte
void enter32(int mem, int nest)
{
  *position++ = 0xc8;
  *position++ = (byte)mem;
  *position++ = 0x00;
  *position++ = (byte)nest;
}

void fild32Ebp(int x)
{
  *position++ = 0xdb;
  *position++ = 0x45;
  *position++ = (signed char)x;
}

void movNumEax(int num)
{
  int* pint;
  *position++ = 0xb8;
  pint = (void*)position;
  *pint++ = num;
  position = (void*)pint;
}

void movMemEax_Ebp_disp(int num)
{
  *position++ = 0x8b;
  *position++ = 0x45;

  *position++ = (byte)num;
}

void movNumEcx(int num)
{
  int *foo;

  *position++ = 0xb9;
  foo = (void*)position;
  *foo++ = num;
  position = (void*)foo;
}

void fildDwordEsp(void)
{
  *position++ = 0xdb;
  *position++ = 0x04;
  *position++ = 0x24;
}

void fistpDwordEbp(int num)
{
  *position++ = 0xdb;
  *position++ = 0x5d;

  *position++ = (byte)num;
}

void fadd()
{
  *position++ = 0xde;
  *position++ = 0xc1;
}

void fsub()
{
  *position++ = 0xde;
  *position++ = 0xe9;
}

void fmul()
{
  *position++ = 0xde;
  *position++ = 0xc9;
}

void fdiv()
{
  *position++ = 0xde;
  *position++ = 0xf9;
}
