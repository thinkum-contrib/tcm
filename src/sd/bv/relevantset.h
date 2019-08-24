#ifndef _RELEVANTSET_H
#define _RELEVANTSET_H

#include "bool.h"
#include "llist.h"
#include "lstring.h"
#include "eventset.h"
#include <string.h>

class RelevantSet : public EventSet {
	protected:
		unsigned char RelevantFlag[(MAX_EVENTS + 7) / 8];
	public:
		RelevantSet();
		~RelevantSet() { };
		unsigned add(const string &event);
		void print();
		void SetRelevant(const EventSet &relev);
		string GetGuards() const;
};

#endif
