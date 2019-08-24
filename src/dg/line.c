////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "grafport.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "assoclist.h"
#include "inputfile.h"
#include "outputfile.h"
#include "rectangle.h"
#include "line.h"
#include "edge.h"
#include "textshape.h"
#include <stdlib.h>
#include <math.h>
#include "config.h"

const int Line::CL_DISTX = 14;
const int Line::CL_DISTY = 10;

Line::Line(ShapeView *v, Grafport *g, GShape *shape1, GShape *shape2, 
	List<Point *> *l, bool Curved): GShape(v,g,0,0) {

	string c = *GetViewer()->GetDefaultLineColor();
	SetColor(&c);
	SetLineStyle(GetViewer()->GetDefaultEdgeLineStyle());
	fromShape = shape1;
	toShape = shape2;
	SetNrHandles(0);
	line = new List<Point *>;
	for (l->first(); !l->done(); l->next()) {
		Point *p1 = l->cur();
		line->add(new Point(*p1));
	}
	curved = Curved;
	end1.SetType(LineEnd::EMPTY);
	end2.SetType(LineEnd::EMPTY);
	order = 1;
	count = 1;
	nameDirection = ReadDirection::NONE;
	orientation = 0;
	if (line->count() > 2)
		lineNumber = line->count()/2;
	else
		lineNumber = 1;
	directionPoints = new DPoint[4];
	CalcEndPoints();
	CalcPosition();
}

Line::Line(ShapeView *v, Grafport *g, GShape *shape1, GShape *shape2, 
		bool Curved): GShape(v, g, 0, 0) {
	fromShape = shape1;
	toShape = shape2;
	end1.SetType(LineEnd::EMPTY);
	end2.SetType(LineEnd::EMPTY);
	curved = Curved;
	SetNrHandles(0);
	line = new List<Point *>;
	nameDirection = ReadDirection::NONE;
	order = 1;
	count = 1;
	lineNumber = 1;
	orientation = 0;
	directionPoints = new DPoint[4];
}

Line::Line(const Line &s): GShape(s) {
	fromShape = s.fromShape;
	toShape = s.toShape;
	end1 = s.end1;
	end2 = s.end2;
	curved = s.curved;
	lineNumber = s.lineNumber;
	line = new List<Point *>;
	for (s.line->first(); !s.line->done(); s.line->next()) {
		Point *p1 = s.line->cur();
		line->add(new Point(*p1));
	}
	nameDirection = s.nameDirection;
	directionPoints = new DPoint[4];
	for (int i=0; i<4; i++)
		directionPoints[i] = s.directionPoints[i];
	order = s.order;
	count = s.count;
	orientation = s.orientation;
	CalcEndPoints();
	CalcPosition();
};

Line::~Line() {
	line->clear();
	delete line;
	delete [] directionPoints;
}

void Line::UpdatePosition() {
	if (IsVisible())
		Undraw();
	CalcEndPoints();
	CalcPosition();
	CalcDirection();
	if (IsVisible())
		Draw();
}


void Line::UpdateEnd1(LineEnd::Type t) {
	if (IsVisible())
		Undraw();
	SetEnd1(t);
	if (IsVisible())
		Draw();
}

void Line::UpdateEnd2(LineEnd::Type t) {
	if (IsVisible())
		Undraw();
	SetEnd2(t);
	if (IsVisible())
		Draw();
}

void Line::DrawGraySelect() {
	if (!IsSelected()) 
		return;
	GetGrafport()->SetLineStyle(LineStyle::SOLID);
	GetGrafport()->SetLineWidth(1);
	// dark gray.
	GetGrafport()->SetForegroundColor("light gray");
	if ( line->first() )
		do {
			const Point *p = line->cur();
			GetGrafport()->FillRectangle(
				p->x - HANDLE_WIDTH/2,
				p->y - HANDLE_WIDTH/2,
				HANDLE_WIDTH, HANDLE_WIDTH);
			while ( line->next() && *p == *(line->cur()) )
				;
		} while ( ! line->done() );
}

void Line::DrawSelect() {
	if (!IsSelected()) 
		return;
	GetGrafport()->SetLineStyle(LineStyle::SOLID);
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black"); 
	if ( line->first() )
		do {
			const Point *p = line->cur();
			GetGrafport()->FillRectangle(
				p->x - HANDLE_WIDTH/2,
				p->y - HANDLE_WIDTH/2,
				HANDLE_WIDTH, HANDLE_WIDTH);
			while ( line->next() && *p == *(line->cur()) )
				;
		} while ( ! line->done() );
}


void Line::DrawShape() {
	if ( check(line->count()>=2)
			&& GetGrafport()->GetLineStyle() != LineStyle::INVISIBLE) {
		GetGrafport()->SetLineStyle(LineStyle::SOLID);
		int b = 1, e = line->count() - 2;
		DPoint l0 = *(*line)[0], ep1;
		while ( (ep1 = *(*line)[b]) == l0 )
			if ( b++ > e ) {
				ep1 = *GetToShape()->GetPosition();
				break;
			}
		DPoint le = *(*line)[e + 1], ep2;
		while ( (ep2 = *(*line)[e]) == le )
			if ( e-- < b ) {
				ep2 = *GetFromShape()->GetPosition();
				break;
			}
		DPoint nep1, nep2;
		end1.Draw(GetGrafport(), &ep1, &l0, &nep1);
		end2.Draw(GetGrafport(), &ep2, &le, &nep2);
		GetGrafport()->SetLineStyle(GetLineStyle());
		if (curved) 
			DrawBezier(&nep1, &nep2);
		else	
			DrawLine(&nep1, &nep2, b, e);
	}
}
 

void Line::DrawLine(const DPoint *ep1, const DPoint *ep2, int b, int e) /* const */ {
	int cnt = e - b + 3;
	if ( cnt < 2 || ! check(line->first()) )
		return;
	DPoint *p = new DPoint[cnt];
	int i = cnt;
	p[--i] = *ep1;
	while ( --b )
		line->next();
	while ( --i ) {
		line->next();
		p[i] = *line->cur();
	}
	p[0] = *ep2;
	GetGrafport()->DrawOpenPolygon(p, cnt);
	delete [/* cnt */] p;
}


void Line::Move(const Point *delta) {
	GShape::Move(delta);
	for (line->first(); !line->done(); line->next()) {
		Point p = *line->cur();
		p += *delta;
		if (p.x <= 0)
			p.x = 1;
		if (p.y <= 0)
			p.y = 1;
		if (check(GetView()))
			GetView()->Snap(&p);
		*line->cur() = p;
	}
	CalcEndPoints();
	CalcPosition();
}

void Line::MoveRaw(const Point *delta) {
	Point pos = *GetPosition() + *delta;
	SetPosition(&pos, False);
	for (line->first(); !line->done(); line->next()) {
		line->cur()->x += delta->x;
		if (line->cur()->x <= 0)
			line->cur()->x = 1;
		line->cur()->y += delta->y;
		if (line->cur()->y <= 0)
			line->cur()->y = 1;
	}
	GetName()->Move(delta);
}


Point Line::RecalcPositionName(bool useReadDirection) {
	Point *from, *to, *save;
	save = from = to = (*line)[0];
	for (unsigned i = 1; i<=lineNumber; i++) {
		from = save;
		to = (*line)[i];
		save = to;
	}
	Point pos = *GetPosition();
	int wd = to->x - from->x;
	int ht = to->y - from->y;
	pos.x = min(from->x, to->x) + abs(wd) / 2;
	pos.y = min(from->y, to->y) + abs(ht) / 2;
	SetWidth(wd);
	SetHeight(ht);
	SetPosition(&pos, False);
	if (curved) {
		return pos;
	}
	// keep the position of the name at fixed distance of the line.
	double alpha;
	if (wd != 0)
		alpha = atan((double)ht/(double)wd);
	else
		alpha = 2*atan(1);

	int RD_DISTX = 0;
	if (useReadDirection && (GetNameDirection() != ReadDirection::NONE))
		RD_DISTX = 12;

	double extraxrd = ((CL_DISTX + RD_DISTX)* sin(alpha));
	double extrax = (CL_DISTX * sin(alpha));
	double extray = (CL_DISTY * cos(alpha));

	if (extray <= 0.01 && extray >= -0.01) {
		extrax = -fabs(extrax);
		extraxrd = -fabs(extraxrd);
	}

	if (extrax < 0)
		extrax = extraxrd;		// including ReadDirection Arrow space

	Point pt;
	pt.x = pos.x + (int)extrax;
	pt.y = pos.y - (int)extray;
	return pt;
}


void Line::CalcPositionName() {
	Point pt = RecalcPositionName(True);
	GetName()->SetPosition(&pt);
	CalcDirection();
}


void Line::CalcEndPoints() {
	if (!check(fromShape) || !check(toShape))
		return;
	Point from, to;
	Point *firstPt, *lastPt;
	int code = orientation;
	int len = line->count();

	firstPt = (*line)[0];
	lastPt = (*line)[len-1];

	if ((*line)[1] == lastPt) 
		to = *(toShape->GetPosition());
	else
		to = *(*line)[1];
	if ((*line)[len-2] == firstPt) 
		from = *(fromShape->GetPosition());
	else 
		from = *(*line)[len-2];

	if ((count == 1) || (fromShape == toShape)) {
		if (len == 2) {
			if ( fromShape->IsLine() && toShape->IsNodeShape() ) {
				from = fromShape->GiveOrthoSnp(to);
				to = toShape->GiveSnp(from);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if ( toShape->IsLine() && fromShape->IsNodeShape() ) {
				to = toShape->GiveOrthoSnp(from);
				from = fromShape->GiveSnp(to);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if ( fromShape->IsLine() && toShape->IsLine() ) {
				Point p1 = *fromShape->GetPosition();
				Point p2 = *toShape->GetPosition();
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
			}
			else {
				Point p1 = fromShape->GiveSnp(to);
				Point p2 = toShape->GiveSnp(from);
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
			}
		}
		else {
			Point p1 = fromShape->GiveOrthoSnp(to);
			Point p2 = toShape->GiveOrthoSnp(from);
			firstPt->Set(p1.x, p1.y);
			lastPt->Set(p2.x, p2.y);
		}
	}
	else {
		Point p1 = fromShape->GiveSnp(to, order, count, code);
		Point p2 = toShape->GiveSnp(from, order, count, code);
		firstPt->Set(p1.x, p1.y);
		lastPt->Set(p2.x, p2.y);
	}
}

void Line::SetPoint(const Point *pt, unsigned int n) {
	if (!check (n <= line->count()-1)) {
		error("handle cannot be updated at position %d\n", n);
		return;
	}
	*(*line)[n] = *pt;
}

void Line::AddPoint(const Point *pt, unsigned int n) {
	if (curved)
		return;
	if (!check (n <= line->count())) {
		error("cannot insert at position %d\n", n);
		return;
	}
	Point *p = new Point(*pt);
	line->insert(p, n); 
	if (line->count() == 3) {
		CalcEndPoints();
	}
	CalcPosition();
	count = 1;
	order = 1;
}

void Line::RemovePoint(unsigned int n) {
	if (curved)
		return;
	if (!check (n <= line->count()-1)) {
		error("no handle at position %d\n", n);
		return;
	}
	Point *p = (*line)[n];
	line->removei(n); 
	if (n > 0 && n <= lineNumber-1) {
		lineNumber--;
	}
	if (line->count() == 2) {
		CalcEndPoints();
	}
	CalcPosition();
	delete p;
}

bool Line::CalcEndPoint(const Point *pt, unsigned int n) {
	if (!check(fromShape) || !check(toShape))
		return False;
	unsigned len = line->count();
	if (n != 0 && n != len-1)
		return True;
	Undraw();
	bool redirected = 
		GetViewer()->GetDiagram()->RedirectEdge(this, (n==0), pt);
	Draw();
	if (!redirected && len == 2) {
		if (n == 0)
	 		*(*line)[0] = fromShape->GiveSnp(*pt);
		else
	 		*(*line)[len-1] = toShape->GiveSnp(*pt);
	}
	else if (len > 2) {
		if (n == 0) {
			if (redirected)
	 			*(*line)[0] = fromShape->GiveOrthoSnp(*(*line)[1]);
			else {
	 			// *(*line)[0] = fromShape->GiveOrthoSnp(*pt);
	 			*(*line)[0] = fromShape->GiveSnp(*pt);
			}
		}
		else {
			if (redirected)
	 			*(*line)[len-1] = 
					toShape->GiveOrthoSnp(*(*line)[len-2]);
			else {
	 			// *(*line)[len-1] = toShape->GiveOrthoSnp(*pt);
	 			*(*line)[len-1] = toShape->GiveSnp(*pt);
			}
		}
	}
	return True;
}

bool Line::ContainsPt(int x, int y) {
	Point *pt1, *pt2;
	int xx, yy;
	if (!line->first())
		return False;
	else
		pt1 = line->cur();
	while (line->next()) {
		pt2 = line->cur();
		if (ContainsPtLine(x, y, pt1, pt2, xx, yy))
			return True;
		pt1 = pt2;
	}
	return False;
}

bool Line::GetLine(int x, int y) {
	Point *pt1, *pt2;
	int xx, yy;
	if (!line->first())
		return False;
	else
		pt1 = line->cur();
	lineNumber = 1;
	while (line->next()) {
		pt2 = line->cur();
		if (ContainsPtLine(x, y, pt1, pt2, xx, yy))
			return True;
		pt1 = pt2;
		lineNumber++;
	}
	if (line->count() > 2)
		lineNumber = line->count()/2;
	else
		lineNumber = 1;
	return False;
}

bool Line::GetSegments(Point pt, Point *pt1, Point *pt2) {
	int n = line->count();
	Point *a1, *a2;
	for (int i=0; i<n; i++) {
		if (pt.x == (*line)[i]->x &&
		    pt.y == (*line)[i]->y) { 
			if (i>0)
				a1 = (*line)[i-1];
			else
				a1 = (*line)[i];
			if (i<n-1)
				a2 = (*line)[i+1];
			else
				a2 = (*line)[i];
			pt1->Set(a1->x, a1->y);
			pt2->Set(a2->x, a2->y);
			return True;
		}
	}
	return False;
}


bool Line::GetSegment(int n, Point *pt1, Point *pt2) {
	if (n > 0 && n <= (int) line->count()) {

		Point *a1, *a2;
		a1 = (*line)[n-1];
		a2 = (*line)[n];

		pt1->Set(a1->x, a1->y);
		pt2->Set(a2->x, a2->y);
		return True;
	}
	return False;
}


bool Line::GetSegment(int n, DPoint *pt1, DPoint *pt2) {
	if (n > 0 && n <= (int) line->count()) {
		Point *a1, *a2;
		a1 = (*line)[n-1];
		a2 = (*line)[n];

		pt1->Set(a1->x, a1->y);
		pt2->Set(a2->x, a2->y);
		return True;
	}
	return False;
}


int Line::HitHandles(int x, int y) {
	for (unsigned n = 0; n<line->count(); n++) {
		Point *pt = (*line)[n];
		Rectangle rect (pt->x-HANDLE_WIDTH/2, pt->y-HANDLE_WIDTH/2,
			HANDLE_WIDTH, HANDLE_WIDTH);
		if (rect.Inside(x,y))
			return n;
	}
	return -1;
}

bool Line::InTextArea(int x, int y) {
	if (IsFixedName())
		return False;
	else if (ContainsPt(x, y))
		return True;
	else 
		return GetName()->InTextArea(x, y);
}


TextShape *Line::ChooseTextShape(int x, int y) {
	if (IsFixedName())
		return 0;
	else if (GetName()->IsEmpty()) {
		if (GetLine(x, y)) {
			if (GetNameDirection() != ReadDirection::NONE)
				DrawDirection();
			Line::CalcPositionName();
			if (GetNameDirection() != ReadDirection::NONE)
				DrawDirection();
			return GetName();
		} else
			return 0;
	}
	else
		return GetName();
}


int Line::GetLeftMost() const {
	int a = GShape::GetLeftMost();
	for (line->first(); !line->done(); line->next()) {
		int x = line->cur()->x;
		if  (x < a)
			a = x;
	}
	return a;
}


int Line::GetTopMost() const {
	int a = GShape::GetTopMost();
	for (line->first(); !line->done(); line->next()) {
		int y = line->cur()->y;
		if  (y < a)
			a = y;
	}
	return a;
}


int Line::GetRightMost() const {
	int a = GShape::GetRightMost();
	for (line->first(); !line->done(); line->next()) {
		int x = line->cur()->x;
		if  (x > a)
			a = x;
	}
	return a;
}


int Line::GetBottomMost() const {
	int a = GShape::GetBottomMost();
	for (line->first(); !line->done(); line->next()) {
		int y = line->cur()->y;
		if  (y > a)
			a = y;
	}
	return a;
}


static inline double square(double r) { return r * r; }

bool Line::ContainsPtLine(int x, int y, const Point *from, const Point *to,
		int &c_x, int &c_y) const {
	double dx = to->x - from->x;
	double dy = to->y - from->y;
	// Ax = b
	// ( a11   a12 )   ( x1 )   ( b1 )
	// (           ) * (    ) = (    )
	// ( a21   a22 )   ( x2 )   ( b2 )
	double a11 = dx, a12 = -dy;
	double a21 = dy, a22 = dx;
	double det = a11 * a22 - a12 * a21;
	double x1, x2;
	if ( det ) {
		double b1 = x - from->x;
		double b2 = y - from->y;
		x1 = (b1 * a22 - b2 * a12) / det;
		x2 = (b2 * a11 - b1 * a21) / det;
	} else {
		x1 = -1.0;
		x2 = 0.0;
	}
	double dist2;
	if ( x1 < 0.0 ) {
		dist2 = square(x - from->x) + square(y - from->y);
		c_x = from->x;
		c_y = from->y;
	} else if ( x1 > 1.0 ) {
		dist2 = square(x - to->x) + square(y - to->y);
		c_x = to->x;
		c_y = to->y;
	} else {
		dist2 = square(x2) * det;
		c_x = int(0.5 + from->x + dx * x1);
		c_y = int(0.5 + from->y + dy * x1);
	}
	// dist2 = square of the distance between (x,y) and the line
	return dist2 < square(GetViewer()->GetDiagram()->GetConfig()->GetLineSelectDistance());
}

void Line::DrawBezier(const DPoint *ep1, const DPoint *ep2) /* const */ {
	DPoint pt[4];
	if (!check(line->count()==4))
		return;
	pt[0] = *ep1;
	pt[1] = DPoint(*(*line)[1]);
	pt[2] = DPoint(*(*line)[2]);
	pt[3] = *ep2;
	GetGrafport()->DrawCurve(pt);
}

void Line::SetFromTop() {
	if (!check(fromShape) || !check(toShape))
		return;
	(*line)[0]->y = fromShape->GetPosition()->y-fromShape->GetWidth()/2;
	(*line)[0]->x = fromShape->GetPosition()->x;
}
 
void Line::SetToTop() {
	if (!check(fromShape) || !check(toShape))
		return;
	(*line)[line->count()-1]->y = toShape->GetPosition()->y-toShape->GetWidth()/2;
	(*line)[line->count()-1]->x = toShape->GetPosition()->x;
}
 
void Line::SetFromBottom() {
	if (!check(fromShape) || !check(toShape))
		return;
	(*line)[0]->y = fromShape->GetPosition()->y + fromShape->GetWidth() / 2;
	(*line)[0]->x = fromShape->GetPosition()->x;
}
 
void Line::SetToBottom() {
	if (!check(fromShape) || !check(toShape))
		return;
	(*line)[line->count()-1]->y = toShape->GetPosition()->y+
				      toShape->GetWidth()/2;
	(*line)[line->count()-1]->x = toShape->GetPosition()->x;
}

void Line::WriteMembers(OutputFile *ofile) {
	// size and position are not written. They can easily be
	// derived by the read operation.
	(*ofile) << "\t{ View " << 
			(check(GetView())?GetView()->GetId():0) << " }\n";
	(*ofile) << "\t{ Subject " << 
			(check(GetSubject())?GetSubject()->GetId():0) << " }\n";
	(*ofile) << "\t{ FromShape " << 
			(check(fromShape)?fromShape->GetId():0) << " }\n";
	(*ofile) << "\t{ ToShape " << 
			(check(toShape)?toShape->GetId():0) << " }\n";
	(*ofile) << "\t{ Curved " << (curved?"True":"False") << " }\n";
	string x;
        LineEnd::Type2String(end1.GetType(), &x);
        (*ofile) << "\t{ End1 " << x << " }\n";
        LineEnd::Type2String(end2.GetType(), &x);
        (*ofile) << "\t{ End2 " << x << " }\n";
	(*ofile) << "\t{ Points " << line->count() << " }\n";
	for (line->first(); !line->done(); line->next())
		(*ofile) << "\t{ Point " << *(line->cur()) << " }\n";
	(*ofile) << "\t{ NamePosition " << 
			*(GetName()->GetPosition()) << " }\n";
	(*ofile) << "\t{ Color " << '"' << *GetColor() << '"' << " }\n";
	WriteGraphicsPart(ofile);
	// write font and text alignment.
	WriteTextPart(ofile);
}

bool Line::ReadMembers(InputFile *ifile, double format) {
	string val1, val2;
	int x,y;
	if (format >= 1.20) {
		if (!ifile->ReadAttribute("View", &val1))
			return False;
		GShape::SetView((ShapeView *)(val1.toulong()));
	}
	if (!ifile->ReadAttribute("Subject", &val1))
		return False;
	GShape::SetSubject((Subject *)(val1.toulong()));
	if (format < 1.25) {
		if (!ifile->ReadAttribute("End1", &val1))
			return False;
	}
	else { 
		if (!ifile->ReadAttribute("FromShape", &val1))
			return False;
	}
	fromShape = (GShape *)(val1.toulong());
	if (format < 1.25) {
		if (!ifile->ReadAttribute("End2", &val1))
			return False;
	}
	else {
		if (!ifile->ReadAttribute("ToShape", &val1))
			return False;
	}
	toShape = (GShape *)(val1.toulong());
	if (!ifile->ReadAttribute("Curved", &val1))
		return False;
	curved = (val1 == "True");
	if (format >= 1.25) {
		if (!ifile->ReadAttribute("End1", &val1))
			return False;
		end1.SetType(LineEnd::String2Type(&val1));
		if (!ifile->ReadAttribute("End2", &val1))
			return False;
		end2.SetType(LineEnd::String2Type(&val1));
	}
	if (!ifile->ReadAttribute("Points", &val1))
		return False;
	int numItems = val1.toint();
	if (numItems < 2)
		return False;
	// Read points
	for (int i=0; i<numItems; i++) {
		if (!ifile->ReadAttribute2("Point", &val1, &val2))
			return False;
		x = val1.toint(); y = val2.toint();
		line->add(new Point(x, y));
	}
	// calc. position, topleft, width and height.
GShape *fromShapeSave = fromShape;
fromShape = NULL;
	CalcPosition();
fromShape = fromShapeSave;
	// read position of the name text shape.
	if (!ifile->ReadAttribute2("NamePosition", &val1, &val2))
		return False;
	x = val1.toint(); y = val2.toint();
	if (x <= 0 || y <= 0) 
		GetName()->SetWellPositioned(False);
	if (format >= 1.21) {
		// read color
		if (!ifile->ReadStringAttribute("Color", &val1))
			return False;
		SetColor(&val1);
	}
	// read font and text alignment.
	Point p(x, y);
	if (!ReadGraphicsPart(ifile, format))
		return False;
	if (!ReadTextPart(ifile, format))
		return False;
	GetName()->SetPosition(&p);
	return True;
}

bool Line::SetAssocSubject(AssocList *al) {
	if (!GShape::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && GetSubject()->IsEdge()))
		return True;
	SetSubject(0);
	return False;
}

bool Line::SetReferences(AssocList *al) {
	Assoc *find, *assoc;
	find = new Assoc(fromShape);
	assoc = al->Get(find);
	delete find;
	if (check(assoc))
		fromShape = (GShape *)assoc->copy;
	else { 
		error("line %ld has no existing fromShape\n", GetId());
		fromShape = 0;
		return False;
	}
	if (!fromShape || !fromShape->IsShape()) {
		error("line %ld has no real shape as fromShape\n", GetId());
		fromShape = 0;
		return False;
	}
	find = new Assoc(toShape);
	assoc = al->Get(find);
	delete find;
	if (check(assoc))
		toShape = (GShape *)assoc->copy;
	else {
		error("line %ld has no existing toShape\n", GetId());
		toShape = 0;
		return False;
	}
	if (!toShape || !toShape->IsShape()) {
		error("line %ld has no real shape as toShape\n", GetId());
		toShape = 0;
		return False;
	}
	Point *l = (*line)[0];
	*l = fromShape->GiveSnp(*l);
	l = (*line)[line->count() - 1];
	*l = toShape->GiveSnp(*l);
	return True;
}

void Line::SetTextShape() {
	GShape::SetTextShape();
	// get first and last point of line
	Point *firstPt = (*line)[0];
	Point *lastPt = (*line)[line->count()-1];
	// are end points to be recalculated ?
	if (firstPt->x == 0 || firstPt->y == 0 || 
	    lastPt->x == 0 || lastPt->y == 0)
		CalcEndPoints();	
	// is name position to be recalculated ?
	if (!GetName()->IsWellPositioned()) {
		CalcPositionName();
		GetName()->SetWellPositioned(True);
	}
	// set line number of name.
	Point pt = *GetName()->GetPosition();
	(void)GetLine(pt.x, pt.y);
}

bool Line::BelowLine(int x, int y, Point *from, Point *to) {
	double dy = (double)(to->y - from->y);
	double dx = (double)(to->x - from->x);
	double rc = dy/dx;
	return y >= (int)(rc*(x - from->x) + from->y);
}
 
bool Line::AboveLine(int x, int y, Point *from, Point *to) {
	double dy = to->y - from->y;
	double dx = to->x - from->x;
	double rc = dy/dx;
	return y <= (int)(rc*(x - from->x) + from->y);
}

bool Line::CheckReferences() {
	if (!GShape::CheckReferences())
		return False;
	if (check(fromShape) && check(toShape)) {
		// fromShape and toShape should exist and be part of the same view.
		if (check(GetView()->HasShape(fromShape)) &&
		    check(GetView()->HasShape(toShape)))
			return True;
	}
	return False;
}

void Line::UpdatePosition(const Point *p, bool snap) {
	GShape::UpdatePosition(p, snap);
}
 
void Line::SetPosition(const Point *p, bool snap) {
	GShape::SetPosition(p, snap);
}
 
Point Line::GiveSnp(Point p) const {
	return GiveOrthoSnp(p);
}

Point Line::GiveSnp(Point, int ord, int cnt, int &) {
	Point p1 = *(*line)[lineNumber-1];
	Point p2 = *(*line)[lineNumber];
	int wd = p2.x - p1.x;
	int ht = p2.y - p1.y;
	int delta_x = int(0.5 + (double)wd/(cnt+1) * ord);
        int delta_y = int(0.5 + (double)ht/(cnt+1) * ord);
	Point pt = Point(p2.x - delta_x, p2.y - delta_y);
	return pt;
}

Point Line::GiveOrthoSnp(Point p) const {
	Point p1 = *(*line)[lineNumber-1];
	Point p2 = *(*line)[lineNumber];
	int a = p1.x;
	int b = p1.y;
	int c = p2.x;
	int d = p2.y;
	int e = p.x;
	int f = p.y;
	int x = 0, y = 0;
	if (a > c) { 
		int swap;
		swap = a;
      		a = c;
      		c = swap;
      		swap = b;
      		b = d;
      		d = swap;
	}
	if (a != c && b != d) { 
        	x=int(0.5 + ((double)(b*b*c-a*b*d-b*c*d+a*d*d+a*a*e-
			2*a*c*e+c*c*e+a*b*f-b*c*f-a*d*f+c*d*f))/
			((double)(a*a+b*b-2*a*c+c*c-2*b*d+d*d)));
        	y=int(0.5 + ((d-b)*x/((double)(c-a)))+b-(((double)(d-b)*a)/((double)(c-a))));
    	}
	else if (b == d) {
		x = e;
		y = b;
	}
	else if (a == c) {
		x = a;
		y = f;
	}
	x = max(min(x, c), a);
	if (b < d)
		y = max(min(y, d), b);
	else
		y = max(min(y, b), d);
	return Point(x, y);
}

void Line::UpdateCurve(bool b) {
	if (curved != b) {
		Undraw();
		curved = b;
		Draw();
	}
}
 
void Line::UpdateNameDirection(ReadDirection::Type d) {
        if (nameDirection != d) {
                Undraw();
                nameDirection = d;
		CalcDirection();
                Draw();
        }
}

void Line::CalcDirection() {
	if (GetNameDirection() == ReadDirection::NONE)
		return;
	DPoint ep1, ep2;
	GetSegment(GetLineNumber(), &ep1, &ep2);
	if (GetNameDirection() == ReadDirection::FROMSHAPE) {
		Point save = ep1;
		ep1 = ep2;
		ep2 = save;
	}
	DPoint arpos = *(GetName()->GetPosition());
	arpos.x += GetName()->GetStringWidth()/2;
	// plus space for arrow
	arpos.x += GetFont()->StringWidth("A");
	LineEnd::CalcDirectionDiamond(&ep1, &ep2, &arpos, 
				12, 8, directionPoints);
}

void Line::DrawDirection() {
        if (GetNameDirection() != ReadDirection::NONE) {
               	GetGrafport()->FillPolygon(directionPoints, 3);
//		if (!GetGrafport()->DrawsXor())
//                	GetGrafport()->DrawPolygon(directionPoints, 3);
	}
}

void Line::NotifyTextMove(TextShape *t) {
        if (t == GetName() && GetNameDirection() != ReadDirection::NONE) {
        	// redraw direction arrow
                DrawDirection();
		CalcDirection();
                DrawDirection();
        }
}

