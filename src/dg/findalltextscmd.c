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
#include "findalltextscmd.h"

FindAllTextsCmd::FindAllTextsCmd(ShapeView *v, const string *s, 
		bool sens, bool substr, bool n): SelectAllCmd(v) {
	findString = *s;
	caseSensitive = sens;
	substring = substr;
	nameOnly = n;
}
 
void FindAllTextsCmd::Execute() {
	GetView()->DeselectAll();
	List<GShape *> shapes;
	GetView()->GetShapes(&shapes, &findString, caseSensitive, 
			   substring, nameOnly);
	SetCmdDone(True);
	for (shapes.first(); !shapes.done(); shapes.next())
		GetView()->SelectShape(shapes.cur());
	int count = shapes.count();
	string txt = "find all: ";
	if (count > 0) {
		txt += "found "; 
		txt += count; 
		txt += " shape"; 
		txt += ((count==1)?"":"s");
	}
	else
		txt += "pattern not found";
	GetMainWindow()->SetStatus(&txt);
}

GShape *FindAllTextsCmd::GetNextShape() {
	return GetView()->GetNextShape(&findString, caseSensitive, 
		substring, nameOnly);
}
