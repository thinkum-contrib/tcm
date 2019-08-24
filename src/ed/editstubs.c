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
#include "editstubs.h"
#include "inlineeditor.h"
#include "promptdialog.h"
#include "scaledialog.h"
#include "replacedialog.h"
#include "texteditdialog.h"
#include "fileselectiondialog.h"
#include "colorchooserdialog.h"
#include "ntogglelistdialog.h"
#include "fontchooserdialog.h"
#include "printer.h"
#include "document.h"
#include "helper.h"
#include "viewer.h"
#include "grid.h"
#include "menu.h"
#include "mstring.h"
#include <Xm/ToggleB.h>
#include <Xm/Text.h>

void EditStubs::HelpCB(Widget w, XtPointer cd, XtPointer) {
	Helper::HelpTopicType tp;
	XtVaGetValues(w, XmNuserData, &tp, NULL);
	((Helper *)cd)->Help(tp);
}

void EditStubs::LoadOKCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string fbuf;
	doc->GetFileSelectionDialog()->GetFileName(&fbuf);
	doc->LoadSave(&fbuf);
	doc->SetFSDir();
}

void EditStubs::CancelFSCB(Widget, XtPointer clientData, XtPointer) {
	((Document *)clientData)->SetFSDir();
}

void EditStubs::SaveAsOKCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string fbuf;
	doc->GetFileSelectionDialog()->GetFileName(&fbuf);
	doc->DoSaveAs(&fbuf);
	doc->SetFSDir();
}

void EditStubs::AnnotationOKCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	if (!check(doc))
		return;
	string t;
	doc->GetDocAnnotationDialog()->GetTextString(&t);
	doc->SetAnnotation(&t);
}

void EditStubs::SetModifiedCB(Widget w, XtPointer cd, XtPointer) {
	((Document *)cd)->SetModified(XmToggleButtonGetState(w));
}

void EditStubs::SetAutoResizeCB(Widget w, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	bool s = XmToggleButtonGetState(w);
	v->SetAutoResize(s);
	DrawWindow *mainwindow = v->GetMainWindow();
	mainwindow->SetAutoResize(s);
	Menu *menu = mainwindow->GetViewMenu();
	if (menu)
		Menu::SetChildToggleState(menu->GetWidget(), Menu::PULLDOWN, 
				   "Autoresizing", s);
}


void EditStubs::SetInlineEditCB(Widget w, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	bool s = XmToggleButtonGetState(w);
	v->SetInlineEdit(s);
	DrawWindow *mainwindow = v->GetMainWindow();
	mainwindow->SetInlineEdit(s);
	Menu *menu = mainwindow->GetViewMenu();
	if (menu)
		Menu::SetChildToggleState(menu->GetWidget(), Menu::PULLDOWN,
				   "In-line Editor", s);
}


void EditStubs::SetHierarchicCB(Widget w, XtPointer cd, XtPointer) {
	Document *d = (Document *)cd;
	bool s = XmToggleButtonGetState(w);
	if ( ! d->AllowHierarchic() )
		s = False;
	d->SetHierarchic(s);
//	DrawWindow *mainwindow = d->GetViewer()->GetMainWindow();
//	mainwindow->SetHierarchic(s);
//	Menu *menu = mainwindow->GetDocumentMenu();
//	if ( menu )
//		Menu::SetChildToggleState(menu->GetWidget(),
//			Menu::PULLDOWN, "Hierarchic Document", s);
//	Menu *menu = mainwindow->GetViewMenu();
//	if ( menu )
//		// enable / disable Zoom in/out
}


void EditStubs::ChangeNameCB(Widget w, XtPointer cd, XtPointer) {
	char *text = XmTextGetString(w);
	string name = text;
	((Document *)cd)->NewName(&name);
	XtFree(text);
}

void EditStubs::ChangeDirCB(Widget w, XtPointer cd, XtPointer) {
	char *text = XmTextGetString(w);
	string name = text;
	((Document *)cd)->NewDir(&name);
	XtFree(text);
}

void EditStubs::NewCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->New();
}

void EditStubs::LoadCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Load();
}

void EditStubs::AppendCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Append();
}

void EditStubs::SaveCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Save();
}

void EditStubs::SaveAsCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->SaveAs();
}

void EditStubs::SaveSelectionAsCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->SaveSelectionAs();
}

void EditStubs::QuitCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Quit();
}

void EditStubs::FindCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Find();
}

void EditStubs::ReplaceCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Replace();
}

void EditStubs::DocumentInfoCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->ShowDocInfo();
}

void EditStubs::DocumentSummaryCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->ShowSummary();
}

void EditStubs::DocumentSourceCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->ShowSource();
}

void EditStubs::DocumentSourceOKCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->SaveSource();
}

void EditStubs::CheckDocumentCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->CheckDocument();
}

void EditStubs::AnnotateDocumentCB(Widget, XtPointer cd, XtPointer) {
	((Document *)cd)->Annotate();
}

void EditStubs::ModelCheckPropertyCB(Widget, XtPointer cd, XtPointer) { 
        ((Document *)cd)->ModelCheckProperty();                        
} 

void EditStubs::ClearTraceCB(Widget, XtPointer cd, XtPointer) {
        ((Document *)cd)->ClearTrace();
}


void EditStubs::MoveCB(Widget w, XtPointer cd, XtPointer) {
	int num;
	XtVaGetValues(w, XmNuserData, &num, NULL);
	((Document *)cd)->Move((Document::MoveType)num);
}

void EditStubs::MakeLargerCB(Widget, XtPointer cd, XtPointer) {
	((Scaler *)cd)->MakeLarger();
}

void EditStubs::MakeSmallerCB(Widget, XtPointer cd, XtPointer) {
	((Scaler *)cd)->MakeSmaller();
}

void EditStubs::ScaleFactorCB(Widget, XtPointer cd, XtPointer) {
	((Scaler *)cd)->ScaleFactor();
}

void EditStubs::NormalScaleCB(Widget, XtPointer cd, XtPointer) {
	((Scaler *)cd)->NormalScale();
}

void EditStubs::WholeDrawingCB(Widget, XtPointer cd, XtPointer) {
	((Scaler *)cd)->WholeDrawing();
}

void EditStubs::ScaleFactorOKCB(Widget, XtPointer clientData, XtPointer) {
	Scaler *z = (Scaler *)clientData;
	z->SetScaleFactor((double)z->GetScaleDialog()->GetScaleValue()/10);
}

void EditStubs::FindAllCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string s;
	FindDialog *f = doc->GetFindDialog();
	f->GetTextString(&s);
	doc->FindAll(&s, f->SensitiveOn(), f->SubstringOn(), f->NameOnlyOn());
}

void EditStubs::FindNextCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string s;
	FindDialog *f = doc->GetFindDialog();
	f->GetTextString(&s);
	doc->FindNext(&s, f->SensitiveOn(), f->SubstringOn(), f->NameOnlyOn());
}

void EditStubs::ReplaceFindCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string s;
	ReplaceDialog *r = doc->GetReplaceDialog();
	r->GetTextString(&s);
	doc->FindNext(&s, r->SensitiveOn(), r->SubstringOn(), r->NameOnlyOn());
}

void EditStubs::ReplaceNextCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string s1, s2;
	ReplaceDialog *r = doc->GetReplaceDialog();
	r->GetTextString(&s1);
	r->GetReplaceText(&s2);
	doc->ReplaceNext(&s1, &s2, r->SensitiveOn(), r->SubstringOn(), 
		r->NameOnlyOn());
}

void EditStubs::ReplaceAllCB(Widget, XtPointer clientData, XtPointer) {
	Document *doc = (Document *)clientData;
	string s1, s2;
	ReplaceDialog *r = doc->GetReplaceDialog();
	r->GetTextString(&s1);
	r->GetReplaceText(&s2);
	doc->ReplaceAll(&s1, &s2, r->SensitiveOn(), r->SubstringOn(), 
		r->NameOnlyOn());
}

void EditStubs::SaveAsPSCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	string s;
	p->GetFileSelectionDialog()->GetFileName(&s);
	p->DoSaveAsPS(&s);
}

void EditStubs::SaveAsEPSCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	string s;
	p->GetFileSelectionDialog()->GetFileName(&s);
	p->DoSaveAsEPS(&s);
}

void EditStubs::SaveAsFigTexCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	string s;
	p->GetFileSelectionDialog()->GetFileName(&s);
	p->DoSaveAsFigTex(&s);
}

void EditStubs::SaveAsPNGCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	string s;
	p->GetFileSelectionDialog()->GetFileName(&s);
	p->DoSaveAsPNG(&s);
}

void EditStubs::SaveAsFigPSCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	string s;
	p->GetFileSelectionDialog()->GetFileName(&s);
	p->DoSaveAsFigPS(&s);
}

void EditStubs::SetNameCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	PromptDialog *dialog = p->GetPromptDialog();
	string s;
	dialog->GetTextString(&s);
	p->SetName(&s);
}

void EditStubs::SetPrintCommandCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	PromptDialog *dialog = p->GetPromptDialog();
	string s;
	dialog->GetTextString(&s);
	p->SetPrintCommand(&s);
}

void EditStubs::SetPreviewCommandCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	PromptDialog *dialog = p->GetPromptDialog();
	string s;
	dialog->GetTextString(&s);
	p->SetPreviewCommand(&s);
}

void EditStubs::SetCopiesCB(Widget, XtPointer clientData, XtPointer) {
	Printer *p = (Printer *)clientData;
	p->SetCopies(p->GetScaleDialog()->GetScaleValue());
}

void EditStubs::ShowPageBoundaryCB(Widget w, XtPointer cd, XtPointer) {
	((Printer *)cd)->SetShowPageBoundary(XmToggleButtonGetState(w));
}

void EditStubs::PageOrientationCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, NULL);
		((Printer *)cd)->SetPageOrientation(num/2);
	}
}

void EditStubs::ShowDocumentInfoCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, NULL);
		((Printer *)cd)->ShowInfo(num/2);
	}
}

void EditStubs::ShowPageNumbersCB(Widget w, XtPointer cd, XtPointer) {
	((Printer *)cd)->SetPageNumbering(XmToggleButtonGetState(w));
}

void EditStubs::PrintCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->Print();
}

void EditStubs::ShowPrintPreviewCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->ShowPrintPreview();
}

void EditStubs::ExportAsCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->ExportAs();
}

void EditStubs::ShowPrinterQueueCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->ShowPrinterQueue();
}

void EditStubs::PrinterNameCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->Name();
}

void EditStubs::PrinterCopiesCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->Copies();
}

void EditStubs::PrintCommandCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->PrintCommand();
}

void EditStubs::PrinterQueueCommandCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->PrinterQueueCommand();
}

void EditStubs::PrinterRemoveCommandCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->PrinterRemoveCommand();
}

void EditStubs::PreviewCommandCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->PreviewCommand();
}

void EditStubs::SetPrintColorsCB(Widget w, XtPointer cd, XtPointer) {
	((Printer *)cd)->SetPrintColors(XmToggleButtonGetState(w));
}

void EditStubs::SetDuplexCB(Widget w, XtPointer cd, XtPointer) {
	((Printer *)cd)->SetDuplex(XmToggleButtonGetState(w));
}

void EditStubs::SetTumbleCB(Widget w, XtPointer cd, XtPointer) {
	((Printer *)cd)->SetTumble(XmToggleButtonGetState(w));
}

void EditStubs::BannerPageCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, NULL);
		((Printer *)cd)->SetBannerPage(num/2);
	}
}

void EditStubs::PageSizeCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		// get menu item label and look to which pagesize
		// it corresponds
		XmString xms;
                xms = CreateXmString("");
                XtVaGetValues(w, XmNlabelString, &xms, NULL);
                char *txt;
                if (XmStringGetLtoR(xms, XmFONTLIST_DEFAULT_TAG, &txt)) {
			string s = txt;
			PageSize::Type t = PageSize::Substring2Type(&s);
			((Printer *)cd)->SetPageSize(t);
                        XtFree(txt);
                }
                XmStringFree(xms);
	}
}

void EditStubs::DefaultLineWidthCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultLineWidth();
}

void EditStubs::DefaultLineStyleCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultLineStyle();
}

void EditStubs::UpdateLineColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateLineColor();
}

void EditStubs::DefaultLineColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultLineColor();
}

void EditStubs::UpdateTextColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateTextColor();
}

void EditStubs::DefaultTextColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultTextColor();
}

void EditStubs::UpdateFillColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateFillColor();
}

void EditStubs::DefaultFillColorCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultFillColor();
}

void EditStubs::UpdateLineWidthCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateLineWidth();
}

void EditStubs::UpdateLineStyleCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateLineStyle();
}

void EditStubs::DefaultLineColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	v->SetDefaultLineColor(&s);
}

void EditStubs::UpdateLineColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	v->UpdateLineColorSelection(&s);
}

void EditStubs::DefaultTextColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	v->SetDefaultTextColor(&s);
}

void EditStubs::UpdateTextColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	v->UpdateTextColorSelection(&s);
}

void EditStubs::DefaultFillColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	bool b = v->GetColorChooserDialog()->FillToggleOn();
	if (b)
		v->SetDefaultFillStyle(FillStyle::FILLED);
	else
		v->SetDefaultFillStyle(FillStyle::UNFILLED);
	v->SetDefaultFillColor(&s);
}

void EditStubs::UpdateFillColorOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	string s;
	v->GetColorChooserDialog()->GetTextString(&s);
	FillStyle::Type f;
	if (v->GetColorChooserDialog()->FillToggleOn()) {
		f = FillStyle::FILLED;
	}
	else {
		f = FillStyle::UNFILLED;
	}
	v->UpdateFillColorSelection(&s, f);
}

void EditStubs::DefaultLineColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigLineColor();
}

void EditStubs::UpdateLineColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultLineColor();
}

void EditStubs::DefaultTextColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigTextColor();
}

void EditStubs::UpdateTextColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultTextColor();
}

void EditStubs::DefaultFillColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigFillColor();
}

void EditStubs::UpdateFillColorDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultFillColor();
}

void EditStubs::DefaultLineWidthOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
        NToggleListDialog *d = v->GetLineWidthDialog();
        int n = d->GetValue(0);
        string text;
        d->GetItem(0, n, &text);
	int wd = text.toint();
	v->SetDefaultLineWidth(wd);
}

void EditStubs::DefaultLineWidthDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigLineWidth();
}

void EditStubs::UpdateLineWidthOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
        NToggleListDialog *d = v->GetLineWidthDialog();
        int n = d->GetValue(0);
        string text;
        d->GetItem(0, n, &text);
	int wd = text.toint();
	v->UpdateLineWidthSelection(wd);
}

void EditStubs::UpdateLineWidthDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultLineWidth();
}

void EditStubs::DefaultLineStyleOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	NToggleListDialog *d = v->GetLineStyleDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	v->SetDefaultLineStyle(LineStyle::String2Type(&text));
}

void EditStubs::DefaultLineStyleDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigLineStyle();
}

void EditStubs::UpdateLineStyleOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	NToggleListDialog *d = v->GetLineStyleDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	v->UpdateLineStyleSelection(LineStyle::String2Type(&text));
}

void EditStubs::UpdateLineStyleDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultLineStyle();
}

void EditStubs::DefaultFontCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultFont();
}

void EditStubs::UpdateFontCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateFont();
}

void EditStubs::DefaultFontOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	FontChooserDialog *d = v->GetFontChooserDialog();
	v->SetDefaultFontAttributes(
		d->GetFamily(), d->GetStyle(), d->GetSize());
}

void EditStubs::UpdateFontOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	FontChooserDialog *d = v->GetFontChooserDialog();
	// -1 means that this font attribute should not be updated.
	int f = d->GetOptionValue(0) > 0 ? d->GetFamily() : -1;
	int s = d->GetOptionValue(1) > 0 ? d->GetStyle() : -1;
	int p = d->GetOptionValue(2) > 0 ? d->GetSize() : -1;
	v->UpdateFontSelection(f, s, p);
}

void EditStubs::DefaultFontDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigFont();
}

void EditStubs::UpdateFontDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultFont();
}

void EditStubs::DefaultTextAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->DefaultTextAlignment();
}

void EditStubs::DefaultTextAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	NToggleListDialog *d = v->GetTextAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	v->SetDefaultTextAlignment(TextAlign::String2Type(&text));
}

void EditStubs::DefaultTextAlignmentDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowConfigTextAlignment();
}

void EditStubs::UpdateTextAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->UpdateTextAlignment();
}

void EditStubs::UpdateTextAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Viewer *v = (Viewer *)cd;
	NToggleListDialog *d = v->GetTextAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	v->UpdateTextAlignmentSelection(TextAlign::String2Type(&text));
}

void EditStubs::UpdateTextAlignmentDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *) cd)->ShowDefaultTextAlignment();
}

void EditStubs::UpdateFSFilesCB(Widget, XtPointer cd, XtPointer) {
	((Printer *)cd)->UpdateFSFiles();
}

void EditStubs::UpdateTextCB(Widget, XtPointer cd, XtPointer cbs) {
	XmAnyCallbackStruct *a = (XmAnyCallbackStruct *)cbs;
	int reason = a->reason;
	InlineEditor *e = (InlineEditor *)cd;
	if (!check(e))
		return;
	if (reason == XmCR_OK) {
		string t;
		e->GetTextEditDialog()->GetTextString(&t);
		e->StopWindow(&t);
	}
	else e->CancelWindow();
}

void EditStubs::GridSizeOKCB(Widget, XtPointer cd, XtPointer) {
	Grid *g = (Grid *)cd;
	g->SetGridSize(g->GetScaleDialog()->GetScaleValue());
}
 
void EditStubs::PointDistanceOKCB(Widget, XtPointer cd, XtPointer) {
	Grid *g = (Grid *)cd;
	g->SetPointDistance(g->GetScaleDialog()->GetScaleValue());
}

void EditStubs::PointSnappingCB(Widget w, XtPointer cd, XtPointer) {
	((Grid *)cd)->SetSnap(XmToggleButtonGetState(w));
}
 
void EditStubs::PointDistanceCB(Widget, XtPointer cd, XtPointer) {
	((Grid *)cd)->PointDistance();
}
 
void EditStubs::ShowGridCB(Widget w, XtPointer cd, XtPointer) {
	((Grid *)cd)->SetShowGrid(XmToggleButtonGetState(w));
}
 
void EditStubs::GridSizeCB(Widget, XtPointer cd, XtPointer) {
	((Grid *)cd)->GridSize();
}

void EditStubs::UndoCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *)cd)->Undo();
}
 
void EditStubs::RedoCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *)cd)->Redo();
}

void EditStubs::RefreshCB(Widget, XtPointer cd, XtPointer) {
	((Viewer *)cd)->Refresh();
}

