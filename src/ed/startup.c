//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------

#include "application.h"
#include "startupwindow.h"
#include "util.h"
#include "system.h"
#include "toolkit.h"

int main (int argc, char **argv) {
	new Application(Toolkit::TOOLKIT_NAME);
	new StartupWindow(Toolkit::TOOLKIT_NAME);

	System::SetSignalHandler();

	// Make sure the programmer has remembered to 
	// instantiate an Application object

	if (!check(theApplication))
		return 1;

	// Initialize intrinsics, build all windows
	theApplication->Initialize (argc, argv);

	// enter event loop
	theApplication->HandleEvents();

	// never reached.
	return 0;
}
