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
#include "dfprocess.h"
#include "inputfile.h"
#include "outputfile.h"
#include "graph.h"
#include <ctype.h>

DFProcess::DFProcess(DFGraph *g): DFNode(g) {}

Subject::NameErrType DFProcess::SetIndex(const string *s) {
	// Check index label syntax.
	if (!CorrectIndex(s))
	 	return Subject::IMPOSSIBLE_NAME;
	// Check index label unicity.
	if (*s != *GetIndex() && *s != "" && GetGraph()->CountIndexes(s) >= 1)
	 	return Subject::DOUBLE_NODE;
	return DFNode::SetIndex(s);
}

bool DFProcess::ReadMembers(InputFile *ifile, double format) {
	if (!DFNode::ReadMembers(ifile, format))
		return False;
	string x;
	if (format >= 1.13) {
		if (format >= 1.22)
			return True;
		else if (!ifile->ReadAttribute("Index", &x))
			return False;
	}
	else {
		if (!ifile->ReadStringAttribute("Index", &x))
			return False;
	}
	DFNode::SetIndex(&x);
	return True;
}

bool DFProcess::CorrectIndex(const string *s) {
	if (s == 0 || *s == "")
		return False;
	int i = 0;
	char c = (*s)[i];
	int prevdot = 0;
	// single 0?
	if (c == '0' && s->length()>1)
		return False;
	while (c != '\0') {
		// should be digit or dot 
		if (!isdigit(c) && c != '.')
			return False;
		// should not start with dot
		if (i==0 && c == '.')
			return False;
		// should not contain double dot
		else if (i>0 && c == '.' && prevdot)
			return False;
		prevdot = (c == '.') ? 1: 0;
		c = (*s)[++i];
	}
	// should not end with dot
	if ((*s)[i-1] == '.')
		return False;
	return True;
}
