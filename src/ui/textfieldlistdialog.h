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
#ifndef _TEXTFIELDLISTDIALOG_H
#define _TEXTFIELDLISTDIALOG_H

#include "dialog.h"
#include "llist.h"

/// dialog class for showing a list of text fields.
class TextFieldListDialog: public Dialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	TextFieldListDialog(Widget parent);
	///
	virtual ~TextFieldListDialog();
	///
        const char *GetClassName() { return "TextFieldListDialog";}
	///
	void CreateFields(List<string *> *l, List<string *> *f);

	///
	void GetField(unsigned i, string *f);
	///
	void GetLabel(unsigned i, string *l);

	///
	void SetField(unsigned i, const string *f);
	///
	void SetFieldWidth(unsigned n);
	///
	void SetLabel(unsigned i, const string *l);

	///
	unsigned NumFields();
protected:
	///
	void CreateWidget();
	///
	void Configure();
private:
	/// 
	Widget rc;
	///
	int fieldWidth;
	///
	Widget *textFields;
	///
	unsigned numTextFields;
	///
	Widget *labels;
	///
	unsigned numLabels;
};
#endif
