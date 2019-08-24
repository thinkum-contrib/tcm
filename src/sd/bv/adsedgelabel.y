%{
#include "adsedgelabelparse.h"
#include "adspropertytype.h"
#include "adsclocktypes.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


 





/*
typedef char *CHAR_PTR;
#define YYSTYPE CHAR_PTR
#define YYDEBUG 1
*/



/* variables for normal guards */
 int iprop; /* index on propname and proptype */
 int isintorstrexp; /* bool to check wether integer of string expression is meant */
 int ivar; /* index on varname and vartype */
 int indexin; /* index on in nodes */
 int notindexin; /* index on in nodes */
 int isvar; /* true iff variable occurs in edge label */
 int iselse; /* true iff else clause exists */
 char temp[100];
 char *propname[200];  /* name of prop */
 char *varname[100];    /* name of var */
 char *inname[100];    /* name of in nodes */
 char *notinname[100];    /* name of in nodes */
 enum PropType proptype[200];
 enum PropType vartype[200];

 
/* variables for clock constraints */
 int timetype; /* h/s/m */
 int isclock;  
 int iclock;  /* index on clockconstraint, clockconstrainttype and clocktype */
 int clockconstraint[200]; /* amount */
 enum PropType clockconstrainttype[200];/*,  after, when (mod) */
 enum ClockType clocktype[200];  /* h/s/m  */

/* variables for send actions */
 int hasaction; /* true iff action clause exists */
 char *sendeventname;
 int broadcast;  /* is the action event also directed to the environment? 1= system+environment, 0= only system */


%}


/* BISON Declarations */

%union  {
  char *str_ptr;
      }  
%type  <str_ptr>   atomic isexp QUOTE 

%token QUOTE OPEN CLOSE OPENB CLOSEB NL DAYS HOURS MINUTES SECONDS TIME COLON WHENTOKEN AFTERTOKEN ELSE TRUE LEQ GEQ EQ NEQ GT LT
%token <str_ptr>  IDENTIFIER INTEGER
%left  MINUS PLUS OR
%left  TIMES DIV AND
%left  NEG NOT IN    /* negation--unary minus */
%right '^'         /* exponentiation        */





/* Grammar follows */
%%
input:  line 
;

line:  event guard action
;




event: 
|time 
| IDENTIFIER  {	 
                         proptype[iprop]= EV_FROM_ENV; /* later it will be changed for EV_INT if we detect that it is
							  sent as the action of some transition */
                         propname[iprop]= (char *)malloc (strlen($1)+1);
			 strcpy(propname[iprop],$1);
                         iprop++;

}
;

time:  AFTERTOKEN OPEN INTEGER type CLOSE {
    int amount; 
    isclock=1;
    clockconstrainttype[iclock]=AFTER;
    amount=strtol($3,NULL,10);
    clockconstraint[iclock] = amount;
    clocktype[iclock]=timetype;
    iclock++;
}       
;

type :      {timetype=SECOND;}
         | HOURS {timetype=HOUR;}
         | MINUTES {timetype=MINUTE;}
         | SECONDS {timetype=SECOND;}
         | DAYS {timetype=DAY;}
;



guard:   
        | OPENB pexp CLOSEB
        | OPENB IN OPEN IDENTIFIER {
                          inname[indexin]= (char *)malloc (strlen($4)+1);
                          strcpy(inname[indexin],$4);
                          indexin++;
           } CLOSE CLOSEB
        | OPENB NOT OPEN OPEN IN OPEN IDENTIFIER {
                          notinname[notindexin]= (char *)malloc (strlen($7)+1);
                          strcpy(notinname[notindexin],$7);
                          notindexin++;
           } CLOSE CLOSE CLOSE CLOSEB 
        | OPENB NOT OPEN OPEN NOT IN OPEN IDENTIFIER {
                          inname[indexin]= (char *)malloc (strlen($8)+1);
                          strcpy(inname[indexin],$8);
                          indexin++;
           } CLOSE CLOSE CLOSE CLOSEB 
        | OPENB NOT IN OPEN IDENTIFIER {
                          notinname[notindexin]= (char *)malloc (strlen($5)+1);
                          strcpy(notinname[notindexin],$5);
                          notindexin++;
           } CLOSE CLOSEB 
;

                 
pexp:   | ELSE {iselse=1;} 
        | atomic {}
        | pexp OR pexp   
        | pexp AND pexp    
        | NOT pexp        
        | OPEN pexp CLOSE  
;

/* I only consider IN(p)/NOT IN(p)  but  AND/OR IN(p)!!! */


atomic:   TRUE   	{isvar=0;}
        | IDENTIFIER    { varname[ivar]= (char *)malloc (strlen($1)+1);
			  strcpy(varname[ivar],$1);;
			  strcpy(temp,$1);
                          isvar=1;
                        } 
          isexp   
                        { char name[100];
			  if (!isintorstrexp) {
			             strcpy(name,temp);
				     proptype[iprop]= PROP;
                                     if (isvar) {
                                         vartype[ivar]=PROP;	 
                                         ivar++;
                                     };
			  }
			  else 
			   { strcpy(name,$1); 
			 }
			 propname[iprop]= (char *)malloc (strlen(name)+1);
			 strcpy(propname[iprop],name);
			 iprop++;
}
;

     
isexp:    /* empty */ {isintorstrexp=0;}
	| irel INTEGER        {
      			       proptype[iprop]= INT;
                               if (isvar) {vartype[ivar]=INT;
                                     ivar++;
                               };
			       isintorstrexp =1;}   
	| srel QUOTE         { 
        		       proptype[iprop]= STRING;
                               if (isvar) {vartype[ivar]= STRING;
                                           ivar++;};
	
                               isintorstrexp=1;} 
;

irel:      EQ              
         | NEQ             
         | GT              
         | LT             
         | GEQ            
         | LEQ              
;

	 

srel:      EQ               
         | NEQ           
;


action:   /* empty */ {hasaction=0; broadcast= 0;}

             
	
| DIV IDENTIFIER {    hasaction= 1;
	              if (strncmp($2,"broadcast ",10)==0){
			int lon= strlen($2)-10+1; /* -10 because of "broadcast ", +1 for the \0 */
			int i;
                          sendeventname= (char *) malloc (lon*sizeof(char)); 
			  for (i=0; i< lon-1; i++)
			       sendeventname[i]= $2[i+10];
			  sendeventname[i]= '\0';
			  broadcast= 1;
                      }
		      else{
			  broadcast= 0;
	                  sendeventname= (char *)malloc ((strlen($2)+1)*sizeof(char));
	                  strcpy(sendeventname,$2);
		      }
                 }
;
%%


