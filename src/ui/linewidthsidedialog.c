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
#include "linewidthsidedialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "SideTop.xbm"
#include "SideBottom.xbm"
#include "SideLeft.xbm"
#include "SideRight.xbm"
#include "SideAll.xbm"
#include "SideSurrounding.xbm"

LineWidthSideDialog::LineWidthSideDialog(Widget w): LineWidthDialog(w) { 
}

void LineWidthSideDialog::MakeLabels(List<string *> *labels) {
	LineWidthDialog::MakeLabels(labels);
	labels->add(new string("Side of Selection"));
}

void LineWidthSideDialog::MakeItems(List<List<string *> *> *items) {
	LineWidthDialog::MakeItems(items);
	List<string *> *l = new List<string *>;
	l->add(new string("Top"));
        l->add(new string("Bottom"));
        l->add(new string("Left"));
        l->add(new string("Right"));
        l->add(new string("Surrounding"));
        l->add(new string("All four"));
	items->add(l);
}

void LineWidthSideDialog::MakeBitmaps() {
	LineWidthDialog::MakeBitmaps();
	Bitmap icon1 = {SideTop_width, SideTop_height, SideTop_bits};
	Bitmap icon2 = {SideBottom_width, SideBottom_height, SideBottom_bits};
	Bitmap icon3 = {SideLeft_width, SideLeft_height, SideLeft_bits};
	Bitmap icon4 = {SideRight_width, SideRight_height, SideRight_bits};
	Bitmap icon5 = {SideSurrounding_width, SideSurrounding_height, SideSurrounding_bits};
	Bitmap icon6 = {SideAll_width, SideAll_height, SideAll_bits};
	SetItemBitmap(1, 0, &icon1);
	SetItemBitmap(1, 1, &icon2);
	SetItemBitmap(1, 2, &icon3);
	SetItemBitmap(1, 3, &icon4);
	SetItemBitmap(1, 4, &icon5);
	SetItemBitmap(1, 5, &icon6);
}

void LineWidthSideDialog::MakeLiteClues() {
	LineWidthDialog::MakeLiteClues();
	List<Widget> *tl = (*GetToggleList())[1];
	AddLiteClue((*tl)[0], "Top");
	AddLiteClue((*tl)[1], "Bottom");
	AddLiteClue((*tl)[2], "Left");
	AddLiteClue((*tl)[3], "Right");
	AddLiteClue((*tl)[4], "Surrounding");
	AddLiteClue((*tl)[5], "All");
}

void LineWidthSideDialog::Configure() {
	LineWidthDialog::Configure();
	List<Widget> *tl = (*GetToggleList())[1];
	Widget rc = XtParent((*tl)[1]);
	XtVaSetValues(rc, XmNnumColumns, 3, 
			  XmNorientation, 
			  XmHORIZONTAL, 0);
}
