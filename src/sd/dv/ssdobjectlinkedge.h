//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
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
#ifndef _SSDOBJECTLINKEDGE_H
#define _SSDOBJECTLINKEDGE_H

#include "edge.h"
class SSDGraph;

/// Object Link (SSD) edge class.
class SSDObjectLinkEdge: public Edge {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDObjectLinkEdge(SSDGraph *g, Subject *n1, Subject *n2);
	///
	Subject *Clone() {return new SSDObjectLinkEdge(*this);}
	///
	int GetClassType() const {return Code::SSD_OBJECT_LINK_EDGE;}
	///
	Subject::NameErrType SetName(const string *name);
	///
	bool SetRoleName1(const string *s);
	///
	const string *GetRoleName1() const {return &roleName1;}
	///
	bool SetRoleName2(const string *s);
	///
	const string *GetRoleName2() const {return &roleName2;}
	///
	bool SetRoleName(string *cons, const string *name);
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	string roleName1;
	///
	string roleName2;
};
#endif
