////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or 
// (at your option) any later version.
//
// TCM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "mstring.h"
#include <string.h>
#include <iostream>

XmString CreateXmString(const char *s) {
	XmString xms1;
#if XmVERSION == 1
	XmString xms2;
	XmString line;
	XmString separator;
	char *p;
	char *t = (char *)XtNewString(s);   // Make a copy for strtok does not.
	separator = XmStringSeparatorCreate();
	p = strtok(t,"\n");
	xms1 = XmStringCreateLocalized(p);
	// Prevent execution of strtok() on empty string 
	// at initial loop by testing 'p!=0'.
	while (p!=0 && (p = strtok(0,"\n"))) {
		line = XmStringCreateLocalized(p);
		xms2 = XmStringConcat(xms1,separator);
		XmStringFree(xms1);
		xms1 = XmStringConcat(xms2,line);
		XmStringFree(xms2);
		XmStringFree(line);
	}
	XmStringFree(separator);
	XtFree(t);
#else
	// discard const.
	xms1 = XmStringGenerate((char *)s, 0, XmCHARSET_TEXT, 0);
#endif
	return xms1;
}
