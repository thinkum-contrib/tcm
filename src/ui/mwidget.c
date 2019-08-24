////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "component.h"
#include "mwidget.h"
#include "lstring.h"
#include "liteclue.h"
#include "util.h"
#include <X11/StringDefs.h>
#include <Xm/Xm.h>

MWidget::MWidget(const char *n): Component (n) {
	liteClue = 0;
}

MWidget::~MWidget() {
	// Make sure the widget hasn't already been destroyed
	if (GetWidget()) {
		// Remove destroy callback so Xt can't call the callback
		// with a pointer to an object that has already been freed
		XtRemoveCallback(GetWidget(), 
			XtNdestroyCallback, &MWidget::WidgetDestroyedCB,
			(XtPointer)this);	
	}
}

void MWidget::WidgetDestroyedCB(Widget, XtPointer clientData, XtPointer){
	MWidget *obj = (MWidget *)clientData;	
	obj->WidgetDestroyed();
}

void MWidget::WidgetDestroyed() {
	SetWidget(0);
}

void MWidget::InstallDestroyHandler() {
	if (check(GetWidget()))
		XtAddCallback(GetWidget(), XtNdestroyCallback,
			&MWidget::WidgetDestroyedCB, 
			(XtPointer) this);
}

void MWidget::AddLiteClue(Widget w, const char *text) {
	XcgLiteClueAddWidget(liteClue, w, (char *)text, 0, 0);
}

void MWidget::CreateLiteClue() {
	if (check(GetWidget()))
		liteClue = XtVaCreatePopupShell("LiteClueShell",
                        xcgLiteClueWidgetClass, GetWidget(),
                        XgcNwaitPeriod, 700,
                        XgcNcancelWaitPeriod, 1000, NULL);
}

bool MWidget::IsRealized() {
	if (GetWidget())
		return XtIsRealized(GetWidget());
	else
		return False;
}

void MWidget::Manage() {
	if (check(GetWidget()) && 
	    check(XtHasCallbacks(GetWidget(), XtNdestroyCallback) == 
				XtCallbackHasSome))
		XtManageChild(GetWidget());
}

void MWidget::SetColormap(Colormap cmap) {
	XtVaSetValues(GetWidget(), XmNcolormap, cmap, NULL);
	XSetWindowColormap(GetDisplay(), XtWindow(GetWidget()), cmap);
}

void MWidget::SetDestroyCallback(XtCallbackProc fun, XtPointer cd) {
	if (!check(GetWidget()))
		return;
	XtAddCallback(GetWidget(), XmNdestroyCallback, fun, cd);
}

void MWidget::GetResources (const XtResourceList resources, 
			    const int numResources){
	// Check for errors
	if (check(GetWidget()) && check(resources))
		// Retrieve the requested resources relative to the 
		// parent of this object's base widget
		XtGetSubresources (XtParent(GetWidget()), 
			   	(XtPointer) this, GetName()->getstr(), 
				GetClassName(), resources, numResources, 0, 0);
}

void MWidget::SetDefaultResources (const Widget w, const char **resourceSpec) {
	int i=0;
	// Retrieve the display pointer
	Display *dpy = XtDisplay(w);
	// A resource data base
	XrmDatabase rdb = 0;
	// Create an empty resource database
	rdb = XrmGetStringDatabase("");
	// Add the Component resources, prepending the name of the component
	while (resourceSpec[i] != 0) {
		string buf = "*" + *GetName() + resourceSpec[i++];
		XrmPutLineResource(&rdb, buf.getstr());
	}
	// Merge them into the Xt database, with lowest precendence
	if (rdb) {
		#if (XlibSpecificationRelease>=5)
			XrmDatabase db = XtDatabase(dpy);
			XrmCombineDatabase(rdb, &db, FALSE);
		#else
			XrmMergeDatabases (dpy->db, &rdb);
			dpy->db = rdb;
		#endif
	}
}
