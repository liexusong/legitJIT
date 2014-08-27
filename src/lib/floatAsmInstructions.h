#ifndef FLOATASMINSTRUCTIONS_H_
#define FLOATASMINSTRUCTIONS_H_

#include "memManager.h"

/*-------------------I386_S_OPCODE_TABLE--------------------*/
/*    |     Enum Name    | |       Asm Equivlent     || Op |*/
/*    |                  | |                         ||Code|*/
/*    |                  | |                         ||  1 |*/
#define I386_S_OPCODE_TABLE(S_OP)                            \
  S_OP(ret,              "ret",                        0xc3) \
  S_OP(leave,            "leave",                      0xc9) \
  S_OP(push_eax,         "push eax",                   0x50) \
  S_OP(push_ecx,         "push ecx",                   0x51) \
  S_OP(mov_eax,          "mov eax",                    0xb8) \
  S_OP(mov_eax_addr,     "mov eax [\"i\"]",            0xa1) \
  S_OP(mov_ecx,          "mov ecx",                    0xb9) \
/*----------------------------------------------------------*/

/*----------------------I386_D_OPCODE_TABLE-----------------------*/
/*    |     Enum Name    | |       Asm Equivlent     || Op || Op |*/
/*    |                  | |                         ||Code||Code|*/
/*    |                  | |                         ||  1 ||  2 |*/
#define I386_D_OPCODE_TABLE(D_OP)                                  \
  D_OP(fadd,             "fadd",                       0xde, 0xc1) \
  D_OP(fsub,             "fsub",                       0xde, 0xe9) \
  D_OP(fmul,             "fmul",                       0xde, 0xc9) \
  D_OP(fdiv,             "fdiv",                       0xde, 0xf9) \
  D_OP(fcos,             "fcos",                       0xd9, 0xff) \
  D_OP(fsin,             "fsin",                       0xd9, 0xfe) \
  D_OP(fild_dword_addr,  "fild  dword [\"i\"]",        0xdb, 0x05) \
  D_OP(fistp_dword_addr, "fistp dword [\"i\"]",        0xdb, 0x1d) \
  D_OP(fistp_dword_ebp,  "fistp dword [ebp + \"i\"]",  0xdb, 0x5d) \
  D_OP(mov_eax_ebp_disp, "mov eax [ebp + \"i\"]",      0x8b, 0x45) \
/*----------------------------------------------------------------*/

/*-------------------------I386_T_OPCODE_TABLE--------------------------*/
/*    |     Enum Name    | |       Asm Equivlent     || Op || Op || Op |*/
/*    |                  | |                         ||Code||Code||Code|*/
/*    |                  | |                         ||  1 ||  2 ||  3 |*/
#define I386_T_OPCODE_TABLE(T_OP)                                        \
  T_OP(fild_dword_ptr_esp, "fild dword [esp + \"i\"]", 0xdb, 0x04, 0x24) \
/*----------------------------------------------------------------------*/

typedef enum
{
#define S_OP(name, b, c) name,
  I386_S_OPCODE_TABLE(S_OP)
#undef S_OP
#define D_OP(name, b, c, d) name,
  I386_D_OPCODE_TABLE(D_OP)
#undef D_OP
#define T_OP(name, b, c, d, e) name,
  I386_T_OPCODE_TABLE(T_OP)
#undef T_OP
} I386_Opcode;

extern void emit       (I386_Opcode opcode);
extern void emit_1a_b(I386_Opcode opcode, int num);
extern void emit_1a_i(I386_Opcode opcode, int num);
extern void emit_1a_p(I386_Opcode opcode, int *num);

extern void enter32(int m, int n);

#endif /* FLOATASMINSTRUCTIONS_H_ */
