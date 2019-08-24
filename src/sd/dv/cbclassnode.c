////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "cbclassnode.h"
#include "cbgraph.h"
#include "inputfile.h"
#include "outputfile.h"
#include "lstring.h"

CBClassNode::CBClassNode(CBGraph *g): Node (g) {
	stereotype = "<< - >>";
	properties = "{ - }";
}

CBClassNode::CBClassNode(const CBClassNode &s): Node(s) {
	stereotype = s.stereotype;
	properties = s.properties;
}

bool CBClassNode::SetStereotype(const string *s) {
	if (*s != "" && s->letters()==0)
		return False;
	stereotype = *s;
	return True;
}

bool CBClassNode::SetProperties(const string *s) {
	if (*s != "" && s->letters()==0)
		return False;
	properties = *s;
	return True;
}

bool CBClassNode::ReadMembers(InputFile *ifile, double format) {
	if (!Node::ReadMembers(ifile, format))
		return False;
	stereotype = "<< - >>";
	if (!ifile->ReadStringAttribute("Stereotype", &stereotype))
		return False;
	properties = "{ - }";
	if (!ifile->ReadStringAttribute("Properties", &properties))
		return False;
	return True;
}

void CBClassNode::WriteMembers(OutputFile *ofile) {
	Node::WriteMembers(ofile);
	(*ofile) << "\t{ Stereotype " << '"' << stereotype << '"' << " }\n";
	(*ofile) << "\t{ Properties " << '"' << properties << '"' << " }\n";
}
