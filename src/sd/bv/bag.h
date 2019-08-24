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

//------------------------------------------------------------------------------
#ifndef _BAG_H
#define _BAG_H

#define MAXLENGTH 200

#include "element.h"
#include "bool.h"
#include "llist.h"
#include "subject.h"
#include "adshyperedge.h"

/// lists of objects of arbitrary type T.
template <class T> class Bag  {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// create an empty list.
	Bag(); 
	///
	Bag (const List<T> &l, int n);
	///
	Bag (const Bag <T> &b);
	/// add e to bag
	void add(const T &e);

	/// add e to n times to bag
	void add(const T &e, int n);

	/// insert e to i+1'th position of the list. 
	//	void insert(const T &e, const unsigned i); 

	/// return index of first element equal to e, if not found, return -1.
	//	int find(const T &e) const; 	

	/// return list is set			                       
	bool isSet() const;                                             

        /// count the number of times e occurs in the list
	int count(const T &e) const;                                   

	int length(void);

	/// return if bag contains bag l                            
	bool contains(Bag<T> &l) const;                               

	void join(const Bag <T> &l);

	// difference
	bool diff( Bag <T> &l);

	// get all elements (including those that might not be in the bag)
	void GetList(List<T> &l) const {l=list;};

	/// get all elements that occur more than once and put them in set
	void GetSet(List<T> *l);

	bool remove(const T &e);

	void empty();
private:
	///
        List <T> list ;
	/// list[i] is countl[i] times in the bag
	int countl[MAXLENGTH];	
};


#endif
