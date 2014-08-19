#ifndef FLOATASMINSTRUCTIONS_H_
#define FLOATASMINSTRUCTIONS_H_

#include "memManager.h"
#include <stdio.h>

#define SINGLE_OPCODE_TABLE(S_OP) \
S_OP(ret,      0xc3) \
S_OP(leave,    0xc9) \
S_OP(push_eax, 0x50) \
S_OP(push_ecx, 0x51)

#define DUAL_OPCODE_TABLE(D_OP) \
D_OP(fadd, 0xde, 0xc1) \
D_OP(fsub, 0xde, 0xe9) \
D_OP(fmul, 0xde, 0xc9) \
D_OP(fdiv, 0xde, 0xf9)

typedef enum
{
#define S_OP(name, code) name,
  SINGLE_OPCODE_TABLE(S_OP)
#undef S_OP
} S_Opcode;

typedef enum
{
#define D_OP(name, code1, code2) name,
  DUAL_OPCODE_TABLE(D_OP)
#undef D_OP
} D_Opcode;

void s_emit(S_Opcode opcode);
void d_emit(D_Opcode opcode);

void enter32(int m, int n);
void fild32Ebp(int x);
void movNumEax(int num);
void movMemEax_Ebp_disp(int num);
void movNumEcx(int num);
void fildDwordEsp(void);
void fistpDwordEbp(int num);

#endif /* FLOATASMINSTRUCTIONS_H_ */
