#ifndef FLOATASMINSTRUCTIONS_H_
#define FLOATASMINSTRUCTIONS_H_

#include "memManager.h"
#include <stdio.h>

#define SINGLE_OPCODE_TABLE(S_OP) \
S_OP(ret,      0xc3) \
S_OP(leave,    0xc9) \
S_OP(push_eax, 0x50) \
S_OP(push_ecx, 0x51) \
S_OP(mov_eax,  0xb8) \
S_OP(mov_ecx,  0xb9)

#define DUAL_OPCODE_TABLE(D_OP) \
D_OP(fadd,             0xde, 0xc1) \
D_OP(fsub,             0xde, 0xe9) \
D_OP(fmul,             0xde, 0xc9) \
D_OP(fdiv,             0xde, 0xf9) \
D_OP(fistp_dword_ebp,  0xdb, 0x5d) \
D_OP(mov_eax_ebp_disp, 0x8b, 0x45)

#define TRI_OPCODE_TABLE(T_OP) \
T_OP(fild_dword_ptr_esp, 0xdb, 0x04, 0x24)

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

typedef enum
{
#define T_OP(name, code1, code2, code3) name,
  TRI_OPCODE_TABLE(T_OP)
#undef T_OP
} T_Opcode;

extern void s_emit(S_Opcode opcode);
extern void d_emit(D_Opcode opcode);
extern void t_emit(T_Opcode opcode);
extern void d_emit_1a_b(D_Opcode opcode, int num);
extern void s_emit_1a_i(S_Opcode opcode, int num);

extern void enter32(int m, int n);

#endif /* FLOATASMINSTRUCTIONS_H_ */
