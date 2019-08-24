////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam
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
#include "inputfile.h"
#include "outputfile.h"
#include "lstring.h"
#include "stringlist.h"
#include "stringlistnode2.h"

StringListNode2::StringListNode2(Graph *g): StringListNode(g) {
	stringList2 = new List<string *>;
	stringListLabel2 = "Strings2";
	stringLabel2 = "String2";
}

StringListNode2::StringListNode2(const StringListNode2 &s): StringListNode(s) {
	stringList2 = new List<string *>;
	for (s.stringList2->first(); !s.stringList2->done(); 
			s.stringList2->next()) {
		string *a = s.stringList2->cur();
		stringList2->add(new string(*a));
	}
	stringListLabel2 = s.stringListLabel2;
	stringLabel2 = s.stringLabel2;
}

StringListNode2::~StringListNode2() {
	stringList2->clear();
	delete stringList2;
}

bool StringListNode2::HasString2(const string *s) {
	for (stringList2->first(); !stringList2->done();
             stringList2->next()) {
                if (*stringList2->cur() == *s)
                        return True;
        }
        return False;
}

StringListNode2::StringErrorType StringListNode2::SetString2(
                const string *s, unsigned n, bool update) {
        StringList::Insert(stringList2, s, n, update);
        return StringListNode::STRING_OK;
}

bool StringListNode2::ReadMembers(InputFile *ifile, double format) {
	if (!StringListNode::ReadMembers(ifile, format))
		return False;
	string val;
	if (!ifile->ReadAttribute(&stringListLabel2, &val))
		return False;
	int numItems = val.toint();
	for (int i=0; i<numItems; i++) {
		string *at = new string;
		if (!ifile->ReadStringAttribute(&stringLabel2, at)) {
			delete at;
			return False;
		}
		stringList2->add(at);
	}
	return True;
}

void StringListNode2::WriteMembers(OutputFile *ofile) {
	StringListNode::WriteMembers(ofile);
	int numItems = stringList2->count();
	(*ofile) << "\t{ " << stringListLabel2 << " " << numItems << " }\n";
	for (int i=0; i<numItems; i++) {
		(*ofile) << "\t{ " << stringLabel2 << " " << '"' 
			 << *(*stringList2)[i] << '"' << " }\n";
	}
}
