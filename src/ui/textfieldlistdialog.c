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
#include "textfieldlistdialog.h"
#include "util.h"
#include "mstring.h"
#include <Xm/XmAll.h>

TextFieldListDialog::TextFieldListDialog(Widget w): Dialog(w) {
	fieldWidth = 20;
	rc = 0;
	numTextFields = 0;
	numLabels = 0;
	textFields = 0;
	labels = 0;
	SetAutoUnmanage(True);
}

TextFieldListDialog::~TextFieldListDialog() {
	if (textFields)
		delete[] textFields;
	if (labels)
		delete[] labels;
}

void TextFieldListDialog::CreateFields(List<string *> *names, 
		List<string *> *values) {
	if (!check(names->count() == values->count()))
		return;
	if (rc) {
		XtDestroyWidget(rc);
		rc = 0;
		delete[] textFields;
		delete[] labels;
		textFields = 0;
		labels = 0;
	}
	numTextFields = 0;
	numLabels = 0;
	// create a manager widget as a child of the dialog.
	rc = XtVaCreateWidget("rc",
		xmRowColumnWidgetClass, GetWidget(),
		XmNnumColumns, 2,
		XmNpacking, XmPACK_COLUMN,
		XmNorientation, XmVERTICAL, 0);
	labels = new Widget[names->count()];
	for (names->first(); !names->done(); names->next()) {
		Widget w1 = XtVaCreateManagedWidget(names->cur()->getstr(), 
			xmLabelWidgetClass, rc, 0);
		labels[numLabels] = w1;
		numLabels++;
	}
	textFields = new Widget[values->count()];
	for (values->first(); !values->done(); values->next()) {
		Widget w2 = XtVaCreateManagedWidget("field",
			xmTextFieldWidgetClass, rc, 0);
		XmTextSetString(w2, (char *)values->cur()->getstr());
		textFields[numTextFields] = w2;
		numTextFields++;
	}
	XtManageChild(rc);
}

 
void TextFieldListDialog::SetFieldWidth(unsigned n) {
	fieldWidth = n;
	for (unsigned i=0; i<numTextFields; i++)
		XtVaSetValues(textFields[i], XmNcolumns, n, 0);
}

unsigned TextFieldListDialog::NumFields() {
	return numTextFields;
}

void TextFieldListDialog::SetLabel(unsigned i, const string *n) {
	if (check(i < numLabels))
		XtVaSetValues(labels[i], XmNvalue, n->getstr(), 0);
}

void TextFieldListDialog::GetLabel(unsigned i, string *n) {
	if (check(i < numLabels)) {
		char *s;
		XtVaGetValues(labels[i], XmNvalue, &s, 0);
		*n = s;
		XtFree(s);
	}
}

void TextFieldListDialog::SetField(unsigned i, const string *v) {
	if (check(i < numTextFields))
		XmTextSetString(textFields[i], (char *)v->getstr());
}

void TextFieldListDialog::GetField(unsigned i, string *v) {
	if (check(i < numTextFields)) {
		char *s = XmTextGetString(textFields[i]);
		*v = s;
		XtFree(s);
	}
}

void TextFieldListDialog::CreateWidget() {
	Arg args[10]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateMessageDialog(GetParent(), (char *)GetClassName(), args, i));
}

void TextFieldListDialog::Configure() {
	ManageHelpButton(False);
}
