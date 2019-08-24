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
#ifndef _ADSCLOCKMANAGER_H
#define _ADSCLOCKMANAGER_H


// The clock manager manages dependencies between timers


#include "adsclock.h"
#include "bool.h"
#include "atdiagram.h"
#include "outputfile.h"
#include "thing.h"

#define MAX 200

class OutputFile;
class AmHyperEdge;

/// variable class.
class ClockManager {
/*@Doc: {\large {\bf scope:} } */
public:
        ///
        ClockManager(); //  relative clock
	///
	~ClockManager();
	///
	ClockManager(const ClockManager &c);
	///
	bool operator==( ClockManager c);
	///
	bool ExistScheduled();
	///
	bool ExistTimeouts();
	///
	//	bool NextTimeouts(List <ClockConstraint *> *l);
	///
	void GetTimeouts(List <ClockConstraint *> *l);
	///
	bool Update(List <ClockConstraint *> *zero, // new timers
		    List <ClockConstraint *> *off); // irrelevant timers
       

	///
	bool Tick();

	void Write() ;
	///
	void Write(OutputFile *ofile);
	
	void SetInterval(int i){interval=i;};
	

 private:
  
	///
	List <ClockConstraint *> cl; // running timers
		
	///
	int integer_timespent[MAX]; // for each timer the time already spent
	///
	int fraction_timespent[MAX]; // for each timer the time already spent
	// timers that are independent have the same value
	
	/// 
	int interval; // interval with which the clock ticks

	

};
#endif
