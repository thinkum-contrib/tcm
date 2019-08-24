////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente, Enschede.
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
////////////////////////////////////////////////////////////////////////////////
#include "scwindow.h"
#include "scviewer.h"
#include "sizeshapebordercmd.h"
#include "scdcreateandlinecmd.h"
#include "code.h"
#include "nodeshape.h"
#include "line.h"

SCViewer::SCViewer(Config *c, SCWindow *d): DiagramViewer(c, d) { }

/* virtual */ Command *SCViewer::Connect(int x, int y) {
	GShape *shape;
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	int w;
	// look for shape.
	if (Toolkit::EditorWithInterEdgeConnections(
			GetMainWindow()->GetTool())) { 
		if ((shape = GetCurView()->HitShape(x, y))) {
			if ( shape->IsNodeShape() && shape->IsSelected() && 
			    (w = shape->HitHandles(x, y)) >= 0)
				return new SizeShapeBorderCmd(shape, w);
			else if ( shape->IsNodeShape() || (shape->IsLine() &&
				 !((Line*)shape)->IsCurved()) ) {
				if ( Code::SCD_AND_EDGE == GetDefaultEdgeType() )
					return new SCDCreateAndLineCmd(shape);
				return new CreateEdgeCmd(shape);
			}
		}
	} else if ((shape = GetCurView()->HitNodeShape(x, y))) {
		if (shape->IsSelected() && (w = shape->HitHandles(x, y)) >= 0)
			return new SizeShapeBorderCmd(shape, w);
		else if ( Code::SCD_AND_EDGE == GetDefaultEdgeType() )
			return new SCDCreateAndLineCmd(shape);
		return new CreateEdgeCmd(shape);
	}
	return 0;
}
