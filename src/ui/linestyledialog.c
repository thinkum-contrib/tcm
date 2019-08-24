////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "linestyledialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "LineStyleSolid.xbm"
#include "LineStyleDashed.xbm"
#include "LineStyleDotted.xbm"
#include "LineStyleWideDotted.xbm"
#include "LineStyleDual.xbm"

LineStyleDialog::LineStyleDialog(Widget w): NToggleListDialog(w, False) { 
	SetAutoUnmanage(False);
}

void LineStyleDialog::MakeLabels(List<string *> *labels) {
        labels->add(new string("Line Style"));
}

void LineStyleDialog::MakeItems(List<List<string *> *> *items) {
        List<string *> *l = new List<string *>;
	l->add(new string("Solid"));
        l->add(new string("Dashed"));
        l->add(new string("Dotted"));
        l->add(new string("Dual"));
        l->add(new string("Invisible"));
        l->add(new string("WideDotted"));
        items->add(l);
}

void LineStyleDialog::MakeBitmaps() {
	Bitmap solidIcon = {LineStyleSolid_width, LineStyleSolid_height, 
			    LineStyleSolid_bits};
	Bitmap dashedIcon = {LineStyleDashed_width, LineStyleDashed_height, 
			    LineStyleDashed_bits};
	Bitmap dottedIcon = {LineStyleDotted_width, LineStyleDotted_height, 
			    LineStyleDotted_bits};
	Bitmap dualIcon = {LineStyleDual_width, LineStyleDual_height, 
			    LineStyleDual_bits};
	Bitmap widedottedIcon = 
		{LineStyleWideDotted_width, LineStyleWideDotted_height, 
			    LineStyleWideDotted_bits};
	SetItemBitmap(0, 0, &solidIcon);
	SetItemBitmap(0, 1, &dashedIcon);
	SetItemBitmap(0, 2, &dottedIcon);
	SetItemBitmap(0, 3, &dualIcon);
	SetItemBitmap(0, 5, &widedottedIcon);
}

void LineStyleDialog::MakeLiteClues() {
	List<Widget> *tl = (*GetToggleList())[0];
	AddLiteClue((*tl)[0], "Solid");
	AddLiteClue((*tl)[1], "Dashed (4-2)");
	AddLiteClue((*tl)[2], "Dotted (1-1)");
	AddLiteClue((*tl)[3], "Dual lines");
	AddLiteClue((*tl)[4], "Invisible");
	AddLiteClue((*tl)[5], "Wide dotted (2-2)");
}

void LineStyleDialog::Configure() {
	NToggleListDialog::Configure();
	List<string *> labels;
	List<List<string *> *> items;
	MakeLabels(&labels);
        MakeItems(&items);
	CreateToggleLists(&labels, &items);
	labels.clear();
	for (items.first(); !items.done(); items.next())
                items.cur()->clear();
	items.clear();
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	MakeBitmaps();
	MakeLiteClues();
	List<Widget> *tl = (*GetToggleList())[0];
	Widget rc = XtParent((*tl)[0]);
	XtVaSetValues(rc, XmNnumColumns, 3, 
			  XmNorientation, XmHORIZONTAL, NULL);
}
