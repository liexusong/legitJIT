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

		s_emit_1a_i(mov_eax, num1);
		s_emit_1a_i(mov_ecx, num2);

		s_emit(push_eax);
		t_emit(fild_dword_ptr_esp);
		s_emit(push_ecx);
		t_emit(fild_dword_ptr_esp);

		switch(o)
		{
		case '*':
			d_emit(fmul);
			break;
		case '/':
			d_emit(fdiv);
			break;
		case '+':
			d_emit(fadd);
			break;
		case '-':
			d_emit(fsub);
			break;
		default:
			fprintf(stderr, "[!] invalid operation\n");
			done = true;
			break;
		}

		d_emit_1a_b(fistp_dword_ebp,  -4);
		d_emit_1a_b(mov_eax_ebp_disp, -4);

		s_emit(leave);
		s_emit(ret);

		checkVal(allocMem(), 		       "memory allocation failed!"      );
		checkVal(copyExecutableCode(), "copying executable code failed!");

		startTimer();
		/* Execute the JIT'ted function pointer containing opcodes */
		res = executeMem();
		finishTimer();
		fprintf(stderr, "JIT result   = %d\n",   res);
	  fprintf(stderr, "elapsed time = %" PRIu64 " nanos\n", getElapsedTime());

		checkVal(freeMem(), "freeing memory failed!");
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
