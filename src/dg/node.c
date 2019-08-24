////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "node.h"
#include "graph.h"
#include "inputfile.h"
#include "outputfile.h"

Node::Node(Graph *g): Subject(g) { 
	index = "";
}

Node::Node(HyperGraph *hg): Subject(hg) {  
        index = "";                       
}

bool Node::InGraph() const {
	return GetGraph()->HasNode((Node *)this);
}

Subject::NameErrType Node::SetIndex(const string *s) {
	index = *s;
	return Subject::OK;
}

void Node::WriteMembers(OutputFile *ofile) {
	Subject::WriteMembers(ofile);
	(*ofile) << "\t{ Index " << '"' << *GetIndex() << '"' << " }\n";
}

bool Node::ReadMembers(InputFile *ifile, double format) {
	if (!Subject::ReadMembers(ifile, format))
		return False;
	if (format >= 1.22) {
		string x;
		if (!ifile->ReadStringAttribute("Index", &x))
			return False;
		SetIndex(&x);
	}
	return True;
}

void Node::GetParentIndex(string *s) {
	if (GetParent()) {
		*s = *GetParent()->GetIndex();
		return;
	}
	// construct index because parent does not exist.
	if (*GetIndex() == "0") {
		*s = "c";
		return;
	}
	*s = *GetIndex();
	if (*s != "") {
		int len = s->length();
		int i = len-1;
		while (i > 0) {
			if ((*s)[i] == '.') {
				for(int j=i; j<len; j++)
					s->remove();
				return;
			}
			else
				i--;
		}
		*s = "";
	}
}
