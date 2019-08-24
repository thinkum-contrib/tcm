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
#ifndef _ADSSEMANTICS_H
#define _ADSSEMANTICS_H

#include <stdio.h>
#include "llist.h"
#include "atdiagram.h"    
#include "adshypergraph.h"
#include "adshyperedge.h"
#include "adscks.h"
#include "adsclockmanager.h"
#include "atdtransitionedge.h"
#include "adsvaluation.h"
#include "adstransition.h"
#include "bag.h"

//class ClockManager;


class PropVal;

class ADSSem {
/*@Doc: {\large {\bf scope:} } */
public:

        ///
	ADSSem() {};
	///
	~ADSSem(void) {};

	///
	bool inparallel(ADSHyperGraph *ah,Subject *a, Subject *b);
	///
	void tokengame(ADSHyperGraph *h,ADSCks *c);
	/// the requirements level semantics
	void ComputeCKS(ADSHyperGraph*, ADSCks*, bool reduce);
	/// the implementation level semantics
	void ComputeImpCKS(ADSHyperGraph*, ADSCks*);
	/// given stable state a, in eadkl all possible unstable states are returned
	void Event(ADSHyperGraph *h, ADSValuation *a,List <ADSValuation *> *eadkl,bool reduce);
	///
	void InterleavedEvent(ADSHyperGraph *h, ADSValuation *a,List <ADSValuation *> *eadkl,bool reduce);

	/// in steplist all candidate steps are listed
	void Step(ADSHyperGraph *h, ADSValuation *ak, Bag <ADSHyperEdge *> *enab, List<Bag<ADSHyperEdge *> *> *steplist);
	/// 
        ADSValuation *TakeStep(ADSHyperGraph *am,
		      ADSCks *c,
		      ADSValuation *from,
		      Bag <ADSHyperEdge *> *step
		      );
	///
	void ComputeEnabled(ADSHyperGraph *h, ADSValuation *ak, 
			    Bag <ADSHyperEdge *> *enab);

	///
	bool Consistent(ADSHyperGraph *ah,
			Bag <Subject *> cfg, 
			Bag <ADSHyperEdge *> l);
	///
	bool NextStateAfterStep(ADSHyperGraph *ah,
			Bag <Subject *> cfg, 
			Bag <ADSHyperEdge *> l, 
			Bag <Subject *> *newcfg, 
			Bag <ATDActionStateNode *> *termresp,
			List <ClockConstraint *> *zero,
			List <ClockConstraint *> *off,
				List <Prop *> *pl);
	///
	bool ParseLabel(const string *str, List <PropVal *> *p);

};

#endif
