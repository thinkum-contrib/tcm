#ifndef _EVALLABELPARSE_H
#define _EVALLABELPARSE_H


#include "adspropertytype.h"


int x;

/* Functions for parsing labels on activity diagrams. */
#ifdef __cplusplus
extern "C" {
  	typedef struct yy_buffer_state *YY_BUFFER_STATE;
  	extern int adsedgelabelevaluationparse();
  	extern YY_BUFFER_STATE adsedgelabelevaluation_scan_string(const char *str);
 	extern int adsedgelabelevaluation_delete_buffer(YY_BUFFER_STATE);
  	extern char adsedgelabelevaluation_errormsg[];
  	extern char adsedgelabelevaluation_constraint[];
        int proptype[200];  // should be initialised by caller
        char *propname[200];// should be initialised by caller
        int boollist[200];// should be initialised by caller
        int count;// should be initialised by caller
        int isin;

        int outcome; // result
}
#endif



#endif
