#ifndef _EVENTSET_H
#define _EVENTSET_H

#include "bool.h"
#include "llist.h"
#include "lstring.h"
#include <string.h>

#define MAX_EVENTS 256

class RelevantSet;

class EventSet {
	private:
		static List<string> EventNames;

		int current;
		unsigned char EventFlag   [(MAX_EVENTS + 7) / 8];

		friend class RelevantSet;
	public:
		EventSet();
		~EventSet() { };
		unsigned add(const string &event);
		void sub(string event);
		void clear();
		bool HasEvent(string event) const;
		unsigned count() const;
		bool empty() const;
		const string &operator[](int index) const;
		bool operator==(const EventSet &comp) const {
			return memcmp(&EventFlag, &comp.EventFlag, (MAX_EVENTS + 7) / 8) == 0;
		};
		bool operator< (const EventSet &comp) const {
			return memcmp(&EventFlag, &comp.EventFlag, (MAX_EVENTS + 7) / 8) < 0;
		};
		bool operator> (const EventSet &comp) const {
			return comp < *this;
		};
		bool operator<=(const EventSet &comp) const {
			return ! (comp < *this);
		};
		bool operator>=(const EventSet &comp) const {
			return ! (*this < comp);
		};
		bool operator!=(const EventSet &comp) const {
			return ! (*this == comp);
		};

		bool first();
		bool last();
		const string &cur() {
			return current < 0 ? string::EMPTY : EventNames[current];
		};
		bool next();
		bool prev();
		void print();
		string GetEvents(const char *prefix = (const char *) NULL)
			const;
		string GetGuards() const;
};

#endif



