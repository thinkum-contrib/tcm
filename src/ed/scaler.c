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
#include "scaler.h"
#include "viewer.h"
#include "grafport.h"
#include "drawwindow.h"
#include "scaledialog.h"
#include "editstubs.h"
#include "config.h"
#include "inputfile.h"
#include "outputfile.h"

const double Scaler::MIN_SCALE_VALUE = 0.1;
const double Scaler::MAX_SCALE_VALUE = 10.0;
const double Scaler::MIN_SCALE_FACTOR = 0.1;  
const double Scaler::MAX_SCALE_FACTOR = 5.0; 

Scaler::Scaler(Config *c, Viewer *v, DrawWindow *d) {
	viewer = v;
	mainwindow = d;
	SetScaleFactor(c->GetScaleFactor());
	defaultScaleFactor = scaleFactor;
	scaleValue = 1.0;
	scaleDialog = new ScaleDialog(d->GetWidget());
	scaleDialog->Initialize();
	scaleDialog->SetTitle("Scale factor");
	scaleDialog->SetScaleLabel("Scale factor");
	scaleDialog->SetValueChangedCallback(EditStubs::ScaleFactorOKCB, this);
}

Scaler::~Scaler() {
	delete scaleDialog;
}

void Scaler::MakeLarger() {
	mainwindow->SetStatus("action: make larger");
	SetScaleValue (scaleValue * scaleFactor);
}

void Scaler::MakeSmaller() {
	mainwindow->SetStatus("action: make smaller");
	SetScaleValue (scaleValue / scaleFactor);
}

void Scaler::NormalScale() {
	mainwindow->SetStatus("action: normal scale");
	// scaleValue = -1;
	SetScaleValue(1);
	mainwindow->SetStatus("document in normal scale");
}

void Scaler::WholeDrawing() {
	mainwindow->SetStatus("action: fit whole drawing to one page");
	double width, height;
	// physical size of the data.
	Point tp, br;
	viewer->CalcSizeElements(tp, br);
	// soft shapes size.
	double sx = br.x + 10;
	double sy = br.y + 10;
	// hard shapes size
	double hx = Scale(sx);
	double hy = Scale(sy);
	// size of physical page.
	viewer->GetPageSize(width, height);
	if (hx > width || hy > height) {
		// does not fit to one page.
		double f1 = width / sx;
		double f2 = height / sy;
		double scale_val;
		if (f1<f2)
			scale_val = f1;
		else
			scale_val = f2;
		SetScaleValue(scale_val);
	}
	mainwindow->SetStatus("whole document on single page");
}

void Scaler::ScaleFactor() {
	mainwindow->SetStatus("action: scale factor");
	int initValue = (int)(scaleFactor*10 + 0.5);
	int minValue = (int)(MIN_SCALE_FACTOR*10 + 0.5);
	int maxValue = (int)(MAX_SCALE_FACTOR*10 + 0.5);
	scaleDialog->SetScaleValues(minValue, maxValue, 
		initValue, 1, (int)(defaultScaleFactor*10));
	scaleDialog->Popup();
}

void Scaler::SetScaleFactor(double d) {
	scaleFactor = (d<MAX_SCALE_FACTOR) ? d : MAX_SCALE_FACTOR;
	if (scaleFactor < MIN_SCALE_FACTOR)
		scaleFactor = MIN_SCALE_FACTOR;
	string txt = "scale factor set to ";
	txt += scaleFactor;
	mainwindow->SetStatus(&txt);
}

void Scaler::SetScaleValue(double newValue) {
	if (scaleValue != newValue && newValue >= MIN_SCALE_VALUE && 
	    newValue <= MAX_SCALE_VALUE) {
		string zbuf;
		zbuf.setPrecision(1);
		scaleValue = newValue;
		viewer->GetGrafport()->SetZoomValue(scaleValue);
		mainwindow->FitDocument();
		viewer->Refresh();
		string txt = "scaled to ";
		txt += scaleValue*100;
		txt += " percent"; 
		mainwindow->SetStatus(&txt);
		zbuf = scaleValue*100;
		zbuf += "%";
		mainwindow->SetScaleValue(zbuf.getstr());
	}
	else if (newValue < MIN_SCALE_VALUE)
		mainwindow->SetStatus("this is small enough");
	else if (newValue > MAX_SCALE_VALUE)
		mainwindow->SetStatus("this is big enough");
}


void Scaler::Save(OutputFile *ofile) {
        (*ofile) << "Scale " << '\n';
        (*ofile) << "{\n";
        (*ofile) << "\t{ " << "ScaleValue " << scaleValue << " }\n";
        (*ofile) << "}\n\n";
}
 
bool Scaler::Load(InputFile *ifile, double format) {
        if (format < 1.30)
                return True;
        string val = "Scale";
	string s1;
        if (!(ifile->ReadWord(&val) &&
             ifile->LookupChar('{') &&
             ifile->ReadAttribute("ScaleValue", &s1) &&
	     ifile->LookupChar('}')))
                return False;
	SetScaleValue(s1.todouble());
	return True;
}

bool Scaler::Check(InputFile *ifile, double format) {
        if (format < 1.30)
                return True;
        string val = "Scale";
        return (ifile->ReadWord(&val) &&
                ifile->LookupChar('{') &&
                ifile->ReadAttribute("ScaleValue", &val) &&
                ifile->LookupChar('}'));
}
