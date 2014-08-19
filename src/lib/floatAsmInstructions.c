#include "floatAsmInstructions.h"

struct memManagerVars mMV;
byte* position = mMV.asmCode;

void s_emit(S_Opcode opcode)
{
#define S_OP(name, code) if(name == opcode) *position++ = code;
  SINGLE_OPCODE_TABLE(S_OP)
#undef S_OP
}

void d_emit(D_Opcode opcode)
{
#define D_OP(name, code1, code2) if(name == opcode) {*position++ = code1; *position++ = code2;}
  DUAL_OPCODE_TABLE(D_OP)
#undef D_OP
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
