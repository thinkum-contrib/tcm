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
#include "lineenddialog.h"
#include "lineend.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "LineEndEmpty.xbm"
#include "LineBeginOpenArrow.xbm"
#include "LineBeginFilledArrow.xbm"
#include "LineBeginDoubleOpenArrow.xbm"
#include "LineBeginDoubleFilledArrow.xbm"
#include "LineBeginWhiteCircle.xbm"
#include "LineBeginBlackCircle.xbm"
#include "LineBeginWhiteDiamond.xbm"
#include "LineBeginBlackDiamond.xbm"
#include "LineBeginWhiteTriangle.xbm"
#include "LineBeginBlackTriangle.xbm"
#include "LineEndOpenArrow.xbm"
#include "LineEndFilledArrow.xbm"
#include "LineEndDoubleOpenArrow.xbm"
#include "LineEndDoubleFilledArrow.xbm"
#include "LineEndWhiteCircle.xbm"
#include "LineEndBlackCircle.xbm"
#include "LineEndWhiteDiamond.xbm"
#include "LineEndBlackDiamond.xbm"
#include "LineEndWhiteTriangle.xbm"
#include "LineEndBlackTriangle.xbm"
 

LineEndDialog::LineEndDialog(Widget w): NToggleListDialog(w, False) { 
	SetAutoUnmanage(False);
}

void LineEndDialog::Configure() {
	NToggleListDialog::Configure();
	List<string *> labels;
	labels.add(new string("Begin of line"));
	labels.add(new string("End of line"));
	List<List<string *> *> items;
	List<string *> l1;
	List<string *> l2;
	for (int i=1; i<=LineEnd::NUMTYPES; i++) {
		LineEnd::Type t = (LineEnd::Type)i;
		string *s1 = new string;
		string *s2 = new string;
		LineEnd::Type2String(t, s1);
		LineEnd::Type2String(t, s2);
		l1.add(s1);
        	l2.add(s2);
	}
	items.add(&l1);
	items.add(&l2);
	CreateToggleLists(&labels, &items);
	labels.clear();
	l1.clear();
	l2.clear();
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	Bitmap icon1 = 
		{LineEndEmpty_width, LineEndEmpty_height, 
		 LineEndEmpty_bits};
	Bitmap iconb2 = 
		{LineBeginOpenArrow_width, LineBeginOpenArrow_height, 
	         LineBeginOpenArrow_bits};
	Bitmap iconb3 = 
		{LineBeginFilledArrow_width, LineBeginFilledArrow_height, 
		 LineBeginFilledArrow_bits};
	Bitmap iconb4 = 
		{LineBeginDoubleOpenArrow_width, LineBeginDoubleOpenArrow_height, 
		 LineBeginDoubleOpenArrow_bits};
	Bitmap iconb5 = 
		{LineBeginDoubleFilledArrow_width, LineBeginDoubleFilledArrow_height,
		 LineBeginDoubleFilledArrow_bits};
	Bitmap iconb6 = 
		{LineBeginWhiteCircle_width, LineBeginWhiteCircle_height,
		 LineBeginWhiteCircle_bits};
	Bitmap iconb7 = 
		{LineBeginBlackCircle_width, LineBeginBlackCircle_height,
	   	 LineBeginBlackCircle_bits};
	Bitmap iconb8 = 
		{LineBeginWhiteDiamond_width, LineBeginWhiteDiamond_height,
		 LineBeginWhiteDiamond_bits};
	Bitmap iconb9 = 
		{LineBeginBlackDiamond_width, LineBeginBlackDiamond_height,
	    	 LineBeginBlackDiamond_bits};
	Bitmap iconb10 = 
		{LineBeginWhiteTriangle_width, LineBeginWhiteTriangle_height,
		 LineBeginWhiteTriangle_bits};
	Bitmap iconb11 = 
		{LineBeginBlackTriangle_width, LineBeginBlackTriangle_height,
		 LineBeginBlackTriangle_bits};
	Bitmap icone2 = 
		{LineEndOpenArrow_width, LineEndOpenArrow_height, 
	         LineEndOpenArrow_bits};
	Bitmap icone3 = 
		{LineEndFilledArrow_width, LineEndFilledArrow_height, 
		 LineEndFilledArrow_bits};
	Bitmap icone4 = 
		{LineEndDoubleOpenArrow_width, LineEndDoubleOpenArrow_height, 
		 LineEndDoubleOpenArrow_bits};
	Bitmap icone5 = 
		{LineEndDoubleFilledArrow_width, LineEndDoubleFilledArrow_height,
		 LineEndDoubleFilledArrow_bits};
	Bitmap icone6 = 
		{LineEndWhiteCircle_width, LineEndWhiteCircle_height,
		 LineEndWhiteCircle_bits};
	Bitmap icone7 = 
		{LineEndBlackCircle_width, LineEndBlackCircle_height,
	   	 LineEndBlackCircle_bits};
	Bitmap icone8 = 
		{LineEndWhiteDiamond_width, LineEndWhiteDiamond_height,
		 LineEndWhiteDiamond_bits};
	Bitmap icone9 = 
		{LineEndBlackDiamond_width, LineEndBlackDiamond_height,
	    	 LineEndBlackDiamond_bits};
	Bitmap icone10 = 
		{LineEndWhiteTriangle_width, LineEndWhiteTriangle_height,
		 LineEndWhiteTriangle_bits};
	Bitmap icone11 = 
		{LineEndBlackTriangle_width, LineEndBlackTriangle_height,
		 LineEndBlackTriangle_bits};
	SetItemBitmap(0, 0, &icon1);
	SetItemBitmap(0, 1, &iconb2);
	SetItemBitmap(0, 2, &iconb3);
	SetItemBitmap(0, 3, &iconb4);
	SetItemBitmap(0, 4, &iconb5);
	SetItemBitmap(0, 5, &iconb6);
	SetItemBitmap(0, 6, &iconb7);
	SetItemBitmap(0, 7, &iconb8);
	SetItemBitmap(0, 8, &iconb9);
	SetItemBitmap(0, 9, &iconb10);
	SetItemBitmap(0, 10, &iconb11);
	SetItemBitmap(1, 0, &icon1);
	SetItemBitmap(1, 1, &icone2);
	SetItemBitmap(1, 2, &icone3);
	SetItemBitmap(1, 3, &icone4);
	SetItemBitmap(1, 4, &icone5);
	SetItemBitmap(1, 5, &icone6);
	SetItemBitmap(1, 6, &icone7);
	SetItemBitmap(1, 7, &icone8);
	SetItemBitmap(1, 8, &icone9);
	SetItemBitmap(1, 9, &icone10);
	SetItemBitmap(1, 10, &icone11);
	List<Widget> *tl1 = (*GetToggleList())[0];
	List<Widget> *tl2 = (*GetToggleList())[1];
	XtVaSetValues(XtParent((*tl1)[0]), 
		XmNnumColumns, 4, XmNorientation, XmHORIZONTAL, 0);
	XtVaSetValues(XtParent((*tl2)[0]), 
		XmNnumColumns, 4, XmNorientation, XmHORIZONTAL, 0);
	for (int k=1; k<=LineEnd::NUMTYPES; k++) {
		LineEnd::Type t = (LineEnd::Type)k;
		string s1;
		string s2;
		LineEnd::Type2String(t, &s1);
		LineEnd::Type2String(t, &s2);
		AddLiteClue((*tl1)[k-1], s1.getstr());
		AddLiteClue((*tl2)[k-1], s2.getstr());
	}
}
