//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _MWIDGET_H
#define _MWIDGET_H

#include "component.h"

/// base class for wrapping all Motif widgets.
class MWidget: public Component {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// 
	MWidget(const char *name); 
	///
	virtual ~MWidget();
	///
	virtual void Manage();
	///
	virtual const char *GetClassName() {return "MWidget";}

	/// Is the widget realized ?
	bool IsRealized();

	/// Set the colormap of the window to cmap.
	void SetColormap(Colormap cmap);

	/// Add a widget destroyed callback.
	void SetDestroyCallback(XtCallbackProc fun, XtPointer clientData);

	///
	void AddLiteClue(Widget w, const char *text);

protected:
	///
        Widget GetLiteClue() {return liteClue;}
	///
	void CreateLiteClue();

	/// Easy hook for derived classes
	void InstallDestroyHandler(); 
private:
	/// Called by widgetDestroyedCallback() if base widget is destroyed
	virtual void WidgetDestroyed(); 

	/// Loads component's default resources into database
	void SetDefaultResources(const Widget, const char** resources);

	/// Retrieve resources for this clsss from the resource manager
	void GetResources(const XtResourceList, const int);

	/// Interface between XmNdestroyCallback and this class
	static void WidgetDestroyedCB(Widget, XtPointer, XtPointer);

	/// Widget for popping up online help messages.
        Widget liteClue;
};
#endif
