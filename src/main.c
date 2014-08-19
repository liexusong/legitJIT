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

	printf("[?] Enter the expression, like this \"NUM2 OPERAND NUM2\": ");
	scanf("%i %c %i", &num1, &o, &num2);

	enter32(4, 0);

	movNumEax(num1);
	movNumEcx(num2);

	switch(o)
	{
	case '*':
		s_emit(push_eax);
		fildDwordEsp();
		s_emit(push_ecx);
		fildDwordEsp();
		d_emit(fmul);
		break;
	case '/':
		s_emit(push_eax);
		fildDwordEsp();
		s_emit(push_ecx);
		fildDwordEsp();
		d_emit(fdiv);
		break;
	case '+':
		s_emit(push_eax);
		fildDwordEsp();
		s_emit(push_ecx);
		fildDwordEsp();
		d_emit(fadd);
		break;
	case '-':
		s_emit(push_eax);
		fildDwordEsp();
		s_emit(push_ecx);
		fildDwordEsp();
		d_emit(fsub);
		break;
	default:
		fprintf("[!] invalid operation\n", );
	}

	fistpDwordEbp(-4);
	movMemEax_Ebp_disp(-4);

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
		fprintf(stderr, "ERROR: %s\n", msg);
		exit(EXIT_FAILURE);
	}
}
