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


#ifndef __HASHLIST_H
#define __HASHLIST_H


#include "llist.h"
class ADSValuation;
class ADSTransition;

/// hashlist for valuations
class ValuationHashList{
/*@Doc: {\large {\bf scope:} } */
	public:
                /// 
                ValuationHashList();
		///
		void add(ADSValuation *, int);
		///
		ADSValuation *isin(ADSValuation *, int);
		
         private:
		///
		List < List <ADSValuation *> *> hash_list;
};


/// hashlist for transitions
class TransitionHashList{
/*@Doc: {\large {\bf scope:} } */
	public:
                /// 
                TransitionHashList();
		///
		void add(ADSTransition *, int);
		///
		ADSTransition *isin(ADSTransition *, int);
        private:
		///
		List < List <ADSTransition *> *> hash_list;
};


#endif
