%{
#include <stdio.h>
#include <string.h>
#include "adsedgelabel.tab.h"
#include "adsedgelabelparse.h"

char adsedgelabel_errormsg[1024] = "";
char adsedgelabel_constraint[1024] = "";
%}

integer   [0-9]+
string    [A-Za-z](([ _][A-Za-z0-9])|([A-Za-z0-9]))*
qstring   \"[^\n|()]+\"

%%
"[" 	   {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "[");return(OPENB);}
"]"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "]");return(CLOSEB);}
"("	   {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "(");return(OPEN);}
")"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, ")");return(CLOSE);}
"<="       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "<=");return(LEQ);}
">="       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, ">=");return(GEQ);}
"="        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "=");return(EQ);}
"!="       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "!=");return(NEQ);}
"<>"       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "<>");return(NEQ);}
"<"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "<");return(LT);}
">"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, ">");return(GT);}
"+"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "+");return(PLUS);}
"-"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "-");return(MINUS);}
"*"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "*");return(TIMES);}
"/"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "/");return(DIV);}
"&"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "&");return(AND);}
"|"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "|");return(OR);}
"~"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "~");return(NOT);}
"!"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "~");return(NOT);}
":"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, ":");return(COLON);}
"\n"       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "\n");return NL;}
"h"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "h");return HOURS;}
"hours"    {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "h");return HOURS;}
"m"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "m");return MINUTES;}
"minutes"  {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "m");return MINUTES;}
"s"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "s");return SECONDS;}
"seconds"  {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "s");return SECONDS;}
"d"        {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "d");return DAYS;}
"days"     {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "d");return DAYS;}
IN         {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "IN");return IN;}
true       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "true");return(TRUE);}
else       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "else");return(ELSE);}
after      {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "after");return(AFTERTOKEN);}
when       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "when");return(WHENTOKEN);}
time       {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, "time");return(TIME);}
{integer}  {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, adsedgelabeltext); return INTEGER;}
{string}   {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, adsedgelabeltext); return IDENTIFIER;}
{qstring}  {adsedgelabellval.str_ptr=adsedgelabeltext;strcat(adsedgelabel_constraint, adsedgelabeltext);return(QUOTE);}
[ \t\r-]+     {}

%%


int adsedgelabelwrap() {
	return(1);
}

int adsedgelabelerror(char *s) {
        strcpy(adsedgelabel_errormsg, s);
        return 0;
}

