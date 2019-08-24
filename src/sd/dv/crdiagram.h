//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
//-----------------------------------------------------------------------------
#ifndef _CRDIAGRAM_H
#define _CRDIAGRAM_H

#include "erdiagram.h"
#include "classnode.h"
class CRViewer;
class CRWindow;
class CRGraph;
class CRChecks;

/// class-relationship diagram class.
class CRDiagram: public ERDiagram {
/*@Doc: {\large {\bf scope:} TCRD} */
public:
	///
	CRDiagram(Config *, CRWindow *, CRViewer*, CRGraph *);
	///
	virtual ~CRDiagram();
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
	///
	void CheckDocument();

	/// Set Attribute in obj at position nr.
	bool SetAttribute(ClassNode *obj, const string *s, unsigned nr);

	/// Set Operation in obj at position nr.
	bool SetOperation(ClassNode *obj, const string *s, unsigned nr);

protected:
	/// Give error after failing to update attribute or operation.
	void MakeErrorMessage(ClassNode *obj, ClassNode::TextErrType result, 
		const string *s, string *msg);

	/// Checks if combining TaxonomyJunction and ModeJunction is correct.
	bool CheckTaxonomyCombination(Edge *edge);
	///
	Thing *CreateThing(int classNr);
	///
	CRChecks *GetCRChecks() {return crChecks;}
private:
	///
	CRChecks *crChecks;
};
#endif
