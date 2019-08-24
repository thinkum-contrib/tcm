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
#include "textalignmentdialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "TextAlignmentCenter.xbm"
#include "TextAlignmentLeft.xbm"
#include "TextAlignmentRight.xbm"
#include "TextAlignmentVCenter.xbm"
#include "TextAlignmentVTop.xbm"
#include "TextAlignmentVBottom.xbm"

TextAlignmentDialog::TextAlignmentDialog(Widget w, bool h): 
		NToggleListDialog(w, False) { 
	horizontal = h;
	SetAutoUnmanage(False);
}

void TextAlignmentDialog::Configure() {
	NToggleListDialog::Configure();
	SetOKButtonLabel("Apply");
	List<string *> labels;
	labels.add(new string("Text Aligment"));
	List<List<string *> *> items;
	List<string *> l;
	if (horizontal) {
		l.add(new string("Left"));
        	l.add(new string("Center"));
		l.add(new string("Right"));
	}
	else {
		l.add(new string("Top"));
        	l.add(new string("Center"));
		l.add(new string("Bottom"));
	}
	items.add(&l);
	CreateToggleLists(&labels, &items);
	labels.clear();
	l.clear();
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	Bitmap leftIcon = {TextAlignmentLeft_width,
		TextAlignmentLeft_height, TextAlignmentLeft_bits};
	Bitmap centerIcon = {TextAlignmentCenter_width,
		TextAlignmentCenter_height, TextAlignmentCenter_bits};
	Bitmap rightIcon = {TextAlignmentRight_width,
		TextAlignmentRight_height, TextAlignmentRight_bits};
	Bitmap vCenterIcon = {TextAlignmentVCenter_width,
		TextAlignmentVCenter_height, TextAlignmentVCenter_bits};
	Bitmap vTopIcon = {TextAlignmentVTop_width,
		TextAlignmentVTop_height, TextAlignmentVTop_bits};
	Bitmap vBottomIcon = {TextAlignmentVBottom_width,
		TextAlignmentVBottom_height, TextAlignmentVBottom_bits};
	if (horizontal) {
		SetItemBitmap(0, 0, &leftIcon);
		SetItemBitmap(0, 1, &centerIcon);
		SetItemBitmap(0, 2, &rightIcon);
	}
	else {
		SetItemBitmap(0, 0, &vTopIcon);
		SetItemBitmap(0, 1, &vCenterIcon);
		SetItemBitmap(0, 2, &vBottomIcon);
	}
	List<Widget> *tl = (*GetToggleList())[0];
        Widget rc = XtParent((*tl)[0]);
	if (horizontal) {
		AddLiteClue((*tl)[0], "Left adjusted");
		AddLiteClue((*tl)[1], "Centered");
		AddLiteClue((*tl)[2], "Right adjusted");
	}
	else {
		AddLiteClue((*tl)[0], "Top");
		AddLiteClue((*tl)[1], "Center");
		AddLiteClue((*tl)[2], "Bottom");
	}
        XtVaSetValues(rc, XmNnumColumns, 3, 0);
}
