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
#include "stringlistnode.h"

StringListNode::StringListNode(Graph *g): Node(g) {
	stringList = new List<string *>;
	stringListLabel = "Strings";
	stringLabel = "String";
}

StringListNode::StringListNode(const StringListNode &s): Node(s) {
	stringList = new List<string *>;
	for (s.stringList->first(); !s.stringList->done(); 
			s.stringList->next()) {
		string *a = s.stringList->cur();
		stringList->add(new string(*a));
	}
	stringListLabel = s.stringListLabel;
	stringLabel = s.stringLabel;
}

StringListNode::~StringListNode() {
	stringList->clear();
	delete stringList;
}

bool StringListNode::HasString(const string *s) {
	for (stringList->first(); !stringList->done();
             stringList->next()) {
                if (*stringList->cur() == *s)
                        return True;
        }
        return False;
}

StringListNode::StringErrorType StringListNode::SetString(
                const string *s, unsigned n, bool update) {
        StringList::Insert(stringList, s, n, update);
        return StringListNode::STRING_OK;
}

bool StringListNode::ReadMembers(InputFile *ifile, double format) {
	if (!Node::ReadMembers(ifile, format))
		return False;
	string val;
	if (!ifile->ReadAttribute(&stringListLabel, &val))
		return False;
	int numItems = val.toint();
	for (int i=0; i<numItems; i++) {
		string *at = new string;
		if (!ifile->ReadStringAttribute(&stringLabel, at)) {
			delete at;
			return False;
		}
		stringList->add(at);
	}
	return True;
}

void StringListNode::WriteMembers(OutputFile *ofile) {
	Node::WriteMembers(ofile);
	int numItems = stringList->count();
	(*ofile) << "\t{ " << stringListLabel << " " << numItems << " }\n";
	for (int i=0; i<numItems; i++) {
		(*ofile) << "\t{ " << stringLabel << " " << '"' 
			 << *(*stringList)[i] << '"' << " }\n";
	}
}
