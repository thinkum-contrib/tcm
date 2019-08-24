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
#include "menuitem.h"

const MenuItem MenuItem::SEP = MenuItem("",MenuItem::SEPARATOR,0,0,0,0,0,0,0,0);

const MenuItem MenuItem::NUL = MenuItem();

MenuItem::MenuItem(const char *l, ItemType i) {
	label=l; 
	itemType=i;
        mnemonic=0; 
	accelerator=0; 
	accelText=0;
        callback=0; 
	callbackData=0; 
	userData=0;
        subitems=0; 
	sensitive=0;
	showBitmap = False;
}
 
MenuItem::MenuItem(const char *l, ItemType i, char m, const char *a, 
		char const *t, XtCallbackProc c, XtPointer d, XtPointer u, 
		MenuItem *si, int s) {
        label=l; 
	itemType=i; 
	mnemonic=m; 
	accelerator=a;
        accelText=t; 
	callback=c; 
	callbackData=d;
        userData=u; 
	subitems=si; 
	sensitive=s;
	showBitmap = False;
}

MenuItem::MenuItem(const char *l, const Bitmap *b, ItemType i, char m, 
	const char *a, const char *t, XtCallbackProc c, XtPointer d, 
	XtPointer u, MenuItem *si, int s) {
        label = l; 
	bitmap = *b;
	itemType=i; 
	mnemonic=m; 
	accelerator=a;
        accelText=t; 
	callback=c; 
	callbackData=d;
        userData=u; 
	subitems=si; 
	sensitive=s;
	showBitmap = True;
}
