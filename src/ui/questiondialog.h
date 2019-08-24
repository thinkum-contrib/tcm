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
#ifndef _QUESTIONDIALOG_H
#define _QUESTIONDIALOG_H

#include "messagedialog.h"

/// question dialog class.
class QuestionDialog: public MessageDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// answers to no/yes/cancel dialog questions.
	enum AnswerType {UNKNOWN, YES, NO, CANCEL};
	///
	QuestionDialog(Widget parent, bool cancel);
	///
        const char *GetClassName() { return "QuestionDialog";}

	/// do not use.
	void Popup();
	/// do not use.
	void Show(const char *, const char *);
	/// do not use.
	void Show(const char *, const string *);
	///
	AnswerType GetAnswer();
	///
	void SetAnswer(AnswerType a) {answer=a;}
protected:
	///
	void CreateWidget();
	///
	void Configure();
	///
	static void ResponseCB(Widget, XtPointer answer, XtPointer cbs);
private:
	///
	bool withCancel;
	///
	AnswerType answer;
};
#endif
