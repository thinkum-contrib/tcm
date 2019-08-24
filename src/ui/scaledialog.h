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
#ifndef _SCALEDIALOG_H
#define _SCALEDIALOG_H

#include "messagedialog.h"

/// scale dialog class.
class ScaleDialog: public MessageDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	ScaleDialog(Widget parent);
	///
        const char *GetClassName() { return "ScaleDialog";}
	///
	void SetScaleValues(int min, int max, int init, int decimal, int def);
	///
	void SetScaleLabel(const char *text);
	///
	void SetValueChangedCallback(XtCallbackProc fun, XtPointer clientData);
	///
	void SetScaleValue(int val);
	///
	int GetScaleValue();
	///
	int GetDefaultValue() {return defaultValue;}
	///
	int GetInitValue() {return initValue;}
protected:
	///
	void CreateWidget();
	///
	void Configure();
	///
	static void SetDefaultCB(Widget, XtPointer cd, XtPointer);
	///
	static void SetInitCB(Widget, XtPointer cd, XtPointer);
private:
	///
	Widget scale;
	///
	int defaultValue;
	///
	int initValue;
	///
	XtCallbackProc valueChangeFun;
	///
	XtPointer clientData;
};
#endif
