//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SSDCLASSNODE_H
#define _SSDCLASSNODE_H

#include "stringlistnode2.h"
class SSDGraph;

/// TSSD class node.
class SSDClassNode: public StringListNode2 {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDClassNode(SSDGraph *g);
	///
	SSDClassNode(const SSDClassNode &c);
        ///
        int GetClassType() const {return Code::SSD_CLASS_NODE;}
	///
	Subject *Clone() {return new SSDClassNode(*this);}
	///
	StringListNode::StringErrorType SetString(
		const string *s, unsigned n, bool update);
	///
	StringListNode::StringErrorType SetString2(
		const string *s, unsigned n, bool update);
	///
	StringListNode::StringErrorType SetStereotype(const string *s); 
	///
	StringListNode::StringErrorType SetProperties(const string *s); 
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
