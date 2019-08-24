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
#include "inputfile.h"
#include "outputfile.h"
#include "grafport.h"
#include "node.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "gshape.h"

GShape::GShape(ShapeView *v, Grafport *g, int x, int y): Shape(v, g) {
	// restriction: all text shapes have the same font.
	name = new TextShape(v, g, this);
	Point pt(x,y);
	SetPosition(&pt);
	lineWidth = GetViewer()->GetDefaultLineWidth();
	lineStyle = LineStyle::SOLID;
	fixedName = False;
}

GShape::GShape(const GShape &s): Shape(s) {
	name = new TextShape(*(s.name));
	lineStyle = s.lineStyle;
	lineWidth = s.lineWidth;
	name->SetParent(this);
	name->SetPosition(GetPosition());
	fixedName = s.fixedName;
}

/* virtual */ GShape::~GShape() {
	delete name;
}

void GShape::Draw() {
	SetOutlineAttributes();
	if (IsFirstSelected())
		DrawSelect();
	else
		DrawGraySelect();
	SetDrawAttributes();
	DrawShape();
	DrawTextShapes();
}

void GShape::Undraw() {
	SetOutlineAttributes();
	if (IsFirstSelected())
		UndrawSelect();
	else
		UndrawGraySelect();
	SetDrawAttributes();
	UndrawShape();
	UndrawTextShapes();
}


void GShape::DrawWithChildren() {
//	if ( GetViewer()->GetDiagram()->IsHierarchic() ) {
	if ( Toolkit::HierarchicEditor(
				GetViewer()->GetMainWindow()->GetTool()) ) {
		List<GShape *> *s = GetView()->GetShapes();
		for ( int i = s->count() ; i-- > 0 ; ) {
			GShape *shape = (*s)[i];
			if ( shape->GetSubject()->GetParent() == GetSubject() )
				shape->DrawWithChildren();
		}
	}
	Draw();
}


void GShape::UndrawWithChildren() {
//	if ( GetViewer()->GetDiagram()->IsHierarchic() ) {
	if ( Toolkit::HierarchicEditor(
				GetViewer()->GetMainWindow()->GetTool()) ) {
		List<GShape *> *s = GetView()->GetShapes();
		for ( int i = s->count() ; i-- > 0 ; ) {
			GShape *shape = (*s)[i];
			if ( shape->GetSubject()->GetParent() == GetSubject() )
				shape->UndrawWithChildren();
		}
	}
	Undraw();
}


/* virtual */ void GShape::SetTextShape() {
	// subject should be correct, because of Shape::SetReferences()
	if (check(GetSubject()))
		SetNameString(GetSubject()->GetName());
	// parent field is corrupted by reading in the data
	name->SetParent(this);
}

/* virtual */ void GShape::SetDrawAttributes() {
	Shape::SetDrawAttributes();
	GetGrafport()->SetLineWidth(lineWidth);
	GetGrafport()->SetLineStyle(lineStyle);
}

/* virtual */ TextShape *GShape::HitTextShape(int x, int y) {
	return name->ContainsPt(x, y) ? name :0;
}

void GShape::UpdateLineWidth(unsigned n) {
	Undraw();
	lineWidth = n;
	Draw();
}

void GShape::UpdateLineStyle(LineStyle::Type x) {
	Undraw();
	lineStyle = x;
	Draw();
}

void GShape::UpdateTextColor(const string *c) {
       Undraw();
       SetTextColor(c);
       Draw();
}


/* virtual */ void GShape::UpdateParent(Node *parent) {
	if ( IsVisible() )
		UndrawWithChildren();
	GetSubject()->SetParent(parent);
	if ( IsVisible() )
		DrawWithChildren();
}


/* virtual */ int GShape::GetLeftMost() const {
	return min(Shape::GetLeftMost(), name->GetLeftMost());
}

/* virtual */ int GShape::GetTopMost() const {
	return min(Shape::GetTopMost(), name->GetTopMost());
}

/* virtual */ int GShape::GetRightMost() const {
	return max(Shape::GetRightMost(), name->GetRightMost());
}

/* virtual */ int GShape::GetBottomMost() const {
	return max(Shape::GetBottomMost(), name->GetBottomMost());
}

/* virtual */ void GShape::SetSelect(bool s) {
	Shape::SetSelect(s);
	name->SetSelect(s);
}

/* virtual */ void GShape::SnapPosition() {
	Shape::SnapPosition();
	name->SetPosition(GetPosition());
}

/* virtual */ void GShape::SnapTopleft() {
	Shape::SnapTopleft();
	name->SetPosition(GetPosition());
}

void GShape::WriteGraphicsPart(OutputFile *ofile) {
	(*ofile) << "\t{ LineWidth " << lineWidth << " }\n";
	string s;
	LineStyle::Type2String(lineStyle, &s);
	(*ofile) << "\t{ LineStyle " <<  s << " }\n";
}

bool GShape::ReadGraphicsPart(InputFile *ifile, double format) {
	if (format >= 1.21) {
		string val1;
		if (!ifile->ReadAttribute("LineWidth", &val1))
			return False;
		lineWidth = val1.toint();
		if (!ifile->ReadAttribute("LineStyle", &val1))
			return False;
		lineStyle = LineStyle::String2Type(&val1);
	}
	return True;
}

void GShape::WriteTextPart(OutputFile *ofile) {
	string fd;
	(*ofile) << "\t{ FixedName " << (fixedName ? "True":"False") << " }\n";
	name->GetFont()->GetXLFD(&fd);
	(*ofile) << "\t{ Font " << '"' << fd << '"' << " }\n";
	string s;
	TextAlign::Type2String(name->GetAlignment(), &s);
	(*ofile) << "\t{ TextAlignment " << s << " }\n";
	(*ofile) << "\t{ TextColor " << '"' << *name->GetColor() 
		 << '"' << " }\n";
	(*ofile) << "\t{ NameUnderlined " << (name->IsUnderlined() ? "True":"False") << " }\n";
}

bool GShape::ReadTextPart(InputFile *ifile, double format) {
	string val1;
	if (format >= 1.24) {
		if (!ifile->ReadAttribute("FixedName", &val1))
			return False;
		fixedName = (val1 %= "True");
	}
	if (format >= 1.09) {
		if (!ifile->ReadStringAttribute("Font", &val1))
			return False;
		XFont *ft = GetViewer()->GetFont(val1.getstr());
		if (ft)
			SetFont(ft);
		if (!ifile->ReadAttribute("TextAlignment", &val1))
			return False;
		TextAlign::Type alignment = TextAlign::String2Type(&val1);
		SetAlignment(alignment);
	}
	if (format >= 1.21) {
		if (!ifile->ReadStringAttribute("TextColor", &val1))
			return False;
		SetTextColor(&val1);
	}
	if (format >= 1.26) {
		if (!ifile->ReadAttribute("NameUnderlined", &val1))
			return False;
		name->SetUnderlined(val1 %= "True");
	}
	return True;
}

/* virtual */ void GShape::SetGrafport(Grafport *g) {
	Shape::SetGrafport(g);
	name->SetGrafport(g);
}

/* virtual */ void GShape::SetView(ShapeView *v) {
	Shape::SetView(v);
	name->SetView(v);
}

bool GShape::CheckReferences() {
	if (!Shape::CheckReferences())
		return False;
	// Check that name exists and has the correct parent reference.
	else if (!check(name))
		return False;
	else if (!check(name->GetParent() == this))
		return False;
	return True;
}

/* virtual */ TextShape *GShape::ChooseTextShape(int, int) {
	return fixedName? 0: name;
}

/* virtual */ void GShape::UpdateNameString(const string *s) {
	if (IsVisible())
		Undraw();
	SetNameString(s);
	if (IsVisible())
		Draw();
}

/* virtual */ void GShape::UpdateFont(XFont *ft) {
        if (IsVisible())
                Undraw();
        SetFont(ft);
        if (IsVisible())
                Draw();
}

/* virtual */ void GShape::UpdateAlignment(TextAlign::Type alignment) {
        if (IsVisible())
                Undraw();
        SetAlignment(alignment);
        if (IsVisible())
                Draw();
}
