//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef __BVINSTANCES_H
#define __BVINSTANCES_H

#ifdef __GNUC__

//GNU g++ does not implement a separate pass to instantiate template
//functions and classes at this point; for this reason, it will not work,
//for the most part, to declare your template functions in one file and
//define them in another. The compiler will need to see the entire
//definition of the function, and will generate a static copy of the
//function in each file in which it is used.
// 
//g++ does not automatically instantiate templates defined in other
//files. Because of this, code written for cfront will often produce
//undefined symbol errors when compiled with g++. You need to tell g++
//the file where they are defined.

#include "dginstances.h"

// Part for TSTD
#include "../sd/bv/stnode.h"
#include "../sd/bv/transition.h"

template class List<STNode *>;
template class List<Transition *>;

#include "../sd/bv/scnode.h"
#include "../sd/bv/scdtransitionedge.h"

template class List<SCNode *>;
template class List <SCDTransitionEdge *>


#ifdef MODELCHECK
#include "../sd/bv/klocation.h"
template class List<KLocation *>;
#endif

// Part for TATD

#include "../sd/bv/atdactionstatenode.h"             
#include "../sd/bv/adsvaluation.h"       
#include "../sd/bv/adstransition.h"
#include "../sd/bv/adshyperedge.h"
#include "hyperedge.h"
#include "../sd/bv/adsproperty.h"
#include "../sd/bv/adsvariable.h"
#include "../sd/bv/adspropertyvaluation.h"
#include "../sd/bv/adsactivity.h"
#include "../sd/bv/adsclock.h"
#include "../sd/bv/adsclockconstraint.h"
#include "../sd/bv/bag.h"
#include "../sd/bv/adsvariable.h"

template class List<ADSValuation *>;
template class List<List <ADSValuation *> *>;
template class List<ADSTransition *>;
template class List<ATDActionStateNode *>;
template class List<ADSHyperEdge *>;
template class List<Bag<ADSHyperEdge *> *>;
template class List<Prop *>;
template class List<ADSVar *>;
template class List<PropVal *>;
template class List<ADSActivity *>;
template class List<Clock *>;
template class List<ClockConstraint *>;
template class List<List<bool> *>;



#endif
#endif
