#include "ktransition.h"
#include "klocation.h"
#include <ctype.h>

KTransition::KTransition(unsigned c): Vector<Subject *>(c) {
	while ( c )
		(*this)[--c] = NULL;
	InputTransition = False;
	to = NULL;
}


bool KTransition::operator< (const KTransition &comp) const {
	if ( InputTransition < comp.InputTransition )
		return True;
	if ( InputTransition > comp.InputTransition )
		return False;
	if ( (char *)to - (char *)comp.to < 0 )
		return True;
	if ( (char *)to - (char *)comp.to > 0 )
		return False;
	return Vector<Subject *>::operator< (comp);
}


unsigned IsClockReset(const string &s) {
	/* returns 0, if the string s doesn't contain a clock reset action.
	   Otherwise, returns the number of characters which make up the
	   clock name. */
	unsigned u = s.length();
	const char *cp = s.getstr() + u;
	/* cp will be == &s.getstr()[u] during the largest part of the
           function: */
	do
		if ( u < 4 )
			return 0U;
	while ( --u, --cp, isspace(*cp) );
	if ( '0' != *cp )
		return 0U;
	while ( --u, --cp, isspace(*cp) )
		if ( u < 3 )
			return 0U;
	if ( '=' != *cp || ':' != (--u, *--cp) )
		return 0U;
	while ( --cp, isspace(*cp) && --u )
		;
	return u;
}


string KTransition::GetEvents() const {
	/* returns a string consisting of the actions in the transitions which
	   are the components of this KTransition. */
	string result;
	for ( int i = count() ; --i >= 0 ; ) {
		Transition *tp = dynamic_cast<Transition *>((*this)[i]);
		if ( NULL != tp )
			for ( unsigned j = 0 ; j < tp->NrActions() ; ++j ) {
				const string *actp = tp->GetAction(j);
				if ( ! IsClockReset(*actp) ) {
					if ( result.length() )
						result += ' ';
					result += *actp;
				}
			}
	}
	return result;
}


string KTransition::GetGuards() const {
	return to->inputset.GetGuards();
}


string KTransition::GetClockResets() const {
	string result(InputTransition ? "t" : ""); // ('t');
	for ( int i = count() ; --i >= 0 ; ) {
		Transition *tp = dynamic_cast<Transition *>((*this)[i]);
		if ( NULL != tp )
			for ( unsigned j = 0 ; j < tp->NrActions() ; ++j ) {
				const string *actp = tp->GetAction(j);
				if ( unsigned u = IsClockReset(*actp) ) {
					if ( result.length() )
						result += ' ';
					result.add(*actp, u);
				}
			}
	}
	return result;
}
