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
#ifndef _ADSVALUATION_H
#define _ADSVALUATION_H

#include "atdactionstatenode.h"
#include "lstring.h"
#include "subject.h"
#include "bag.h"
#include "node.h"
#include "adscks.h"
#include "llist.h"
#include "adsclockmanager.h"

class Clock;
class PropVal;
class OutputFile;

enum StateType {unstable, stable}; // in unstable state an event has occurred

/// Class to model the valuation of the state variables (configuration, terminated action state nodes, variables, clocks)
class ADSValuation: public Node {
/*@Doc: {\large {\bf scope:} } */
	public:
                /// 
                ADSValuation(ADSCks *c,StateType s );
		///
		~ADSValuation();
		///
		Subject *Clone(){return new ADSValuation(*this);}
		///
		ADSValuation(const ADSValuation &copy);
		///
		ADSValuation(const ADSValuation &copy,StateType s);
		///
		bool operator==( ADSValuation &comp);
		///
		void Write(OutputFile *f) ;
		///
		void  WriteScreen();
		///
		void GetConfig(Bag <Subject *> *);
		///
		void SetConfig(Bag <Subject *> c);
		///
		void GetPropList(List <PropVal *> *);
		///
		void SetPropList(List <PropVal *> p);
		///
				void GetQueue(List <PropVal *> *);
		///
			void SetQueue(List <PropVal *> p);
		///
		void GetTerminated(Bag <ATDActionStateNode *> *);
		///
		void AddTerminated(Bag <ATDActionStateNode *> t);
		///
		     void GetQTerminated(Bag <ATDActionStateNode *> *);
		///
         		void AddQTerminated(Bag <ATDActionStateNode *> t);
		///
		ClockManager GetClockManager();
		///
		void SetClockManager(ClockManager&);
		///
		void GetClockConstraints(List <ClockConstraint *> *);
		///
		void SetClockConstraints(List <ClockConstraint *> );
		///
		void GetQClockConstraints(List <ClockConstraint *> *);
		///
		void SetQClockConstraints(List <ClockConstraint *> );
		///
		bool HasClockConstraints(){return (clist.count()>0);}
		/// set index for model checker input
		void SetNumber(int);
		/// get index for model checker input
		int GetNumber();
		///
		bool isStable(){return (st==stable);}
		///
		void makeStable(){st=stable;}
		/// get key
		int ComputeKey();
                ///
                bool hassameconfig( ADSValuation &comp);


	private:
		/// Configuration (containing nodes only)
		Bag <Subject *> cfg; //Nodes from hyperedge
		/// Terminated action state nodes
		Bag <ATDActionStateNode *> tlist; //Subbag from cfg
		/// Boolean properties valuations
		List <PropVal *> plist; // Abstraction from LVar + input
		/// Clock manager
		ClockManager cm;
		/// list of timeout events
	      	List <ClockConstraint *> clist; 
		///
		StateType st; // stable or unstable
		///
		int index; // index for for model checker input
		///
		int key; // key for hashtable
		/*
		///queue (only for implementation level semantics
	       	List <PropVal *> queue; 
		/// terminated activities (only for implementation level semantics)
		Bag <ATDActionStateNode *> qtermlist; //Subbag from terminated
		/// list of timeout events in ILS semantics
	      	List <ClockConstraint *> qclist; 
		*/
};

#endif
