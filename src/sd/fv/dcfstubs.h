//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl) 
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
#ifndef _DCFSTUBS_H
#define _DCFSTUBS_H

#include "dfstubs.h"

/// Callback stubs for specific EFD functions.
class DCFStubs: public DFStubs {
/*@Doc: {\large {\bf scope:} TDEFD} */
public:
	///
	static void PersistenceCB(Widget w, XtPointer, XtPointer);
	///
	static void PersistenceOKCB(Widget, XtPointer, XtPointer);
	///
	static void ActivationToggleCB(Widget w, XtPointer, XtPointer);
	///
	static void ActivationOKCB(Widget w, XtPointer, XtPointer);
	///
	static void ActivationCB(Widget, XtPointer, XtPointer);
};
#endif
