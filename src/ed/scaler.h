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
#ifndef _SCALER_H
#define _SCALER_H

#include "util.h"
#include "point.h"
#include "lstring.h"
class Viewer;
class DrawWindow;
class Config;
class ScaleDialog;
class InputFile;
class OutputFile;

/// class for scaling coordinates
class Scaler {
/*@Doc: {\large {\bf scope:} editor} */
public:
	///
	Scaler(Config *c, Viewer *v, DrawWindow *d);
	///
	virtual ~Scaler();

	/// Make larger. Change scale value.
	void MakeLarger(); 	

	/// Make smaller. Change scale value.
	void MakeSmaller(); 

	/// Popup scale factor dialog.
	void ScaleFactor(); 

	/// Return to normal scaling.
	void NormalScale();

	/// Calculate scale value such that whole document fits to one page.
	void WholeDrawing();

	///
	void ScreenFit();

	/// scale coordinate x.
	double Scale(double x) const {return x * scaleValue;}

	///
	Point Scale(const Point *p) const {
		Point pt; pt.x = int(p->x * scaleValue);
		pt.y = int(p->y * scaleValue); return pt;
	}
	/// Correct X-window coordinate to the right scaled coordinate.
	double ScaleCorrect(double x) const {return x / scaleValue;}
	///
	Point ScaleCorrect(const Point *p) const {
		Point pt; pt.x = int(p->x / scaleValue);
		pt.y = int(p->y / scaleValue); return pt;};

	/// Really do the scaling. Redraws the contents of the viewer.
	void SetScaleValue(double newValue); 
	///
	double GetScaleValue() const {return scaleValue;}
	///
	void SetScaleFactor(double d);
	///
	DrawWindow *GetMainWindow() const {return mainwindow;}
	///
	ScaleDialog *GetScaleDialog() const {return scaleDialog;}

	/// Save scale value to file.
        void Save(OutputFile *f);
 
        /// Load scale value from file.
        bool Load(InputFile *f, double format);
 
        /// Check (but not load) scale value from file.
        bool Check(InputFile *f, double format);

private:
	///
	Viewer *viewer;
	///
	DrawWindow *mainwindow;
	///
	ScaleDialog *scaleDialog;

	/// current value to multiply coordinates with 1 = no scaling.
	double scaleFactor; 
	///
	double scaleValue;
	///
	double defaultScaleFactor;
	///
	static const double MIN_SCALE_VALUE;
	///
	static const double MAX_SCALE_VALUE;
	///
	static const double MIN_SCALE_FACTOR;
	///
	static const double MAX_SCALE_FACTOR;
};
#endif
