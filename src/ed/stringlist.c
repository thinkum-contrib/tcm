////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "stringlist.h"
#include "lstring.h"
#include "util.h"

void StringList::Insert(List<string *> *list, const string *s, 
			unsigned n, bool update) {
	if (!check(list && s))
		return;
	if (*s != "") {
		if (update) {
			if (n < list->count()) {
				// update existing value
				*(*list)[n] = *s;
			}
			else if (n== list->count()) {
				// add new value at end of list.
				string *ns = new string(*s);
				list->add(ns);
			}
			else {
				error("%s, line %d, impl error:"
					" impossible string position\n", 
					__FILE__, __LINE__);
				return;
			}
		}
		else {  // insert new string between the others. 
			if (n < list->count()) {
				string *ns = new string(*s);
				list->insert(ns, n);
			}
			else if (n == list->count()) {
				string *ns = new string(*s);
				list->add(ns);
			}
			else {
				error("%s, line %d, impl error: "
					"impossible string position\n", 
					__FILE__, __LINE__);
				return;
			}
		}
	}
	else
		// empty string -> delete this value.
		if (update) {
			if (n < list->count()) {
				string *x = (*list)[n];
				list->removei(n);
				delete x;
			}
		}
}
