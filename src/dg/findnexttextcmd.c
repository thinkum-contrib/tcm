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
#include "shapeview.h"
#include "drawwindow.h"
#include "gshape.h"
#include "findnexttextcmd.h"

FindNextTextCmd::FindNextTextCmd(ShapeView *v, const string *s, bool sens, 
	bool substr, bool n): FindAllTextsCmd(v, s, sens, substr, n) {
}
 
void FindNextTextCmd::Execute() {
	GetView()->DeselectAll();
	SetCmdDone(True);
	GShape *shape = GetNextShape();
	if (shape) {
		GetView()->SelectShape(shape);
		GetMainWindow()->SetStatus(
			"find next: pattern found (shape is selected)");
		const Point *pt = shape->GetPosition();
		double x = Scale(pt->x);
		double y = Scale(pt->y);
		GetMainWindow()->ShowPosition(static_cast<int>(0.5 + x),
									  static_cast<int>(0.5 + y));
	}
	else
		GetMainWindow()->SetStatus("find next: pattern not found");
}
