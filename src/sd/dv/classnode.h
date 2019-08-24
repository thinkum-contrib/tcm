//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _CLASSNODE_H
#define _CLASSNODE_H

#include "stringlistnode2.h"
class CRGraph;

/// object class (CRD) node class.
class ClassNode: public StringListNode2 {
/*@Doc: {\large {\bf scope:} TCRD} */
public:
	///
	ClassNode(CRGraph *g);
	///
	Subject *Clone() {return new ClassNode(*this);}
	///
	int GetClassType() const {return Code::CLASS_NODE;}
	///
	enum TextErrType {MEMBER_OK, IMPOSSIBLE_ATTRIBUTE, 
		IMPOSSIBLE_OPERATION, ATTRIBUTE_EXISTS, OPERATION_EXISTS, 
		FUNCTION_EXISTS, COMPONENT_EXISTS, RELATION_EXISTS};
	///
	ClassNode::TextErrType SetAttribute(const string *s, unsigned n, 
		bool update); 
	///
	const string *GetAttribute(unsigned n);
	///
	unsigned NrAttributes();
	///
	bool HasAttribute(const string *s);
	///
	ClassNode::TextErrType SetOperation(const string *s, unsigned n, 
		bool update); 
	///
	const string *GetOperation(unsigned n);
	///
	unsigned NrOperations();
	///
	bool HasOperation(const string *s);
	///
	bool ReadMembers(InputFile *f, double format);
};
#endif
