%option noyywrap

%{
#include <stdlib.h>

#include "flexBisonExample.tab.h"
%}

whitespace [ \n\t]+
number     [0-9][0-9A-Za-z_]*

%%
{number}      {yylval.i = atoi(yytext); return NUMBER;}
{whitespace}	{}

.				{return (int)*yytext;}
%%
