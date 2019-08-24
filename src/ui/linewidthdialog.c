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
#include "linewidthdialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "LineWidth1.xbm"
#include "LineWidth2.xbm"
#include "LineWidth3.xbm"
#include "LineWidth4.xbm"
#include "LineWidth5.xbm"
#include "LineWidth6.xbm"
#include "LineWidth7.xbm"
#include "LineWidth8.xbm"
#include "LineWidth9.xbm"

LineWidthDialog::LineWidthDialog(Widget w): NToggleListDialog(w, False) { 
	SetAutoUnmanage(False);
}

void LineWidthDialog::MakeLabels(List<string *> *labels) {
	labels->add(new string("Line Width"));
}

void LineWidthDialog::MakeItems(List<List<string *> *> *items) {
	List<string *> *l = new List<string *>;
	l->add(new string("1"));
        l->add(new string("2"));
        l->add(new string("3"));
        l->add(new string("4"));
        l->add(new string("5"));
        l->add(new string("6"));
        l->add(new string("7"));
        l->add(new string("8"));
        l->add(new string("9"));
	items->add(l);
}

void LineWidthDialog::MakeBitmaps() {
	Bitmap icon1 = {LineWidth1_width, LineWidth1_height, LineWidth1_bits};
	Bitmap icon2 = {LineWidth2_width, LineWidth2_height, LineWidth2_bits};
	Bitmap icon3 = {LineWidth3_width, LineWidth3_height, LineWidth3_bits};
	Bitmap icon4 = {LineWidth4_width, LineWidth4_height, LineWidth4_bits};
	Bitmap icon5 = {LineWidth5_width, LineWidth5_height, LineWidth5_bits};
	Bitmap icon6 = {LineWidth6_width, LineWidth6_height, LineWidth6_bits};
	Bitmap icon7 = {LineWidth7_width, LineWidth7_height, LineWidth7_bits};
	Bitmap icon8 = {LineWidth8_width, LineWidth8_height, LineWidth8_bits};
	Bitmap icon9 = {LineWidth9_width, LineWidth9_height, LineWidth9_bits};
	SetItemBitmap(0, 0, &icon1);
	SetItemBitmap(0, 1, &icon2);
	SetItemBitmap(0, 2, &icon3);
	SetItemBitmap(0, 3, &icon4);
	SetItemBitmap(0, 4, &icon5);
	SetItemBitmap(0, 5, &icon6);
	SetItemBitmap(0, 6, &icon7);
	SetItemBitmap(0, 7, &icon8);
	SetItemBitmap(0, 8, &icon9);
}

void LineWidthDialog::MakeLiteClues() {
	List<Widget> *tl = (*GetToggleList())[0];
	AddLiteClue((*tl)[0], "1");
	AddLiteClue((*tl)[1], "2");
	AddLiteClue((*tl)[2], "3");
	AddLiteClue((*tl)[3], "4");
	AddLiteClue((*tl)[4], "5");
	AddLiteClue((*tl)[5], "6");
	AddLiteClue((*tl)[6], "7");
	AddLiteClue((*tl)[7], "8");
	AddLiteClue((*tl)[8], "9");
}

void LineWidthDialog::Configure() {
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
