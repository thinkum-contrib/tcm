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
#ifndef _ADSHYPEREDGE_H
#define _ADSHYPEREDGE_H

#include "hyperedge.h"
#include "llist.h"
#include "adsclockconstraint.h"
#include <stdlib.h>

class Prop;
class ADSVar;
class OutputFile;
class ADSHyperGraph;

/// Graph activity machine hyper edge class
class ADSHyperEdge: public HyperEdge {
/*@Doc: {\large {\bf scope:} diagram} */
public:
     ///
     ADSHyperEdge(ADSHyperGraph *a) : HyperEdge((HyperGraph *)a){cc=0;sendevent=NULL;internal=False;};
     ///
     ADSHyperEdge(ADSHyperGraph *a, Edge *e);
     ///
     bool AddProp(Prop *p);
     ///
     bool AddVar(ADSVar *v);
     ///
     bool refersto(ADSVar *v){return varl.contains(v);};
     ///
     void GetPropList(List <Prop *> &p);
     ///
     void GetVarList(List <ADSVar *> &v);
     ///
     void SetClockConstraint(ClockConstraint *);
     ///
     ClockConstraint *GetClockConstraint();
     ///
     bool hasClockConstraint();
     ///
     void WriteMembers(OutputFile *f);
     ///
     void WriteScreen();
     ///
     void AddEdges(List <Subject *> l);
     ///
     void GetEdges(List <Subject *> *l);
     /// 
     void AddConflict(ADSHyperEdge *ah){conflict.add(ah);}
     ///
     void GetConflict(List <ADSHyperEdge *> *al){*al=conflict;}
     ///
     bool conflicts(ADSHyperEdge *);
     ///
     bool isconflicting();
     ///
     bool inpredicaterefersto(Subject *n){return (inlist.contains(n)||notinlist.contains(n));}
     /// 
     void AddInNode(Subject *n){if (!inlist.contains(n)) inlist.add(n);}
     ///
     void GetInNodes(List <Subject *> *nl){*nl=inlist;}
     /// 
     void AddNotInNode(Subject *n){if (!notinlist.contains(n)) notinlist.add(n);}
     ///
     void GetNotInNodes(List <Subject *> *nl){*nl=notinlist;}
     ///
     void SetSendEvent(Prop *p){sendevent=p;}
     ///
     Prop *GetSendEvent(){return sendevent;}
     ///
     void SetInternal(){internal=True;}
     ///
     bool GetInternal(){return internal;}
     ///
     string GetUniqueName();

private:
     ///
     List <Prop *> propl;
     ///
     List <ADSVar *>  varl;
     ///
     ClockConstraint *cc;
     /// list of nodes tested with `in' predicate
     List <Subject *>  inlist;
     /// list of nodes tested with `not in' predicate
     List <Subject *>  notinlist;
     ///
     List <Subject *> edgelist; 
     ///
     List <ADSHyperEdge *> conflict;
     ///
     Prop *sendevent;
     /// true if triggered by internal event
     bool internal;
};

#endif
