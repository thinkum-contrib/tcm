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
#include "dcfstubs.h"
#include "dcfdiagram.h"
#include "dcfviewer.h"

void DCFStubs::PersistenceCB(Widget, XtPointer cd, XtPointer) {
	((DCFViewer *)cd)->Persistence();
}

void DCFStubs::ActivationCB(Widget, XtPointer cd, XtPointer) {
	((DCFViewer *)cd)->Activation();
}

void DCFStubs::PersistenceOKCB(Widget, XtPointer cd, XtPointer) {
	if (!check(cd))
		return;
	((DCFDiagram *)cd)->SetPersistence();
}

void DCFStubs::ActivationToggleCB(Widget, XtPointer cd, XtPointer) {
	if (!check(cd))
		return;
	((DCFDiagram *)cd)->UpdateActivationToggle();
}

void DCFStubs::ActivationOKCB(Widget, XtPointer cd, XtPointer) {
	if (!check(cd))
		return;
	((DCFDiagram *)cd)->SetActivation();
}
