////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include <math.h>
#include "binaryrelationship.h"
#include "c2r2mlistline.h"
#include "cbobjectlinkedge.h"
#include "cbclasslinkedge.h"
#include "cbdmessage.h"
#include "erviewer.h"
#include "cbviewer.h"
#include "updatereaddirectioncmd.h"
#include "updatemessagedirectioncmd.h"


C2R2MListLine::C2R2MListLine(ShapeView *v, Grafport *g, GShape *node1, 
							GShape *node2, List<Point *> *aline, bool Curved): 
		T4TListLine(v, g, node1, node2, aline, Curved) {
	InitTextShapes();
	plist->add(new Point(1, 2));	//add first dummy point to plist...
}

C2R2MListLine::C2R2MListLine(ShapeView *v, Grafport *g, GShape *node1,
	GShape *node2, bool Curved): T4TListLine(v, g, node1, node2, Curved) {
	InitTextShapes();
}

void C2R2MListLine::InitTextShapes() {
	// names are default underlined.
	GetName()->SetUnderlined(True);
	GetTextShape1()->SetDescription("Cardinality Constraint");
	GetTextShape2()->SetDescription("Cardinality Constraint");
	GetTextShape3()->SetDescription("Role Name");
	GetTextShape4()->SetDescription("Role Name");
	GetTextShape1()->SetOneLine(True);
	GetTextShape2()->SetOneLine(True);
	SetNameDirection(ReadDirection::NONE);
	plist = new List <Point *>;
}

bool C2R2MListLine::SetAssocSubject(AssocList *al) {
	if (!T4TListLine::SetAssocSubject(al))
		return False;
	int classType = GetSubject()->GetClassType();
	if (check(GetSubject() && 
	    (classType==Code::CBD_CLASS_LINK_EDGE ||
	     classType==Code::CBD_OBJECT_LINK_EDGE)))
		return True;
	SetSubject(0);
	return False;
}




void C2R2MListLine::SetTextShape() {
	T4TListLine::SetTextShape();
	int classType = GetSubject()->GetClassType();
	if (check(GetSubject() && 
	    (classType==Code::CBD_CLASS_LINK_EDGE ||
	     classType==Code::CBD_OBJECT_LINK_EDGE))) {
		GetTextShape1()->SetString(
			((BinaryRelationship *)GetSubject())->GetConstraint1());
		GetTextShape2()->SetString(
			((BinaryRelationship *)GetSubject())->GetConstraint2());
		GetTextShape3()->SetString(((BinaryRelationship *)GetSubject())->
				GetRoleName1());
		GetTextShape4()->SetString(((BinaryRelationship *)GetSubject())->
				GetRoleName2());

		if (!check(GetSubject()))
			return;
//		unsigned numItems = ((CBObjectLinkEdge *)GetSubject())->NrOfMessages();
//		unsigned numCLEItems = ((CBClassLinkEdge *)GetSubject())->NrOfMessages();

		for (unsigned i=0; i<plist->count(); i++) {
			TextShape *t = new TextShape(GetView(), GetGrafport(), this);
			t->SetDescription("Message");
			t->SetFont(GetName()->GetFont());
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(i);
			t->SetString(((CBObjectLinkEdge *)GetSubject())->GetMessage(i)->GetString());
			t->SetParent(this);
			t->SetPosition(plist->elem(i));
			t->SetDirected(True);
			CBDMessage::DirectionType tdir = 
			(((CBObjectLinkEdge *)GetSubject())->GetMessage(i)->GetDirection());
			t->SetReadDirection((ReadDirection::Type) tdir);
			GetTList()->add(t);
		}
	}
}

TextShape *C2R2MListLine::ChooseTextShape(int x, int y) {
	Rectangle rect2(GetName()->GetTopLeft()->x +
			GetName()->GetWidth(), 
			GetName()->GetTopLeft()->y,
			16,
			GetName()->GetHeight());
	if (rect2.Inside(x, y)) {
		if (GetName()->GetStringWidth() > 0) {	// toggle OK
			int newDir = ((int) GetNameDirection() + 1) % 3;
			ERViewer *erviewer = dynamic_cast<ERViewer *>(GetViewer());
			if (erviewer)
				erviewer->UpdateReadDirection((ReadDirection::Type) newDir);
		}	//toggle OK
		return GetName();
	}

	int up_x = 0;
	int up_y = 0;
	int dn_x = 0;
	int dn_y = 0;
	bool ADJUSTING = False;
	
	Point p1 = *GetPosition();
	Point p2 = *(GetName()->GetPosition());

	if (GetNameDirection() != ReadDirection::NONE)
		p2 = RecalcPositionName(False); 		//ignore readDirection

	Point p3 = *GetPosition();	//init

	if (p1.x < p2.x)
		p3.x -= (p2.x - p1.x);
	else
		p3.x += (p1.x - p2.x);


	if (p1.y < p2.y)
		p3.y -= (p2.y - p1.y);
	else
		p3.y += (p1.y - p2.y);

	up_x = p3.x - 10;
	up_y = p3.y - 10;
	dn_x = p3.x + 10;
	dn_y = p3.y + 10;

	if (GetTList()->first()) {
		up_x = GetTList()->cur()->GetTopLeft()->x;
		up_y = GetTList()->cur()->GetTopLeft()->y;
		dn_x = GetTList()->cur()->GetTopLeft()->x +
			     GetTList()->cur()->GetStringWidth();
		dn_y = GetTList()->cur()->GetTopLeft()->y +
			     GetTList()->cur()->GetStringHeight() +
				 GetTList()->cur()->GetFontHeight()/2;
	} 

	int j = 0;
	bool dir = False;
	for (GetTList()->first(); !GetTList()->done(); GetTList()->next()) {
		up_x = min(up_x, GetTList()->cur()->GetTopLeft()->x);
		up_y = min(up_y, GetTList()->cur()->GetTopLeft()->y);
		dn_x = max(dn_x, GetTList()->cur()->GetTopLeft()->x +
		     				GetTList()->cur()->GetStringWidth());
		dn_y = max(dn_y, GetTList()->cur()->GetTopLeft()->y +
		     				GetTList()->cur()->GetStringHeight() +
			 				GetTList()->cur()->GetFontHeight()/2);
		j++;
		if (GetTList()->cur()->IsDirected()) 
			dir = True;
	} 

	//adjust for initial empty textshape
	if (j==1 && up_x==dn_x ) {
		ADJUSTING = True;
		if (GetTList()->first()) {
			Point tpt = *GetTList()->cur()->GetPosition();
			up_x = tpt.x - 10;
			up_y = tpt.y - 10;
			dn_x = tpt.x + 10;
			dn_y = tpt.y + 10;
		}
	}

	if (dir)
			dn_x += 16;		//adjusting for msg arrow 

	Rectangle rect3(up_x, 
			up_y, 
			(dn_x - up_x), 
			(dn_y - up_y));

	if (rect3.Inside(x, y)) {
		int k = 0;
		for (GetTList()->first(); !GetTList()->done(); GetTList()->next()) {
			int pt_y = GetTList()->cur()->GetPosition()->y;
			int textHeight = GetTList()->cur()->GetFontHeight();
			pt_y += textHeight/2;
			if (ADJUSTING ||
				(GetTList()->cur()->ContainsPt(x,y) && y <= pt_y)) {
				// get the message.
				TextShape *t = GetTList()->cur();
				//#### toggle message arrow ?
				if (t->IsDirected())  {

//##### START TOGGLE
	int up_msg_x = t->GetTopLeft()->x + t->GetStringWidth();
	int up_msg_y = t->GetTopLeft()->y;
	int dn_msg_x = up_msg_x + 16;
	int dn_msg_y = up_msg_y + t->GetStringHeight() + t->GetFontHeight()/2;
	Rectangle rect4(up_msg_x, 
					up_msg_y, 
					(dn_msg_x - up_msg_x), 
					(dn_msg_y - up_msg_y));

	if (rect4.Inside(x, y)) {
		if (t->GetStringWidth() > 0) {	// toggle OK
			CBDMessage *msg = 
				(CBDMessage *)((CBObjectLinkEdge *)GetSubject())->GetMessage(k);
			CBDMessage::DirectionType oldDir = msg->GetDirection();
			int newDir = 3 - (int) oldDir;
			CBViewer *cbviewer = dynamic_cast<CBViewer *>(GetViewer());
			if (cbviewer)
				cbviewer->UpdateMessageDirection(t, msg, k,
												(ReadDirection::Type) newDir);
		}	//toggle OK
	} 

//##### END TOGGLE
				}
				// return the message
				return t;
			}
			k++;
		} 
		// below the list ??
		if (GetTList()->last()) {
			if (GetTList()->cur()->ContainsPt(x,y))
				return GetTList()->cur();
		}

		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetDescription("Message");
		t->SetFont(GetName()->GetFont());
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(k);
		t->SetParent(this);
		t->SetPosition(&p3);
		t->SetReadDirection(ReadDirection::TOSHAPE);
		t->SetDirected(True);
		GetTList()->add(t);
		return t;
	}

	return T4TListLine::ChooseTextShape(x, y);
}




bool C2R2MListLine::InTextArea(int x, int y) {
	if (T4TListLine::InTextArea(x, y))
		return True;
	else 
		for (GetTList()->first(); !GetTList()->done(); GetTList()->next())
			if (GetTList()->cur()->InTextArea(x, y))
				return True;
	return False;
}

TextShape *C2R2MListLine::HitTextShape(int x, int y) {
	Rectangle rect2(GetName()->GetTopLeft()->x +
			GetName()->GetWidth(), 
			GetName()->GetTopLeft()->y,
			16,
			GetName()->GetHeight());

	if ((GetNameDirection() != ReadDirection::NONE) && rect2.Inside(x, y))
		return GetName();

	int up_x = 0;
	int up_y = 0;
	int dn_x = 0;
	int dn_y = 0;

	if (GetTList()->first()) {
		up_x = GetTList()->cur()->GetTopLeft()->x;
		up_y = GetTList()->cur()->GetTopLeft()->y;
		dn_x = GetTList()->cur()->GetTopLeft()->x +
				 GetTList()->cur()->GetStringWidth();
		dn_y = GetTList()->cur()->GetTopLeft()->y +
				 GetTList()->cur()->GetStringHeight() +
				 GetTList()->cur()->GetFontHeight()/2;
	} 

	int j = 0;
	for (GetTList()->first(); !GetTList()->done(); GetTList()->next()) {
		up_x = min(up_x, GetTList()->cur()->GetTopLeft()->x);
		up_y = min(up_y, GetTList()->cur()->GetTopLeft()->y);
		dn_x = max(dn_x, GetTList()->cur()->GetTopLeft()->x +
		     				GetTList()->cur()->GetStringWidth());
		dn_y = max(dn_y, GetTList()->cur()->GetTopLeft()->y +
		     				GetTList()->cur()->GetStringHeight() +
			 				GetTList()->cur()->GetFontHeight()/2);
		j++;
	} 

	Rectangle rect3(up_x, up_y, 
					(dn_x - up_x), (dn_y - up_y));
	if (rect3.Inside(x, y)) {
		int l = 0;
		for (GetTList()->first(); !GetTList()->done(); GetTList()->next()) {
			int pt_y = GetTList()->cur()->GetPosition()->y;
			int textHeight = GetTList()->cur()->GetFontHeight();
			pt_y += textHeight/2;

			if (GetTList()->cur()->ContainsPt(x,y) && y <= pt_y) {
				// return the action.
				TextShape *t = GetTList()->cur();
				return t;
			}
			l++;
		} 
		// below the list ??
		if (GetTList()->last()) {
			if (GetTList()->cur()->ContainsPt(x,y))
				return GetTList()->cur();
		}
	}
	return T4TListLine::HitTextShape(x, y);
}



void C2R2MListLine::UpdateTListTextShape(const string *s, unsigned n) {
	if (IsVisible())
		Undraw();
	if (n < GetTList()->count()) {
		if (*s != "")
			GetTList()->elem(n)->SetString(s);
		else 
			GetTList()->removei(n);
	}
	else {
		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetDescription("Message");
		t->SetFont(GetName()->GetFont());
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(n);
		t->SetString(s);
		t->SetParent(this);

		Point pt = *(GetTList()->elem(n-1)->GetPosition());
		pt.y += GetTList()->elem(n-1)->GetFontHeight();
		t->SetPosition(&pt);

		t->SetReadDirection(ReadDirection::TOSHAPE);
		t->SetDirected(True);
		GetTList()->add(t);
	}

	if (IsVisible())
		Draw();
}


void C2R2MListLine::UndrawTListTextShape(const string *, unsigned ) {
	if (IsVisible())
		Undraw();
}


void C2R2MListLine::ReDrawTListTextShape(const string *s, unsigned n) {
	if (n < GetTList()->count()) {
		if (*s != "")
			GetTList()->elem(n)->SetString(s);
		else
			GetTList()->removei(n);
	} 
	else {
		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetDescription("Message");
		t->SetFont(GetName()->GetFont());
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(n);
		t->SetString(s);
		t->SetParent(this);

		Point pt = *(GetTList()->elem(n-1)->GetPosition());
		pt.y += GetTList()->elem(n-1)->GetFontHeight();

		t->SetPosition(&pt);
		t->SetAlignment(TextAlign::LEFT);		//HZ
		t->SetReadDirection(ReadDirection::TOSHAPE);
		t->SetDirected(True);

		GetTList()->add(t);
	}
	if (IsVisible())
		Draw();
}


void C2R2MListLine::DrawShape() {
	T4TListLine::DrawShape();
	CalcDirection();
	DrawDirection();
	CalcPositionTextShapes();
	if ((CBDMessage *)((CBObjectLinkEdge *)GetSubject())->NrOfMessages() > 0) {
		int i = 0;
		for (GetTList()->first(); !GetTList()->done(); GetTList()->next()) {
//			CBDMessage *msg = (CBDMessage *)((CBObjectLinkEdge *)GetSubject())->GetMessage(i);
//			CBDMessage::DirectionType mDir = msg->GetDirection();
			CalcMsgDirection(i);
			GetTList()->cur()->Draw();
			i++;
		}
	}
}


void C2R2MListLine::CalcMsgDirection(unsigned n) {
	CBDMessage *msg = (CBDMessage *)((CBObjectLinkEdge *)GetSubject())->GetMessage(n);
	if (msg == 0)
		return;
	else {	// valid message
		CBDMessage::DirectionType MsgDirection = msg->GetDirection();
		if ( MsgDirection == CBDMessage::NONE)
			return;
		DPoint ep1, ep2;
		GetSegment(GetLineNumber(), &ep1, &ep2);
		if (MsgDirection == CBDMessage::FROMSHAPE) {
			DPoint save = ep1;
			ep1 = ep2;
			ep2 = save;
		}
		DPoint arpos1 = *(GetTList()->elem(n)->GetPosition());
		arpos1.x += GetTList()->elem(n)->GetStringWidth() * 0.5;
        // plus space for arrow
        arpos1.x += GetFont()->StringWidth("A");

		DPoint *zdirectionPoints = new DPoint[4];
		dummy.SetLength(6);
		dummy.SetWidth(6);
		dummy.CalcDirectionDiamond(&ep1, &ep2, &arpos1, 
					8, 8, zdirectionPoints);
		DPoint newEnd;
		dummy.SetType(LineEnd::FILLED_ARROW);
		dummy.SetLength(8);
		dummy.SetWidth(8);
		dummy.Draw(GetGrafport(), 
				&zdirectionPoints[3],
				&zdirectionPoints[1],
				&newEnd);
		DPoint arpos0 = *(GetTList()->elem(n)->GetPosition());
		arpos0.x += GetTList()->elem(n)->GetStringWidth() * 0.5;
		DPoint too;
		too.x = (zdirectionPoints[0].x + zdirectionPoints[2].x) * 0.5;
		too.y = (zdirectionPoints[0].y + zdirectionPoints[2].y) * 0.5;
		DPoint newStart;
		if (newEnd.x > too.x)
			newStart.x = too.x - (newEnd.x - too.x);
		else
			newStart.x = too.x + (too.x - newEnd.x);
		if (newEnd.y > too.y)
			newStart.y = too.y - (newEnd.y - too.y);
		else
			newStart.y = too.y + (too.y - newEnd.y);
		GetGrafport()->DrawLine(newStart.x, newStart.y,
								newEnd.x, newEnd.y);
	} 	// valid message
}

void C2R2MListLine::WriteMembers(OutputFile *ofile) {
	T4TListLine::WriteMembers(ofile);
}

bool C2R2MListLine::ReadMembers(InputFile *ifile, double format) {
	if (!T4TListLine::ReadMembers(ifile, format))
		return False;
	if (format >= 1.32) {
		string val;
		if (!ifile->ReadAttribute("NameDirection", &val))
			return False;
		SetNameDirection(ReadDirection::String2Type(&val));
	} else
		SetNameDirection(ReadDirection::NONE);
	string val1 = 0,  val2 = 0;
	if (format < 1.32) {	//pre-production version
		/*  just ignore... */
		if (!ifile->ReadAttribute2("T5Position", &val1, &val2)) {
			;	/*  just ignore... */
		}
	}	//pre-production version
	if (!ifile->ReadAttribute("Messages", &val1))
		return False;
	int msgCount = val1.toint(); 
	int x, y;
	// Read message positions
	for (int i=0; i<msgCount; i++) {
		if (!ifile->ReadAttribute2("TnPosition", &val1, &val2))
			return False;
		x = val1.toint(); y = val2.toint();
		plist->add(new Point(x, y));
	}
	return True;
}

