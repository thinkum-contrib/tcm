//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#ifndef _ESDDIAGRAM_H
#define _ESDDIAGRAM_H

#include "erdiagram.h"
#include "stringlistnode.h"
class SSDViewer;
class ESDWindow;
class SSDGraph;
class SSDChecks;
class SSDClassNode;
class StringListNode2;

/// UML static structure diagram class.
class ESDDiagram : public ERDiagram {
/*@Doc: {\large {\bf scope:} TESD} */
public:
	///
	ESDDiagram(Config *, ESDWindow *, SSDViewer *, SSDGraph *);
	///
	virtual ~ESDDiagram();
	///
	Node *CreateNode();
	///
	Edge *CreateEdge(Subject *n1, Subject *n2);
	///
	NodeShape *CreateNodeShape(Node *node, int x, int y);
	///
	Line *CreateLine(Edge *edge, GShape *fromShape, 
		GShape *toShape, List<Point *> *line);
	///
	void UpdateNodeType(int n);
	///
	void UpdateEdgeType(int n);

	///
        bool SetText(TextShape *t, const string *s);

	/// Set Attribute in class obj at position nr.
	bool SetAttribute(StringListNode *n, const string *s, unsigned nr);

	/// Set nr-th role name of subject. Check name syntax. 
	bool SetRoleName(Subject *subj, const string *s, unsigned nr);

	/// check the soft constraints on a ESD.
	void CheckDocument();

protected:
	/// Give error after failing to update attribute or operation.
	void MakeErrorMessage(StringListNode *node, 
		StringListNode::StringErrorType result, 
		const string *s, string *text);
	///
	Thing *CreateThing(int classNr);
	///
	SSDChecks *GetSSDChecks() {return ssdChecks;}

	///
        static const int MINI_ELLIPSE_WIDTH;
        ///
        static const int MINI_ELLIPSE_HEIGHT;
private:
	///
	SSDChecks *ssdChecks;
};
#endif
