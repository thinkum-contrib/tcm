//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SSDTRIPLECLASSBOX_H
#define _SSDTRIPLECLASSBOX_H

#include "tripleclassbox.h"
class SSDSingleClassBox;
class SSDDoubleClassBox;
 
/// A triple box used for a object class.
class SSDTripleClassBox: public TripleClassBox {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDTripleClassBox(ShapeView *v, Grafport *g, int x, int y, 
		int w = TRIPLECLASSBOX_WIDTH, int h = TRIPLECLASSBOX_HEIGHT);
	///
	SSDTripleClassBox(const SSDTripleClassBox &s);
	///
	SSDTripleClassBox(const SSDDoubleClassBox &s);
	///
	SSDTripleClassBox(const SSDSingleClassBox &s);
	///
        ~SSDTripleClassBox();
	///
	Shape *Clone() {return new SSDTripleClassBox(*this);}
	///
        int GetClassType() const {return Code::SSD_TRIPLE_CLASS_BOX;}

	///
        void SetFont(XFont *ft);
        ///
        void SetTextColor(const string *color);
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;
        ///
	void AdjustSize();

	///
        void UpdateShowStereotype(bool b);
        ///
        void UpdateShowProperties(bool b);
 
        /// update string of stereotype text shape and redraw.
        void UpdateStereotypeLabelString(const string *s);
        ///
        const string *GetStereotypeLabelString() {
			return stereotypeLabel->GetString();}
	///
	TextShape *GetStereotypeLabel() const {return stereotypeLabel;}

        /// update string of properties text shape and redraw.
        void UpdatePropertiesLabelString(const string *s);
        ///
        const string *GetPropertiesLabelString() {
                        return propertiesLabel->GetString();}
        ///
        TextShape *GetPropertiesLabel() const {return propertiesLabel;}

	///
	void SetTextShape();

	/// contains s as string (case sensitive, substring).
        bool HasString(const string *s, bool sens, bool sub) const;
        ///
        bool HasString(const string*, bool, bool, List<TextShape *> *list);
 
	///
        void SetShowStereotype(bool b) {showStereotype=b;}
        ///
        void SetShowProperties(bool b) {showProperties=b;}
	///
        bool IsShowStereotype() const {return showStereotype;}
        ///
        bool IsShowProperties() const {return showProperties;}
 
	///
        void WriteMembers(OutputFile *f);
        ///
        bool ReadMembers(InputFile *f, double format);
protected:
	///
	virtual void CalcPositionLabels();
private:
	///
	void DrawTextShapes();
        ///
	int RequiredHeight();
	///
	int RequiredWidth();
	///
	int DoubleBoxHeight();
	///
	int TripleBoxHeight();
        ///
        void SetStereotypeLabelString(const string *s) {
			stereotypeLabel->SetString(s);}
        ///
        void SetPropertiesLabelString(const string *s) {
                        propertiesLabel->SetString(s);}
	///
	void CalcPositionLabels2();
        ///
        void CalcPositionStereotypeLabel();
        ///
        void CalcPositionPropertiesLabel();
	///
	void AdjustSizes(const string *s);
        ///
        TextShape *stereotypeLabel;
        ///
        TextShape *propertiesLabel;
	///
        bool showStereotype;
        ///
        bool showProperties;
};
#endif
