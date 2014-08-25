#include "floatAsmInstructions.h"

#include <stdio.h>
#include <assert.h>

struct memManagerVars mMV;
byte* position = mMV.asmCode;

void emit(I386_Opcode opcode)
{
  if(false) {}

#define S_OP(name, b, code) \
  else if(name == opcode) *position++ = code;
  I386_S_OPCODE_TABLE(S_OP)
#undef S_OP
#define D_OP(name, b, code1, code2) \
  else if(name == opcode) {*position++ = code1; *position++ = code2;}
  I386_D_OPCODE_TABLE(D_OP)
#undef D_OP
#define T_OP(name, b, code1, code2, code3) \
  else if(name == opcode) {*position++ = code1; *position++ = code2; *position++ = code3;}
  I386_T_OPCODE_TABLE(T_OP)
#undef T_OP

  else assert(false);
}

void emit_1a_b(I386_Opcode opcode, int num)
{
  if(false) {}

#define S_OP(name, b, code1) \
  else if(name == opcode) {*position++ = code1; *position++ = (byte)num;}
  I386_S_OPCODE_TABLE(S_OP)
#undef S_OP
#define D_OP(name, b, code1, code2) \
  else if(name == opcode) {*position++ = code1; *position++ = code2; *position++ = (byte)num;}
  I386_D_OPCODE_TABLE(D_OP)
#undef D_OP

  else assert(false);
}

void emit_1a_i(I386_Opcode opcode, int num)
{
  if(false) {}

#define S_OP(name, b, code) \
  else if(name == opcode) *position++ = code;
  I386_S_OPCODE_TABLE(S_OP)
#undef S_OP
#define D_OP(name, b, code1, code2) \
  else if(name == opcode) {*position++ = code1; *position++ = code2;}
  I386_D_OPCODE_TABLE(D_OP)
#undef D_OP

  else assert(false);

  int* pint;
  pint = (void*)position;
  *pint++ = num;
  position = (void*)pint;
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
