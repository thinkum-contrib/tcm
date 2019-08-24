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
#ifndef _BINARYRELATIONSHIP_H
#define _BINARYRELATIONSHIP_H

#include "edge.h"
class ERGraph;

/// binary relationship (ER) edge class.
class BinaryRelationship: public Edge {
/*@Doc: {\large {\bf scope:} TERD} */
public:
	///
	BinaryRelationship(Graph *g, Subject *n1, Subject *n2);
	///
	Subject *Clone() {return new BinaryRelationship(*this);}
	///
	int GetClassType() const {return Code::BINARY_RELATIONSHIP;}
	///
	Subject::NameErrType SetName(const string *name);
	///
	bool SetConstraint1(const string *s);
	///
	const string *GetConstraint1() const {return &constraint1;}
	///
	bool SetConstraint2(const string *s);
	///
	const string *GetConstraint2() const {return &constraint2;}
	///
	bool SetRoleName1(const string *s);
	///
	const string *GetRoleName1() const {return &roleName1;}
	///
	bool SetRoleName2(const string *s);
	///
	const string *GetRoleName2() const {return &roleName2;}
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	string constraint1;
	///
	string constraint2;
	///
	string roleName1;
	///
	string roleName2;
	///
	virtual bool SetConstraint(string *cons, const string *name);
	///
	virtual bool SetRoleName(string *cons, const string *name);
	///
	bool ParseCardConstraint(const string *s);
};
#endif
