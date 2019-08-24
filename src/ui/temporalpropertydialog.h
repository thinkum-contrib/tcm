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
#ifndef _TPDIALOG_H
#define _TPDIALOG_H

#include "selectiondialog.h"

/// temporal property dialog class.
class TPDialog: public SelectionDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	TPDialog(Widget parent);
	///
        const char *GetClassName() { return "TPDialog";}
	///
	bool SensitiveOn();
	///
	bool SubstringOn();
	///
	bool NameOnlyOn();
	///
	void ManageSensitiveToggle(bool b);
	///
	void ManageSubstringToggle(bool b);
	///
	void ManageNameOnlyToggle(bool b);
protected:
	///
	void Configure();
	///
	void CreateWidget();
	///
	Widget GetForm() {return form;}
	///
	Widget GetToggleRC() {return toggleRC;}
	///
	virtual void AttachToggles();
private:
	///
	Widget form;
	///
	Widget toggleRC;
	///
	Widget substringToggle;
	///
	Widget sensitiveToggle;
	///
	Widget nameOnlyToggle;
};
#endif
