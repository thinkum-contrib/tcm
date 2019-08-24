//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _STRINGLISTEDGE_H
#define _STRINGLISTEDGE_H

#include "edge.h"

/// An edge that has an extra list of strings.
class StringListEdge: public Edge {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	StringListEdge(Graph *g, Subject *n1, Subject *n2);
	///
	StringListEdge(const StringListEdge &s);
	///
	virtual ~StringListEdge();
	///
	enum StringErrorType {
		STRING_OK, STRING_SYNTAX_ERROR, STRING_ALREADY_EXISTS};
	///
	virtual StringListEdge::StringErrorType SetString(
		const string *s, unsigned n, bool update); 
	///
	const string *GetString(unsigned n) 
		{return ((n < stringList->count())?(*stringList)[n] : 0);}
	///
	unsigned NrStrings() {return stringList->count();}
	///
	bool HasString(const string *s);
	///
        const string *GetStringListLabel() {return &stringListLabel;}
        ///
        const string *GetStringLabel() {return &stringLabel;}
        ///
        const List<string *> *GetStringList() {return stringList;}
        ///
        void SetStringListLabel(const string *s) {stringListLabel=*s;}
        ///
        void SetStringLabel(const string *s) {stringLabel=*s;}
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	List<string *> *stringList;
	///
	string stringListLabel;
	///
	string stringLabel;
};
#endif
