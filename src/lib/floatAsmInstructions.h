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

#ifndef FLOATASMINSTRUCTIONS_H_
#define FLOATASMINSTRUCTIONS_H_

#include "memManager.h"
#include <stdio.h>

void ret(void);
void leave(void);
void pushEax(void);
void pushEcx(void);
void enter32(int m, int n);
void fild32Ebp(int x);
void movNumEax(int num);
void movMemEax_Ebp_disp(int num);
void movNumEcx(int num);
void fildDwordEsp(void);
void fistpDwordEbp(int num);

void fadd();
void fsub();
void fmul();
void fdiv();

#endif /* FLOATASMINSTRUCTIONS_H_ */
