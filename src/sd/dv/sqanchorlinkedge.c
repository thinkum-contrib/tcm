//------------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "sqanchorlinkedge.h"
#include "sqgraph.h"
#include "inputfile.h"
#include "outputfile.h" 
#include "subject.h"


SQAnchorLinkEdge::SQAnchorLinkEdge(SQGraph *g, Subject *n1, Subject *n2): 
		Edge(g, n1, n2) {
		
std::cout << "SQAnchorLinkEdge::SQAnchorLinkEdge(CBGraph *g, Subject *n1, Subject *n2): " << std::endl << std::flush;

// std::cout << "subj1=" << n1->GetId() << ", subj2=" << n2->GetId() << std::endl << std::flush; 



		}



bool SQAnchorLinkEdge::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
std::cout << "eA" << std::endl << std::flush;
	string val;

	string val1, val2;
	if (!ifile->ReadAttribute2("Anchor1", &val1, &val2)) {
std::cout << "Wrong anchor1: " << val1 << ", " << val2 << std::endl << std::flush; 
		return False;
	}

//HZ	anchors->add(new Anchorpoint(val1, val2));
//	anchors->add(new Point(val1.toint(), val2.toint())); 
	anchor1.Set(val1.toint(), val2.toint()); 
std::cout << "Got anchor1 : " << val1 << ", " << val2 << " | " << anchor1 << std::endl << std::flush; 


	if (!ifile->ReadAttribute2("Anchor2", &val1, &val2)) {
std::cout << "Wrong anchor2: " << val1 << ", " << val2 << std::endl << std::flush; 
		return False;
	}
	anchor2.Set(val1.toint(), val2.toint()); 
std::cout << "Got anchor2 : " << val1 << ", " << val2 << " | " << anchor2 << std::endl << std::flush; 

	return True;
}


void SQAnchorLinkEdge::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ Anchor1 " << anchor1 << " }\n";
	(*ofile) << "\t{ Anchor2 " << anchor2 << " }\n";
}

