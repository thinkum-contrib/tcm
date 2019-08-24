%{
#include <stdio.h>
#include <string.h>
#include "adsmcoutput.tab.h"
#include "adsmcoutputparse.h"

char adsmcoutput_errormsg[1024] = "";
char adsmcoutput_constraint[1024] = "";
%}


string    [A-Za-z0-9.:,/@\|!()<>=&_*+]+ 

%%
"--"      {adsmcoutputlval.str_ptr=adsmcoutputtext;return COMMENT;}
"#"  {adsmcoutputlval.str_ptr=adsmcoutputtext;return HASH;}
"c____counter ="  {adsmcoutputlval.str_ptr=adsmcoutputtext;return COUNTER;}
"seq"     {return IQ;}
"enabled = 1" {adsmcoutputlval.str_ptr=adsmcoutputtext;return ENABLED;} /* enabled = 1 iff some hyperedge is taken */
"State" {return STATE;} 
"= 0\n" {adsmcoutputlval.str_ptr=adsmcoutputtext;return ISZERO;} 
"= 1\n" {adsmcoutputlval.str_ptr=adsmcoutputtext;return ISONE;} 
"in-" {adsmcoutputlval.str_ptr=adsmcoutputtext;return IN;} 
"->" {adsmcoutputlval.str_ptr=adsmcoutputtext; return ARROW;} 
"\n"  {adsmcoutputlval.str_ptr=adsmcoutputtext;return NL;}
"\r"  {adsmcoutputlval.str_ptr=adsmcoutputtext;return NL;}
{string}  {adsmcoutputlval.str_ptr=adsmcoutputtext;  return STRING;}
[ \t]+     {}
[\-]	{}


%%


int adsmcoutputwrap() {
	return(1);
}

int adsmcoutputerror(char *s) {
        strcpy(adsmcoutput_errormsg, s);
        return 0;
}

