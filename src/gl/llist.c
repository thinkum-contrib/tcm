////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#ifndef __LIST_C
#define __LIST_C

#include "llist.h"

#if defined(__SUNPRO_CC)
#include "lstring.h"
#if __SUNPRO_CC >= 0x500
template<> inline void List<string>::clear() { empty(); }
template<> inline void List<unsigned>::clear() { empty(); }
template<> inline void List<int>::clear() { empty(); }
#else
inline void List<string>::clear() { empty(); }
inline void List<unsigned>::clear() { empty(); }
inline void List<int>::clear() { empty(); }
#endif
#endif

template <class T> List<T>::List() {
	head = 0;
	tail = 0;
	current = 0;
	length = 0;
}

template <class T> List<T>::~List() {
	Element<T> *p = head, *q;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
}

template <class T> List<T>::List(const List<T> &l) {
	head = 0;
	tail = 0;
	length = 0;
	current = 0;
	unsigned s = l.count();
	for (unsigned i = 0; i < s; i++)
		add(l[i]);
	current = head;
}

template <class T> List<T> &List<T>::operator=(const List<T> &l) {
	if (this == &l) 
		return *this;
	empty();
	unsigned s = l.count();
	for (unsigned i = 0; i < s; i++)
		add(l[i]);
	current = head;
	return *this;	
}

template <class T> List<T> *List<T>::add(const T &e) {
	Element<T> *p = new Element<T>;
	p->item = e;
	p->prev = tail;
	p->next = 0;
	if (tail != 0) 
		tail->next = p;
	if (head == 0) 
		head = p;
	tail = p;
	if (current == 0)
		current = head;
	length++;
	return this;
}

template <class T> void List<T>::insert(const T &e, const unsigned i) {
	if (i >= length) {
		add(e); 
		return;
	}
	Element<T> *p = new Element<T>;
	Element<T> *q = head;
	unsigned j = 0;
	p->item = e;
	while (j++ < i) 
		q = q->next;
	p->next = q;
	if (q != 0) {
		p->prev = q->prev;
		q->prev = p;
	} 
	else {
		p->prev = tail;
		tail = p;
	}
	if (p->prev != 0)
		p->prev->next = p;
	else
		head = p;
	length++;
}
 
template <class T> int List<T>::find(const T &e) const {
	Element<T> *q = head;
	int i = 0;
	while (q != 0) {
		if (q->item == e) 
			return i;
		i++;
		q = q->next;
	}
	return -1;
}

template <class T> void List<T>::remove(const T &e) {
	int i;
	while ((i = find(e)) >= 0)
		removei((unsigned) i);
}

template <class T> void List<T>::removei(const unsigned i) {
	unsigned j = 0;
	Element<T> *q = head;
	if (i >= length) 
		return;
	while (j++ < i) 
		q = q->next;
	if (q->prev != 0)
		q->prev->next = q->next;
	else 
		head = q->next;
	if (q->next != 0)
		q->next->prev = q->prev;
	else 
		tail = q->prev;
	if (current == q)
		current = q->next;
	delete q;
	length--;
}

// added by David N. Jansen <dnjansen@cs.utwente.nl>
template <class T> bool List<T>::removecur() {
        if ( 0 == current )
                return False;
        Element<T> *q = current;
        current = q->next;
        if ( 0 != q->prev )
                q->prev->next = current;
        else
                head = current;
        if ( 0 != current )
                current->prev = q->prev;
        else
                tail = q->prev;
        delete q;
        length--;
        return True;
}

// added by Rik Eshuis <eshuis@cs.utwente.nl>
template <class T> bool List<T>::isSet(void) const {
        Element<T> *q = head;
        while (q != 0) {
        	if (count(q->item)>1) 
			return False;     
        	q = q->next;
        }
        return True;
}

// added by Rik Eshuis <eshuis@cs.utwente.nl>
template <class T> int List<T>::count(const T &e) const {
        int c=0;
        Element<T> *q = head;
        while (q != 0) {
        	if (q->item == e) {
            		c++;
          	}
          	q = q->next;
        }
        return c;
}

// added by Rik Eshuis <eshuis@cs.utwente.nl>
// The following procedure is a bit inefficient since multiple
// elements are counted every time they occur in list l
//template <class T> bool List<T>::contains(List<T> *l) const {
//	for (l->first();!l->done();l->next()){
//   		if (l->count(l->cur()) > this->count(l->cur())) 
//			return False;
// 	}
//  	return True;
//}

template <class T> T &List<T>::operator[] (const unsigned i) const {
	Element<T> *q = head;
	unsigned j = 0;
	while (j++ < i) 
		q = q->next;
	return q->item;
}

template <class T> T &List<T>::elem(const unsigned i) const {
	Element<T> *q = head;
	unsigned j = 0;
	while(j++ < i) 
		q = q->next;
	return q->item;
}

template <class T> void List<T>::replace(const T &old, const T &fresh) {
	Element<T> *q = head;
	while(q != 0)
		if(q->item == old)	
			q->item = fresh;
}

template <class T> void List<T>::sort(int (*cmp)(T, T)) {
	Element<T> *p, *q;
	if (head == 0)
		return;
	for (p=head; p->next!=0; p=p->next) {
		for(q=tail;(p!=q && p!=q->next); q=q->prev) {
			if ((*cmp) (q->item, q->prev->item) < 0) {
				T temp = q->item;
				q->item = q->prev->item;
				q->prev->item = temp;
			}
		}
	}
}

template <class T> void List<T>::reverse() {
	Element<T> *p, *q;
	if (head == 0)
		return;
	for (p=head,q=tail; (p!=q && p!=q->next);p=p->next,q=q->prev) {
		T temp = p->item;
		p->item = q->item;
		q->item = temp;
	}
}

template <class T> void List<T>::empty() {
	Element<T> *p = head, *q;
	// delete all nodes.
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	length = 0;
}

template <class T> void List<T>::clear() { 
	Element<T> *p = head, *q;
	// delete all items.
	while (p != 0) {
		// dangerous when p is not a pointer.
		if (p->item) 
			delete p->item;
		p = p->next;
	}
	// delete all nodes.
	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	length = 0;
	current = 0;
}

template <class T> int List<T>::setcur(const T &e) {
	Element<T> *q = head;
	while (q != 0) {
		if (q->item == e) {
			current = q;
			return 1;
		}
		q = q->next;
	}
	return 0;
}

//
// template <class T> ostream &operator<<(ostream &o, const List<T> &l) {
// 	Element<T> *q = l.head;
// 	while(q++ != 0)
// 		o << q->item;
// }


#ifdef __GNUC__
#include "instances.h"
#endif

#ifdef XLC
#include "xlcinstances.h"
#endif

#endif
