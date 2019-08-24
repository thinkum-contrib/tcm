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
#ifndef _TEXTEDITDIALOG_H
#define _TEXTEDITDIALOG_H

#include "textviewdialog.h"

/// manages text editor dialogs.
class TextEditDialog: public TextViewDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	TextEditDialog(Widget parent);
	///
        const char *GetClassName() { return "TextEditDialog";}
	///
	void Load();
	///
	void Replace();
	///
	void ClearReplace();
protected:
	///
	void Configure();
	///
	void InitMenuItems();
	///
	static void LoadCB(Widget, XtPointer, XtPointer);
	///
	static void LoadOKCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteAllCB(Widget, XtPointer, XtPointer);
	///
	static void CutCB(Widget, XtPointer, XtPointer);
	///
	static void PasteCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceNextCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceFindCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceAllCB(Widget, XtPointer, XtPointer);
	///
	static void ClearReplaceCB(Widget, XtPointer, XtPointer);
};
#endif
