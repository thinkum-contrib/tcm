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
#ifndef _STRINGLISTNODE2_H
#define _STRINGLISTNODE2_H

#include "stringlistnode.h"

/// A node that has two extra lists of strings.
class StringListNode2: public StringListNode {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	StringListNode2(Graph *g);
	///
	StringListNode2(const StringListNode2 &s);
	///
	virtual ~StringListNode2();
	///
	virtual StringListNode::StringErrorType SetString2(
		const string *s, unsigned n, bool update); 
	///
	const string *GetString2(unsigned n) 
		{return ((n < stringList2->count()) ? (*stringList2)[n] : 0);}
	///
	unsigned NrStrings2() {return stringList2->count();}
	///
	const string *GetStringListLabel2() {return &stringListLabel2;}
	///
	const string *GetStringLabel2() {return &stringLabel2;}
	///
	void SetStringListLabel2(const string *s) {stringListLabel2=*s;}
	///
	void SetStringListLabel2(const char *s) {stringListLabel2=s;}
	///
	void SetStringLabel2(const string *s) {stringLabel2=*s;}
	///
	void SetStringLabel2(const char *s) {stringLabel2=s;}
	///
	bool HasString2(const string *s);
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
protected:
	///
	List<string *> *GetStringList2() {return stringList2;}
private:
	///
	List<string *> *stringList2;
	///
	string stringListLabel2;
	///
	string stringLabel2;
};
#endif
