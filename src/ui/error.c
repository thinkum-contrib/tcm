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
#include "error.h"
#include "application.h"
#include "messagelogdialog.h"
#if defined(LINUX) || defined(__CYGWIN__)
#include <stdio.h>
#endif
#include <stdarg.h>

void error(const char *fmt ...) {
	// we're not getting huge strings
	char msgbuf[BUFSIZ];
	va_list args;
 
	va_start(args, fmt);
#ifndef NO_VPRINTF
	(void) vsprintf(msgbuf, fmt, args);
#else // !NO_VPRINTF
	FILE foo;
	foo._cnt = BUFSIZ;
	foo._base = foo._ptr = msgbuf; // (unsigned char *) ??
	foo._flag = _IOWRT+_IOSTRG;
	(void) _doprnt(fmt, args, &foo);
	*foo._ptr = '\0'; // plant terminating null character
#endif // NO_VPRINTF
	va_end(args);

	bool allocmsg = (strstr(msgbuf, "Cannot allocate colormap entry") != 0);
	if (allocmsg) {
		theApplication->CreatePrivateColormap();
		return;
	}
	if (theApplication->Initialized()) {
#ifdef DEBUG
		std::cerr << msgbuf << std::endl;
#endif
		MessageLogDialog *log = theApplication->GetMessageLogDialog();
		log->InsertText(msgbuf);
		log->Popup();
	}
	else 
		std::cerr << msgbuf << std::endl;
}
