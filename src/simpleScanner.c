#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "timer.h"
#include "memManager.h"
#include "floatAsmInstructions.h"

void checkVal (bool func, char* msg);

int main(int argc, char **argv)
{
    int res;
    char o;
    int num1, num2;

    initTiming();

    bool done = false;
    while(!done)
    {
        printf("[?] Enter the expression, like this \"NUM2 OPERAND NUM2\" \
	      \n[?] Press enter without any input to quit: ");
        if(scanf("%i %c %i", &num1, &o, &num2) < 3)
	    break;

        enter32(4, 0);

        emit_1a_i(mov_ecx, num1);
        emit(push_ecx);
        emit(fild_dword_ptr_esp);

        emit_1a_i(mov_ecx, num2);
        emit(push_ecx);
        emit(fild_dword_ptr_esp);

        switch(o)
        {
        case '*':
            emit(fmul);
            break;
        case '/':
            emit(fdiv);
            break;
        case '+':
            emit(fadd);
            break;
        case '-':
            emit(fsub);
            break;
        default:
            fprintf(stderr, "[!] invalid operation\n");
            done = true;
            break;
        }

        emit_1a_b(fistp_dword_ebp,  -4);
        emit_1a_b(mov_eax_ebp_disp, -4);

        emit(leave);
        emit(ret);

        checkVal(allocMem(), 		       "memory allocation failed!"      );
        checkVal(copyExecutableCode(), "copying executable code failed!");

        startTimer();
        /* Execute the JIT'ted function pointer containing opcodes */
        res = executeMem();
        finishTimer();
        fprintf(stderr, "JIT result   = %d\n",   res);
        fprintf(stderr, "elapsed time = %" PRIu64 " nanos\n", getElapsedTime());

        checkVal(freeMem(), "freeing memory failed!");
        freeMem();

        res = 0;
    }
    exit(EXIT_SUCCESS);
}

/**
* Checks the return value from a statement and prints the associated error
* message if it is false
**/
void checkVal(bool func, char* msg)
{
    if(!func)
    {
        fprintf(stderr, "[!] %s\n", msg);
        exit(EXIT_FAILURE);
    }
}

