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
#ifndef _CBDIAGRAM_H
#define _CBDIAGRAM_H

#include "erdiagram.h"
class CBViewer;
class CBWindow;
class CBGraph;
class CBChecks;
class CBClassNode;

/// UML collaboration diagram class.
class CBDiagram : public ERDiagram {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	CBDiagram(Config *, CBWindow *, CBViewer *, CBGraph *);
	///
	virtual ~CBDiagram();
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

	/// Set nr-th role name of subject. Check name syntax. 
	bool SetRoleName(Subject *subj, const string *s, unsigned nr);

	/// Set stereotype string of a class node.
	bool SetStereotype(CBClassNode *object, const string *s);
	/// Set properties string of a class node.
	bool SetProperties(CBClassNode *object, const string *s);

	/// Set Message in objectlink at position nr.
	bool SetMessage(Subject *t, const string *s, unsigned nr);

	/// check the soft constraints on a ESD.
	void CheckDocument();

protected:
	///
	Thing *CreateThing(int classNr);
	///
	CBChecks *GetCBChecks() {return cbChecks;}
private:
	///
	CBChecks *cbChecks;
};
#endif
