//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
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
#ifndef _COLORCHOOSERDIALOG_H
#define _COLORCHOOSERDIALOG_H

#include "selectiondialog.h"
#include "color.h"
#include "llist.h"

/// color chooser dialog class.
class ColorChooserDialog: public SelectionDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	ColorChooserDialog(Widget parent);
	///
	~ColorChooserDialog();
	///
	const char *GetClassName() { return "ColorChooserDialog";}
	///
	static void UpdateColorCB(Widget, XtPointer, XtPointer);
	///
	void ShowColor(unsigned p);
	///
	void ManageFillToggle(bool b);
	///
	void SetFillToggle(bool b);
	///
	bool FillToggleOn();
	///
	void SetFillToggleLabel(const char *s);
	///
	void Popup();
protected:
	///
	void Configure();
private:
	///
	Widget colorLabel;
        /// 
        List<Color *> *colors;
	/// X colormap.
        Colormap colormap;
	///
	Widget fillToggle;
};
#endif
