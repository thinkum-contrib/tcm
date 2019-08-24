////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or 
// (at your option) any later version.
//
// TCM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "application.h"
#include "util.h"
#include "system.h"
#include "dcfwindow.h"
#include "snwindow.h"
#include <stdlib.h>

int main (int argc, char **argv) {
	Application *app = new Application(Toolkit::TOOLKIT_NAME);

	strcpy(System::currentProgram, argv[0]);
	System::SetSignalHandler();
	char *prog;
	char *p = strrchr(argv[0], '/');
	if (p == 0)
		prog = strdup(argv[0]);
	else
		prog = strdup(++p);
	if (equal(prog, "tdfd"))
		new DFWindow(Toolkit::TOOLKIT_NAME);
	else if (equal(prog, "tefd"))
		new DCFWindow(Toolkit::TOOLKIT_NAME);
	else if (equal(prog, "tsnd"))
		new SNWindow(Toolkit::TOOLKIT_NAME);
	else {
		error("%s: unknown tool\n", prog);
		exit(1);
	}
	// Make sure the programmer has remembered to 
	// instantiate an Application object
	if (!check (theApplication))
		return 1;
	free(prog);
	// Init Intrinsics, build all windows, and enter event loop
	theApplication->Initialize (argc, argv);
	theApplication->HandleEvents();
}
