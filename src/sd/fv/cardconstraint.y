%{
#include "erparse.h"
#include <stdio.h>
#define YYERROR_VERBOSE
%}
%token COMMA NUMBER N M DOTDOT UNDEFINED
%token EQUAL NOTEQUAL LESS LESSEQUAL GREATER GREATEREQUAL

%%

cardconstraint	: expr
		| cardconstraint COMMA expr
		;

expr		: NUMBER DOTDOT NUMBER
		| nletter EQUAL NUMBER
		| nletter NOTEQUAL NUMBER
		| nletter LESS NUMBER
		| nletter LESSEQUAL NUMBER
		| nletter GREATER NUMBER
		| nletter GREATEREQUAL NUMBER
		| NUMBER
		;

nletter		: N
		| M
		|	        /* no letter */
		;
%%
