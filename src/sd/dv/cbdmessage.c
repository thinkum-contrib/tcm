////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "cbdmessage.h"
#include "lstring.h"

void CBDMessage::DirectionType2String(DirectionType t, string *s) {
	if (t == FROMSHAPE)
		*s = "FromShape";
	else 
		*s = "ToShape";
}
 
CBDMessage::DirectionType CBDMessage::String2DirectionType(const string *s) {
	if (*s %= "FromShape")
		return FROMSHAPE;
	else 
		return TOSHAPE;
}


void CBDMessage::ControlFlowType2String(ControlFlowType t, string *s) {
	if (t == FLATFLOW)
		*s = "FlatFlow";
	else if (t == NESTEDFLOW)
		*s = "NestedFlow";
	else 
		*s = "Asynchronous";
}
 
CBDMessage::ControlFlowType CBDMessage::String2ControlFlowType(const string *s) {
	if (*s %= "FlatFlow")
		return FLATFLOW;
	else if (*s %= "NestedFlow")
		return NESTEDFLOW;
	else 
		return ASYNCHRONOUS;
}
