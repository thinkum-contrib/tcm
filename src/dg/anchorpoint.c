////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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
#include "anchorpoint.h"
#include "lstring.h"

void AnchorPoint::Type2String(AnchorType t, string *s) {
	if (t == START_FOC)
		*s = "StartFOC";
	else if (t == END_FOC)
		*s = "End_FOC";
	else if (t == START_ANCHOR)
		*s = "StartAnchor";
	else if (t == END_ANCHOR)
		*s = "EndAnchor";
	else if (t == MULTI_ANCHOR)
		*s = "MultiAnchor";
	else if (t == NON_DESTR_END)
		*s = "NonDestructiveEnd";
	else if (t == DESTR_END)
		*s = "DestructiveEnd";
	else 
		*s = "None";
}
 
AnchorPoint::AnchorType AnchorPoint::String2Type(const string *s) {
	if (*s %= "StartFOC")
		return START_FOC;
	if (*s %= "End_FOC")
		return END_FOC;
	if (*s %= "StartAnchor")
		return START_ANCHOR;
	if (*s %= "EndAnchor")
		return END_ANCHOR;
	if (*s %= "MultiAnchor")
		return MULTI_ANCHOR;
	if (*s %= "NonDestructiveEnd")
		return NON_DESTR_END;
	if (*s %= "DestructiveEnd")
		return DESTR_END;
	else 
		return NONE;
}
