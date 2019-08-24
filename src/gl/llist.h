//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _LIST_H
#define _LIST_H

#include "element.h"
#include "bool.h"

/// lists of objects of arbitrary type T.
template <class T> class List {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// create an empty list.
	List();

	/// delete entire list (but not the elements of the list).
	virtual ~List();		

	/// create list, initialized by elements of l.
	List(const List<T> &l); 

	/// copy list into an other, elements are copied too (e.g. l2 = l1).
	List<T> &operator=(const List<T> &l); 

	/// add e to the end of the list.
	List<T> *add(const T &e);

	/// insert e to i+1'th position of the list. 
	void insert(const T &e, const unsigned i); 

	/// return index of first element equal to e, if not found, return -1.
	int find(const T &e) const; 	

	/// return list is set
        bool isSet() const;

	/// count the number of times e occurs in the list
        int count(const T &e) const;

	/// return if list contains list l
        //bool contains(List<T> *l) const;

	/// return if list contains e.
	bool contains(const T &e) const {return (find(e) != -1);} 	

	/// remove all elements equal to e.
	void remove(const T &e);

	/// removes i+1'th element (0 <= i <= count()-1).
	void removei(const unsigned i = 0); 

	/// removes current element and advances the current to the next one.
        bool removecur(); 

	/// removes all elements from list.
	void empty();

	/// removes all elements + free elements (which should be pointers).
	virtual void clear(); 		

	/// returns ref. to i+1'th element, like array index (e.g. e = l[5]).
	T &operator[] (const unsigned i) const; 

	/// same as [] (different syntax).
	T &elem(const unsigned i) const; 	

	/// returns number of elements in list.
	unsigned count() const {return length;}

	/// replaces all elements equal to old by new.
	void replace(const T &old, const T &fresh); 

	/// sort all elements according to cmp function.
	void sort(int (*cmp)(T, T));

	/// reverse all elements in list.
	void reverse();		

	/// return if there is a first element + sets current to first element. 
	int first() { current = head; return (current != 0);} 

	/// sets current to last element + returns if there is a last element.
	int last() { current = tail; return (current != 0);}

	/// sets current to next element + returns if there is a next element.
	int next() { 
		if (current) current=current->next; return (current != 0); }

	/// sets current to prev. element + returns if there is a prev. element.
	int prev() { 
		if (current) current=current->prev; return (current != 0); }

	/// returns current element (Check first with 'done'!)
	T &cur() const { return current->item;}

	/// returns if current is out of list.
	bool done() const { return current == 0; }

	/// returns if T is in list + sets current to that element. 
	int setcur(const T &);

	// attempt.
	// friend ostream &operator<<(ostream &o, const List<T> &l);
private:
	/// head of the list.
	Element<T>* head;

	/// tail of the list.
	Element<T>* tail;

	/// current element.
	Element<T>* current;

	/// length of the list.
	unsigned length;
};

#ifdef __SUNPRO_CC
class string;
template<> void List<string>::clear();
#endif

#endif
