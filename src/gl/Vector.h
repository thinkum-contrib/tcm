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

#ifndef _VECTOR_H
#define _VECTOR_H

#include "bool.h"
#include "llist.h"

template <class T> class Vector {
	public:
		Vector(unsigned c) {
			cnt = c;
			ar = new T[c];
		};
		Vector(const List<T> &copy);
		Vector(const Vector<T> &copy);
		~Vector() {
			delete [/* cnt */] ar;
		};
		const Vector<T> &operator=(const Vector<T> &copy);
		const Vector<T> &operator=(const List<T> &copy);
		T &operator [](int i) {
			return ar[i];
		};
		const T &operator[](int i) const {
			return ar[i];
		};
		unsigned count() const {
			return cnt;
		};
		bool operator==(const Vector<T> &comp) const;
		bool operator< (const Vector<T> &comp) const;
		bool operator> (const Vector<T> &comp) const {
			return comp < *this;
		};
		bool operator<=(const Vector<T> &comp) const {
			return ! (comp < *this);
		};
		bool operator>=(const Vector<T> &comp) const {
			return ! (*this < comp);
		};
		bool operator!=(const Vector<T> &comp) const {
			return ! (*this == comp);
		};
	private:
		unsigned cnt;
		T *ar;
};

#endif
