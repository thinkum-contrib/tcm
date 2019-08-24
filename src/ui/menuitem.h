//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _MENUITEM_H
#define _MENUITEM_H

#include "bool.h"
#include "bitmap.h"
#include <X11/Intrinsic.h>

/// data structure that comprises all the important aspects of a menu item.
class MenuItem {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	enum ItemType {
		PUSHBUTTON, LABEL, SUBMENU, 
		RADIOBUTTON, CHECKBUTTON, SEPARATOR};

	/// the label for the item 
	const char *label;

	///
	Bitmap bitmap;

	///
	bool showBitmap;

	/// pushbutton, submenu, checkbox, radiobox, separator .. 
	ItemType itemType;

	/// mnemonic; 0 character if none 
	char mnemonic;

	/// accelerator; 0 if none 
	const char *accelerator;	

	/// to be converted to compound string 
	const char *accelText; 	

	/// routine to call; 0 if none 
	XtCallbackProc callback;

	/// client data for callback() 
	XtPointer callbackData;

	/// user data for callback.
	XtPointer userData;

	/// pullright menu items, if not: 0 
	MenuItem *subitems;

	/// 0: insensitive, 1: sensitive 
	int sensitive;

	///
	MenuItem() {label=0;}

	///
	MenuItem(const char *l, ItemType i); 
	///
	MenuItem(const char *l, ItemType i, char m, const char *a, 
		const char *t, XtCallbackProc c, XtPointer d, XtPointer u, 
		MenuItem *si, int s); 
	///
	MenuItem(const char *l, const Bitmap *b, ItemType i, char m, 
		const char *a, const char *t,
		XtCallbackProc c, XtPointer d, XtPointer u, 
		MenuItem *si, int s); 
	///
	static const MenuItem NUL;
	///
	static const MenuItem SEP;
};

#endif
