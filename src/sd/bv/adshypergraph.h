//////////////////////////////////////////////////////////////////////////////////
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Rik Eshuis (eshuis@cs.utwente.nl).
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
#ifndef _ADSHYPERGRAPH_H
#define _ADSHYPERGRAPH_H


#include "hypergraph.h"
#include "llist.h"
#include "bag.h"
#include "bool.h"

#define MAXACT 100
#define MAXNODE 100

class ADSActivity;
class ATDActionStateNode;
class Prop;
class ADSVar;
class OutputFile;
class Clock;
class ClockConstraint;

/// (abstract) graph class.
class ADSHyperGraph: public HyperGraph {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ADSHyperGraph(); 
	///
	~ADSHyperGraph();

	/// does a interfere with b?
	bool GetInterference(ADSActivity *a, ADSActivity *b);
	///
	bool GetInterference(ATDActionStateNode *a1, ATDActionStateNode *a2);
	///
	bool isConflicting(Bag <ADSHyperEdge *> *step, ADSHyperEdge *he);
	///
	void Initialise();
	///
	void Finalise();
	///
	bool AddProp(Prop *p);
	///
	bool AddVar(ADSVar *v);
	///
	void RemoveProp(Prop *p);

	///
	void GetPropList(List <Prop *> &l);
	///
	void GetExtPropList(List <Prop *> &l);
	///
	void GetIntPropList(List <Prop *> &l);
	///
	void GetVarList(List <ADSVar *> &l);
	///
	Prop *FindSimilarProp(Prop *p);
	///
	ADSVar *FindSimilarVar(ADSVar *p);
	
	///
	Node *FindNode(string name);
	///
	//	ADSActivity *FindAct(string);
	///  update the upper bound of each node  
       	void UpdateBounds(Bag <Subject *> *cfg);
	///  return the upper bound of node s
	int GetBound(Subject *s);

	///
	int GetNrTimeouts(){return timeoutnumber;};

	///
       	void WriteSubjects(OutputFile *ofile);
        ///
        string DeadEdgesNodesConstraints();
        ///
        void SetInitialFinalNames();
        ///
        void UnSetInitialFinalNames();
	///
        void WriteNuSMV(OutputFile *ofile, bool);
	///
	string ComputeFinalPredicate();
	///
	void GetFinalNodes(List <Subject *> *final);

	///
	void RemoveLocalVariables(List <ADSVar *> *used);

	///
	void RemoveNodes(List <Node *> , List <ADSVar *>, bool reduction);


 protected:
	///
	void ComputeActivities();
	///
	void ComputeConflicts();
	///
	void ComputeInterferences();
	///
	void ComputeInternalProperties();
	///
	void ComputeInternalHyperEdges();
	///
	void ComputeExternalProperties();
	/// how many timeout are there in the hypergraph
	void ComputeNrTimeouts();
	///
	void InitialiseBounds();



	/// Here come the reduction rules



	bool NodeReferredToBySomeInpredicate(Subject *n);

	bool VarTestedInHyperEdgeWithoutUpdate(ADSVar *v);

	bool VarUpdatedByTwoActivities(ADSVar *v);

	bool isRemovableHyperEdge(ADSHyperEdge *hedge, List <Node *> nodeused, List <ADSVar *> varused, bool reduction);

 private:




	/// the list of properties
	List <Prop *> propl;   
	///	the list of variables
	List <ADSVar *> varl;  
	/// the variables updated in activities. Needed for deriving the interference relation
	List <ADSVar *> updatedinactivities; 
	/// the activities
	List <ADSActivity *> actlist;  
	/// n by n matrix (indexed by actlist)
	int interference[MAXACT][MAXACT];
	/// the list of properties that can be set by the environment
	List <Prop *> extproplist;
	/// the list of properties that are updated in activities 
	List <Prop *> intproplist; 
	/// the number of timeouts. Needed to initialise the interval of the clock manager
        int timeoutnumber;
	/// the bound of each node; needed for model checker input
	int bound[MAXNODE];
};
#endif
