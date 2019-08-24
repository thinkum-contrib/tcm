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
#include "questiondialog.h"
#include "application.h"
#include "error.h"
#include "mstring.h"
#include <Xm/XmAll.h>

QuestionDialog::QuestionDialog(Widget w, bool cancel): 
		MessageDialog(w, MessageDialog::QUESTION) {
	withCancel = cancel;
	answer = UNKNOWN;
}

void QuestionDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateQuestionDialog(GetParent(), (char *)GetClassName(), args, i));
}

void QuestionDialog::Configure() {
	SetModal(True);
	if (!withCancel)
		ManageHelpButton(False);
	SetOKButtonLabel("Yes");
	SetCancelButtonLabel("No");
	SetHelpButtonLabel("Cancel");
	// define callback for the yes, no and cancel button
	SetOKCallback(ResponseCB, this);
	SetCancelCallback(ResponseCB, this);
	if (withCancel)
		SetHelpCallback(ResponseCB, this);
	else
		ManageHelpButton(False);
}

void QuestionDialog::Popup() {
	error("%s, line %d: Use GetAnswer() in question dialog\n",
		__FILE__, __LINE__);
}

void QuestionDialog::Show(const char *, const char *) {
	error("%s, line %d: Use GetAnswer() in question dialog\n",
		__FILE__, __LINE__);
}

void QuestionDialog::Show(const char *s, const string *m) {
	Show(s, m->getstr());
}

QuestionDialog::AnswerType QuestionDialog::GetAnswer() {
	MessageDialog::Popup();
	answer = UNKNOWN;
	// while the user has not provided an answer, simulate main
	// loop. The answer changes as soon as the user selects one of
	// the buttons and the callback routine changes its value.
	// Don't break loop until XtPending() also returns False to
	// assure widget destruction.
	XtAppContext applicationContext = theApplication->GetAppContext();
	while (answer == UNKNOWN)
		XtAppProcessEvent(applicationContext, XtIMAll);
	return answer;
}

void QuestionDialog::ResponseCB(Widget, XtPointer cd, XtPointer cbs) {
	XmAnyCallbackStruct *s = (XmAnyCallbackStruct *)cbs;
	QuestionDialog *q = (QuestionDialog *)cd;
	AnswerType a = NO;
	switch (s->reason) {
	case XmCR_CANCEL:
		a = NO;
		break;
	case XmCR_OK:
		a = YES;
		break;
	case XmCR_HELP:
		a = CANCEL;
		break;
	default:
		break;
	}
	q->SetAnswer(a);
}
