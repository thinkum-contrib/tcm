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
#ifndef _LINEPIECE_H
#define _LINEPIECE_H

#include "point.h"
#include "linestyle.h"
class InputFile;
class OutputFile;
class Grafport;

/// horizontal or vertical line (cell boundary).
class LinePiece {
/*@Doc: {\large {\bf scope:} table} */
public:			 	
	///
	LinePiece(Grafport *g, Point *from, Point *to, 
		LineStyle::Type style, unsigned width);

	///
	void Draw();
	///
	void Undraw();

	/// return iff (x,y) is on line piece
	bool HitLine(int x, int y); 

	///
	void SetLineStyle(LineStyle::Type t) {
		lineStyle = t;}
	///
	LineStyle::Type GetLineStyle() {return lineStyle;}
	///
	void UpdateLineStyle(LineStyle::Type t);

	///
	void SetLineWidth(unsigned n) {lineWidth = n;}
	///
	unsigned GetLineWidth() {return lineWidth;}
	///
	void UpdateLineWidth(unsigned n);

	///
	void SetBegin(const Point *pt) {beginP = *pt;}
	///
	void SetEnd(const Point *pt) {endP = *pt;}

	///
	void SetPoints(const Point *pt1, const Point *pt2) 
		{beginP = *pt1; endP = *pt2;}
	///
	void UpdatePoints(const Point *pt1, const Point *pt2);
	///
	void UpdateBegin(const Point *pt);
	///
	void UpdateEnd(const Point *pt);
	///
	void SetGrafport(Grafport *g) {grafport = g;}
	///
	void Write(OutputFile *f);
	///
	bool Read(InputFile *f, double format);
	///
	Point *GetBegin() {return &beginP;}
	///
	Point *GetEnd() {return &endP;}
	///
	bool IsVisible() {return visible;}
	///
	void SetVisible(bool b) {visible=b;}
private:
	/// 
	Point beginP;
	///
	Point endP;
	///
	bool visible;
	///
	LineStyle::Type lineStyle;
	///
	unsigned lineWidth;
	///
	Grafport *grafport;
};
#endif
