#include "eventset.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

List<string> EventSet::EventNames;

EventSet::EventSet() {
	memset(EventFlag, '\0', sizeof(EventFlag));
}


unsigned EventSet::add(const string &event) {
	string e(event);
	while ( isspace(e[0]) )
		e.remove(0);
	while ( isspace(e[e.length() - 1]) )
		e.remove();
	int i = EventNames.find(e);
	if ( i < 0 ) {
		i = EventNames.count();
		if ( i >= MAX_EVENTS ) {
			printf("Error: Maximum number of events reached.\n");
			exit(1);
		}
		EventNames.add(e);
	}
	EventFlag[i >> 3] |= 0200 >> (i & 07);
	return i;
}


void EventSet::sub(string event) {
	while ( isspace(event[0]) )
		event.remove(0);
	while ( isspace(event[event.length() - 1]) )
		event.remove();
	int i = EventNames.find(event);
	if ( i >= 0 )
		EventFlag[i >> 3] &= ~(0200 >> (i & 07));
}


void EventSet::clear() {
	for ( int i = (MAX_EVENTS + 7) / 8 ; --i >= 0 ; )
		EventFlag[i] = 0;
}


bool EventSet::HasEvent(string event) const {
	while ( isspace(event[0]) )
		event.remove(0);
	while ( isspace(event[event.length() - 1]) )
		event.remove();
	int i = EventNames.find(event);
	return i >= 0 && 0 != (EventFlag[i >> 3] & 0200 >> (i & 07));
}


unsigned EventSet::count() const {
	unsigned result = 0;
	for ( int i = (MAX_EVENTS + 7) / 8 ; --i >= 0 ; ) {
		register int flag = EventFlag[i];
		if ( flag & 0200 ) ++result;
		if ( flag & 0100 ) ++result;
		if ( flag &  040 ) ++result;
		if ( flag &  020 ) ++result;
		if ( flag &  010 ) ++result;
		if ( flag &   04 ) ++result;
		if ( flag &   02 ) ++result;
		result += flag & 01;
	}
	return result;
}


bool EventSet::empty() const {
	for ( int i = (MAX_EVENTS + 7) / 8 ; --i >= 0 ; )
		if ( EventFlag[i] )
			return False;
	return True;
}


const string &EventSet::operator[](int index) const {
	if ( index >= 0 )
		for ( int i = 0 ; i < MAX_EVENTS ; i++ )
			if ( EventFlag[i >> 3] & 0200 >> (i & 07)
			     && --index < 0 )
				return EventNames[i];
	return string::EMPTY;
}

bool EventSet::first() {
	current = 0;
	while ( 0 == (EventFlag[current >> 3] & 0200 >> (current & 07)) )
		if ( ++current >= MAX_EVENTS ) {
			current = -1;
			return False;
		}
	return True;
}

bool EventSet::last() {
	current = MAX_EVENTS;
	return prev();
}

bool EventSet::next() {
	if ( current >= 0 )
		do
			if ( ++current >= MAX_EVENTS ) {
				current = -1;
				return False;
			}
		while ( 0 == (EventFlag[current >> 3] & 0200 >> (current & 07)) );
	return True;
}

bool EventSet::prev() {
	if ( current >= 0 )
		do
			if ( --current < 0 )
				return False;
		while ( 0 == (EventFlag[current >> 3] & 0200 >> (current & 07)) );
	return True;
}

void EventSet::print() {
	for ( int i = EventNames.count() ; i != 0 ; ) {
		--i;
		printf("%c%s ",
			EventFlag[i >> 3] & 0200 >> (i & 07) ? '+' : '-',
			EventNames[i].getstr());
	}
}


string EventSet::GetEvents(const char *prefix /* = NULL */) const {
	/* calculates a string composed of all the events, without guards */
	string result;
	for ( int i = EventNames.count() ; i != 0 ; ) {
		--i;
		const string *str = &EventNames[i];
		if ( EventFlag[i >> 3] & 0200 >> (i & 07) &&
		     ('[' != (*str)[0] || ']' != (*str)[str->length() - 1]) ) {
			if ( result.length() )
				result += ' ';
			if ( prefix )
				result += prefix;
			result += *str;
		}
	}
	return result;
}


string EventSet::GetGuards() const {
	/* calculates a string composed of all the guards */
	string result;
	for ( int i = EventNames.count() ; i != 0 ; ) {
		--i;
		const string *str = &EventNames[i];
		if ( '[' == (*str)[0] && ']' == (*str)[str->length() - 1] &&
		    EventFlag[i >> 3] & 0200 >> (i & 07) ) {
			if ( result.length() )
				result += " and ";
			result += '(';
			result.add(str->getstr() + 1, str->length() - 2);
			result += ')';
		}
	}
	return result;
}
