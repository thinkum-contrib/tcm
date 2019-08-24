//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "sqstubs.h"
#include "sqviewer.h"


void SQStubs::AddFOCCB(Widget, XtPointer cd, XtPointer) {
	((SQViewer *)cd)->UpdateShowStereotypes(True);
}

void SQStubs::DeleteFOCCB(Widget, XtPointer cd, XtPointer) {
	//((SQViewer *)cd)->UpdateShowStereotypes(True);
	((SQViewer *)cd)->DeleteFOC();
}


void SQStubs::ShowStereotypeCB(Widget, XtPointer cd, XtPointer) {
	((SQViewer *)cd)->UpdateShowStereotypes(True);
}

void SQStubs::HideStereotypeCB(Widget, XtPointer cd, XtPointer) {
	((SQViewer *)cd)->UpdateShowStereotypes(False);
}

void SQStubs::ShowPropertiesCB(Widget, XtPointer cd, XtPointer) {
	((SQViewer *)cd)->UpdateShowProperties(True);
}

void SQStubs::HidePropertiesCB(Widget, XtPointer cd, XtPointer) {
	((SQViewer *)cd)->UpdateShowProperties(False);
}
