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
#include "diagram.h"
#include "messagedialog.h"
#include "replacealltextscmd.h"

ReplaceAllTextsCmd::ReplaceAllTextsCmd(ShapeView *v, const string *p, 
		const string *o, bool c, bool s, bool n): 
	ReplaceTextCmd(v, p, o, c, s, n) {}

void ReplaceAllTextsCmd::Execute() {
	int count = 0;
	int replaces = 0;
	bool error = False;
	if (*pattern == *replace) {
		MessageDialog *d = new MessageDialog(
			GetMainWindow()->GetWidget(), MessageDialog::ERROR);
		d->Show("Error", 
			"Replace all: find and replace text are identical");
		GetMainWindow()->SetStatus(
			"aborted: identical find and replace");
		Abort();
		return;
	}
	List<GShape *> shapes2(*view->GetShapes());
	view->DeselectAll();
	for (shapes2.first(); !shapes2.done(); shapes2.next()) {
		int r = 0;
		Shape *shape = (Shape *)shapes2.cur();
		if (nameOnly) {
			if (shape->HasNameString(pattern, caseSensitive, 
			    substring)) {
				TextShape *ts;
				if (shape->IsTextShape())
					ts = ((GShape *)shape)->GetName();
				else
					ts = (TextShape *)shape;
				textShapes->add(ts);
				Point *pt = new Point(
					shape->GetWidth(), shape->GetHeight()); 
				oldSizes->add(pt);
				const string *name = ts->GetString();
				string copy = *name;
				oldStrings->add(new string(copy));
				if (!error && (substring || *pattern == copy)) {
					r = copy.replace(*pattern, *replace, 
							 caseSensitive);
					if (copy != *name) {
						if (!GetDiagram()->
							SetText(ts, &copy))
							error = True;
					}
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
					if (!error & (substring || 
							*pattern == copy)) {
						r = copy.replace(*pattern, 
							*replace, 
							caseSensitive);
						if (copy != *name) {
							if (!GetDiagram()->
							SetText(ts, &copy))
								error = True;
						}
					}
				}
				tshapes.empty();
			}
		}
		if (r > 0) {
			count++;
			replaces += r;
			view->SelectShape(shapes2.cur());
		}
	}
	if (error) {
		MessageDialog *d = new MessageDialog(
				GetMainWindow()->GetWidget(), 
				MessageDialog::WARNING);
		d->SetCenteredOnPointer(False);
		d->Show("Warning", 
			"Replace all is aborted after\n"
			"the first encountered error");
	}
	if (count == 0)
		GetMainWindow()->SetStatus("replace all: pattern not found");
	else {
		string txt = "replace all: ";
		txt += count;
		txt += " shapes found, made ";
		txt += replaces;
		txt += " replacements";
		GetDocument()->IncChanges();
		SetCmdDone(True);
		GetMainWindow()->SetStatus(&txt);
	}
}
