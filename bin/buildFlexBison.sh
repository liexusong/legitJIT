#!/bin/bash
#

flex ../src/./flexBisonExample.l
bison -d ../src/./flexBisonExample.y
gcc -I../src/lib flexBisonExample.tab.c lex.yy.c liblegitJITLib.a -o flexBisonExample
rm -f flexBisonExample.tab.c flexBisonExample.tab.h lex.yy.c
