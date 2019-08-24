////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "mousecursor.h"
#include "error.h"
#include <X11/cursorfont.h>

MouseCursor::MouseCursor(Widget w) {
	widget = w;
	normalPtr = True;
}

const int MouseCursor::WATCH = XC_watch;
const int MouseCursor::LEFT_PTR = XC_left_ptr;
const int MouseCursor::PLUS = XC_plus;
const int MouseCursor::TERM = XC_xterm;
const int MouseCursor::FLEUR = XC_fleur;
const int MouseCursor::H_DOUBLE_ARROW = XC_sb_h_double_arrow;
const int MouseCursor::V_DOUBLE_ARROW = XC_sb_v_double_arrow;

void MouseCursor::Set(int x) {
	if (x == XC_left_ptr) {
		if (!normalPtr)
			normalPtr = True;
		else
			return;
	}
	else
		normalPtr = False;
	Display *d = XtDisplay(widget);
	Cursor c1 = XCreateFontCursor(d, x);
	XDefineCursor(d, XtWindow(widget), c1);
	XFlush(d);
}
 
void MouseCursor::SetSize(int w) {
	switch (w) {
	case 0: Set(XC_fleur);
		break;
	case 1: Set(XC_top_left_corner);
		break;
	case 2: Set(XC_top_right_corner);
		break;
	case 3: Set(XC_bottom_right_corner);
		break;
	case 4: Set(XC_bottom_left_corner);
		break;
	case 5: Set(XC_bottom_side);
		break;
	case 6: Set(XC_top_side);
		break;
	case 7: Set(XC_left_side);
		break;
	case 8: Set(XC_right_side);
		break;
	default:
		error("%s, line %d: impl error: wrong size cursor position\n",
			 __FILE__, __LINE__);
		break;
	}
}
