/* This file generates quick-and-dirty NuSMV output */

#include "llist.h"
#include "lstring.h"
#include "graph.h"

class SMV {
public:
	SMV(Graph *st);
	~SMV();

	void WriteSMV(const char *filename, List<string> *internal,
				const string *formula);
private:
	static void AddNames(List<string> *names, List<string> *guards,
				const string *statename);
	Graph *graph;
};
