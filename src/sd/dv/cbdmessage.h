//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _CBDMESSAGE_H
#define _CBDMESSAGE_H

//class string;
#include "lstring.h"

/// different read directions
class CBDMessage {
/*@Doc: {\large {\bf scope:} tcbd} */
public:
	///
	enum DirectionType {NONE, FROMSHAPE, TOSHAPE};
	///
	enum ControlFlowType {FLATFLOW, NESTEDFLOW, ASYNCHRONOUS};

	/// Construct and initialize message.
	CBDMessage(string *s, DirectionType d = FROMSHAPE,
		   ControlFlowType f = FLATFLOW) {
			name = *s; direction = d; flow = f; }

	/// Construct and initialize message.
	CBDMessage(string *s) {
			name = *s; direction = FROMSHAPE; flow = FLATFLOW; }

	/// set text and recalculate the sizes.
	void SetString(const string *s) {name = *s;} 
	///
	const string *GetString() const {return &name;}

	/// set direction type of msg arrow
	void SetDirection(DirectionType d) {direction = d;} 
	///
	CBDMessage::DirectionType GetDirection() const {return direction;}

	/// set controlflow type of msg arrow
	void SetFlow(ControlFlowType f) {flow = f;} 
	///
	CBDMessage::ControlFlowType GetFlow() const {return flow;}

	/// e.g. convert "FromShape" to FROMSHAPE.
	static CBDMessage::DirectionType String2DirectionType(const string *s);

	/// e.g. convert FROMSHAPE to "FromShape".
	static void DirectionType2String(DirectionType t, string *s);


	/// e.g. convert "FlatFlow" to FLATFLOW.
	static CBDMessage::ControlFlowType String2ControlFlowType(const string *s);

	/// e.g. convert FLATFLOW to "FlatFlow".
	static void ControlFlowType2String(ControlFlowType t, string *s);

private:
	///
	string name;
	///
	DirectionType direction;
	///
	ControlFlowType flow;
};
#endif
