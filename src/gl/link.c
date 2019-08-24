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
//
// Adapted from the book "Motif Programming, The Essentials...and More"
// by Marshall Brain.
// Published by Digital Press, ISBN 1-55558-089-0.
// To order the book, call 1-800-DIGITAL and ask for EY-J816E-DP.
// 
// Copyright 1992, by Digital Equipment Corp.
// 
// This is the implementation of the link library. 
//
#include "link.h"
#if defined(__CYGWIN__)
#include <asm/socket.h> // for FIONREAD.
#endif
#if defined(LINUX)
#include <termios.h> // for FIONREAD.
#elif defined(HPUX) || defined(AIX) || defined(OSF1) || defined(__CYGWIN__)
#include <sys/ioctl.h>
#else
#include <sys/filio.h>
#endif
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void Link::Open(const char *name, const char *param) {
	pipe(pipefd1);
	pipe(pipefd2);
	if((pid = fork()) == 0) { // child
		close(pipefd1[0]);
		close(1);
		dup(pipefd1[1]);
		close(2);	// 2 new lines
		dup(pipefd1[1]);
		close(pipefd2[1]);
		close(0);
		dup(pipefd2[0]);
		execlp(name, name, param, (char *)0);
	}
	else {
		fpin = fdopen(pipefd1[0], "r");
		fpout = fdopen(pipefd2[1], "w");
		close(pipefd1[1]); 
		close(pipefd2[0]); 
	}
}

void Link::Close() {
	// wait((union wait *) 0);
	wait(0);
	close(pipefd1[1]);
	close(pipefd2[0]);
	fclose(fpin);
	fclose(fpout);
	pid=0;
}

int Link::Read(char *s) {
	int eof_flag;
	if (fgets(s, 100, fpin) == 0)
		eof_flag = 1;  
		// linked-to process has terminated on its own.
	else {
		s[strlen(s)-1] = '\0'; // lose the newline character.
		eof_flag = 0;
	}
	return(eof_flag);
}

int Link::InputWaiting() {
	int num;
	ioctl(pipefd1[0], FIONREAD, &num); // see how many chars in buffer.
	return num;
}

void Link::WriteChar(char c) {
	fprintf(fpout, "%c", c);
	fflush(fpout);
}

void Link::Write(const char *s) {
	fprintf(fpout, "%s\n", s);
	fflush(fpout);
}

void Link::Kill() {
	kill(pid, SIGKILL);
	Close();
}
