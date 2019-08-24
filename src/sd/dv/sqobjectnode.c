///////////////////////////////////////////////////////////////////////////////
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
#include "sqobjectnode.h"
#include "sqgraph.h"
#include "inputfile.h"
#include "outputfile.h"
#include "lstring.h"
#include <limits.h>


SQObjectNode::SQObjectNode(SQGraph *g): Node (g) {
	stereotype = "<< - >>";
	properties = "{ - }";
	anchors = new List<Point *>;
	std::cout << "{ Stereotype [" << stereotype << "]" << std::endl << std::flush; 
	std::cout << "{ Properties [" << properties << "]" << std::endl << std::flush; 
}

SQObjectNode::SQObjectNode(const SQObjectNode &s): Node(s) {
	stereotype = s.stereotype;
	properties = s.properties;
	anchors = new List<Point *>;
	for (s.anchors->first(); !s.anchors->done(); s.anchors->next()) {
		Point *a = s.anchors->cur();
		Point *b = new Point(*a);
		anchors->add(b);
	}                   
}

SQObjectNode::~SQObjectNode() {
	anchors->clear();
	delete anchors;
} 



bool SQObjectNode::SetStereotype(const string *s) {
	if (*s != "" && s->letters()==0)
		return False;
	stereotype = *s;
	return True;
}

bool SQObjectNode::SetProperties(const string *s) {
	if (*s != "" && s->letters()==0)
		return False;
	properties = *s;
	return True;
}

void SQObjectNode::AddAnchor(int ypos, int atype) {
std::cout << " void SQObjectNode::AddAnchor(" << ypos << ", " << atype << ") {"
<< std::endl << std::flush;


	std::cout<<"=====(((())))====="<<anchors<<std::endl<<std::flush;


		anchors->add(new Point(ypos, atype));
}


void SQObjectNode::InsertAnchor(int ypos, int atype) {
std::cout << " void SQObjectNode::InsertAnchor(" << ypos << ", " << atype << ") {"
<< std::endl << std::flush;


	unsigned idx = 0; 	//init
	bool posFound = False;
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "B4 *ap=" << *ap << std::endl << std::flush;

		if (!posFound && (ap->x > ypos)) {
std::cout << " going 2 insert [" << ypos << "] b4 [" << ap->x << "]" << std::endl << std::flush;
			posFound = True;
			anchors->insert(new Point(ypos, atype), idx);
std::cout << " IDXIDXIDXIDXIDXIDX insert ===> " << idx << std::endl << std::flush;
		}
		idx++;
	}
	if (!posFound) {
std::cout << "IDXIDXIDXIDXIDXIDX going 2 add [" << ypos << "] @end " << std::endl << std::flush;
		anchors->add(new Point(ypos, atype));
	}

for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "NA *ap=" << *ap << std::endl << std::flush;
	}

}



void SQObjectNode::RemoveAnchor(int ypos, int atype) {
std::cout << " void SQObjectNode::RemoveAnchor(" << ypos << ", " << atype << ") {"
<< std::endl << std::flush;

	unsigned idx = 0; 	//init
	bool posFound = False;
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "SCANNING *ap=" << *ap << std::endl << std::flush;

		if (!posFound &&  (ap->x == ypos) && (ap->y == atype) ) {
std::cout << " Found: " << *ap << std::endl << std::flush;
			posFound = True;
			anchors->removei(idx);
std::cout << " IDXIDXIDXIDXIDXIDX remove ===> " << idx << std::endl << std::flush;

		}
		idx++;
	}

	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "NA *ap=" << *ap << std::endl << std::flush;
	}

	if (!posFound) {
std::cout << " anchor NOT found!" << std::endl << std::flush;
	}
}






void SQObjectNode::SortAnchors() {
std::cout << " void SQObjectNode::SortAnchors() {"
<< std::endl << std::flush;
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "B4 *ap=" << *ap << std::endl << std::flush;
	}
		anchors->sort(CompareAnchor);


	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "NA *ap=" << *ap << std::endl << std::flush;
	}

}


int SQObjectNode::GetMinAnchor() {
std::cout << " int SQObjectNode::GetMinAnchor() {" << std::endl << std::flush;
	int minA = INT_MAX; 	//init
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "scanning *ap=" << *ap << std::endl << std::flush;

		if (ap->x < minA) {
std::cout << " new minA found " << minA << " --> " << ap->x <<  std::endl << std::flush;
			minA = ap->x;
		}
	}
std::cout << "==> int SQObjectNode::GetMinAnchor() --> " << minA << std::endl << std::flush;
	return minA;
}


int SQObjectNode::GetMaxAnchor() {
std::cout << " int SQObjectNode::GetMaxAnchor() {" << std::endl << std::flush;
	int maxA = 0; 	//init
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "scanning *ap=" << *ap << std::endl << std::flush;

		if (ap->x > maxA) {
std::cout << " new maxA found " << maxA << " --> " << ap->x <<  std::endl << std::flush;
			maxA = ap->x;
		}
	}
std::cout << "==> int SQObjectNode::GetMaxAnchor() --> " << maxA << std::endl << std::flush;
	return maxA;
}


bool SQObjectNode::ReadMembers(InputFile *ifile, double format) {
	if (!Node::ReadMembers(ifile, format))
		return False;
	stereotype = "<< - >>";
	if (!ifile->ReadStringAttribute("Stereotype", &stereotype))
		return False;
	properties = "{ - }";
	if (!ifile->ReadStringAttribute("Properties", &properties))
		return False;

std::cout << "A" << std::endl << std::flush;
std::cout << "B" << std::endl << std::flush;
	string val;
	if (!ifile->ReadAttribute("Anchors", &val)) {
std::cout << "C" << std::endl << std::flush;
		return False;
	}
std::cout << "D" << std::endl << std::flush;
	unsigned numAnchors = val.toint();

std::cout << "Nr Anchors: " << val << " == " << numAnchors << std::endl << std::flush;


	string val1, val2;
	for (unsigned i=0; i<numAnchors; i++) {
		if (!ifile->ReadAttribute2("Anchor", &val1, &val2)) {
std::cout << "Wrong anchor: " << val1 << ", " << val2 << std::endl << std::flush;
			return False;
		}
std::cout << "Got anchor " << i << " : " << val1 << ", " << val2 << std::endl << std::flush;

//HZ	anchors->add(new Anchorpoint(val1, val2));
		anchors->add(new Point(val1.toint(), val2.toint()));

	}

	return True;
}

void SQObjectNode::WriteMembers(OutputFile *ofile) {
	Node::WriteMembers(ofile);
	(*ofile) << "\t{ Stereotype " << '"' << stereotype << '"' << " }\n";
	(*ofile) << "\t{ Properties " << '"' << properties << '"' << " }\n";

	(*ofile) << "\t{ Anchors " << anchors->count() << " }\n";
	for(anchors->first(); !anchors->done(); anchors->next()) {
		Point *ap = anchors->cur();
std::cout << "*ap=" << *ap << std::endl << std::flush;
		(*ofile) << "\t{ Anchor " << *ap << " }\n";
	}     
}
