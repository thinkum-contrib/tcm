#ifndef _MYGUARDLABELPARSE_H
#define _MYGUARDLABELPARSE_H


#include "adspropertytype.h"
#include "adsclocktypes.h"

/* Functions for parsing labels on activity diagrams. */
#ifdef __cplusplus
extern "C" {
	typedef struct yy_buffer_state *YY_BUFFER_STATE;
	extern int adsedgelabelparse();

	extern YY_BUFFER_STATE adsedgelabel_scan_string(const char *str);
	extern int adsedgelabel_delete_buffer(YY_BUFFER_STATE);
	extern char adsedgelabel_errormsg[];
	extern char adsedgelabel_constraint[];

	extern int indexin, notindexin, hasaction,broadcast,iprop,ivar,iselse;	// see adsedgelabel.y
	extern char *propname[];        // see adsedgelabel.y
        extern char *varname[] ;        // see adsedgelabel.y
        extern char *inname[] ;        // see adsedgelabel.y
        extern char *notinname[] ;        // see adsedgelabel.y

  extern char *sendeventname;
        extern int iclock,isclock;
        extern int clockconstraint[];
        extern enum PropType clockconstrainttype[];  // after, when (mod)
        extern enum ClockType clocktype[];           // h/s/m 

        extern enum PropType proptype[];
        extern enum PropType vartype[];
}
#endif



#endif
