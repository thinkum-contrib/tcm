////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "nodeshape.h"
#include "diagramviewer.h"
#include "inputfile.h"
#include "outputfile.h"
#include "shapetype.h"
#include "node.h"
#include "diagram.h"

NodeShape::NodeShape(ShapeView *v, Grafport *g, double x, double y,
	const ShapeType *st)
:GShape(v, g, int(0.5 + x), int(0.5 + y)),
shapetype(st),
fixedIndexLabel(st->GetIndexPoint() == NULL),
resizable(IsResizable())
{
	SetWidth(static_cast<int>(0.5 + st->GetDefaultWidth()));
	SetHeight(static_cast<int>(0.5 + st->GetDefaultHeight()));
	SetFillStyle(GetViewer()->GetDefaultFillStyle());
	string s = *GetViewer()->GetDefaultFillColor();
	SetFillColor(&s);
	s = *GetViewer()->GetDefaultLineColor();
	SetColor(&s);
	SetLineStyle(GetViewer()->GetDefaultNodeLineStyle());
	SetFixedName(st->GetNameArea() == NULL);
	SetHandles(8);
	indexLabel = new TextShape(v, g, this);
	indexLabel->SetOneLine(True);
	indexLabel->SetDescription("Index");
//	CalcPositionIndexLabel();
	SetPosition(GetPosition());
}


NodeShape::NodeShape(const NodeShape &c, const ShapeType *st)
:GShape(c)
{
	shapetype = NULL != st ? st : c.shapetype;
	indexLabel = new TextShape(*(c.indexLabel));
	indexLabel->SetParent(this);
	fixedIndexLabel = shapetype->GetIndexPoint() == NULL;
	resizable = IsResizable();
	fillColor = c.fillColor;
	fillStyle = c.fillStyle;
//	CalcPositionIndexLabel();
	SetFixedName(shapetype->GetNameArea() == NULL);
	SetHandles(8);
	SetPosition(GetPosition());
}



/* virtual */ NodeShape::~NodeShape() {
	delete indexLabel;
}


/* virtual */ void NodeShape::DrawShape() {
	const Point *pos = GetPosition();

	CalcPositionLabels(); // ???

	if ( GetFillStyle() == FillStyle::FILLED ) {
		GetGrafport()->SetForegroundColor(GetFillColor());
		GetShapeType()->Fill(GetGrafport(), pos->x, pos->y,
			GetWidth(), GetHeight(), GetName());
	}
	GetGrafport()->SetForegroundColor(GetColor());
	GetShapeType()->Draw(GetGrafport(), pos->x, pos->y,
		GetWidth(), GetHeight(), GetName(),
		GetFillStyle() == FillStyle::UNFILLED ? (const string *) NULL
		: GetFillColor());
}


void NodeShape::DrawOutLine(double x, double y, double w, double h)
{
	SetOutlineAttributes();
//	if ( 0.0 == w )
//		w = GetWidth();
//	if ( 0.0 == h )
//		h = GetHeight();
	GetShapeType()->DrawOutLine(GetGrafport(),
		GetView()->Snap(static_cast<int>(0.5 + x)), 
		GetView()->Snap(static_cast<int>(0.5 + y)), w, h,
		GetName()->GetStringWidth(), GetName()->GetStringHeight());
}


/* virtual */ void NodeShape::DrawOutLine(const Point *centre) {
	DrawOutLine(
		GetView()->Snap(centre->x), GetView()->Snap(centre->y),
		GetWidth(), GetHeight());
}


/* virtual */ Point NodeShape::GiveSnp(Point to) const {
	const Point *pos = GetPosition();
//	int lw = GetLineWidth();
//	switch ( GetLineStyle() ) {
//	case LineStyle::INVISIBLE:
//		lw = 0;
//		break;
//	case LineStyle::DUAL:
//		lw *=3;
//		break;
//	}
	DPoint u(GetShapeType()->GiveSnp(to.x - pos->x, to.y - pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
	u.x += pos->x;
	u.y += pos->y;
	return Point(u);
}


/* virtual */ Point NodeShape::GiveSnp(Point to, int order, int count,
	int &) /* const */
{
	const Point *pos = GetPosition();
//	int lw = GetLineWidth();
//	switch ( GetLineStyle() ) {
//	case LineStyle::INVISIBLE:
//		lw = 0;
//		break;
//	case LineStyle::DUAL:
//		lw *=3;
//		break;
//	}
	DPoint u(GetShapeType()->GiveSnp(order, count,
		to.x - pos->x, to.y - pos->y, GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
	u.x += pos->x;
	u.y += pos->y;
	return Point(u);
}


/* virtual */ Point NodeShape::GiveOrthoSnp(Point to) const {
	const Point *pos = GetPosition();
//	int lw = GetLineWidth();
//	switch ( GetLineStyle() ) {
//	case LineStyle::INVISIBLE:
//		lw = 0;
//		break;
//	case LineStyle::DUAL:
//		lw *=3;
//		break;
//	}
	DPoint u(GetShapeType()->GiveOrthoSnp(to.x - pos->x, to.y - pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
	u.x += pos->x;
	u.y += pos->y;
	return Point(u);
}


/* virtual */ void NodeShape::DrawDuplicate() {
	const PolyPoint *dp = GetShapeType()->GetDuplicatePoint();
	if ( NULL == dp )
		return;
	TextShape dupl(*GetName());
	dupl.SetString("*");
	const Point *pos = GetPosition();
	dp->Write(GetGrafport(), pos->x, pos->y, GetWidth(), GetHeight(),
		&dupl);
}


void NodeShape::DrawMultiplicity() {
	const PolyPoint *mp = GetShapeType()->GetMultiplicityPoint();
	if ( NULL == mp )
		return;
	TextShape multi(*GetName());
	multi.SetString("2");
	const Point *pos = GetPosition();
	mp->Write(GetGrafport(), pos->x, pos->y, GetWidth(), GetHeight(),
		&multi);
}


/* virtual */ bool NodeShape::ContainsPt(int x, int y) {
	if ( HitHandles(x, y) != -1 )
		return True;
	const Point *pos = GetPosition();
	if ( ! IsSelected() && GetViewer()->GetDiagram()->IsHierarchic() )
		return GetShapeType()->IsHit(pos->x - x, pos->y - y,
			GetWidth(), GetHeight(),
			GetName()->GetStringWidth(),
			GetName()->GetStringHeight());
	else
		return GetShapeType()->IsInside(pos->x - x, pos->y - y,
			GetWidth(), GetHeight(),
			GetName()->GetStringWidth(),
			GetName()->GetStringHeight());
}


bool NodeShape::ContainsChild(const GShape *gs) const {
	if ( ! gs->IsNodeShape() || GetShapeType()->GetChildArea() == NULL )
		return False;
	const NodeShape *ns = (const NodeShape *) gs;
	const Point *pos = GetPosition(), *posns = ns->GetPosition();
	return GetShapeType()->ContainsChild(
		pos->x - posns->x, pos->y - posns->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight(),
		ns->GetShapeType(),
		ns->GetWidth(), ns->GetHeight(),
		ns->GetName()->GetStringWidth(),
		ns->GetName()->GetStringHeight());
}


bool NodeShape::InTextArea(int x, int y) {
	if ( NULL == GetShapeType()->GetNameArea() )
		return False;
	const Point *pos = GetPosition();
	return GetShapeType()->IsInside(pos->x - x, pos->y - y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight());
	// or is (x,y) in the name area?
}


/* virtual */ int NodeShape::HitHandles(int x, int y) {
	if ( ! resizable )
		return -1;
	int dir = GShape::HitHandles(x, y);
	if ( dir > 0 ) {
		if ( shapetype->HasFixedWidth() )
			dir = 3 == dir || 4 == dir || 5 == dir ? 5 : 6;
		if ( shapetype->HasFixedHeight() )
			dir = 1 == dir || 4 == dir || 7 == dir ? 7 : 8;
	}
	return dir;
}


TextShape *NodeShape::ChooseTextShape(int x, int y) {
	const PolyPoint *ip = GetShapeType()->GetIndexPoint();
	if ( GetViewer()->IsShowIndexes() && NULL != ip ) {
		DPoint pt;
		const Point *pos = GetPosition();
		ip->CalcPoint(&pt, pos->x, pos->y, GetWidth(), GetHeight(),
			GetIndexLabel()->GetStringWidth(),
			GetIndexLabel()->GetStringHeight());
		pt.x -= x;
		if ( pt.x < 0 )
			pt.x = -pt.x;
		pt.y -= y;
		if ( pt.y < 0 )
			pt.y = -pt.y;
		if ( (pt.x <= 5 ||
		  pt.x * 2 <= GetIndexLabel()->GetStringWidth()) &&
		  (pt.y <= 5 ||
		  pt.y * 2 <= GetIndexLabel()->GetStringHeight()) )
			return GetIndexLabel();
	}
	return GShape::ChooseTextShape(x, y);
}


/* virtual */ void NodeShape::SetNameString(const string *s) {
	GShape::SetNameString(s);
//	CalcPositionIndexLabel();
	SetPositionHandles(); /* for shapes whose size depends on the name */
}


/* virtual */ void NodeShape::SetSize(int w, int h) {
	if ( ! resizable )
		return;
	double ww = w, hh = h;
	GetShapeType()->CorrectScale(&ww, &hh,
		GetName()->GetStringWidth(), GetName()->GetStringHeight(),
		false, false);
	GShape::SetSize(int(0.5 + ww), int(0.5 + hh));
//	CalcPositionIndexLabel();
}


/* virtual */ void NodeShape::AdjustSize() {
	// update size of gshape (does not work when it is a line) to
	// fit the name textshape.
	if ( /* IsNodeShape() && */ GetShapeType()->GetNameArea() != NULL ) {
		double w = GetWidth(), h = GetHeight();
		GetShapeType()->FitText(&w, &h,
			GetName()->GetStringWidth() + 4,
			GetName()->GetStringHeight() + 4);
		UpdateSize(int(0.5 + w), int(0.5 + h));
		GetViewer()->ShapePositionUpdate(this);
//		GetMainWindow()->FitDocument();
	}
}


/* virtual */ int NodeShape::GetLeftMost() const {
	const Point *pos = GetPosition();
	return int(0.5 + GetShapeType()->GetLeftMost(pos->x, pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
}


/* virtual */ int NodeShape::GetTopMost() const {
	const Point *pos = GetPosition();
	return int(0.5 + GetShapeType()->GetTopMost(pos->x, pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
}


/* virtual */ int NodeShape::GetBottomMost() const {
	const Point *pos = GetPosition();
	return int(0.5 + GetShapeType()->GetBottomMost(pos->x, pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
}


/* virtual */ int NodeShape::GetRightMost() const {
	const Point *pos = GetPosition();
	return int(0.5 + GetShapeType()->GetRightMost(pos->x, pos->y,
		GetWidth(), GetHeight(),
		GetName()->GetStringWidth(), GetName()->GetStringHeight()));
}


void NodeShape::CalcCompleteIndex(string *s) const {
	Node *parent = GetSubject()->GetParent();
	if ( ! parent )
		parent = GetView()->GetParent();
	NodeShape *shape;
	if ( parent && (shape = (NodeShape *) GetView()->GetShape(parent)) ) {
		shape->CalcCompleteIndex(s);
		if ( s->length() )
			*s += '.';
	} else
		*s = "";
	*s += *indexLabel->GetString();
}


/* virtual */ void NodeShape::DrawTextShapes() {
	// set background color.
	string oldBackground;
	if (GetFillStyle() != FillStyle::UNFILLED) {
		oldBackground = *GetGrafport()->GetBackgroundColor();
		GetGrafport()->SetBackgroundColor(GetFillColor());
	}

	CalcPositionLabels();
	if ( GetShapeType()->GetNameArea() != NULL )
		GetName()->Draw();
	if ( GetShapeType()->GetIndexPoint() && indexLabel ) {
		TextShape il(*indexLabel);
//		if ( Toolkit::HierarchicEditor(
//		   GetViewer()->GetMainWindow()->GetTool()) ) {
//		   && GetSubject() && GetSubject()->GetParent() ) {
			string s;
			CalcCompleteIndex(&s);
			il.SetString(&s);
//		}
		il.Draw();
	}

	if (IsDuplicate())
		DrawDuplicate();

	// restore background color.
	if (GetFillStyle() != FillStyle::UNFILLED)
		GetGrafport()->SetBackgroundColor(&oldBackground);
}


/* virtual */ void NodeShape::SetPositionHandles() {
	// Positions of the handles:
	//   0----5----1
	//   |         |
	//   6         7
	//   |         |
	//   3----4----2
	const Point *pos = GetPosition();
	DPoint tl, br;
	GetShapeType()->CalcTopLeft().CalcPoint(&tl,
		pos->x - HANDLE_WIDTH * 0.5, pos->y - HANDLE_WIDTH * 0.5,
		GetWidth(), GetHeight(), GetName()->GetStringWidth(),
		GetName()->GetStringHeight());
	GetShapeType()->CalcBottomRight().CalcPoint(&br,
		pos->x - HANDLE_WIDTH * 0.5, pos->y - HANDLE_WIDTH * 0.5,
		GetWidth(), GetHeight(), GetName()->GetStringWidth(),
		GetName()->GetStringHeight());
	handles[0].Set(int(0.5 + tl.x), int(0.5 + tl.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[1].Set(int(0.5 + br.x), int(0.5 + tl.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[2].Set(int(0.5 + br.x), int(0.5 + br.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[3].Set(int(0.5 + tl.x), int(0.5 + br.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[4].SetPosition(int(0.5 - HANDLE_WIDTH * 0.5 + pos->x), int(0.5 + br.y));
	handles[5].SetPosition(int(0.5 - HANDLE_WIDTH * 0.5 + pos->x), int(0.5 + tl.y));
	if ( ! resizable || GetShapeType()->HasFixedHeight() ) {
		handles[4].width = handles[5].width =
		handles[4].height = handles[5].height = 0;
	} else {
		handles[4].width = handles[5].width = HANDLE_WIDTH;
		handles[4].height = handles[5].height = HANDLE_WIDTH;
	}
	handles[6].SetPosition(int(0.5 + tl.x), int(0.5 - HANDLE_WIDTH * 0.5 + pos->y));
	handles[7].SetPosition(int(0.5 + br.x), int(0.5 - HANDLE_WIDTH * 0.5 + pos->y));
	if ( ! resizable || GetShapeType()->HasFixedWidth() ) {
		handles[6].width = handles[7].width =
		handles[6].height = handles[7].height = 0;
	} else {
		handles[6].width = handles[7].width = HANDLE_WIDTH;
		handles[6].height = handles[7].height = HANDLE_WIDTH;
	}
	SetNrHandles(8);
}


/* virtual */ void NodeShape::CalcPositionLabels() {
	const Point *pos = GetPosition();
	Point p;
	DPoint pt;
	const Polygon *na = GetShapeType()->GetNameArea();
	if ( NULL != na ) {
		na->CalcCentre().CalcPoint(&pt, pos->x, pos->y,
			GetWidth(), GetHeight(),
			GetName()->GetStringWidth(),
			GetName()->GetStringHeight());
		p.Set(int(0.5 + pt.x), int(0.5 + pt.y));
		GetName()->SetPosition(&p);
	}
	const PolyPoint *ip = GetShapeType()->GetIndexPoint();
	if ( NULL != ip ) {
		ip->CalcPoint(&pt, pos->x, pos->y,
			GetWidth(), GetHeight(),
			indexLabel->GetStringWidth(),
			indexLabel->GetStringHeight());
		p.Set(int(0.5 + pt.x), int(0.5 + pt.y));
		indexLabel->SetPosition(&p);
	}
	return;
}


void NodeShape::UpdateFillColor(const string *c) {
	if (GetFillStyle() == FillStyle::UNFILLED)
		SetFillColor(c);
	else {
		Undraw();
		SetFillColor(c);
		Draw();
	}
}

 
void NodeShape::UpdateFillStyle(FillStyle::Type f) {
	if (GetFillStyle() != f) {
		Undraw();
		SetFillStyle(f);
		Draw();
	}
}


void NodeShape::SetPosition(const Point *pos, bool snap) {
	GShape::SetPosition(pos, snap);
	const Polygon *na = GetShapeType()->GetNameArea();
	if ( na != NULL ) {
		DPoint p;
		na->CalcCentre().CalcPoint(&p, pos->x, pos->y,
			GetWidth(), GetHeight(),
			GetName()->GetStringWidth(),
			GetName()->GetStringHeight());
		Point pt = p;
		GetName()->SetPosition(&pt);
	}
//	CalcPositionIndexLabel();
}


/* virtual */ void NodeShape::SetFont(XFont *ft) {
	GShape::SetFont(ft);
	indexLabel->SetFont(ft);
//	CalcPositionIndexLabel();
	SetPositionHandles();
}


void NodeShape::SetTextColor(const string *c) {
	GShape::SetTextColor(c);
	indexLabel->SetColor(c);
}


void NodeShape::SetGrafport(Grafport *g) {
	GShape::SetGrafport(g);
	indexLabel->SetGrafport(g);
}
 

void NodeShape::SetView(ShapeView *v) {
	GShape::SetView(v);
	indexLabel->SetView(v);
}


void NodeShape::UpdateIndexLabel(const string *s) {
	if (IsVisible())
		UndrawWithChildren();
	SetIndexLabel(s);
	if (IsVisible())
		DrawWithChildren();
}


/* virtual */ void NodeShape::SetIndexLabel(const string *s) {
	indexLabel->SetString(s);
}

 
bool NodeShape::SetAssocSubject(AssocList *al) {
	if (!Shape::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && !GetSubject()->IsEdge()))
		return True;
	SetSubject(0);
	return False;
}


bool NodeShape::ReadMembers(InputFile *ifile, double format) {
	if (!Shape::ReadMembers(ifile, format))
		return False;
	if (!ReadGraphicsPart(ifile, format))
		return False;
	if (format >= 1.21) {
		string val1;
		if (!ifile->ReadAttribute("FillStyle", &val1))
			return False;
		fillStyle = FillStyle::String2Type(&val1);
		if (!ifile->ReadStringAttribute("FillColor", &fillColor))
			return False;
	}
	if (!ReadTextPart(ifile, format))
		return False;
	SetPosition(GetPosition(), false);
	return True;
}


void NodeShape::WriteMembers(OutputFile *ofile) {
	Shape::WriteMembers(ofile);
	WriteGraphicsPart(ofile);
	string fs;
	FillStyle::Type2String(fillStyle, &fs);
	(*ofile) << "\t{ FillStyle " << fs  << " }\n";
	(*ofile) << "\t{ FillColor " <<  '"' << fillColor << '"' << " }\n";
	WriteTextPart(ofile);
}


void NodeShape::SetTextShape() {
	GShape::SetTextShape();
	// set position of top label.
	if (GetViewer()->IsShowIndexes())
		if (check(GetSubject() && !GetSubject()->IsEdge()))
			GetIndexLabel()->
				SetString(((Node *)GetSubject())->GetIndex());
	else {
		string empty("");
		GetIndexLabel()->SetString(&empty);
	}
	GetIndexLabel()->SetParent(this);
//	CalcPositionIndexLabel();
}


bool NodeShape::HasTextShape(TextShape *t) const {
	if (t == GetName())
		return True;
	else if (t == indexLabel)
		return True;
	else
		return False;
}

 
bool NodeShape::HasString(const string *s, bool sens, bool sub) const {
	if (GShape::HasString(s, sens, sub))
		return True;
	else if (*s != "" && indexLabel->HasString(s, sens, sub))
		return True;
	else
		return False;
}

 
bool NodeShape::HasString(const string *s, bool sens, bool sub,
		List<TextShape *> *list) {
	bool b= GShape::HasString(s, sens, sub, list);
	if (*s != "")
		b += indexLabel->HasString(s, sens, sub, list);
	return b;
}

