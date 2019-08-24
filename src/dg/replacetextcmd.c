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
#include "gshape.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "replacetextcmd.h"

ReplaceTextCmd::ReplaceTextCmd(ShapeView *v, const string *p, const string *o, 
		bool c, bool s, bool n): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	diagram = v->GetViewer()->GetDiagram();
	pattern = new string(*p);
	replace = new string(*o);
	caseSensitive = c;
	substring = s;
	nameOnly = n;
	oldSelection = new List<GShape *> (*view->GetSelection());
	textShapes = new List<TextShape *>;
	oldStrings = new List<string *>;
	oldSizes = new List<Point *>;
}

ReplaceTextCmd::~ReplaceTextCmd() {
	oldStrings->clear();
	oldSizes->clear();
	delete textShapes;
	delete pattern;
	delete replace;
	delete oldSelection;
	delete oldSizes;
	delete oldStrings;
}

void ReplaceTextCmd::UnExecute() {
	for (unsigned i=0; i<textShapes->count(); i++) {
		TextShape *s = (*textShapes)[i];
		if (diagram->SetText(s, ((*oldStrings)[i]))) {
			if (GetViewer()->IsAutoResize()) {
				GShape *parent = (GShape *)s->GetParent();
				int oldWidth = (*oldSizes)[i]->x;
				int oldHeight = (*oldSizes)[i]->y;
				if (parent->GetWidth() != oldWidth || 
		    	    		parent->GetHeight() != oldHeight) {
					parent->UpdateSize(oldWidth, oldHeight);
					view->GetViewer()->
						ShapePositionUpdate(parent);
				}
			}
		}
	}
	view->DeselectAll();
	for (oldSelection->first(); !oldSelection->done(); oldSelection->next())
 	{
		GShape *shape = oldSelection->cur();
		view->SelectShape(shape);
	}
	Command::UnExecute();
}

void ReplaceTextCmd::ReExecute() {
	textShapes->empty();
	oldStrings->clear();
	oldSizes->clear();
	Execute();
}
