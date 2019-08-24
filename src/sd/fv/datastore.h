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
#ifndef _DATASTORE_H
#define _DATASTORE_H

#include "dfstore.h"
class DFGraph;

/// data store (DF) node class.
class DataStore: public DFStore {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DataStore(DFGraph *g);
	///
	DataStore(const DataStore &dt);
	///
	virtual ~DataStore();
	///
	int GetClassType() const {return Code::DATA_STORE;}
	///
	Subject *Clone() { return new DataStore(*this);}
	/// 
	void WriteMembers(OutputFile *f); 
	/// 
	bool ReadMembers(InputFile *f, double format);
private:
	///
	List<string *> *atomicSubjects;
};
#endif
