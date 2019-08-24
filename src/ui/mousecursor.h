//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _MOUSECURSOR_H
#define _MOUSECURSOR_H
 
#include <X11/Intrinsic.h>
#include "bool.h"

/// functions to set mouse cursor to different shapes.
class MouseCursor {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	MouseCursor(Widget w);

	/// cursor shapes.
	static const int WATCH;
	///
	static const int LEFT_PTR;
	///
	static const int PLUS;
	///
	static const int TERM;
	///
	static const int FLEUR;
	///
	static const int H_DOUBLE_ARROW;
	///
	static const int V_DOUBLE_ARROW;

	/// change the cursor to cursorNum (see /usr/include/X11/cursorfont.h).
	void Set(int cursorNum);

	/// change the cursor to a resize cursor depending on the place.
	void SetSize(int place);
private:
	///
	bool normalPtr;
	///
	Widget widget;
};
#endif
