/* What concerns deep and shallow copies: a tree owns its members, so a copy
   constructor for a tree needs to make a deep copy. A list doesn't own its
   members, so a shallow copy is enough. */

#include "kronos.h"
#include "ktransition.h"
#include "graph.h"
#include "transition.h"
#include "initialstate.h"
#include <ctype.h>

void Kronos::GenerateKronos(List<string> *internal) {
	/* Generate the data structure needed for conversion to Kronos
	   format. */
	locpList.empty(); /* empty list, but don't delete the elements */
	locpSet.clear(); /* empty set and delete elements */
	LocationNumber = TransitionNumber = 0;

	List<Subject *> initStates;
	diagram->GetGraph()->GetNodes(&initStates, Code::INITIAL_STATE);
	ComponentNumber = initStates.count();
	SaveLocation(new KLocation(initStates));
	if ( locpList.first() )
		do
			if ( ! HandleEvents(locpList.cur()) )
				GenerateEvents(locpList.cur(), internal);
		while ( locpList.next() );
}


bool Kronos::HandleEvents(KLocation *locp) {
	/* Look at the inputset attribute of *locp. Choose the
	   possible transitions; insert the transitions and
	   locations found into the data structure.
	   Returns true if some transition has been added. */
	Vector<TransPList> translist(ComponentNumber);
	LookForTransitions(locp, &translist);

	if ( ! FirstTransition(&translist) )
		return False;

	locp->Transient = True;
	do {
		KTransition *trans = new KTransition(locp->count());
		KLocation *goal = new KLocation(locp->count());
		for ( unsigned i = locp->count() ; i != 0 ; ) {
			--i;
			(*goal)[i] = (*locp)[i];
		}
		for ( unsigned i = locp->count() ; i != 0 ; )
			if ( ! translist[--i].done() ) {
				Transition *tp = translist[i].cur();
				(*trans)[i] = tp;
				(*goal)[i] = tp->GetSubject2();
				for (unsigned j = tp->NrActions() ; j > 0 ; ) {
					const string *actp = tp->GetAction(--j);
					if ( ! IsClockReset(*actp) )
						goal->inputset.add(*actp);
				}
			}
		trans->InputTransition = False;
		trans->to = SaveLocation(goal);
		SaveTransition(locp, trans);
	} while ( NextTransition(&translist) );
	return True;
}


void Kronos::LookForTransitions(const KLocation *locp, Vector<TransPList> *transp) {
	/* Look for transitions from the components of loc. The transitions are
	   saved in *transp, for each component of loc a different list. */
	for ( int i = locp->count() ; --i >= 0 ; ) {
		TransPList &ltp = (*transp)[i];
		/* find all edges departing from (*locp)[i] */
		diagram->GetGraph()->GetEdgesFrom(reinterpret_cast<List<Subject *> *>(&ltp), (*locp)[i]);
		/* check which edges are possible according to the event set */
		for ( ltp.first() ; ! ltp.done() ; )
			if ( ! CheckEvents(locp, *ltp.cur()->GetEvent()) )
				ltp.removecur();
			else
				ltp.next();
	}
}


bool Kronos::FirstTransition(Vector<TransPList> *transp) {
	/* Makes the first elements of *transp the current ones.
	   To be used in connection with NextTransition().
	   Returns false iff there are no transitions. */
	bool result = False;
	for ( unsigned i = transp->count() ; i != 0 ; )
		result |= (*transp)[--i].first();
		/* because of side effects of first(), you can't return as soon
		   as first() returns True. So, it's |=, not ||=.*/
	return result;
}


bool Kronos::NextTransition(Vector<TransPList> *transp) {
	/* Advances the current elements of *transp to point to the next
	   transition (in the lexicographic order). Returns false iff there
	   are no more transitions. */
	for ( unsigned i = transp->count() ; i != 0 ; ) {
		if ( (*transp)[--i].next() )
			return True;
		(*transp)[i].first();
	}
	return False;
}


void Kronos::GenerateEvents(KLocation *locp, List<string> *internal) {
	/* Generate input transitions departing from location loc.
	   All elements of internal are considered internal events.
	   (The procedure is intended for locations without hanging events,
	   i.e. locations where HandleEvents doesn't find any transitions.) */
	EventSet allinput;
	int i;

	locp->Transient = False;
	for ( i = locp->count() ; --i >= 0 ; ) {
		TransPList edgelist;
		diagram->GetGraph()->GetEdgesFrom(reinterpret_cast<List<Subject *> *>(&edgelist), (*locp)[i]);
		if ( edgelist.first() )
			do
				AddEvents(&allinput, *edgelist.cur()->GetEvent(), internal);
			while ( edgelist.next() );
	}
	/* allinput = set of all relevant input events.
	   So, let's add a transition for every subset of it. */
	for ( i = 1 << allinput.count() ; --i > 0 ; ) {
		KLocation *newlocp = new KLocation(locp->count());
		for ( unsigned j = locp->count() ; j != 0 ; ) {
			--j;
			(*newlocp)[j] = (*locp)[j];
		}
		newlocp->inputset.SetRelevant(allinput);
		allinput.first();
		for ( int j = i ; j != 0 ; j >>= 1, allinput.next() )
			if ( j & 1 )
				newlocp->inputset.add(allinput.cur());
		newlocp = SaveLocation(newlocp);
		KTransition *newtrans = new KTransition(ComponentNumber);
		newtrans->InputTransition = True;
		newtrans->to = newlocp;
		SaveTransition(locp, newtrans);
	}
}


void Kronos::AddEvents(EventSet *input, const string &events,
		List<string> *internal) const
{
	/* Chops events into single events. -- Clock constraints (contain one
	   of the characters > < =) are handled similar to events; however,
	   other guards are ignored. */
	const char *cp = events.getstr();
	while ( *cp ) {
		while ( *cp && isspace(*cp) )
			++cp;
		if ( ! *cp )
			break;
		const char *ep = cp;
		bool ignore;
		if ( '[' == *cp ) {
			ignore = True;
			while ( *++ep ) {
				if ( ']' == *ep ) {
					++ep;
					break;
				}
				if ( '<' == *ep || '>' == *ep || '=' == *ep )
					/* It's a clock constraint, not a
					   guard */
					ignore = False;
			}
		} else {
			while ( *++ep && ! isspace(*ep) && '[' != *ep )
				;
			ignore = ep - cp > 2 && 'i' == cp[0] && '.' == cp[1];
		}
		if ( ! ignore ) {
			/* ignore events starting with ``i.'' and guards */
			string event;
			event.add(cp, ep - cp);
			if ( internal->find(event) < 0 )
				input->add(event);
		}
// else { fprintf(stderr, "%*s ignored. ", (int)(ep - cp), cp); } /*DEBUG*/
		cp = ep;
	}
}


bool Kronos::CheckEvents(const KLocation *locp, const string &events) const {
	/* Tests whether the single events which make up events are contained
	   in the inputset of *locp. Also checks whether the guards in events
	   are true in *locp. */
	const char *cp = events.getstr();
	while ( *cp ) {
		while ( *cp && isspace(*cp) )
			++cp;
		if ( ! *cp )
			break;
		const char *ep = cp;
		bool guard;
		if ( '[' == *cp ) {
			guard = True;
			while ( *++ep ) {
				if ( ']' == *ep ) {
					++ep;
					break;
				}
				if ( '<' == *ep || '>' == *ep || '=' == *ep )
					/* It's a clock constraint, not a
					   guard */
					guard = False;
			}
		} else {
			guard = False;
			while ( *++ep && ! isspace(*ep) && '[' != *ep )
				;
			if ( ep - cp > 2 && 'i' == cp[0] && '.' == cp[1] )
				cp += 2;
		}
		if ( guard ) {
			string event;
			event.add(cp + 1, ep - cp - 2);
			if ( ! locp->HasProp(event) )
				return False;
		} else {
			string event;
			event.add(cp, ep - cp);
			if ( ! locp->inputset.HasEvent(event) )
				return False;
		}
		cp = ep;
	}
	return True;
}


KLocation *Kronos::SaveLocation(KLocation *locp) {
	/* Saves the location in the structure of locations. If it exists
	   already, this procedure deletes *locp and returns a pointer to the
	   already-existing copy. Otherwise, it returns locp. */
	KLocation *result = locpSet.search(locp, SInsert);
	if ( NULL != result ) {
		delete locp;
		return result;
	}
// fprintf(stderr, "Location %lu added.\n", /*DEBUG*/
	locp->number = ++LocationNumber
// )
	;
	locpList.add(locp);
	return locp;
}


KTransition *Kronos::SaveTransition(KLocation *locp, KTransition *transp) {
	/* Saves the transition in the structure of transitions. If it exists
	   already, this procedure deletes *transp and returns a pointer to the
	   already-existing copy. Otherwise, it returns transp. */
	/* Well, this procedure does a little bit too much. It would be enough
	   to just store the transition, as no transition is generated more
	   than once (this is different for the locations). -- If we would
	   produce the output immediately, on the fly, it would even become
	   superfluous to save the transitions. */
	KTransition *result = locp->transSet.search(transp, SInsert);
	if ( NULL != result ) {
		delete transp;
		return result;
	}
// fprintf(stderr, "  Transition %lu added.\n", /*DEBUG*/
	++TransitionNumber
// )
	;
	return transp;
}

/*-------------------------*/
/* Second phase procedures */

void Kronos::SaveKronos(const char *filename, const char *clock) {
	/* Save the generated data structure in Kronos format. */
	if ( (fp = fopen(filename, "w")) == NULL )
		return /* False */;
	fprintf(fp, "#locs %ld\n", LocationNumber + 1L);
	fprintf(fp, "#trans %ld\n", TransitionNumber + 1L);
	fprintf(fp, "#clocks t %s\n", clock);
	fprintf(fp, "#sync\n\n");
	fprintf(fp, "loc: 0\n");
	fprintf(fp, "prop: init\n");
	fprintf(fp, "invar: t=0\n");
	fprintf(fp, "trans:\n");
	if ( locpList.first() ) {
		/* print initialization actions */
		fprintf(fp, "true=>%s;reset{%s};goto 1\n\n",
			GetInitialActions(locpList.cur()).getstr(),
			GetInitialClockResets(locpList.cur()).getstr());
		do
			PrintLocation(locpList.cur());
		while ( locpList.next() );
	}
	fclose(fp);
}


string Kronos::GetInitialActions(KLocation *init) const {
	string result;
	for ( int i = init->count() ; --i >= 0 ; ) {
		InitialState *ip = dynamic_cast<InitialState *>((*init)[i]);
		if ( NULL != ip )
			for ( unsigned j = 0 ; j < ip->NrActions() ; ++j ) {
				const string *actp = ip->GetAction(j);
				if ( ! IsClockReset(*actp) ) {
					if ( result.length() )
						result += ' ';
					result += *actp;
				}
			}
	}
	return result;
}


string Kronos::GetInitialClockResets(KLocation *init) const {
	string result('t');
	for ( int i = init->count() ; --i >= 0 ; ) {
		InitialState *ip = dynamic_cast<InitialState *>((*init)[i]);
		if ( NULL != ip )
			for ( unsigned j = 0 ; j < ip->NrActions() ; ++j ) {
				const string *actp = ip->GetAction(j);
				if ( unsigned u = IsClockReset(*actp) ) {
//					if ( result.length() )
						result += ' ';
					result.add(*actp, u);
				}
			}
	}
	return result;
}


void Kronos::PrintLocation(KLocation *locp) {
	/* prints one KLocation to the file *fp. */
	string invar = locp->GetInvar();
	fprintf(fp, "loc: %ld\nprop: %s\ninvar: %s\ntrans:\n", locp->number,
		locp->GetProp().getstr(),
		invar.length() ? invar.getstr() : "true");
	if ( locp->transSet.first() )
		do
			PrintTransition(locp->transSet.cur(), invar);
		while ( locp->transSet.next() );
	fputc('\n', fp);
}


//void Kronos::SplitPropInvar(const string &event, string *propp, string *invarp, const char *prefix /* = NULL */) {
//	/* splits the event in parts which express properties and parts which
//	   express invariants. In front of every property, the procedure adds
//	   the specified prefix. */
//	if ( ! event.length() )
//		return;
//	if ( propp->length() )
//		*propp += ' ';
//	string *addto = propp;
//	bool addprefix = True;
//	for ( const char *cp = event.getstr() ; *cp ; ++cp )
//		switch( *cp ) {
//		case ' ':
//		case '\t':
//		case '\n':
//		case '\r':
//			*addto += ' ';
//			addprefix = (addto == propp);
//			break;
//		case '[':
//			addto = invarp;
//			if ( cp[1] != ']' ) {
//				if ( invarp->length() )
//					*invarp += " and ";
//				*invarp += '(';
//				addprefix = False;
//			} else
//				++cp;
//			break;
//		case ']':
//			addto = propp;
//			if ( propp->length() )
//				*propp += ' ';
//			*invarp += ')';
//			addprefix = True;
//			break;
//		default:
//			if ( addprefix && NULL != prefix ) {
//				*addto += prefix;
//				addprefix = False;
//			}
//			*addto += *cp;
//			break;
//		}
//}


void Kronos::PrintTransition(KTransition *transp, const string &invar) {
	/* prints one KTransition to the file *fp. */
	string guard = transp->GetGuards();
	if ( guard.length() && invar.length() )
		guard += " and ";
	guard += invar;
	/* TBD: de string event bevat soms bepaalde events twee keer; dat is
	   niet nodig. Wel nodig is het dat je uit beide bronnen events haalt,
	   want er zijn gevallen waarin geen van de twee een subset van de andere
	   is. */
	string event = transp->InputTransition ? transp->to->inputset.GetEvents() : transp->GetEvents();
//	string event = transp->GetEvents();
//	if ( event.length )
//		event += ' ';
//	event += transp->to->inputset.GetEvents();
	fprintf(fp, "%s=>%s;reset{%s};goto %ld\n",
		guard.length() ? guard.getstr() : "true",
		event.getstr(),
		transp->GetClockResets().getstr(), transp->to->number);
}
