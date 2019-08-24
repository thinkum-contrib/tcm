//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _GDUPDATENODESHAPETYPECMD_H
#define _GDUPDATENODESHAPETYPECMD_H

#include "updatenodeshapetypecmd.h"

/// command for changing node shape types in a TGD
class GDUpdateNodeShapeTypeCmd: public UpdateNodeShapeTypeCmd {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	GDUpdateNodeShapeTypeCmd(ShapeView *v, 
		List<int *> *fromTypes, int toType);
	///
        virtual Thing *Transform(Thing *thing);
private:
	///
	static bool SolidShape(int type);
};
#endif
