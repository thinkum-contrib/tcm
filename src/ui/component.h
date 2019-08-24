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
#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <X11/Intrinsic.h>
#include "bool.h"
#include "lstring.h"

/// base class for all UI components.
class Component {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// 
	Component(const char *name);
	///
	virtual ~Component();

	/// Manage widget tree
	virtual void Manage();

	/// Is widget tree managed.
	bool IsManaged();

	/// Unmanage widget tree
	virtual void Unmanage(); 

	///
	Widget GetWidget() {return widget;}
	///
	Display *GetDisplay() {return XtDisplayOfObject(widget);}
	///
	Window GetWindow() {return XtWindowOfObject(widget);}
protected:
	///
	void SetWidget(Widget w) {widget=w;}
	///
	const string *GetName() const {return &name;}
	///
	void SetName(const string *s) {name=*s;}
	///
	void SetName(const char *s) {name=s;}
private:
	///
	string name;
	///
	Widget widget;
};
#endif
