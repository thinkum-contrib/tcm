//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente, Enschede
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
#ifndef _SCDCREATEANDLINECMD_H
#define _SCDCREATEANDLINECMD_H

#include "createedgecmd.h"

/// statechart create and line class
class SCDCreateAndLineCmd: public CreateEdgeCmd {
/*@Doc: {\large {\bf scope:} TSCD} */
public:
	///
	SCDCreateAndLineCmd(GShape *from);
	///
	virtual ~SCDCreateAndLineCmd();
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	const char *GetName() const { return "create and line";}
};

#endif
