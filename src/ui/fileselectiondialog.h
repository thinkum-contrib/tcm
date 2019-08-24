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
#ifndef _FILESELECTIONDIALOG_H
#define _FILESELECTIONDIALOG_H

#include "selectiondialog.h"
#include "llist.h"

/// file selection dialog class.
class FileSelectionDialog: public SelectionDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	FileSelectionDialog(Widget parent);
	///
        const char *GetClassName() { return "FileSelectionDialog";}

	///
	void SetExtension(const char *extension);
	///
	void SetExtension(const string *extension);
	///
	void SetDirectory(const char *d);
	///
	void SetDirectory(const string *d);
	///
	void SetDefaultFile(const char *f);
	///
	void SetDefaultFile(const string *f);

	///
	void CreateOptionMenu(string *label, List<string *> *items);
	///
	void GetOption(string *item);

	///
	void Popup();

	/// returns selected file name.
	void GetFileName(char *name);
	///
	void GetFileName(string *name);

	/// returns current directory
	void GetDirectory(char *dir);
	///
	void GetDirectory(string *name);

	///
	const string *GetDefaultFile() const {return &defaultFile;}

	///
	void ManageOptionMenu(bool b);

	///
	void SetOptionChangedCallback(XtCallbackProc fun, XtPointer cd);
	///
	void SetOption(const string *s);
protected:
	///
	void CreateWidget();
	///
	void Configure();
	///
	static void OptionChangedCB(Widget, XtPointer, XtPointer);
	///
	static void SetDefaultFileCB(Widget, XtPointer, XtPointer);
private:
	///
	Widget pane;
	///
	Widget menuFrame;
	///
	Widget menu;
	///
	string defaultFile;
};
#endif
