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
#include "datastore.h"
#include "inputfile.h"
#include "outputfile.h"
#include "dfgraph.h"

DataStore::DataStore(DFGraph *g): DFStore(g) {
	atomicSubjects = new List<string *>;
}

DataStore::DataStore(const DataStore &dt): DFStore(dt) {
	atomicSubjects = new List<string *>;
	for (dt.atomicSubjects->first(); !dt.atomicSubjects->done(); dt.atomicSubjects->next()) {
		string *a = dt.atomicSubjects->cur();
		string *b = new string(*a);
		atomicSubjects->add(b);
	}
}

DataStore::~DataStore() {
	atomicSubjects->clear();
	delete atomicSubjects;
}

void DataStore::WriteMembers(OutputFile *ofile) {
	DFStore::WriteMembers(ofile);
	(*ofile) << "\t{ AtomicSubjects " << atomicSubjects->count() << " }\n";
	for(atomicSubjects->first(); !atomicSubjects->done(); atomicSubjects->next()) {
		string *s = atomicSubjects->cur();
		(*ofile) << "\t{ AtomicSubject " << '"' << *s << '"' << " }\n";
	}
}

bool DataStore::ReadMembers(InputFile *ifile, double format) {
	if (!DFStore::ReadMembers(ifile, format))
		return False;
	if (format >= 1.13) {
		string val;
		if (!ifile->ReadAttribute("AtomicSubjects", &val))
			return False;
		unsigned numItems = val.toint();
		for (unsigned i=0; i<numItems; i++) {
			string *s = new string;
			if (!ifile->ReadStringAttribute("AtomicSubject", s)) {
				delete s;
				return False;
			}
			atomicSubjects->add(s);
		}
	}
	return True;
}
