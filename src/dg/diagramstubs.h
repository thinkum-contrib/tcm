//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _DIAGRAMSTUBS_H
#define _DIAGRAMSTUBS_H

#include "editstubs.h"

/// Callback stubs specific for all diagram editors.
class DiagramStubs: public EditStubs {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// Callbacks for setting current node and edge.
	static void SetNodeCB(Widget w, XtPointer num, XtPointer cbs);
	///
	static void SetEdgeCB(Widget w, XtPointer num, XtPointer cbs);
	///
	static void SetCurveCB(Widget w, XtPointer num, XtPointer cbs);

	/// Callbacks for the edit functions.
	static void AlignNodeShapesCB(Widget, XtPointer, XtPointer);
	///
	static void AlignNodeShapesOKCB(Widget, XtPointer, XtPointer);
	///
	static void AlignNodeShapesDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteAllCB(Widget, XtPointer, XtPointer);
	///
	static void CutCB(Widget, XtPointer, XtPointer);
	///
	static void CopyCB(Widget, XtPointer, XtPointer);
	///
	static void PasteCB(Widget, XtPointer, XtPointer);
	///
	static void DuplicateCB(Widget, XtPointer, XtPointer);
	///
	static void SelectAllCB(Widget, XtPointer, XtPointer);
	///
	static void SameSizeCB(Widget, XtPointer, XtPointer);

	///
	static void AnnotateCB(Widget, XtPointer, XtPointer);
	///
	static void SubjectAnnotationOKCB(Widget, XtPointer, XtPointer);

	///
	static void ShowIndexesCB(Widget w, XtPointer, XtPointer);

	/// Callbacks for view functions.
	static void ZoomInCB(Widget, XtPointer, XtPointer);
	///
	static void ZoomOutCB(Widget, XtPointer, XtPointer);
	///
	static void TopLevelCB(Widget, XtPointer, XtPointer);
	///
	static void ReindexCB(Widget w, XtPointer, XtPointer);
 
	/// Callbacks for properties functions.
	///
	static void DefaultNodeLineStyleCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultEdgeLineStyleCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateNodeShapeTypeCB(Widget, XtPointer, XtPointer);
	///
	static void ConvertNodeShapeTypeCB(Widget, XtPointer, XtPointer);
	///
	static void ConvertNodeShapesOKCB(Widget, XtPointer, XtPointer);
	///
	static void ConvertNodeShapesDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateLineEndCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineEndDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineEndOKCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateCurveCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextUnderlineCB(Widget, XtPointer, XtPointer);
};
#endif
