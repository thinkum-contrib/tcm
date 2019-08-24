//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _ANCHORPOINT_H
#define _ANCHORPOINT_H

#include "lstring.h"

/// anchorpoint to attach to 
class AnchorPoint {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	enum AnchorType { NONE, START_FOC, END_FOC, 
			START_ANCHOR, END_ANCHOR, MULTI_ANCHOR, NON_DESTR_END, DESTR_END};

	/// Construct and initialize message.
	AnchorPoint(int o, AnchorType a = NONE) {
			offset = o; anchorType = a; }

	/// Construct and initialize message.
	AnchorPoint(int o) {
			offset = o; anchorType = NONE; }

	/// set offset 
	void SetOffset(int o) {offset = o;} 
	///
	int GetOffset() const {return offset;}

	/// set anchor type
	void SetAnchorType(AnchorType t) {anchorType = t;} 
	///
	AnchorPoint::AnchorType GetAnchorType() const {return anchorType;}

	/// e.g. convert "NonDestructiveEnd" to NON_DESTR_END.
	static AnchorPoint::AnchorType String2Type(const string *s);

	/// e.g. convert DESTR_END to "DestructiveEnd".
	static void Type2String(AnchorType t, string *s);

private:
	///
	int offset;
	///
	AnchorType anchorType;
};
#endif
