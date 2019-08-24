////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "colorchooserdialog.h"
#include "application.h"
#include "mstring.h"
#include <Xm/XmAll.h>
#if defined(LINUX)
#include <stdio.h>
#endif
#include <stdlib.h>

ColorChooserDialog::ColorChooserDialog(Widget w): SelectionDialog(w) {
	colors = new List<Color *>;
	SetAutoUnmanage(False);
}

ColorChooserDialog::~ColorChooserDialog() {
	colors->clear();
	delete colors;
}

void ColorChooserDialog::Configure() {
	SelectionDialog::Configure();
	ManageCancelButton(True);
        ManageHelpButton(True);
        SetHelpButtonLabel("Default");
        SetOKButtonLabel("Apply");
        SetCancelButtonLabel("Dismiss");
        SetCancelCallback(Dialog::UnmanageCB, this);
        SetHelpCallback(SetDefaultCB, this);
	SetEditable(False);
	ManageApplyButton(False);
	ManageSelectionLabel(False);
	ManageTextString(False);
	List<Color *> *appColors = theApplication->GetColors();
        for (appColors->first(); !appColors->done(); appColors->next()) {
		Color *r = new Color(*appColors->cur());
		AddItem(&appColors->cur()->name);
		colors->add(r);;
	}
	XtAddCallback(GetList(), XmNbrowseSelectionCallback, 
		      UpdateColorCB, this);
	Widget rc = XtVaCreateManagedWidget("rc", 
		xmRowColumnWidgetClass, GetWidget(), NULL);
	fillToggle = XtVaCreateManagedWidget("fill them",
                xmToggleButtonWidgetClass, rc,
                XmNset, True, NULL);
	Widget rc2 = XtVaCreateManagedWidget("rc2",
                xmRowColumnWidgetClass, rc,
                XmNorientation, XmHORIZONTAL, NULL);
	XtVaCreateManagedWidget("preview: ", xmLabelWidgetClass, rc2, NULL);
	colorLabel = XtVaCreateManagedWidget(
		"", xmTextFieldWidgetClass, rc2, 
		XmNeditable, False, 
		XmNcursorPositionVisible, False, NULL);
	XtVaGetValues(GetWidget(), XmNcolormap, &colormap, NULL);
}

void ColorChooserDialog::UpdateColorCB(Widget, XtPointer p, XtPointer cbs) {
	XmListCallbackStruct *c = (XmListCallbackStruct *)cbs;
	int pos = c->item_position-1;
	ColorChooserDialog *d = (ColorChooserDialog *)p;
	d->ShowColor(pos);
}

void ColorChooserDialog::ShowColor(unsigned pos) {
	if (check(pos < colors->count())) {
		Color *r = (*colors)[pos];
		Pixel pixel;
		if (r->allocated)
			pixel = r->pixel;
		else {
        		XColor color;
			char b[16];
			int red= int(255*r->red);
                        int green= int(255*r->green);
                        int blue= int(255*r->blue);
			sprintf(b, "%.2x%.2x%.2x", red, green, blue);
			string c = "#";
			c += b;
			if (!XParseColor(GetDisplay(), colormap, 
					 c.getstr(), &color)) {
				error("Error: color %s not found\n",c.getstr());
				return;
			}
                	if (XAllocColor(GetDisplay(), colormap, &color)) {
                        	pixel = color.pixel;
        			r->allocated = True;                
				r->pixel = pixel;
			}
			else {
				error("Warning: Cannot allocate colormap "
					"entry %s\n", c.getstr());
				return;
			}
                }
		XtVaSetValues(colorLabel, XmNbackground, pixel, NULL);
	}
}

void ColorChooserDialog::Popup() {
	int *ilist;
	int count;
	if (XmListGetSelectedPos(GetList(), &ilist, &count)) {
		int pos = ilist[0];
		ShowColor(pos-1);
		XtFree((char *)ilist);
	}
        Dialog::Popup();
}

bool ColorChooserDialog::FillToggleOn() {
        return XmToggleButtonGetState(fillToggle);
}

void ColorChooserDialog::SetFillToggle(bool b) {
        XmToggleButtonSetState(fillToggle, b, True);
}

void ColorChooserDialog::ManageFillToggle(bool b) {
        b ? XtManageChild(fillToggle) :
            XtUnmanageChild(fillToggle);
}

void ColorChooserDialog::SetFillToggleLabel(const char *txt) {
        if (!check(fillToggle))
                return;
        XmString text_string = CreateXmString(txt);
        XtVaSetValues(fillToggle, XmNlabelString, text_string, NULL);
        XmStringFree(text_string);
}

