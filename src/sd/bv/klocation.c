#include "klocation.h"
#include <string.h>
#include <ctype.h>

KLocation::KLocation(unsigned c)
:Vector<Subject *>(c),
inputset(),
number(0),
transSet(),
Transient(False) {
}


KLocation::~KLocation() {
}


KLocation::KLocation(const KLocation &copy)
:Vector<Subject *>(copy),
inputset(copy.inputset),
number(copy.number),
transSet(copy.transSet),
Transient(copy.Transient) {
	/* makes deep copies of the lists, but shallow copies of the Subject
	   pointers. However, the PtrSet copying makes deep copies. */
}


KLocation::KLocation(const List<Subject *> &copy)
:Vector<Subject *>(copy),
inputset(),
number(0),
transSet(),
Transient(False) {
}


bool KLocation::operator==(const KLocation &comp) const {
	if ( count() != comp.count() )
		return False;
	for ( int i = count() ; --i >= 0 ; )
		if ( (*this)[i] != comp[i] )
			return False;
	return inputset == comp.inputset;
}


bool KLocation::operator<(const KLocation &comp) const {
	if ( count() != comp.count() )
		return count() < comp.count();
	for ( int i = count() ; --i >= 0 ; )
		if ( (*this)[i] != comp[i] )
			return (char *)((*this)[i]) - (char *)(comp[i]) < 0;
	return inputset < comp.inputset;
}


bool KLocation::HasProp(const string &prop) const {
	/* Checks whether this KLocation has the property prop. */
	for ( int i = count() ; --i >= 0 ; ) {
		const char *cp = (*this)[i]->GetName()->getstr();
		while ( *cp ) {
			while ( *cp && isspace(*cp) )
				++cp;
			if ( ! *cp )
				break;
			const char *ep = cp;
			if ( '[' == *cp ) {
				while ( *++ep )
					if ( ']' == *ep ) {
						++ep;
						break;
					}
			} else {
				while ( *++ep && ! isspace(*ep) && '[' != *ep )
					;
				if ( memcmp(cp, prop.getstr(), ep - cp) == 0 )
					return True;
			}
			cp = ep;
		}
	}
	return False;
}


string KLocation::GetProp() const {
	string result = inputset.GetEvents("I_");
	for ( int i = count() ; --i >= 0 ; ) {
		const char *cp = (*this)[i]->GetName()->getstr(), *bp;
		while ( *cp ) {
			bp = strchr(cp, '[');
			if ( bp != cp ) {
				if ( result.length() )
					result += ' ';
				result.add(cp, bp ? bp - cp : 0);
				if ( ! bp )
					break;
			}
			cp = bp + 1;
			bp = strchr(cp, ']');
			if ( ! bp )
				break;
			cp = bp + 1;
		}
	}
	char *cp = const_cast<char *>(result.getstr());
	for ( int i = result.length() ; --i >= 0 ; )
		if ( isspace(cp[i]) )
			cp[i] = ' ';
	return result;
}


string KLocation::GetInvar() const {
	string result = inputset.GetGuards();
	if ( Transient ) {
		if ( result.length() )
			result += " and t=0";
		else
			result = "t=0";
	}
	for ( int i = count() ; --i >= 0 ; ) {
		const char *cp = (*this)[i]->GetName()->getstr(), *bp;
		while ( *cp ) {
			bp = strchr(cp, '[');
			if ( ! bp )
				break;
			cp = bp + 1;
			bp = strchr(cp, ']');
			if ( bp != cp ) {
				if ( result.length() )
					result += " and ";
				result += '(';
				result.add(cp, bp ? bp - cp : 0);
				result += ')';
				if ( ! bp )
					break;
			}
			cp = bp + 1;
		}
	}
	char *cp = const_cast<char *>(result.getstr());
	for ( int i = result.length() ; --i >= 0 ; )
		if ( isspace(cp[i]) )
			cp[i] = ' ';
	return result;
}
