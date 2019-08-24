%{
#include <stdio.h>
#include <string.h>
#include "adsedgelabelevaluation.tab.h"
#include "adsedgelabelevaluationparse.h"

char adsedgelabelevaluation_errormsg[1024] = "";
char adsedgelabelevaluation_constraint[1024] = "";

%}


integer   [0-9]+
string    [A-Za-z](([ _][A-Za-z0-9])|([A-Za-z0-9]))*
qstring   \"[^\n|()]+\"

%%
"[" 	   {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(OPENB);}
"]"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(CLOSEB);}
"("	   {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(OPEN);}
")"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(CLOSE);}
"<="       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(LEQ);}
">="       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(GEQ);}
"="        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(EQ);}
"!="       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(NEQ);}
"<>"       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(NEQ);}
"<"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(LT);}
">"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(GT);}
"+"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(PLUS);}
"-"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(MINUS);}
"*"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(TIMES);}
"/"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(DIV);}
"&"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(AND);}
"|"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(OR);}
"~"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(NOT);}
"!"        {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(NOT);}
"\n"       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return NL;}
"IN"       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return IN;}
true       {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(TRUE);}
{integer}  {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext; return INTEGER;}
{string}   {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return IDENTIFIER;}
{qstring}  {adsedgelabelevaluationlval.str=adsedgelabelevaluationtext;return(QUOTE);}
[ \t\r]+     {}

%%


int adsedgelabelevaluationwrap() {
	return(1);
}

int adsedgelabelevaluationerror(char *s) {
        strcpy(adsedgelabelevaluation_errormsg, s);
        return 0;
}

