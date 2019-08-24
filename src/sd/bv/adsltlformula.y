%{
#include "adsltlformulaparse.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


 
  /* adapted from the nusmv ltl parser */



  /*
typedef char *CHAR_PTR;
#define YYSTYPE CHAR_PTR
#define YYDEBUG 1
  */

  char *ltlprop; /* the temporal property */
  char *initial; /* predicate characterising initial configuration */
  /*  char *final; */ /*predicate characterising final configuration */
  int isfinal; /* true iff FINAL is part of requirement */

  char *identifier[100];    /* name of var */
  int identifier_count;

  char *mycpy(char *text);
  char *Mymalloc(unsigned size);
  char *mystrconcat3(char *s1, char *s2, char *s3);
  char *mystrconcat2(char *s1, char *s2);

  extern char adsltlformulatext[];

  int isltl; /* if true, then formula is ltl formula*/

%}


/* BISON Declarations */
%token QUOTE OPEN CLOSE  NL IDENTIFIER  COLON TRUE FALSE LEQ GEQ EQ NEQ GT LT FUTURE GLOBALLY NEXT UNTIL IMPLIES EQUIV INITI FINAL AF EG AG EF
%left   OR
%left   AND
%left  NEG NOT IN    /* negation--unary minus */
%right '^'         /* exponentiation        */

%union  {
  char *str_ptr;
      }  
%type  <str_ptr>   input line simple_expr ident ltlexpr orexpr andexpr untilexpr atomexpr 





/* Grammar follows */
%%
input:  line {ltlprop=mycpy($1);}
;

line:  ltlexpr 

;



simple_expr:   TRUE {$$=mycpy("TRUE");}
|              FALSE {$$=mycpy("FALSE");}
|              INITI {$$=mycpy(initial);}
|              FINAL {$$=mycpy("FINAL");isfinal=1;}
|              IN OPEN ident CLOSE { $$=mystrconcat2($3,">0");}
|              ident  {$$=$1;}
;



ident: IDENTIFIER {
int i;
$$ = mycpy(adsltlformulalval.str_ptr);
 i=strlen($$);
 while (i){
   if ($$[i-1]==' ') $$[i-1]='_'; /* replace spaces by underscores for model checker */
   if ($$[i-1]=='-') $$[i-1]='_'; /* replace dashes by underscores for model checker */
   i--;
 }
 identifier[identifier_count]=mycpy(adsltlformulalval.str_ptr);
 identifier_count++; 
}
;

ltlexpr    : orexpr {$$=$1;}
           | ltlexpr IMPLIES orexpr {$$ = mystrconcat3($1," -> ",$3);} 
           | ltlexpr EQUIV orexpr {$$ = mystrconcat3($1," <-> ",$3);} 
           ;
orexpr     : andexpr   {$$ = $1;}
           | orexpr OR andexpr  {$$ = mystrconcat3($1," | ",$3);} 
           ;
andexpr    : untilexpr    {$$=$1;}
           | andexpr AND untilexpr  {$$ = mystrconcat3($1," & ",$3);}
           ;
untilexpr  : atomexpr  {$$=$1;}
           | untilexpr UNTIL atomexpr {$$ = mystrconcat3($1," U ",$3);}
           ;
atomexpr   : NOT atomexpr  	{$$ = mystrconcat2("! ",$2);} 
           | NEXT atomexpr  	{$$ = mystrconcat2("X ",$2);}
           | GLOBALLY atomexpr 	{$$ = mystrconcat2("G ",$2);} 
           | FUTURE atomexpr 	{$$ = mystrconcat2("F ",$2);}
           | EF atomexpr 	{$$ = mystrconcat2("EF ",$2);isltl=0;}
           | AF atomexpr 	{$$ = mystrconcat2("AF ",$2);isltl=0;}
           | AG atomexpr 	{$$ = mystrconcat2("AG ",$2);isltl=0;}
           | EG atomexpr 	{$$ = mystrconcat2("EG ",$2);isltl=0;}
           | OPEN ltlexpr CLOSE {$$ = mystrconcat3("(",$2,")");}
	   | simple_expr	{$$ = $1;}
           ;







%%
char *mystrconcat2(char *s1, char *s2)
{
  char *ret;
  int len;
  len = strlen(s1);
  len += strlen(s2);
  ret = (char *)malloc(sizeof(char)*(len+1));
  strcpy(ret,s1);
  strcat(ret,s2);
  return(ret);
}


char *mystrconcat3(char *s1, char *s2, char *s3)
{
  char *ret;
  int len;
  len = strlen(s1);
  len += strlen(s2);
  len += strlen(s3);
  ret = (char*)malloc(sizeof(char)*(len+3));
  strcpy(ret,s1);
  strcat(ret," ");
  strcat(ret,s2);
  strcat(ret," ");
  strcat(ret,s3);
  return(ret);
}
         

char *mycpy(char *text)
{
  char *cptr;
  cptr = (char *) Mymalloc(strlen(text) + 1);
  strcpy(cptr, text);
  return(cptr);
}
 
char *Mymalloc(unsigned size)
{
  char *ret;
 
  ret = malloc(size);
  if (ret == NULL) {
    printf("malloc returns NULL\n");
    exit(1);
  }
  return(ret);
}  

