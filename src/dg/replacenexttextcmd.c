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
#include "diagram.h"
#include "replacenexttextcmd.h"

ReplaceNextTextCmd::ReplaceNextTextCmd(ShapeView *v,
	const string *p, const string *o, bool c, bool s, bool n): 
	ReplaceTextCmd(v, p, o, c, s, n) {}

void ReplaceNextTextCmd::Execute() {
	if (*replace == *pattern) {
		MessageDialog *d = new MessageDialog(
			GetMainWindow()->GetWidget(), 
			MessageDialog::ERROR);
		d->Show("Error", 
			"replace next: find and replace text are identical");
		GetMainWindow()->SetStatus(
			"aborted: identical find and replace");
		Abort();
		return;
	}
	int i = view->GetCurrentShapeNr();
	if (i == 0)
		i = view->NrOfShapes()-1;
	else
		i--;
	view->SetCurrentShapeNr(i);
	GShape *shape = view->GetNextShape(pattern, 
					caseSensitive, substring, nameOnly);
	if (shape) {
		view->DeselectAll();
		int r = 0;
		if (nameOnly) {
			if (shape->HasNameString(pattern, caseSensitive, 
						 substring)) {
				TextShape *ts;
				if (shape->IsTextShape())
					ts = (TextShape *)shape;
				else
					ts = ((GShape *)shape)->GetName();
				textShapes->add(ts);
				Point *pt = new Point(shape->GetWidth(), 
							shape->GetHeight()); 
				oldSizes->add(pt);
				const string *name = ts->GetString();
				string copy = *name;
				oldStrings->add(new string(copy));
				if (substring || *pattern == copy) {
					r = copy.replace(*pattern, *replace, 
							 caseSensitive);
					if (copy != *name) 
						GetDiagram()->
							SetText(ts, &copy);
				}
			}
		}
		else {
			List<TextShape *> tshapes;
			if (shape->HasString(pattern, caseSensitive, 
						substring, &tshapes)) {
				for (tshapes.first(); !tshapes.done(); 
					tshapes.next()) {
					TextShape *ts = tshapes.cur();
					textShapes->add(ts);
					Point *pt = new Point(shape->GetWidth(),
							shape->GetHeight()); 
					oldSizes->add(pt);
					oldStrings->add(new 
						string(*(ts->GetString())));
					const string *name = ts->GetString();
					string copy = *name;
					if (substring || *pattern == copy) {
						r += copy.replace(*pattern, 
							*replace, 
							caseSensitive);
						if (copy != *name)
							GetDiagram()->
							    SetText(ts, &copy);
					}
				}
			}
		}
		view->SelectShape(shape);
		string txt = "replace next: pattern found, made "; 
		txt += r;
		txt += " replacement";
		txt += ((r==1?"":"s"));
		GetMainWindow()->SetStatus(&txt);
		const Point *pt = shape->GetPosition();
		double x = Scale(pt->x);
		double y = Scale(pt->y);
		GetMainWindow()->ShowPosition(int(0.5 + x), int(0.5 + y));
		GetDocument()->IncChanges();
		SetCmdDone(True);
	}
	else
		GetMainWindow()->SetStatus("replace next: pattern not found");
}
