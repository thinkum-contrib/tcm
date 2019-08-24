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
#ifndef _ADSCKS_H
#define _ADSCKS_H

#include "llist.h"
//#include "point.h"
//#include "lstring.h"
//class Node;
//class AdKTransition;
//class Subject;
//class OutputFile;
//#include "node.h"
//#include "AdKtransition.h"
//#include "AdKlocation.h"
#include "graph.h"
#include "bool.h"
#include "hashlist.h"
//#include "adshypergraph.h"

class ClockManager;
class ADSValuation;
class ADSTransition;
class ADSHyperGraph;

///  class CKS, consisting of valuations and transitions
class ADSCks :public Graph {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ADSCks(ADSHyperGraph *a); 
	///
	~ADSCks();
	///
	void AddNode(Node *);
	///
	void AddEdge(Edge *);
	///
	void InitConnections(){};
      	///
	void WriteSubjects(OutputFile *f);
	///
	void WriteSMVFile(OutputFile *f, bool tlv);
	///
	//bool ExistsSimilarNode( ADSValuation *s);
      	///
	bool ExistsSimilarEdge( ADSTransition *s);
	/// 
	ADSValuation *FindSimilarNode( ADSValuation *s);
	/// checks whether the configuration in valuation s has become unbounded
	/// using a check from the Karp Miller algorithm for Petri nets
	bool GrowsInfinite(ADSValuation *s, string &str);
	///
	void GetClocks(List <string> *l);
	/// generate index number for valuations
	void AssignNumbers();
	/// 
	ADSHyperGraph *GetADSHyperGraph(){return am;};
	/// get valuation with index i
	ADSValuation *GetADSValuation(int i);
	///
        int countconfigs();

 private:
	/// the original activity hypergraph
	ADSHyperGraph *am; 
	///
	//	ValuationHashList vhl;
	///
	//	TransitionHashList thl;
	

};
#endif
