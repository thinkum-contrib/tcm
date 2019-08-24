#ifndef _KLOCATION_H
#define _KLOCATION_H

#include "stnode.h"
#include "lvector.h"
#include "lstring.h"
#include "ptrset.h"
#include "relevantset.h"
#include "llist.h"
#include "ktransition.h"

class KLocation: public Vector<Subject *> {
	public:
		KLocation(unsigned c);
		~KLocation();
		KLocation(const KLocation &copy);
		KLocation(const List<Subject *> &copy);

		bool operator==(const KLocation &comp) const;
		bool operator< (const KLocation &comp) const;
		bool operator> (const KLocation &comp) const {
			return comp < *this;
		};
		bool operator<=(const KLocation &comp) const {
			return ! (comp < *this);
		};
		bool operator>=(const KLocation &comp) const {
			return ! operator<(comp);
		};
		bool operator!=(const KLocation &comp) const {
			return ! operator==(comp);
		};
/* A KLocation has a list of outstanding events. */
		bool HasEvent(const string &event) const {
			return inputset.HasEvent(event);
		};
		bool HasProp(const string &prop) const;
		string GetProp() const;
		string GetInvar() const;
//	private:
		RelevantSet inputset;
		unsigned long number;
		PtrSet<KTransition> transSet;
		bool Transient;
};

#endif
