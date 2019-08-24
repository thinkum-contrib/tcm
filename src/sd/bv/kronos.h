#ifndef _KRONOS_H
#define _KRONOS_H

#include <stdio.h>
#include "llist.h"
#include "stdiagram.h"
#include "transition.h"
#include "klocation.h"
#include "ptrset.h"
#include "lvector.h"

class Kronos {
public:
	typedef List<Transition *> TransPList;

	Kronos(STDiagram *d): LocationNumber(0), TransitionNumber(0), ComponentNumber(0), locpSet(), locpList() {
		diagram = d;
	};
	~Kronos(void) {};

	// eerste fase: de datastructuur (het product) construeren.
	void GenerateKronos(List<string> *internal);
	bool HandleEvents(KLocation *locp);
	void LookForTransitions(const KLocation *locp, Vector<TransPList> *transp);
	bool FirstTransition(Vector<TransPList> *transp);
	bool NextTransition(Vector<TransPList> *transp);
	void AddEvents(EventSet *input, const string &events, List<string> *internal) const;
	bool CheckEvents(const KLocation *locp, const string &events) const;
	void GenerateEvents(KLocation *locp, List<string> *internal);
	KLocation *SaveLocation(KLocation *locp);
	KTransition *SaveTransition(KLocation *locp, KTransition *transp);

	// tweede fase: de geconstrueerde structuur opslaan.
	void SaveKronos(const char *filename, const char *clock);
	string GetInitialActions(KLocation *init) const;
	string GetInitialClockResets(KLocation *init) const;
	void PrintLocation(KLocation *locp);
	void PrintTransition(KTransition *transp, const string &invar);
private:
	unsigned long LocationNumber;
	unsigned long TransitionNumber;
	unsigned ComponentNumber;
	STDiagram *diagram;
	PtrSet<KLocation> locpSet;
	List<KLocation *> locpList;
	FILE *fp;
};

#endif
