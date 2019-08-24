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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SQOBJECTNODE_H
#define _SQOBJECTNODE_H

#include "node.h"
#include "anchorpoint.h"
#include "point.h"
class SQGraph;

/// object class (TSQD) node class.

int CompareAnchor(Point *p1, Point *p2);

class SQObjectNode: public Node {
/*@Doc: {\large {\bf scope:} TSQD} */
public:
	///
	SQObjectNode(SQGraph *g);
	///
	SQObjectNode(const SQObjectNode &s);
	///
	~SQObjectNode();
	///
	Subject *Clone() {return new SQObjectNode(*this);}
	///
	int GetClassType() const {return Code::CBD_OBJECT_NODE;}	//HZ
	///
	bool  SetStereotype(const string *s);
	///
	bool SetProperties(const string *s); 
	///
	const string *GetStereotype() {return &stereotype;}
	///
	const string *GetProperties() const {return &properties;}
	///
	void AddAnchor(int ypos, int atype);
	///
	void InsertAnchor(int ypos, int atype);
	///
	void RemoveAnchor(int ypos, int atype);
	///
	int GetMinAnchor();
	///
	int GetMaxAnchor();
	///
	void SortAnchors();
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
	///
	unsigned NrAnchors() {return anchors->count();}
	///
	List<Point *> *GetAnchors() {return anchors;}
	///
	friend int CompareAnchor(Point *p1, Point *p2) {std::cout << " p1->x=" << p1->x << "  p2->x=" << p2->x << std::endl << std::flush; return p1->x <= p2->x;}
private:
	///
	string stereotype;
	///
	string properties;
	///
	List<Point *> *anchors;
};
#endif
