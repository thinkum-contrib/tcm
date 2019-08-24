////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente, Enschede.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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

#include "Vector.h"
#include "llist.h"
#ifdef __GNUC__
#include "subject.h"
#endif

template<class T> Vector<T>::Vector(const List<T> &copy) {
	cnt = copy.count();
	ar = new T[cnt];
	for ( unsigned i = 0 ; i < cnt ; i++ )
		ar[i] = copy[i];
}

template<class T> Vector<T>::Vector(const Vector<T> &copy) {
	cnt = copy.count();
	ar = new T[cnt];
	for ( unsigned i = 0 ; i < cnt ; i++ )
		ar[i] = copy[i];
}

template<class T> const Vector<T> &Vector<T>::operator=(const Vector<T> &copy) {
	delete [/* cnt */] ar;
	cnt = copy.count();
	ar = new T[cnt];
	for ( unsigned i = 0 ; i < cnt ; i++ )
		ar[i] = copy[i];
	return *this;
}

template<class T> const Vector<T> &Vector<T>::operator=(const List<T> &copy) {
	delete [/* cnt */] ar;
	cnt = copy.count();
	ar = new T[cnt];
	for ( unsigned i = 0 ; i < cnt ; i++ )
		ar[i] = copy[i];
	return *this;
}


template<class T> bool Vector<T>::operator==(const Vector<T> &comp) const {
	for ( int i = count() ; --i >= 0 ; )
		if ( ar[i] != comp.ar[i] )
			return False;
	return True;
}


template<class T> bool Vector<T>::operator< (const Vector<T> &comp) const {
	for ( int i = count() ; --i >= 0 ; )
		if ( ar[i] != comp.ar[i] )
			return ar[i] < comp.ar[i];
	return False;
}

#ifdef __GNUC__
template class Vector<Subject *>;
#endif
