//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#include "cbclassnode.h"
#include "cbsingleclassbox.h"

CBSingleClassBox::CBSingleClassBox(ShapeView *v, Grafport *g, 
		double x, double y): SSDSingleClassBox(v, g, x, y) {
}


CBSingleClassBox::CBSingleClassBox(const StickMan &s): SSDSingleClassBox(s) {
}

void CBSingleClassBox::SetTextShape() {
	Box::SetTextShape();
	if (!check(GetSubject() && 
				 GetSubject()->GetClassType()==Code::CBD_CLASS_NODE))
		return;
	GetStereotypeLabel()->SetString(
			((CBClassNode *)GetSubject())->GetStereotype());
	GetStereotypeLabel()->SetParent(this);
	GetPropertiesLabel()->SetString(
			((CBClassNode *)GetSubject())->GetProperties());
	GetPropertiesLabel()->SetParent(this);
}


bool CBSingleClassBox::SetAssocSubject(AssocList *al) {
	if (!SSDSingleClassBox::SetAssocSubject(al))
		return False;
	if (check(GetSubject()) && 
			  GetSubject()->GetClassType()==Code::CBD_CLASS_NODE)
		return True;
	SetSubject(0);
	return False;
}
