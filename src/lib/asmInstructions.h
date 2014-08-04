/*
===========================================================================================
Name         :  asmInstructions.h
Author       :  Vs37nX
Version      :  0.2
Copyright    :  Jacob Logan 2014
Description  :  This is the header interface for writing to the executable memory space
				(mMV.memSpace)
===========================================================================================
*/

#ifndef ASMINSTRUCTIONS_H_
#define ASMINSTRUCTIONS_H_

#include "memManager.h"

void ret(void);

extern inline void movEaxNum(int x);
extern inline void pushEax  (void);
extern inline void popEcx   (void);
extern inline void popEax   (void);
extern inline void addNum   (int x);

extern inline void imul(int x, int y);
extern inline void add (int x, int y);

#define RET    0xc3
#define MOVAX  0xb8

#define PUSHAX 0x50
#define PUSHCX 0x51
#define PUSHDX 0x52

#define POPAX  0x58
#define POPCX  0x59
#define POPDX  0x5a
#define POPBX  0x5b

#define IMULRMW 0xf7

#define ADDRW 0x03

#define ROTATE 0xc1

#define JMPNP 0xe9

#endif /* ASMINSTRUCTIONS_H_ */
