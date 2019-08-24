%{

#include "adsmcoutputparse.h"



  /*
typedef char *CHAR_PTR;
#define YYSTYPE CHAR_PTR
#define YYDEBUG 1
  */

int mctraceindex;
 int mctrace[100];
 int mcfeedback;

 int enabledindex;
 int enabledhyperedge[2000];
 int enabledstatenumber[2000];
 char *sourcename[2000];  /* name of source */
 char *targetname[2000];    /* name of target */
 int sourcestatenumber[2000];
 int targetstatenumber[2000]; /* what statecounter does sourcestatenumber[i] belong to?*/
 int statecounter;
 int sourceindex, targetindex;
%}


%union  {
  char *str_ptr;
}  

/* BISON Declarations */
%token IQ QUOTE COMMENT COUNTER  HASH ISZERO ISONE STATE NL ARROW
%token <str_ptr> STRING ENABLED IN

/* Grammar follows */
%%
input:  line 
;

line:  start middle end ;




arrowstringseq: STRING arrowstringseq {}
| ISONE arrowstringseq 
| ISZERO arrowstringseq 
| ARROW arrowstringseq
|
;

stringseq: STRING stringseq {}
| ISONE stringseq 
| ISZERO stringseq 
|
;

stringlines: stringseq NL stringlines |
;


start: stringlines COMMENT arrowstringseq NL
;

middle:  middle1 middle2 {mcfeedback=1;}
|{mcfeedback=0;}
;

middle1: COMMENT stringseq NL  /* "as demonstrated by */ 
;

middle2: feedback middle4 | feedback
;


middle4: COMMENT loop COMMENT NL feedback
| middle4 COMMENT loop COMMENT NL feedback
;




feedback:  enabledfeedback {}
;



enabledfeedback: stateseq enabledfeedback2 enabledfeedback {
statecounter++;}
|
/*| enabledfeedback  stateseq enabledfeedback2
  { statecounter++;}*/
;

stateseq:  ARROW state STRING STRING NL {} /* "-> State 1.1 <-" */
;

state : STATE 
;


enabledfeedback2 :    enabledfeedbackatom enabledfeedback2 
|
;

enabledfeedbackatom: STRING ENABLED NL 
{
  int i=3; /* STRING starts with "HE_" */
  char temp[5];
  while ($1[i]!='-'){
    temp[i-3]=$1[i];
    i++;
  }
  temp[i-3]='\0';
  enabledhyperedge[enabledindex]  = atoi(temp);
  enabledstatenumber[enabledindex]= statecounter ;
  enabledindex++;

}
|    STRING ISZERO /*NL  potential source node */
{
  char temp[100];
  int len;
  strcpy(temp,$1);
  len=strcspn(temp,"=\r\n");
  /* printf("name\t%d\t%s\n",len,temp);*/
  sourcename[sourceindex]= (char *)malloc(len+1);
  strncpy(sourcename[sourceindex],temp,len);  
  sourcename[sourceindex][len]='\0';
  sourcestatenumber[sourceindex]=statecounter;
  sourceindex++;
}
|    STRING ISONE /* NL   potential target node */
{
  char temp[100];
  int len;
  strcpy(temp,$1);
  len=strcspn(temp," =\r\n");
  /*  printf("name\t%d\t%s\n",len,temp);*/
  targetname[targetindex]= (char *)malloc(len+1);
  strncpy(targetname[targetindex],temp,len);  
  targetname[targetindex][len]='\0';
  targetstatenumber[targetindex]=statecounter;
  targetindex++;
}
|  STRING STRING ISZERO  {}
|  STRING STRING ISONE {}
/* |  STRING STRING STRING STRING NL {}*/
| ENABLED NL {}
| NL {}
| COUNTER STRING NL
       { 
	 
          mctrace[mctraceindex] =atoi($2);
          mctraceindex++;
       } 
;


hashseq: HASH | hashseq HASH;

loop: stringseq /* STRING= "loop starts here" */
;


end: end1 end2 |
;

end1: hashseq NL stringseq commentseq NL stringseq   
;

end2: hashseq stringseq commentseq NL stringseq 
;

/*
stringseqnl: stringseqnl NL | NL | stringseq NL | stringseqnl stringseq NL;
*/

commentseq: COMMENT commentseq
| COMMENT
;
 


%%


