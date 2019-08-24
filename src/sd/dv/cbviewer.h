//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _CBVIEWER_H
#define _CBVIEWER_H

#include "erviewer.h"
class CBWindow;
class CBDMessage;

/// class-relationship viewer class.
class CBViewer: public ERViewer {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	CBViewer(Config *c, CBWindow * w);

	///
	Command *Drag(int x, int y);

	/// change actor type of selected object types.
	void UpdateNodeShapeType(int);

	/// update show stereotypes type of selected object types.
	void UpdateShowStereotypes(bool);

	/// update show properties type of selected object types.
	void UpdateShowProperties(bool);
	
	/// update message direction arrow of selected message
	void UpdateMessageDirection(TextShape *t, CBDMessage *msg, int k,
								ReadDirection::Type dir);
};
#endif
