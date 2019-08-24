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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _TRVIEWER_H
#define _TRVIEWER_H

#include "diagramviewer.h"
class TRWindow;

/// generic textual tree viewer class.
class TRViewer: public DiagramViewer {
/*@Doc: {\large {\bf scope:} TGTT} */
public:
	///
	TRViewer(Config *c, TRWindow *w);
	///
	void Initialize();
	///
	void Draw();
	///
	void Undraw();
	///
	void UpdateTreeMode(bool newMode);
	///
	bool IsTreeMode() {return treeMode;}
	///
	void DrawTreeFork(Shape *parent, List<Shape *> *children);

	///
	void Select(int x, int y);
	///
	void Adjust(int x, int y);
	///
	void MovingPointer(int x, int y);
	///
	void KeyTyped(int x, int y, int c);
	///
	Command *Drag(int x, int y);
	///
	Command *Connect(int x, int y);

	///
	void Cut();
	///
	void Copy();
	///
	void Paste();
	///
	void DeleteAll();
	///
	void SelectAll();
	///
	void DeleteSubjects();
	///
	void SameSize();
	///
	void AlignNodes(NodeAlign::Type);
	///
	void Annotate();
	///
	void UpdateCurve();
	///
	void MoveAllShapes(Document::MoveType t);
	/// 
	void FindAll(const string *s, bool sens, bool substr, bool nameOnly);
	/// 
	void FindNext(const string *s, bool sens, bool substr, bool nameOnly);
	/// 
	void ReplaceNext(const string *s1, const string *s2,
		bool sens, bool substr, bool nameOnly);
	/// 
	void ReplaceAll(const string *s1, const string *s2,
		bool sens, bool substr, bool nameOnly);
protected:
	///
	enum DirectionType {UP, DOWN};
	///
	void DrawTreeMode();
	///
	void DrawNormalMode();
	///
	void DrawVerticalTreeFork(Shape *parent, List<Shape *> *children, 
		TRViewer::DirectionType d);
	///
	void DrawHorizontalTreeFork(Shape *parent, List<Shape *> *children, 
		TRViewer::DirectionType d);
private:
	///
	bool treeMode;
};
#endif
