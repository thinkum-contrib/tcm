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
#include "nodealignmentdialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "AlignTop.xbm"
#include "AlignBottom.xbm"
#include "AlignLeft.xbm"
#include "AlignRight.xbm"
#include "AlignHorizontal.xbm"
#include "AlignVertical.xbm"

NodeAlignmentDialog::NodeAlignmentDialog(Widget w): 
		NToggleListDialog(w, False) { 
	SetAutoUnmanage(False);
}

void NodeAlignmentDialog::Configure() {
	NToggleListDialog::Configure();
	List<string *> labels;
	labels.add(new string("Node Alignment"));
	List<List<string *> *> items;
	List<string *> l;
        l.add(new string("Top"));
        l.add(new string("Horizontal"));
        l.add(new string("Bottom"));
	l.add(new string("Left"));
        l.add(new string("Vertical"));
        l.add(new string("Right"));
	items.add(&l);
	CreateToggleLists(&labels, &items);
	labels.clear();
	l.clear();
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	Bitmap topIcon = {AlignTop_width, AlignTop_height, 
			    AlignTop_bits};
	Bitmap horizIcon = {AlignHorizontal_width, AlignHorizontal_height, 
			    AlignHorizontal_bits};
	Bitmap bottomIcon = {AlignBottom_width, AlignBottom_height, 
			    AlignBottom_bits};
	Bitmap leftIcon = {AlignLeft_width, AlignLeft_height, 
			    AlignLeft_bits};
	Bitmap vertIcon = {AlignVertical_width, AlignVertical_height, 
			    AlignVertical_bits};
	Bitmap rightIcon = {AlignRight_width, AlignRight_height, 
			    AlignRight_bits};
	SetItemBitmap(0, 0, &topIcon);
	SetItemBitmap(0, 1, &horizIcon);
	SetItemBitmap(0, 2, &bottomIcon);
	SetItemBitmap(0, 3, &leftIcon);
	SetItemBitmap(0, 4, &vertIcon);
	SetItemBitmap(0, 5, &rightIcon);
	List<Widget> *tl = (*GetToggleList())[0];
	Widget rc = XtParent((*tl)[0]);
	AddLiteClue((*tl)[0], "Align top");
	AddLiteClue((*tl)[1], "Align horizontal");
	AddLiteClue((*tl)[2], "Align bottom");
	AddLiteClue((*tl)[3], "Align left");
	AddLiteClue((*tl)[4], "Align vertical");
	AddLiteClue((*tl)[5], "Align right");
	XtVaSetValues(rc, XmNnumColumns, 2, 
			  XmNorientation, XmHORIZONTAL, 0);
}
