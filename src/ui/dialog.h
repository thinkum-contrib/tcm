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
#ifndef _DIALOG_H
#define _DIALOG_H

#include "mwidget.h"

/// abstract dialog class.
class Dialog: public MWidget {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	Dialog(Widget parent);
	///
	virtual ~Dialog();
	///
        const char *GetClassName() { return "Dialog";}

	///
	void Initialize();

	///
	virtual void SetOKCallback(XtCallbackProc fun, XtPointer clientData);
	///
	virtual void SetCancelCallback(XtCallbackProc fun,XtPointer clientData);
	///
	virtual void SetHelpCallback(XtCallbackProc fun, XtPointer clientData);

	///
	void SetOKButtonLabel(const char *txt);
	///
	void SetCancelButtonLabel(const char *txt);
	///
	void SetHelpButtonLabel(const char *txt);

	///
	void ManageOKButton(bool);
	///
	void ManageCancelButton(bool);
	///
	void ManageHelpButton(bool);

	/// delete itself when unmapped.
	virtual void SetAutoDestroy(bool b);

	/// pop up dialog.
	virtual void Popup();
	/// pop down dialog.
	virtual void Popdown();

	/// set title string.
	void SetTitle(const char *title);
	/// 
	void SetTitle(const string *title);

	/// get title string.
	void GetTitle(char *title);
	/// 
	void GetTitle(string *title);

	/// make dialog application modal.
	void SetModal(bool b);
	
	/// 
	void SetAutoUnmanage(bool b);
	///
	bool GetAutoUnmanage() {return autoUnmanage;}
	///
	void SetCenteredOnPointer(bool b) {centeredOnPointer = b;}
	///
	static void UnmanageCB(Widget, XtPointer, XtPointer);
	///
	static void DestroyCB(Widget, XtPointer, XtPointer);
	///
	static void DestroyWidgetCB(Widget, XtPointer, XtPointer);
	///
	static void TraverseNextCB(Widget, XtPointer, XtPointer);
	///
	static void TraverseNextGroupCB(Widget, XtPointer, XtPointer);

	///
	static const unsigned MAXTITLE;
protected:
	///
	Widget GetParent() {return parent;}
	///
	void ManageWidget(Widget, bool);
	///
	virtual void CreateWidget() = 0;
	///
	virtual void Configure() = 0;
	///
	void ManageCenteredOnPointer();
private:
	///
	Widget parent;
	///
	bool autoDestroy;
	///
	bool autoUnmanage;
	///
	bool centeredOnPointer;
};
#endif
