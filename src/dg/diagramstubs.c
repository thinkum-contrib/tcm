////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "diagram.h"
#include "code.h"
#include "nodeshape.h"
#include "lineend.h"
#include "texteditdialog.h"
#include "lineenddialog.h"
#include "nodealignmentdialog.h"
#include "nodeshapedialog.h"
#include "scaledialog.h"
#include "diagramstubs.h"
#include <Xm/ToggleB.h>

void DiagramStubs::SetNodeCB(Widget w, XtPointer cd, XtPointer) {
	// 'unset' event of a toggle button should be discarded.
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, 0);
		((Diagram *)cd)->UpdateNodeType((int)num);
	}
}

void DiagramStubs::SetEdgeCB(Widget w, XtPointer cd, XtPointer) {
	// 'unset' event of a toggle button should be discarded.
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, 0);
		((Diagram *)cd)->UpdateEdgeType((int)num);
	}
}

void DiagramStubs::SetCurveCB(Widget w, XtPointer cd, XtPointer) {
	((Diagram *)cd)->SetCurve(XmToggleButtonGetState(w));
}

void DiagramStubs::DeleteCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->DeleteShapes();
}

void DiagramStubs::DeleteAllCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->DeleteAll();
}

void DiagramStubs::SubjectAnnotationOKCB(Widget, XtPointer cd, XtPointer) {
	Diagram *dg = (Diagram *)cd;
	if (!check(dg))
		return;
	string t;
	dg->GetEltAnnotationDialog()->GetTextString(&t);
	dg->SetSubjectAnnotation(&t);
}

void DiagramStubs::AlignNodeShapesCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->AlignNodeShapes();
}

void DiagramStubs::AlignNodeShapesDefaultCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *) cd)->ShowDefaultNodeAlignment();
}

void DiagramStubs::AlignNodeShapesOKCB(Widget, XtPointer cd, XtPointer) {
	DiagramViewer *v = (DiagramViewer *)cd;
        NToggleListDialog *d = v->GetNodeAlignmentDialog();
        int n = d->GetValue(0);
        string text1;
        d->GetItem(0, n, &text1);
	NodeAlign::Type t = NodeAlign::String2Type(&text1);
        v->AlignNodes(t);
}

void DiagramStubs::CutCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->Cut();
}

void DiagramStubs::CopyCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->Copy();
}

void DiagramStubs::PasteCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->Paste();
}

void DiagramStubs::DuplicateCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->Duplicate();
}

void DiagramStubs::SelectAllCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->SelectAll();
}

void DiagramStubs::SameSizeCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->SameSize();
}

void DiagramStubs::AnnotateCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->Annotate();
}

void DiagramStubs::ZoomInCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->ZoomIn();
}

void DiagramStubs::ZoomOutCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->ZoomOut();
}

void DiagramStubs::TopLevelCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->TopLevel();
}

void DiagramStubs::DefaultNodeLineStyleCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int n;
		XtVaGetValues(w, XmNuserData, &n, 0);
		n = n/2;
		LineStyle::Type i = LineStyle::SOLID;
		if (n == 1)
			i = LineStyle::DASHED;
		else if (n == 2)
			i = LineStyle::DOTTED;
		else if (n == 3)
			i = LineStyle::INVISIBLE;
		((DiagramViewer *)cd)->SetDefaultNodeLineStyle(i);
	}
}

void DiagramStubs::DefaultEdgeLineStyleCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int n;
		XtVaGetValues(w, XmNuserData, &n, 0);
		n = n/2;
		LineStyle::Type i = LineStyle::SOLID;
		if (n == 1)
			i = LineStyle::DASHED;
		else if (n == 2)
			i = LineStyle::DOTTED;
		else if (n == 3)
			i = LineStyle::INVISIBLE;
		((DiagramViewer *)cd)->SetDefaultEdgeLineStyle(i);
	}
}

void DiagramStubs::ShowIndexesCB(Widget w, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->SetIndexes(XmToggleButtonGetState(w));
}

void DiagramStubs::ReindexCB(Widget, XtPointer cd, XtPointer) {
	((Diagram *)cd)->Reindex();
}

void DiagramStubs::UpdateNodeShapeTypeCB(Widget w, XtPointer cd, XtPointer) {
        int num;
        XtVaGetValues(w, XmNuserData, &num, 0);
        ((DiagramViewer *)cd)->UpdateNodeShapeType(num);
}

void DiagramStubs::ConvertNodeShapeTypeCB(Widget, XtPointer cd, XtPointer) {
        ((DiagramViewer *)cd)->ConvertNodeShapes();
}
	
void DiagramStubs::ConvertNodeShapesDefaultCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *) cd)->ShowDefaultNodeShape();
}

void DiagramStubs::ConvertNodeShapesOKCB(Widget, XtPointer cd, XtPointer) {
	DiagramViewer *v = (DiagramViewer *)cd;
        NToggleListDialog *d = v->GetNodeShapeDialog();
        int n = d->GetValue(0);
        string text1;
        d->GetItem(0, n, &text1);
	// NodeAlign::Type t = NodeAlign::String2Type(&text1);
	int c = Code::GetCode(text1.getstr());
        v->UpdateNodeShapeType(c);
}

void DiagramStubs::UpdateLineEndCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *)cd)->UpdateLineEnd();
}

void DiagramStubs::UpdateLineEndDefaultCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *) cd)->ShowDefaultLineEnd();
}

void DiagramStubs::UpdateLineEndOKCB(Widget, XtPointer cd, XtPointer) {
	DiagramViewer *v = (DiagramViewer *)cd;
        NToggleListDialog *d = v->GetLineEndDialog();
        int n = d->GetValue(0);
        int m = d->GetValue(1);
        string text1;
        string text2;
        d->GetItem(0, n, &text1);
        d->GetItem(1, m, &text2);
	LineEnd::Type e1 = LineEnd::String2Type(&text1);
	LineEnd::Type e2 = LineEnd::String2Type(&text2);
        v->UpdateLineEndSelection(e1, e2);
}


void DiagramStubs::UpdateCurveCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *) cd)->UpdateCurve();
}

void DiagramStubs::UpdateTextUnderlineCB(Widget, XtPointer cd, XtPointer) {
	((DiagramViewer *) cd)->UpdateTextUnderline();
}
