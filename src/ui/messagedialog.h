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
#ifndef _MESSAGEDIALOG_H
#define _MESSAGEDIALOG_H

#include "dialog.h"
class string;

/// message dialog class.
class MessageDialog: public Dialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	enum DialogType {ERROR, INFORMATION, MESSAGE, QUESTION,
			 WARNING, WORKING};
	///
	MessageDialog(Widget parent);
	///
	MessageDialog(Widget parent, DialogType t);
	///
        const char *GetClassName() { return "MessageDialog";}
	///
	void Popup();
	///
	virtual void Show(const char *title, const char *msg);
	///
	virtual void Show(const char *title, const string *msg);

	///
	void SetMessageString(const string *s);
	///
	void SetMessageString(const char *s);
protected:
	///
	void CreateWidget();
	///
	void Configure();
private:
	///
	DialogType dialogType;
};
#endif
