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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _CBCLASSNODE_H
#define _CBCLASSNODE_H

#include "subject.h"
#include "node.h"
class CBGraph;

/// object class (TCBD) node class.
class CBClassNode: public Node {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	CBClassNode(CBGraph *g);
	///
	CBClassNode(const CBClassNode &c);
	///
	Subject *Clone() {return new CBClassNode(*this);}
	///
	int GetClassType() const {return Code::CBD_CLASS_NODE;}
	///
	bool  SetStereotype(const string *s);
	///
	bool SetProperties(const string *s); 
	///
	const string *GetStereotype() {return &stereotype;}
	///
	const string *GetProperties() const {return &properties;}
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	string stereotype;
	///
	string properties;
};
#endif
