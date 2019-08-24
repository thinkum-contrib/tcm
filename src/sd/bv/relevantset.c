#include "relevantset.h"
#include "string.h"
#include <stdio.h>

RelevantSet::RelevantSet()
: EventSet() {
	memset(RelevantFlag, '\0', sizeof(RelevantFlag));
}


unsigned RelevantSet::add(const string &event) {
	unsigned u = EventSet::add(event);
	RelevantFlag[u >> 3] |= 0200 >> (u & 07);
	return u;
}


void RelevantSet::SetRelevant(const EventSet &relev) {
	memcpy(RelevantFlag, relev.EventFlag, sizeof(RelevantFlag));
}


void RelevantSet::print() {
	for ( int i = EventNames.count() ; i != 0 ; ) {
		--i;
		if ( EventFlag[i >> 3] & 0200 >> (i & 07) ||
		     RelevantFlag[i >> 3] & 0200 >> (i & 07) )
			printf("%c%s ",
				EventFlag[i >> 3] & 0200 >> (i & 07) ? '+' : '-',
				EventNames[i].getstr());
	}
}


string RelevantSet::GetGuards() const {
	/* calculates a string composed of all the guards */
	string result;
	for ( int i = EventNames.count() ; i != 0 ; ) {
		--i;
		const string *str = &EventNames[i];
		if ( '[' == (*str)[0] && ']' == (*str)[str->length() - 1] &&
		    RelevantFlag[i >> 3] & 0200 >> (i & 07) ) {
			if ( result.length() )
				result += " and ";
			result += '(';
			string ev;
			ev.add(str->getstr() + 1,
				str->length() - 2);
			if ( 0 == (EventFlag[i >> 3] & 0200 >> (i & 07)) )
				for ( int j = 0 ; ; j++ ) {
					if ( j >= ev.length() ) {
						result += "not ";
						result += ev;
						break;
					}
					if ( '<' == ev[j] || '=' == ev[j] || '>' == ev[j] ) {
						result.add(ev.getstr(), j);
						if ( '=' == ev[j] ) {
							result += '<';
							result += &(ev.getstr()[j+1]);
							result += " or ";
							result.add(ev.getstr(),j);
							result += '>';
						} else if ( '<' == ev[j] && '>' == ev[j+1] ) {
							result += '=';
							j++;
						} else {
							result += char('>' + '<' - ev[j]);
							if ( '=' == ev[j+1] )
								j++;
							else
								result += '=';
						}
						result += &(ev.getstr()[j+1]);
						break;
					}
				}
			else
				for ( int j = 0 ; ; j++ ) {
					if ( j >= ev.length() ) {
						result += ev;
						break;
					}
					if ( '<' == ev[j] && '>' == ev[j+1] ) {
						result.add(ev.getstr(), j);
						result += '<';
						result += &(ev.getstr()[j+2]);
						result += " or ";
						result.add(ev.getstr(), j);
						result += '>';
						result += &(ev.getstr()[j+2]);
						break;
					}
				}
			result += ')';
		}
	}
	return result;
}
