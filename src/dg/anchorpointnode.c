////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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
#include "node.h"
#include "anchorpointnode.h"
#include "anchorpoint.h"

AnchorPointNode::AnchorPointNode(Graph *g): Node(g) {
	anchors = new List<AnchorPoint *>;
}

AnchorPointNode::AnchorPointNode(const AnchorPointNode &s): Node(s) {
	anchors = new List<AnchorPoint *>;
	for (s.anchors->first(); !s.anchors->done(); 
			s.anchors->next()) {
		AnchorPoint *a = s.anchors->cur();
		anchors->add(new AnchorPoint(*a));
	}
}

AnchorPointNode::~AnchorPointNode() {
	anchors->clear();
	delete anchors;
}

bool AnchorPointNode::HasAnchor(const AnchorPoint *p) {
	for (anchors->first(); !anchors->done(); anchors->next()) {
                if (anchors->cur()->GetOffset() == p->GetOffset())
                        return True;
        }
        return False;
}

AnchorPointNode::AnchorErrorType AnchorPointNode::SetAnchor(
                const AnchorPoint *p, unsigned n, bool update) {
//HZ	StringList::Insert(anchors, p, n, update);
        return AnchorPointNode::ANCHOR_OK;
}

bool AnchorPointNode::ReadMembers(InputFile *ifile, double format) {
	if (!Node::ReadMembers(ifile, format))
		return False;
	string val;
	if (!ifile->ReadAttribute("anchors", &val))
		return False;
	int numItems = val.toint();
	for (int i=0; i<numItems; i++) {

		// read position of the textShape1 text shape.
		string val1, val2;
		if (!ifile->ReadAttribute2("anchor", &val1, &val2))
			return False;

		int x = val1.toint();
		AnchorPoint::AnchorType at = AnchorPoint::String2Type(&val2);

		AnchorPoint ap = AnchorPoint(x, at);
		AnchorPoint *pap = new AnchorPoint(x, at);

		anchors->add(&ap);
		anchors->add(pap);

	}


std::cout << "AnchorPoints {" << numItems << "} are : " << std::endl << std::flush;
	string x;
	for (int i=0; i<(int) numItems; i++) {


		AnchorPoint::Type2String((*anchors)[i]->GetAnchorType(), &x);
std::cout << "\t Anchor " << i <<
	"\t Offset = " << (int) (*anchors)[i]->GetOffset() << 
	"\t Type   = " << (int) (*anchors)[i]->GetAnchorType() << 
	"\t SType  = " << x <<

std::endl << std::flush;
	}


	return True;
}

void AnchorPointNode::WriteMembers(OutputFile *ofile) {
	Node::WriteMembers(ofile);
	int numItems = anchors->count();
	(*ofile) << "\t{ anchors " << numItems << " }\n";
	for (int i=0; i<numItems; i++) {
		(*ofile) << "\t{ anchor " << (int) (*anchors)[i]->GetOffset() << 
			" " << (int) (*anchors)[i]->GetAnchorType() << " }\n";
	}
}




