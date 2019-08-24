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
#ifndef _SELECTIONDIALOG_H
#define _SELECTIONDIALOG_H

#include "dialog.h"
#include "util.h"

/// selection dialog class.
class SelectionDialog: public Dialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	SelectionDialog(Widget parent);
	///
        const char *GetClassName() { return "SelectionDialog";}

	/// sets selection value
	void SetTextString(const char *v);
	///
	void SetTextString(const string *v);

	/// make text field (un)editable
	void SetEditable(bool b);

	/// returns selection value.
	void GetTextString(char *n);
	///
	void GetTextString(string *n);

	///
	void ManageTextString(bool);

	///
	void SetSelectionLabel(const char *l);
	///
	void ManageSelectionLabel(bool);

	///
	void SetApplyCallback(XtCallbackProc fun, XtPointer clientData);
	///
	void SetApplyButtonLabel(const char *txt);
	///
	void ManageApplyButton(bool);

	///
	static void ClearCB(Widget, XtPointer, XtPointer);
	///
	static void SetDefaultCB(Widget, XtPointer, XtPointer);

	///
	void SetDefaultValue(const char *s);
	///
	void SetDefaultValue(const string *s);
	///
	const string *GetDefaultValue() {return &defaultValue;}

	///
	void SelectItem(const string *label);
	///
	void DeselectAllItems();
	///
	void DeleteAllItems();

	///
	void AddItem(const char *text, int pos = 0);
	///
	void AddItem(const string *text, int pos = 0);
protected:
	///
	Widget GetText() {return text;}
	///
	void SetText(Widget w) {text=w;}
	///
	Widget GetList() {return list;}
	///
	Widget GetSelectionLabel() {return selectionLabel;}
	///
	void SetSelectionLabel(Widget w) {selectionLabel=w;}
	///
	void CreateWidget();
	///
	void Configure();
private:
	///
	string defaultValue;
	///
	Widget text;
	///
	Widget selectionLabel;
	///
	Widget list;
};
#endif
