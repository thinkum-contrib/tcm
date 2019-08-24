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
#include "psprocess.h"
#include "psgraph.h"
#include "inputfile.h"
#include "outputfile.h"
#include "lstring.h"

PSProcess::PSProcess(PSGraph *g): Node(g) {
	cOp = ' ';
	isRoot = False;
	isAction = True;
	treeSequence = 0;
	actionSequence = 0;
}
 
Subject::NameErrType PSProcess::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else
		return Node::SetName(s);
}

bool PSProcess::SetOperator(char c) {
	if (c == ' ')
		cOp = ' ';
	else if (c == 'o' || c == '0' || c == 'O')
		cOp = 'o';
	else if (c == '*')
		cOp = '*';
	else if (c == '!')
		cOp = '!';
	else if (c == '?')
		cOp = '?';
	else
		return False;
	return True;
}
 
void PSProcess::WriteMembers(OutputFile *ofile) {
	Node::WriteMembers(ofile);
	(*ofile) << "\t{ Operator " << '"' << cOp << '"' << " }\n";
	(*ofile) << "\t{ IsRoot " << (isRoot?"True":"False") << " }\n";
	(*ofile) << "\t{ IsAction " << (isAction?"True":"False") << " }\n";
	(*ofile) << "\t{ Sequence " << treeSequence << " }\n";
}
 
bool PSProcess::ReadMembers(InputFile *ifile, double format) {
	if (!Node::ReadMembers(ifile, format))
		return False;
	string val;
	if (!ifile->ReadStringAttribute("Operator", &val))
		return False;
	if (!SetOperator(val[0]))
		return False;
	if (!ifile->ReadAttribute("IsRoot", &val))
		return False;
	isRoot = (val %= "True");
	if (!ifile->ReadAttribute("IsAction", &val))
		return False;
	isAction = (val %= "True");
	if (format < 1.2) {
		if (!ifile->ReadAttribute("Order", &val))
			return False;
	} 
	else {
		if (!ifile->ReadAttribute("Sequence", &val))
			return False;
	}
	treeSequence = val.toint();
	return True;
}
