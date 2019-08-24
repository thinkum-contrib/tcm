//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _LINK_H
#define _LINK_H
//
// link.h: link between separately executing programs.
//
// Adapted from the book "Motif Programming, The Essentials...and More"
// by Marshall Brain.
// Published by Digital Press, ISBN 1-55558-089-0.
// To order the book, call 1-800-DIGITAL and ask for EY-J816E-DP.
// 
// Copyright 1992, by Digital Equipment Corp.
// 
// This module allows a program to form links to other separately
// executing programs and communicate with them. Links can be
// opened and closed, and the program using this library can 
// write to and read from the other program over the link.
//
// Warning -
// This module will not link with all programs. If the program
// does anything weird with stdout, or if it fails to flush
// stdout correctly, then this module will fail. If you are creating
// a stand-alone program that you wish to link to another program
// with this library, then you MUST make sure that stdout is
// flushed correctly. Either call "fflush(stdout)" after every
// printf, or call "setbuf(stdout,0)" at the beginning of the
// program to eliminate buffering.
//
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/ioctl.h>

/// holds all info relevant to one link.
class Link {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// open a link to another program named name, passing a param
	// to the program if desired. This routine will execute name
	// in parallel and you can start communicating with it with
	// Read and Write.
	void Open(const char* name, const char* param);

	/// Close the link to a program that has terminated. Use Kill
	// if the program needs to be terminated as well.
	void Close();

	/// read from the program started with Open. Returns a 0 if
	// there was stuff to read, or a 1 if the linked program terminated.
	int Read(char* s);

	/// Returns the number of bytes waiting in the input buffer. If
	// 0, then Read will block if it is called.
	int InputWaiting();

	/// write a char, without a newline, to the program.
	void WriteChar(char c);

	/// write a string to the program, with a newline.
	void Write(const char* s);

	/// kill the program and close the link. If the program has terminated
	// on its own use Close instead.
	void Kill();
private:
	///
	int pipefd1[2];
	///
	int pipefd2[2];
	///
	int pid;
	///
	FILE* fpin;
	///
	FILE* fpout;
};
#endif
