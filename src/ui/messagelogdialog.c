////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "messagelogdialog.h"
#include "system.h"
#include <Xm/XmAll.h>

MessageLogDialog::MessageLogDialog(Widget w): TextViewDialog(w) { 
	wprPosition = 0;
	SetCenteredOnPointer(False);
	count = 0;
	SetAutoUnmanage(True);
}

void MessageLogDialog::Configure() {
	TextViewDialog::Configure();
	XtVaSetValues(GetTextWidget(),
		XmNscrollHorizontal, False,
		XmNcolumns, 80,
		XmNblinkRate, 0,
		XmNautoShowCursorPosition, True, NULL);
}

void MessageLogDialog::InsertText(const string *txt) {
	InsertText(txt->getstr());
}

void MessageLogDialog::InsertText(const char *txt) {
	count++;
	(void) System::GetTime(timeAt);
	timeAt[19] = '\0';
	char *ptr = &timeAt[11];
	string tmp = "[";
	tmp += ptr;
	tmp += "] ";
	XmTextInsert(GetTextWidget(), wprPosition, (char *)tmp.getstr());
	wprPosition += tmp.length();
	XmTextInsert(GetTextWidget(), wprPosition, (char *)txt);
	wprPosition += strlen(txt);
	XtVaSetValues(GetTextWidget(), XmNcursorPosition, wprPosition, NULL);
	XmTextShowPosition(GetTextWidget(), wprPosition);
}
