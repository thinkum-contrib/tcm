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
#include "dumpwidgettree.h"
#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>

void DumpWidgetTree::Dump(Widget w) {
	WidgetList list = 0;
	Cardinal num_children = 0;
	unsigned i;
	static unsigned n = 0;
	Widget child;
	static const char *indent =
 "----------------------------------------------------------------------------";
	char tmp[256];
	*tmp = '\0';
	if ( n >= strlen(indent) +1) {
		printf("ERROR: Widget tree is too deep ( < %d )!\n", n);
		n = 0;
		return;
	}
	strncpy(tmp, indent, n);
	tmp[n] = '\0';
	printf("%s> widget tree of %s %s \n", tmp, 
		((CoreClassPart *)XtClass(w))->class_name, XtName(w));
	if (!XtIsComposite(w)) {
		printf("%s> %s has no children\n", tmp, XtName(w));
		printf("\n");
		return;
	}
	XtVaGetValues(w,
		XmNchildren, &list,
		XmNnumChildren, &num_children, 0);
	printf("%s> %s has %d %s:\n", tmp,
			XtName(w), num_children, 
			num_children == 1 ? "child" : "children");
	for (i=1; i<=num_children; i++) {
		child = list[i-1];
		printf("%s>    child %2d: %20s\n",
			tmp, i, XtName(child));
	}
	printf("\n");
	for (i=1; i <= num_children; i++) {
		child = list[i-1];
		n += 3;
		Dump(child);
		n -= 3;
	}
	printf("\n");
}
