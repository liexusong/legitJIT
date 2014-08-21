#include "floatAsmInstructions.h"

struct memManagerVars mMV;
byte* position = mMV.asmCode;

void s_emit(S_Opcode opcode)
{
#define S_OP(name, code) \
  if(name == opcode) *position++ = code;
  SINGLE_OPCODE_TABLE(S_OP)
#undef S_OP
}

void d_emit(D_Opcode opcode)
{
#define D_OP(name, code1, code2) \
  if(name == opcode) {*position++ = code1; *position++ = code2;}
  DUAL_OPCODE_TABLE(D_OP)
#undef D_OP
}

void t_emit(T_Opcode opcode)
{
#define T_OP(name, code1, code2, code3) \
  if(name == opcode) {*position++ = code1; *position++ = code2; *position++ = code3;}
  TRI_OPCODE_TABLE(T_OP)
#undef T_OP
}

void d_emit_1a_b(D_Opcode opcode, int num)
{
#define D_OP(name, code1, code2) \
  if(name == opcode) {*position++ = code1; *position++ = code2; *position++ = (byte)num;}
  DUAL_OPCODE_TABLE(D_OP)
#undef D_OP
}

void s_emit_1a_i(S_Opcode opcode, int num)
{
#define S_OP(name, code) \
  if(name == opcode) *position++ = code;
  SINGLE_OPCODE_TABLE(S_OP)
#undef S_OP

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
