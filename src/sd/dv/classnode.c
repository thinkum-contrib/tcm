////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "classnode.h"
#include "lstring.h"
#include "crgraph.h"

ClassNode::ClassNode(CRGraph *g): StringListNode2(g) {
	SetStringLabel("Attribute");
	SetStringListLabel("Attributes");
	SetStringLabel2("Operation");
	SetStringListLabel2("Operations");
}

ClassNode::TextErrType ClassNode::SetAttribute(
		const string *s, unsigned n, bool update) {
	if (*s != "" && s->letters()==0)
		return ClassNode::IMPOSSIBLE_ATTRIBUTE;
	if (HasOperation(s))
		return ClassNode::OPERATION_EXISTS;
	if (HasAttribute(s)) {
		if (n >= NrAttributes() || *GetAttribute(n) != *s || 
		    !update)
			return ClassNode::ATTRIBUTE_EXISTS;
	}
	SetString(s, n, update);
	return ClassNode::MEMBER_OK;
}

ClassNode::TextErrType ClassNode::SetOperation(
		const string *s, unsigned n, bool update) {
	if (*s != "" && s->letters()==0)
		return ClassNode::IMPOSSIBLE_ATTRIBUTE;
	if (HasAttribute(s))
		return ClassNode::ATTRIBUTE_EXISTS;
	if (HasOperation(s)) {
		if (n >= NrOperations() || *GetOperation(n) != *s || !update)
			return ClassNode::OPERATION_EXISTS;
	}
	SetString2(s, n, update);
	return ClassNode::MEMBER_OK;
}

const string *ClassNode::GetAttribute(unsigned n) {
	return GetString(n);
}

unsigned ClassNode::NrAttributes() {
	return NrStrings();
}

const string *ClassNode::GetOperation(unsigned n) {
	return GetString2(n);
}

unsigned ClassNode::NrOperations() {
	return NrStrings2();
}

bool ClassNode::HasAttribute(const string *s) {
	return HasString(s);
}

bool ClassNode::HasOperation(const string *s) {
	return HasString2(s);
}

bool ClassNode::ReadMembers(InputFile *ifile, double format) {
	string s1, s2; 
	if (format < 1.27) {
		s1 = *GetStringListLabel2();
		s2 = *GetStringLabel2();
		SetStringListLabel2("Actions");
		SetStringLabel2("Action");
	}
	bool b = StringListNode2::ReadMembers(ifile, format);
	if (format < 1.27) {
		SetStringListLabel2(&s1);
		SetStringLabel2(&s2);
	}
	return b;
}
