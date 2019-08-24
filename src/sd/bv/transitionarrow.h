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
#ifndef _TRANSITION_ARROW_H
#define _TRANSITION_ARROW_H

#include "line.h"

/// arrow having extra horiz. line separating event and list of actions (STD).
class TransitionArrow: public Line {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	TransitionArrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	TransitionArrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	TransitionArrow(const TransitionArrow &line);
	///
	virtual ~TransitionArrow();
	///
	Shape *Clone() {return new TransitionArrow(*this);}
	///
	int GetClassType() const {return Code::TRANSITION_ARROW;}
	///
	bool InTextArea(int x, int y); 
	///
	TextShape *HitTextShape(int x, int y);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;
	///
	bool ContainsPt(int x, int y);
	///
	void SetSelect(bool s);
	///
	bool HitHLine(int x, int y);
	///
	const Point *GetHLineFrom() const {return &hlineFrom;}
	///
	const Point *GetHLineTo() const {return &hlineTo;}
	///
	void UpdateAnchor(const Point *delta, const Point *position);
	///
	void UpdateEvent(const string *s);
	///
	void UpdateAction(const string *s, unsigned n, bool update);
	///
	void CalcPosition();
	/// as line, but event and actions are also considered.
	int GetLeftMost() const; 
	///
	int GetTopMost() const;
	///
	int GetRightMost() const;
	///
	int GetBottomMost() const;
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	///
	void SetTextColor(const string *color);
	///
	void SetFont(XFont *ft);
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	///
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasNameString(const string *, bool, bool) const{return False;}
	///
	bool HasString(const string*, bool, bool, List<TextShape *> *);
	///
	enum SepType {LEFT, RIGHT, UP, DOWN}; 
	///
	void MoveRaw(const Point *delta);
private:
	///
	TextShape *event;
	///
	List<TextShape *> *actions;
	///
	Point hlineFrom;
	///
	Point hlineTo;
	///
	Point anchorPoint;
	///
	SepType separator;
	///
	const char *Sep2String(SepType sep);
	///
	TransitionArrow::SepType String2Sep(const string *s);
	///
	int HLineLength();
	///
	void CalcSeparator();
	///
	void CalcHLinePart();
	///
	void CalcPositionEvent();
	///
	void CalcPositionActions();
	/// calculate line position and action and event.
	void CalcPositionHLine(); 
	///
	void SetAction(const string *s, unsigned n, bool update);
	/// draw arrow + all labels + 1 horiz line.
	void DrawShape(); 
	/// minimal length hline.
	static const int HLINELEN;
	///
	static const int HLINEXOFFSET;
	///
	static const int HLINEYOFFSET;
	/// distance to horizontal line.
	static const int HLINEDIST;
};
#endif
