//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _ALIGNNODESHAPESCMD_H
#define _ALIGNNODESHAPESCMD_H

#include "moveshapescmd.h"
#include "diagramviewer.h"

/// command class for aligning selected node shapes in view.
class AlignNodeShapesCmd: public MoveShapesCmd {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	AlignNodeShapesCmd(ShapeView *view, List<GShape *> *s,
		       NodeAlign::Type alignType);
	///
	void Execute();
	///
	const char *GetName() const {return "align node shapes";}
private:
	///
	NodeAlign::Type alignType;
};
#endif
