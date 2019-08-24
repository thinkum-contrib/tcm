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
#ifndef _DATAFLOW_H
#define _DATAFLOW_H

#include "dfedge.h"

/// data flow edge class.
class DataFlow: public DFEdge {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DataFlow(DFGraph *g, Subject *n1, Subject *n2);
	///
	int GetClassType() const {return Code::DATA_FLOW;}
	///
	Subject *Clone() {return new DataFlow(*this);}
	///
	Subject::NameErrType SetName(const string *name);
	///
	enum ContentType {UNSPECIFIED, ATOMIC_SUBJECT, ATTRIBUTE, DATA_TYPE};
	/// 
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	ContentType contentType;
	///
	string content;
	///
	static void ContentType2String(ContentType a, string *s);
	///
	static ContentType String2ContentType(const string *s);
};
#endif
