%{
#include <stdio.h>
#include <string.h>
#include "adsltlformula.tab.h"
#include "adsltlformulaparse.h"

char adsltlformula_errormsg[1024] = "";
char adsltlformula_constraint[1024] = "";
%}
%option noyywrap

integer   [0-9]+    
string1   [A-Za-z][A-Za-z][A-Za-z0-9]([ \-_][A-Za-z0-9]|[A-Za-z0-9])*
string2   [BCDFGHIJKLMNOPQRSTVWYZa-z][ABCDEHIJKLMNOPQRSTUVWYZa-z]([ \-_][A-Za-z0-9]|[A-Za-z0-9])*
string3   [ABCDEHIJKLMNOPQRSTVWYZa-z][ \-_](([A-Za-z0-9])|([A-Za-z0-9]))*
qstring   \"[^\n]+\"

%%
"("	   {return(OPEN);}
")"        {return(CLOSE);}
"&"        {return(AND);}
"|"        {return(OR);}
"~"        {return(NOT);}
"!"        {return(NOT);}
"->"        {return(IMPLIES);}
"<->"        {return(EQUIV);}
"IN"       {return IN;}
"F"        {return FUTURE;}
"G"        {return GLOBALLY;}
"U"        {return UNTIL;}
"X"        {return NEXT;} 
"AF"        {return AF;}
"EF"        {return EF;}
"AG"        {return AG;}
"EG"        {return EG;}
"INITIAL"    {return INITI;} 
"FINAL"      {return FINAL;} 
"TRUE"       {return(TRUE);} 
"FALSE"       {return(FALSE);}
{string1}   {adsltlformulalval.str_ptr=adsltlformulatext;return IDENTIFIER;}
{string2}   {adsltlformulalval.str_ptr=adsltlformulatext;return IDENTIFIER;}
{string3}   {adsltlformulalval.str_ptr=adsltlformulatext;return IDENTIFIER;}
[ \n\t\r]+     {}

%%


int adsltlformulawrap() {
	return(1);
}

int adsltlformulaerror(char *s) {
strcpy(adsltlformula_errormsg, s);
printf("ERORORRORO:\t%s\n",s);
        return 0;
}

