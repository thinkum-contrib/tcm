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
#ifndef _TOGGLELISTDIALOG_H
#define _TOGGLELISTDIALOG_H

#include "promptdialog.h"
#include "llist.h"
class string;
class Bitmap;

/// dialog class that shows a list of radio buttons.
class ToggleListDialog: public PromptDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	ToggleListDialog(Widget parent, bool prompt);
	///
	virtual ~ToggleListDialog();
	///
        const char *GetClassName() { return "ToggleListDialog";}
	///
	void SetToggleChangedCallback(XtCallbackProc fun, XtPointer cd);
	///
	void CreateToggles(List<string *> *items);
	///
	void CreateToggles(const string *label, List<string *> *items);
	///
	void SetToggleText(unsigned i, const string *text);
	///
	void SetToggleBitmap(unsigned i, Bitmap *bitmap);
	///
	void GetToggleText(unsigned i, string *text);
	///
	void SetValue(unsigned initVal);
	///
	int GetValue();
	///
	unsigned NumToggles();
	///
	bool IsPromptVisible() {return promptVisible;}
protected:
	///
	void CreateWidget();
	///
	void Configure();
private:
	///
	Widget *toggleList;
	///
	unsigned numToggles;
	///
	XtCallbackProc toggleFun;
	///
	XtPointer clientData;
	///
	bool promptVisible;
};
#endif
