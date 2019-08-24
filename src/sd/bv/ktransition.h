#ifndef _KTRANSITION_H
#define _KTRANSITION_H

#include "subject.h"
#include "lvector.h"
#include "llist.h"
#include "transition.h"

class KLocation;

class KTransition: public Vector<Subject *> {
	public:
		KLocation *to;
		bool InputTransition; /* was: Resett . -- The function has been
		          extended (from indicating whether ``reset{t}'' should
		          be included into the transition to
		          whether the transition is an input transition
		          inserted by GenerateEvents() ). */
		KTransition(unsigned c);
		~KTransition() { };
		bool operator==(const KTransition &comp) const {
			return InputTransition == comp.InputTransition
			       && to == comp.to
			       && Vector<Subject *>::operator==(comp);
		};
		bool operator< (const KTransition &comp) const;
		bool operator> (const KTransition &comp) const {
			return comp < *this;
		};
		bool operator<=(const KTransition &comp) const {
			return ! (comp < *this);
		};
		bool operator>=(const KTransition &comp) const {
			return ! (*this < comp);
		};
		bool operator!=(const KTransition &comp) const {
			return ! (comp == *this);
		};
		string GetGuards() const;
		string GetEvents() const;
		string GetClockResets() const;
};

unsigned IsClockReset(const string &s);
#endif
