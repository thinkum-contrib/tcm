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
#ifndef _MODELCHECKDIALOG_H
#define _MODELCHECKDIALOG_H

#include "selectiondialog.h"

/// model check dialog class.
class ModelCheckDialog: public SelectionDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	ModelCheckDialog(Widget parent);
	///
        /* virtual */ const char *GetClassName() { return "ModelCheckDialog";}
	///
	void GetFormulaString(char *s) { GetTextString(s); }
	///
	void GetFormulaString(string *s) { GetTextString(s); }
	///
	void GetInternString(char *);
	///
	void GetInternString(string *);
	///
	void GetClockString(char *);
	///
	void GetClockString(string *);
protected:
	///
	void Configure();
	///
	void CreateWidget();
	///
	Widget GetForm() {return form;}
private:
	///
	Widget form;

	///
	Widget internLabel;
	///
	Widget internText;
	///
	Widget clockLabel;
	///
	Widget clockText;
};
#endif
