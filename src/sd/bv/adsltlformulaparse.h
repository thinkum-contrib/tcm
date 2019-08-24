#ifndef _LTLFORMULAPARSE_H
#define _LTLFORMULAPARSE_H



/* Functions for parsing labels on activity diagrams. */
#ifdef __cplusplus
extern "C" {
	typedef struct yy_buffer_state *YY_BUFFER_STATE;
	extern int adsltlformulaparse();

	extern YY_BUFFER_STATE adsltlformula_scan_string(const char *str);
	extern int adsltlformula_delete_buffer(YY_BUFFER_STATE);
	extern char adsltlformula_errormsg[];
	extern char adsltlformula_constraint[];
        extern char *ltlprop;
        extern char *initial;
  /*  extern char *final;*/
        extern int isfinal;

        extern char *identifier[];
        extern int identifier_count;

        extern int isltl; /* if true than ltl formula */

}
#endif



#endif
