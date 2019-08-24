//-----------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _COMMAND_H
#define _COMMAND_H

#include "viewer.h"

/// (abstract) undo-able command class.
class Command {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// 
	Command(Document *d, Viewer *v);
	///
	virtual ~Command();

	///
	enum TrackType {TRACK_PRESS, TRACK_DRAG, TRACK_RELEASE, TRACK_UP};

	/// Called while mouse button is pressed dragged and released.
	virtual void TrackMouse(TrackType, Point*, Point*, Point*) {}

	/// Perform the command.
	virtual void Execute();

	/// Undo the command.
	virtual void UnExecute();

	/// Redo the command.
	virtual void ReExecute() {Execute();}

	/// Abort the command.
	virtual void Abort();

	/// command is executed.
	bool CmdDone() const {return cmdDone;}

	///
	virtual const char *GetName() const {return "unknown command";}

	///
	double ScaleCorrect(double x) const {return viewer->ScaleCorrect(x);}
	///
	Point ScaleCorrect(const Point *pt) const {
		return viewer->ScaleCorrect(pt);}
	///
	double Scale(double x) const {return viewer->Scale(x);}
	///
	Point Scale(const Point *pt) const {return viewer->Scale(pt);}
	///
	void SayAborted();
protected:
	///
	void SayCommited(); 
	///
	void SayUndone();
	///
	DrawWindow *GetMainWindow() const {return mainwindow;}
	///
	Viewer *GetViewer() const {return viewer;}
	///
	Document *GetDocument() const {return document;}
	///
	Grafport *GetGrafport() const {return grafport;}
	///
	void SetCmdDone(bool b) {cmdDone=b;}
private:
	///
	bool cmdDone;
	///
	Document *document;
	///
	Viewer *viewer;
	///
	DrawWindow *mainwindow;
	///
	Grafport *grafport;
};
#endif
