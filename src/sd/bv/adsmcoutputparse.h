#ifndef _MCOUTPUTPARSE_H
#define _MCOUTPUTPARSE_H

#include<stdio.h>

/* Functions for parsing output of model checker */
#ifdef __cplusplus
extern "C" {
	typedef struct yy_buffer_state *YY_BUFFER_STATE;
	extern int adsmcoutputparse();
        extern FILE *adsmcoutputin;
//	extern char myguardlabeltext[];
        extern int mctrace[100];
        extern int mctraceindex;
        extern int mcfeedback;

 extern int enabledindex;
 extern int enabledhyperedge[2000];
 extern int enabledstatenumber[2000];
 extern char *sourcename[2000];  /* name of source */
 extern char *targetname[2000];    /* name of target */
 extern int sourcestatenumber[2000];
 extern int targetstatenumber[2000]; /* what statecounter does sourcenumber[i] belong to?*/
 extern int statecounter;
 extern int sourceindex, targetindex;
 extern int eventIndex;
 extern char * occurredEvents[10000];
 extern int occurredEventStates[10000];
 extern int isStable[2000];
}
#endif


#endif
