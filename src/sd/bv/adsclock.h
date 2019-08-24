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
#ifndef _CLOCK_H
#define _CLOCK_H


#include "bool.h"
#include "lstring.h"
#include "adspropertytype.h"
#include "adsvariable.h"
#include "bag.h"
#include "subject.h"

class OutputFile;
class ADSHyperEdge;

/// variable class.
class Clock: public ADSVar {
/*@Doc: {\large {\bf scope:} } */
public:
        Clock(ADSHyperEdge *); //  relative clock
	/// 
	Clock(Edge *); //  relative clock
	///
	Clock();  // absolute clock
	///
	Clock(const Clock &v);  
	///
	~Clock();
	///
	//	bool isTimer();
	///	
	bool operator==(const Clock &comp) const;
	///
	ADSHyperEdge *GetHyperEdge();
	///
	Edge *GetEdge();
	///
	string GetName() const;
	///
	void Write();
	/// 
	//	Bag <Subject *> *GetConfig();
	//	///
	//	void SetConfig(Bag <Subject *> *);
	///
	//void SetReset(bool b);
	///
	//	bool isReset();

 private:

	/// the (unique) hyperedge the clock belongs to
 	ADSHyperEdge *hedge;
	Edge *edge;
	//	Bag <Subject *> *cfg;
	//	bool reset;
	//	int whensuperstep; // the superstep in which the timer is reset 

};
#endif
