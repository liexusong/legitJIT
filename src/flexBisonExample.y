%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "timer.h"
#include "memManager.h"
#include "floatAsmInstructions.h"

#include "flexBisonExample.tab.h"

#define MAXINTS 128

void yyerror(char* msg);
int  yylex();
int  main();

void checkVal (bool func, char* msg);


int foo[MAXINTS];
int fooidx = 0;
int res    = 0;
%}

%union
{
  int i;
  char* s;
}

%token<i> NUMBER
%type <i> expr

%left <i> '+' '-'
%left <i> '*' '/'

%%
prog: {initTiming(); enter32(4, 0);}
    | prog expr {}
    ;

expr: NUMBER {foo[fooidx] = $1; emit_1a_p(fild_dword_addr, &foo[fooidx]); fooidx++;}

    | expr '*' expr {emit(fmul);}
    | expr '/' expr {emit(fdiv);}
    | expr '+' expr {emit(fadd);}
    | expr '-' expr {emit(fsub);}
    | '(' expr ')'  {$$ = $2;}
    ;
%%

int main()
{
  yyparse();

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
  exit(EXIT_SUCCESS);

  return 0;
}

void yyerror(char* msg)
{
  fprintf(stderr, (char*)"[!] yyerror(): %s\n", msg);
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
