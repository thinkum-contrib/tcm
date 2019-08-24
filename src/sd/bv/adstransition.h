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
#ifndef _ADSTRANSITION_H
#define _ADSTRANSITION_H


#include "llist.h"
#include "edge.h"
#include "outputfile.h"
#include "bag.h"


class ADSValuation;
class ADSCks;
class ClockConstraint;
class AmHyperEdge;


class ADSTransition: public Edge {
/*@Doc: {\large {\bf scope:} } */
	public:
                /// transition
                ADSTransition(ADSCks *, 
  			      ADSValuation *,
  			      ADSValuation *);
		/// transition in which step is taken
		ADSTransition(ADSCks *, 
			      ADSValuation *,
			      ADSValuation *,
			      Bag <ADSHyperEdge *> *);
		///
		~ADSTransition() { };
		///
		Subject *Clone(){return new ADSTransition(*this);};
		///
       		void Write(OutputFile *f);
		///
       		void WriteScreen();

		///
		bool operator==( ADSTransition &comp) ;	      
		///
		void GetStep(Bag <ADSHyperEdge *> &st){st=step;}
		///
		int ComputeKey();
 private:
		/// (optional) step that is taken in current transition
		/// (only if subject1 is unstable
		Bag <ADSHyperEdge *> step;
		/// key for hashtable
		int key ;
};

//unsigned IsClockReset(const string &s);
#endif
