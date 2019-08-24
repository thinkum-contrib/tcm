//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "cbupdateactortypecmd.h"
#include "ucdsingleclassbox.h"
#include "stickman.h"

CBUpdateActorTypeCmd::CBUpdateActorTypeCmd(
	ShapeView *v, List<int *> *l, int n): UpdateNodeShapeTypeCmd(v, l, n) {
	TransformAll();
}

Thing *CBUpdateActorTypeCmd::Transform(Thing *thing) {
        NodeShape *oldShape = (NodeShape *)thing;
	if (toType == Code::UCD_SINGLE_CLASS_BOX)
                return new UCDSingleClassBox(*(StickMan *)oldShape);
        else if (toType == Code::STICKMAN)
                return new StickMan(*(UCDSingleClassBox *)oldShape);
        else {
                error("%s, %d: cannot convert actor type %d to %d \n",
                	__FILE__, __LINE__, oldShape->GetClassType(), toType);
                return 0;
        }
}
