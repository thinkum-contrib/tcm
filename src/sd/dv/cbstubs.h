//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _CBSTUBS_H
#define _CBSTUBS_H

#include "erstubs.h"

/// Specific stubs for a TCBD. 
class CBStubs: public ERStubs {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	static void ShowStereotypeCB(Widget, XtPointer, XtPointer);
	///
	static void HideStereotypeCB(Widget, XtPointer, XtPointer);
	///
	static void ShowPropertiesCB(Widget, XtPointer, XtPointer);
	///
	static void HidePropertiesCB(Widget, XtPointer, XtPointer);
};
#endif
