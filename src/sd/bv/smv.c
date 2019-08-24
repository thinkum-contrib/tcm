/* This file generates quick-and-dirty NuSMV output */

#include "smv.h"
#include "transition.h"
#include "initialstate.h"
#include "util.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

SMV::SMV(Graph *st) {
	graph = st;
}


SMV::~SMV() {
}


void SMV::WriteSMV(const char *filename, List<string> *internal,
			const string *formula) {
	/* Generate the data structure needed for conversion to SMV format
	   and write it to disk. */
	FILE *fp;

	fp = fopen(filename, "w");
	if ( ! fp )
		return /* False */;
	fprintf(fp, "MODULE main\n\nVAR\n-- state variables\n\tI___INITIAL : boolean ;\n");

	/* for every state, there is a variable state_<number> */
	List<Subject *> states;
	List<string> names;
	graph->GetNodes(&states, Code::INITIAL_STATE);
	graph->GetNodes(&states, Code::STATE);
	graph->GetNodes(&states, Code::DECISION_POINT);
	for ( states.first() ; ! states.done() ; states.next() ) {
		fprintf(fp, "\tstate_%d : boolean ;\n", states.cur()->GetId());
		AddNames(&names, NULL, states.cur()->GetName());
	}

	fprintf(fp, "-- event variables\n");
	/* for every event, there is a variable ev_<name> */
	List<Subject *>trans;
	List<string> evnames, externevnames;
	graph->GetEdges(&trans, Code::TRANSITION);

	for ( trans.first() ; ! trans.done() ; trans.next() ) {
		Transition *tr = dynamic_cast<Transition *>(trans.cur());
		if ( ! check(tr) )
			continue;
		AddNames(&evnames, NULL, tr->GetEvent());
		AddNames(&externevnames, NULL, tr->GetEvent());
		for ( int i = tr->NrActions() ; i-- > 0 ; ) {
			const string *act = tr->GetAction(i);
			if ( evnames.find(*act) < 0 )
				evnames.add(*act);
		}
	}
	for ( evnames.first() ; ! evnames.done() ; evnames.next() ) {
		fprintf(fp, "\tev_%s : boolean ;\n", evnames.cur().getstr());
		if ( externevnames.find(evnames.cur()) < 0 )
			internal->add(evnames.cur());
	}
	externevnames.empty();

	/* The initial state: I___INITIAL is true, all other states and events
	   are false */
	fprintf(fp, "INIT\n\tI___INITIAL");
	for ( states.first() ; ! states.done() ; states.next() )
		fprintf(fp, "\n\t& ! state_%d", states.cur()->GetId());
	for ( evnames.first() ; ! evnames.done() ; evnames.next() )
		fprintf(fp, "\n\t& ! ev_%s", evnames.cur().getstr());
	fprintf(fp, "\n");

	/* definition of propositional symbols as disjunctions of states */
	fprintf(fp, "DEFINE\n");
	for ( names.first() ; ! names.done() ; names.next() ) {
		string *name = &(names.cur());
		fprintf(fp, "\t%s := FALSE", names.cur().getstr() );
		for ( states.first() ; ! states.done() ; states.next() ) {
			const string *n = states.cur()->GetName();
			const char *found = strstr(n->getstr(), name->getstr());
			if ( found && (n->getstr() == found
					    || isspace(found[-1]))
					&& ('\0' == found[name->length()]
					    || isspace(found[name->length()])) )
				fprintf(fp,"\n\t\t| state_%d",
					states.cur()->GetId());

		}
		fprintf(fp, " ;\n");
	}
	names.empty();

	/* definition of transition enabledness as conditions on source state */
	for ( trans.first() ; ! trans.done() ; trans.next() ) {
		Transition *tr = dynamic_cast<Transition *>(trans.cur());
		if ( ! check(tr) )
			continue;
		fprintf(fp, "\ttrans_%d_enabled := state_%d", tr->GetId(),
					tr->GetSubject1()->GetId());
		List<string> events, guards;
		AddNames(&events, &guards, tr->GetEvent());
		for ( events.first() ; ! events.done() ; events.next() )
			fprintf(fp, "\n\t\t& ev_%s", events.cur().getstr());
		events.empty();
		for ( guards.first() ; ! guards.done() ; guards.next() )
			fprintf(fp, "\n\t\t& %s", guards.cur().getstr());
		guards.empty();
		fprintf(fp, " ;\n");
		fprintf(fp, "\ttrans_%d_taken := trans_%d_enabled\n"
					"\t\t& next(state_%d)",
					tr->GetId(), tr->GetId(),
					tr->GetSubject2()->GetId());
		if ( tr->GetSubject1() != tr->GetSubject2() )
			fprintf(fp, "\n\t\t& next(! state_%d)",
						tr->GetSubject1()->GetId());

		for ( int i = tr->NrActions() ; i-- > 0 ; )
			fprintf(fp, "\n\t\t& next(ev_%s)",
						tr->GetAction(i)->getstr());
		fprintf(fp, " ;\n");
	}

	/* definition of initial transition */
	fprintf(fp, "\tinit_enabled := I___INITIAL ;\n\tinit_taken := init_enabled");
	for ( states.first() ; ! states.done() && Code::INITIAL_STATE == states.cur()->GetClassType() ; states.next() ) {
		InitialState *is = dynamic_cast<InitialState *>(states.cur());
		if ( ! check(is) )
			continue;
		fprintf(fp, "\n\t\t& next(state_%d)", states.cur()->GetId());
		for ( int i = is->NrActions() ; i-- > 0 ; )
			fprintf(fp, "\n\t\t& next(ev_%s)", is->GetAction(i));
	}
	fprintf(fp, " ;\n");

	/* definition of stable state
	   (For a step semantics, change this definition to: stable := 1 ; */
	fprintf(fp,"\tstable := ! init_enabled");
	for ( trans.first() ; ! trans.done() ; trans.next() )
		fprintf(fp,"\n\t\t& ! trans_%d_enabled", trans.cur()->GetId());
	fprintf(fp, " ;\n");

	/* definition of the transition relation */
	fprintf(fp, "\nTRANS\n\tnext(! I___INITIAL)\n");

	/* if a transition is enabled, it is taken -- unless a conflicting
	   transition is taken */
	for ( trans.first() ; ! trans.done() ; trans.next() ) {
		Transition *tr = dynamic_cast<Transition *>(trans.cur());
		if ( ! check(tr) )
			continue;
		fprintf(fp, "\t& (trans_%d_enabled -> (trans_%d_taken",
					tr->GetId(), tr->GetId());
		List<Subject *> conflict;
		graph->GetEdgesFrom(&conflict, tr->GetSubject1(),
					Code::TRANSITION);
		conflict.first();
		if ( ! conflict.done() && (tr != conflict.cur()
						|| (conflict.next(),
						! conflict.done())) ) {
			fprintf(fp, " <-> ");
			for ( ;; ) {
				fprintf(fp, "! trans_%d_taken",
						conflict.cur()->GetId());
				conflict.next();
				if ( conflict.done() || (tr == conflict.cur()
							&& (conflict.next(),
							conflict.done())) )
					break;
				fprintf(fp, " & ");
			}
		}
		conflict.empty();
		fprintf(fp, "))\n");
	}
	fprintf(fp, "\t& (init_enabled -> init_taken)\n");

	/* states only change by taking an edge */
	for ( states.first() ; ! states.done() ; states.next() ) {
		List<Subject *> edges;
		graph->GetEdgesFrom(&edges, states.cur(), Code::TRANSITION);
		graph->GetEdgesTo(&edges, states.cur(), Code::TRANSITION);
		fprintf(fp, "\t& (state_%d = next(state_%d)",
					states.cur()->GetId(),
					states.cur()->GetId());
		for ( edges.first() ; ! edges.done() ; edges.next() )
			fprintf(fp, " | trans_%d_taken", edges.cur()->GetId());
		if ( Code::INITIAL_STATE == states.cur()->GetClassType() )
			fprintf(fp, " | init_taken");
		fprintf(fp, ")\n");
	}
	states.empty();

	/* internal events only happen when specific transitions are taken */
	/* other events only happen when specific transitions are taken or the
	   state is stable. */
	for ( evnames.first() ; ! evnames.done() ; evnames.next() ) {
		string *ev = &(evnames.cur());
		fprintf(fp, "\t& (next(! ev_%s)", ev->getstr());
		for ( trans.first() ; ! trans.done() ; trans.next() ) {
			Transition *tr =
				dynamic_cast<Transition *>(trans.cur());
			if ( ! check(tr) )
				continue;
			if ( tr->HasAction(ev) )
				fprintf(fp, " | trans_%d_taken", tr->GetId());
		}
		if ( ! internal->contains(*ev) )
			fprintf(fp, " | stable");
		fprintf(fp, ")\n");
	}
	trans.empty();

	/* timeouts must happen infinitely often */
	fprintf(fp, "\nFAIRNESS\n\tev_timeout\n");

	/* a timeout never happens at the same time as another event */
	evnames.first();
	if ( ! evnames.done() && ("timeout" != evnames.cur()
				|| (evnames.next(), ! evnames.done())) ) {
		fprintf(fp, "\nINVAR\n\t");
		for ( ;; ) {
				fprintf(fp, "ev_%s", evnames.cur().getstr());
			evnames.next();
			if ( evnames.done() || ("timeout" == evnames.cur()
							&& (evnames.next(),
							evnames.done())) )
				break;
			fprintf(fp, "\n\t| ");
		}
		evnames.empty();
		fprintf(fp, " -> ! ev_timeout\n");
	}

	fprintf(fp, "\nSPEC\n\t%s\n", formula->getstr());
	fclose(fp);
}


void SMV::AddNames(List<string> *names, List<string> *guards,
				const string *statename) {
	/* Extracts single words and guards from statename. */
	const char *cp = statename->getstr();
	while ( *cp ) {
		while ( *cp && isspace(*cp) )
			++cp;
		if ( ! *cp )
			break;
		const char *ep = cp;
		if ( '[' == *cp ) {
			cp++;
			while ( *++ep ) {
				if ( ']' == *ep ) {
					if ( guards ) {
						string name;
						name.add(cp, ep - cp);
						if ( guards->find(name) < 0 )
							guards->add(name);
					}
					++ep;
					break;
				}
			}
		} else {
			while ( *++ep && ! isspace(*ep) && '[' != *ep )
				;
			if ( names ) {
				string name;
				name.add(cp, ep - cp);
				if ( names->find(name) < 0 )
					names->add(name);
			}
		}
		cp = ep;
	}
}
