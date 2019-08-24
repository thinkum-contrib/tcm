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
#ifndef _EDITSTUBS_H
#define _EDITSTUBS_H

#include <X11/Intrinsic.h>

/// static member functions as interface between callback and class.
class EditStubs {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// Callback for the help functions.
	static void HelpCB(Widget, XtPointer, XtPointer);

	/// Callbacks for load and save.
	static void LoadOKCB(Widget, XtPointer, XtPointer);
	/// 
	static void SaveAsOKCB(Widget, XtPointer, XtPointer);
	/// 
	static void AnnotationOKCB(Widget, XtPointer, XtPointer);
	///
	static void CancelFSCB(Widget, XtPointer, XtPointer);

	/// Callbacks for find/replace functions.
	static void FindNextCB(Widget, XtPointer, XtPointer);
	///
	static void FindAllCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceFindCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceNextCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceAllCB(Widget, XtPointer, XtPointer);

	/// Callbacks for some editor properties.
	static void ChangeNameCB(Widget, XtPointer, XtPointer);
	///
	static void ChangeDirCB(Widget, XtPointer, XtPointer);
	///
	static void SetModifiedCB(Widget, XtPointer, XtPointer);
	///
	static void SetAutoResizeCB(Widget, XtPointer, XtPointer);
	///
	static void SetInlineEditCB(Widget, XtPointer, XtPointer);

	/// Callbacks for file functions.
	static void NewCB(Widget, XtPointer, XtPointer);
	///
	static void LoadCB(Widget, XtPointer, XtPointer);
	///
	static void AppendCB(Widget, XtPointer, XtPointer);
	///
	static void SaveCB(Widget, XtPointer, XtPointer);
	///
	static void SaveAsCB(Widget, XtPointer, XtPointer);
	///
	static void SaveSelectionAsCB(Widget, XtPointer, XtPointer);
	///
	static void QuitCB(Widget, XtPointer, XtPointer);

	/// Callbacks for search functions
	static void FindCB(Widget, XtPointer, XtPointer);
	///
	static void ReplaceCB(Widget, XtPointer, XtPointer);

	/// Callbacks for document functions.
	static void DocumentInfoCB(Widget, XtPointer, XtPointer);
	///
	static void DocumentSummaryCB(Widget, XtPointer, XtPointer);
	///
	static void DocumentSourceCB(Widget, XtPointer, XtPointer);
	///
	static void DocumentSourceOKCB(Widget, XtPointer, XtPointer);
	///
	static void CheckDocumentCB(Widget, XtPointer, XtPointer);
	///
	static void AnnotateDocumentCB(Widget, XtPointer, XtPointer);
	///
        static void ModelCheckPropertyCB(Widget, XtPointer, XtPointer);
        ///
        static void ClearTraceCB(Widget, XtPointer, XtPointer);
	///
	static void SetHierarchicCB(Widget, XtPointer, XtPointer);

	/// Callbacks for scale functions.
	static void MakeLargerCB(Widget, XtPointer, XtPointer);
	///
	static void MakeSmallerCB(Widget, XtPointer, XtPointer);
	///
	static void ScaleFactorCB(Widget, XtPointer, XtPointer);
	///
	static void NormalScaleCB(Widget, XtPointer, XtPointer);
	///
	static void WholeDrawingCB(Widget, XtPointer, XtPointer);
	///
	static void ScaleFactorOKCB(Widget, XtPointer, XtPointer);

	/// Callback for arrow buttons.
	static void MoveCB(Widget, XtPointer, XtPointer);

	/// Callbacks for Printer functions.
	static void SaveAsPSCB(Widget, XtPointer, XtPointer);
	///
	static void SaveAsEPSCB(Widget, XtPointer, XtPointer); 
	///
	static void SaveAsFigTexCB(Widget, XtPointer, XtPointer); 
	///
	static void SaveAsFigPSCB(Widget, XtPointer, XtPointer); 
	///
	static void SaveAsPNGCB(Widget, XtPointer, XtPointer); 
	///
	static void SetNameCB(Widget, XtPointer, XtPointer);
	///
	static void SetPrintCommandCB(Widget, XtPointer, XtPointer);
	///
	static void SetPreviewCommandCB(Widget, XtPointer, XtPointer);
	///
	static void SetCopiesCB(Widget, XtPointer, XtPointer);

	/// Callbacks for Printer functions.
	static void ExportAsCB(Widget, XtPointer, XtPointer);
	///
	static void ShowPrintPreviewCB(Widget, XtPointer, XtPointer);
	///
	static void PrintCB(Widget, XtPointer, XtPointer);
	///
	static void ShowPrinterQueueCB(Widget, XtPointer, XtPointer);
	///
	static void PrinterNameCB(Widget, XtPointer, XtPointer);
	///
	static void PrinterCopiesCB(Widget, XtPointer, XtPointer);
	///
	static void PrintCommandCB(Widget, XtPointer, XtPointer);
	///
	static void PrinterQueueCommandCB(Widget, XtPointer, XtPointer);
	///
	static void PrinterRemoveCommandCB(Widget, XtPointer, XtPointer);
	///
	static void PreviewCommandCB(Widget, XtPointer, XtPointer);
	///
	static void SetPrintColorsCB(Widget, XtPointer, XtPointer);
	///
	static void SetTumbleCB(Widget, XtPointer, XtPointer);
	///
	static void SetDuplexCB(Widget, XtPointer, XtPointer);
	///
	static void BannerPageCB(Widget, XtPointer, XtPointer);

	/// Callbacks for Page functions.
	static void ShowPageBoundaryCB(Widget, XtPointer, XtPointer);
	///
	static void PageOrientationCB(Widget, XtPointer, XtPointer);
	///
	static void PageSizeCB(Widget, XtPointer, XtPointer);
	///
	static void ShowPageNumbersCB(Widget, XtPointer, XtPointer);
	///
	static void ShowDocumentInfoCB(Widget, XtPointer, XtPointer);

	/// Callbacks for Properties functions.
	///
	static void DefaultLineWidthCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineWidthOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineWidthDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineWidthCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineWidthOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineWidthDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateLineColorCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineColorDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineColorCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineColorDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateTextColorCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextColorDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultTextColorCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultTextColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultTextColorDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateFillColorCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateFillColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateFillColorDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultFillColorCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultFillColorOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultFillColorDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void DefaultLineStyleCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineStyleOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultLineStyleDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineStyleCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineStyleOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateLineStyleDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void DefaultFontCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultFontOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultFontDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateFontCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateFontOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateFontDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void DefaultTextAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultTextAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultTextAlignmentDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextAlignmentDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateFSFilesCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTextCB(Widget, XtPointer, XtPointer);
	
	/// Callbacks for the grid functions.
	static void PointSnappingCB(Widget, XtPointer, XtPointer);
	///
	static void ShowGridCB(Widget, XtPointer, XtPointer);
	///
	static void GridSizeCB(Widget, XtPointer, XtPointer);
	///
	static void PointDistanceCB(Widget, XtPointer, XtPointer);
	/// 
	static void GridSizeOKCB(Widget, XtPointer, XtPointer);
	///
	static void PointDistanceOKCB(Widget, XtPointer, XtPointer);

	/// view/edit functions.
	static void UndoCB(Widget, XtPointer, XtPointer);
	///
	static void RedoCB(Widget, XtPointer, XtPointer);
	/// 
	static void RefreshCB(Widget, XtPointer, XtPointer);
};
#endif
