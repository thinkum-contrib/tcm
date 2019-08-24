%{
#include "adsedgelabelevaluationparse.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define YYERROR_VERBOSE 

  int proptype[200];  /* should be initialised by caller */
  char *propname[200];/* should be initialised by caller */
  int boollist[200];/* should be initialised by caller */
  int count;/* should be initialised by caller */
  int isin; /* true if IN predicate is part of label */

  int outcome; /* result */


int isintexp,isstrexp;

char temp[100];

int GetBool(char *s, int t){
  int i=0;
  while (i<count){
    if ((!strcmp(propname[i],s))&& (proptype[i]==t)) return boollist[i];
    i++;
  }
  return -1;
}


%}
%union{
  int i;
  char *str;
}


/* BISON Declarations */
%token  <str> QUOTE OPEN CLOSE OPENB CLOSEB NL INTEGER IDENTIFIER TRUE LEQ GEQ EQ NEQ GT LT
%left <i> MINUS PLUS OR
%left <i> TIMES DIV AND
%left <i>  NEG NOT  IN   /* negation--unary minus */
%right <i> '^'         /* exponentiation        */

/* Grammar follows */
%%
input:  line 
;

line:  event guard action {if ($<i>1>=0 && $<i>2>=0) outcome= ($<i>1) && ($<i>2); else outcome=0;  }
;




event: {$<i>$=1;}
| IDENTIFIER   {     
                       int b;
		       b=GetBool($<str>1,EVENT);
		       if (b>=0) $<i>$=b; 
		       else {
			 b=GetBool($<str>1,SENDEVENT);
			 if (b>=0) $<i>$=b; else $<i>$=-1;		      
		       }
                }
;


guard: {$<i>$=1;}
| OPENB pexp CLOSEB {if ($<i>2 >=0) $<i>$=$<i>2;else $<i>$=1;}
;

                 
pexp:     orexp {$<i>$=$<i>1;}  
/*
        | IN OPEN IDENTIFIER CLOSE {$<i>$=1;isin=1; / IN clause checked elsewhere /}
        | pexp OR pexp     {if ($<i>1>=0 && $<i>3>=0) $<i>$=($<i>1 || $<i>3); else $<i>$=-1;}
        | pexp AND pexp    {if ($<i>1>=0 && $<i>3>=0) $<i>$=($<i>1 && $<i>3); else $<i>$=-1;} 
        | NOT pexp         {if ($<i>2>=0) $<i>$=(!$<i>2);else $<i>$=-1;if (isin) $<i>$=1;}
        | OPEN pexp CLOSE  {$<i>$=$<i>2;}
*/
;


orexp  :   andexp {$<i>$=$<i>1;} 
         | orexp OR andexp
                         { if (($<i>3 >= 0) && ($<i>1>=0)) $<i>$=($<i>3 || $<i>1);
                           if (($<i>3 < 0)  && ($<i>1>=0)) $<i>$=($<i>1);
                           if (($<i>3 >= 0) && ($<i>1 < 0)) $<i>$=($<i>3);
                           if (($<i>3 < 0)   && ($<i>1 < 0)) $<i>$=-1;
			 }
;

andexp :   literal {$<i>$=$<i>1;}
         | andexp AND literal 
                         { if (($<i>3 >= 0) && ($<i>1>=0)) $<i>$=($<i>3 && $<i>1);
                           if (($<i>3 < 0)  && ($<i>1>=0)) $<i>$=($<i>1);
                           if (($<i>3 >= 0) && ($<i>1 < 0)) $<i>$=($<i>3);
                           if (($<i>3 < 0)   && ($<i>1 < 0)) $<i>$=-1;
			 }
;

literal:  atomic {if ($<i>1>=0) $<i>$=$<i>1;else $<i>$=-1;}
        | NOT literal {if ($<i>2>=0) $<i>$=(!$<i>2);else $<i>$=-1;if (isin) $<i>$=1;}
        | OPEN pexp CLOSE {$<i>$=$<i>2;}
        | IN OPEN IDENTIFIER CLOSE {$<i>$=1;isin=1; /* IN clause checked elsewhere */}
;

atomic:   TRUE   	{$<i>$=1;}
| IDENTIFIER           {  
			  strcpy(temp,$<str>1);
                        } 
  isexp   
                        { 
                           if (isintexp) {
			     int b;
			     strcpy(temp,$<str>1);
			     b=GetBool(temp,INT);
			     if (b==-1) b=GetBool(temp,INTERNAL_INT);
		             if (b>=0) $<i>$=b; else $<i>$=-1;
			   }
			   else if (isstrexp){
			        int b;
			        strcpy(temp,$<str>1);
				b=GetBool(temp,STRING);
				if (b==-1) b=GetBool(temp,INTERNAL_STRING);
		         	if (b>=0) $<i>$=b; else $<i>$=-1;		 
			   }
			   else{
			     int b;
			     b = GetBool(temp,PROP);
			     if (b==-1) b=GetBool(temp,INTERNAL_PROP);
			     if (b>=0) $<i>$=b; else {$<i>$=-1;}
			   }

}
;

     
isexp:    /* empty */ {isintexp=0;isstrexp=0;}
	| irel INTEGER        {strcpy($<str>$,$<str>1);
			       isintexp =1;isstrexp=0;}   
	| srel QUOTE         { strcpy($<str>$,$<str>1);
                              isintexp=0;isstrexp=1;} 
;

irel:      EQ               {strcpy($<str>$,$<str>1);}
         | NEQ              {strcpy($<str>$,$<str>1);}
         | GT               {strcpy($<str>$,$<str>1);}
         | LT               {strcpy($<str>$,$<str>1);}
         | GEQ              {strcpy($<str>$,$<str>1);}
         | LEQ              {strcpy($<str>$,$<str>1);}
;

	 

srel:      EQ               {strcpy($<str>$,$<str>1);}
         | NEQ              {strcpy($<str>$,$<str>1);}
;




action:   /* empty */ {$<i>$=1;}
          | DIV IDENTIFIER {$<i>$=1;}
;
%%





