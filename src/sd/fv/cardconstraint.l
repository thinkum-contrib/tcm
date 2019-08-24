%{
#include "cardconstraint.tab.h"
#include "erparse.h"
char cardconstraint_errormsg[1024] = "";
char cardconstraint_constraint[1024] = "";
%}

number	0|[1-9][0-9]*

%%
","		{strcat(cardconstraint_constraint, ",");return(COMMA);}
"<="            {strcat(cardconstraint_constraint, "<=");return(LESSEQUAL);}
">="            {strcat(cardconstraint_constraint, ">=");return(GREATEREQUAL);}
"="             {strcat(cardconstraint_constraint, "=");return(EQUAL);}
"!="            {strcat(cardconstraint_constraint, "!=");return(NOTEQUAL);}
"<>"            {strcat(cardconstraint_constraint, "!=");return(NOTEQUAL);}
"<"             {strcat(cardconstraint_constraint, "<");return(LESS);}
">"             {strcat(cardconstraint_constraint, ">");return(GREATER);}
".."            {strcat(cardconstraint_constraint, "..");return(DOTDOT);}
"n"             {return(N);} 
"m"             {return(M);} 
{number}	{strcat(cardconstraint_constraint, cardconstrainttext);return(NUMBER);}
[ \t\r\n]+
.		{return(UNDEFINED);}
%%

int cardconstraintwrap() {
	return(1);
}

int cardconstrainterror(char *s) {
        strcpy(cardconstraint_errormsg, s);
        return 0;
}

