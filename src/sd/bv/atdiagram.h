//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _ATDIAGRAM_H
#define _ATDIAGRAM_H

#include "atviewer.h"
#include "diagram.h"
#include "grafport.h"
class ATGraph;
class ATWindow;
class ATChecks;
class ADSValuation;
class ADSCks;
class ADSHyperGraph;
class TPDialog;

/// activity diagram class.
class ATDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TAT} */
public:
	///
	ATDiagram(Config *, ATWindow *, ATViewer *, ATGraph *);
	///
	virtual ~ATDiagram();
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
	void CheckDocument();
	///
	static const int DOT_WIDTH;

	///
        void ModelCheckProperty();
	///
        static void ModelCheckPropertyOKCB(Widget, XtPointer,   XtPointer); 
	///
        void DoModelCheckProperty(const string *p, bool, bool, bool);
	///
        void DoActualModelChecking(const string *p, string req,bool);

        ///
        void GeneralCheck();
        ///
        void DoGeneralCheck();
        ///
        bool ComputeHyperGraph(ADSHyperGraph *);
        ///
        void ComputeCKS(ADSHyperGraph *,ADSCks *, bool);
        ///
        void ComputeImpCKS(ADSHyperGraph *,ADSCks *);
 
        ///
        void ClearTrace();
	///
	//ADSCks *GetCKS(){return cl;}
	///
	//ADSHyperGraph *GetADSHyperGraph(){return am;}
	///
	TPDialog *GetTPDialog(){return tpd;}
protected:
	///
	Thing *CreateThing(int classNr);
	///
	bool HasIndexNode(int code);
	///
	bool HasIndexShape(int code);
        ///
        void ProvideFeedback(ADSCks *ac);
        ///
        void ProvideFeedback(ADSHyperGraph *ah);
private:
	///
	ATChecks *atChecks;
	///
	// ADSCks *cl;
	///
	// ADSHyperGraph *am;
	///
	TPDialog *tpd;
};
#endif
