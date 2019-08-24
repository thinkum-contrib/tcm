////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "grafport.h"
#include "inputfile.h"
#include "outputfile.h"
#include "assoclist.h"
#include "lifeline.h"
#include "apline.h"
#include "point.h"
#include "llist.h"
#include "sqobjectnode.h"
#include "sqanchorlinkedge.h"

APLine::APLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2,
		List<Point *> *aline, bool Curved):
		Line(v, g, n1, n2, aline, Curved) {

std::cout << " APLine::APLine(*v, *g, *n1, *n2, List, curved)" << std::endl << std::flush;
std::cout << " APLine(*v, *g, GS1=" << n1->GetId()
<< ", GS2=" << n2->GetId()
<< std::endl << std::flush;



	apline = new List<Point *>;
std::cout << " line so far " << std::endl << std::flush;
	for (aline->first(); !aline->done(); aline->next()) {
		Point *p1 = aline->cur();
std::cout << ">> Got line *p1= " << *p1 << std::endl << std::flush;
		apline->add(new Point(*p1));
	}

	apend1.SetType(LineEnd::EMPTY);
	apend2.SetType(LineEnd::EMPTY);
	apend2.SetType(LineEnd::FILLED_ARROW);

std::cout << "reset line " << std::endl << std::flush;


std::cout << "$$$$$$ (Re)CalcEndPoints() {" << std::endl << std::flush;
//hz	ReCalcEndPoints(apline);
	ReCalcEndPoints(apline);
	ReCalcEndPoints(aline);

std::cout << "$$$$ apline after ReCalc" << std::endl << std::flush;
	int i = 0;
	for (apline->first(); !apline->done(); apline->next()) {
		Point *p1 = apline->cur();
std::cout << ">> Got line *p1= " << *p1 << std::endl << std::flush;
		SetPoint( p1 , i);
		i++;
	}

std::cout << "$$$$ ALINE after ReCalc" << std::endl << std::flush;
	for (aline->first(); !aline->done(); aline->next()) {
		Point *p1 = aline->cur();
std::cout << ">> Got line *p1= " << *p1 << std::endl << std::flush;


	}

std::cout << " -a4- " << std::endl << std::flush;
}


APLine::APLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2,
		bool Curved): Line(v, g, n1, n2, Curved) {

std::cout << " APLine::APLine(*v, *g, *n1, *n2, curved)" << std::endl << std::flush;

	apend1.SetType(LineEnd::EMPTY);
	apend2.SetType(LineEnd::FILLED_ARROW);

}

APLine::APLine(const APLine &aline): Line(aline) {

std::cout << " APLine::APLine(const APLine &aline) {" << std::endl << std::flush;

	apend1.SetType(LineEnd::EMPTY);
	apend2.SetType(LineEnd::FILLED_ARROW);
}


void APLine::SetAnchors() {
std::cout << " void APLine::SetAnchors() {" << std::endl << std::flush;

	Point *firstPt, *lastPt;

	int len = GetLine()->count();

	firstPt = (*GetLine())[0];
	lastPt = (*GetLine())[len-1];

std::cout << " firstPt = " << *firstPt << std::endl << std::flush;
std::cout << " lastPt = " << *lastPt << std::endl << std::flush;

	SQAnchorLinkEdge *obj = (SQAnchorLinkEdge *)GetSubject();
std::cout << " -b- " << std::endl << std::flush;

//AleisterMod 20
//std::cout << " obj->gCt=" << obj->GetClassType() << std::endl << std::flush;



std::cout<<""<<std::endl<<std::flush;
std::cout<<"ANCHOR________1"<< *(obj->GetAnchor1()) <<std::endl<<std::flush;
std::cout<<"ANCHOR________2"<<  *(obj->GetAnchor2())<<std::endl<<std::flush;
std::cout<<""<<std::endl<<std::flush;


	Subject *sub1 = (Subject*) obj->GetSubject1();
std::cout << " -c- " << std::endl << std::flush;
	SQObjectNode *sub1a = (SQObjectNode *) sub1;
std::cout << " -C- " << std::endl << std::flush;
	SQObjectNode *on2 = (SQObjectNode *) obj->GetSubject2();
std::cout << " -d- " << std::endl << std::flush;


if((((obj->GetAnchor1()))->x)!=0 && (((obj->GetAnchor1()))->y)!=0 && (((obj->GetAnchor2()))->x)!=0 && (((obj->GetAnchor2()))->y)!=0) {
	sub1a->RemoveAnchor(((obj->GetAnchor1()))->x, 4);
	on2->RemoveAnchor(((obj->GetAnchor2()))->x, 5);
}

	Point *pt1 = new Point(firstPt->y, 4);
	obj->SetAnchor1(pt1);

	Point *pt2 = new Point(lastPt->y, 5);
	obj->SetAnchor2(pt2);

	//if() {

	sub1a->AddAnchor(firstPt->y, 4);
std::cout << " -e- " << std::endl << std::flush;
	on2->AddAnchor(lastPt->y, 5);
std::cout << " -f- " << std::endl << std::flush;

}

void APLine::DrawShape() {

std::cout << " void APLine::DrawShape() {" << std::endl << std::flush;

std::cout << " GetLine->count() = " << GetLine()->count() << std::endl << std::flush;


	if (check(GetLine()->count()>=2)) {
std::cout << " GetLine()->count() = " << GetLine()->count() << std::endl << std::flush;

for (GetLine()->first(); !GetLine()->done(); GetLine()->next()) {
		std::cout << "GetLine()->cur() = [" << *GetLine()->cur() << "]" << std::endl << std::flush;
//HZ	std::cout << "GetLine()->cur() = [" << *(GetLine()->cur()) << "]" << std::endl << std::flush;
}


		DPoint ep1, ep2;
		DPoint tp1 = *(*GetLine())[1];	//convert
		DPoint tp2 = *(*GetLine())[0];	//convert
		DPoint tp3 = *(*GetLine())[GetLine()->count()-2];	//convert
		DPoint tp4 = *(*GetLine())[GetLine()->count()-1];	//convert
std::cout << " tp1: [" << (*GetLine())[1] << " == " << tp1 << std::endl << std::flush;
std::cout << " tp2: [" << (*GetLine())[0] << " == " << tp2 << std::endl << std::flush;
std::cout << " tp3: [" << (*GetLine())[GetLine()->count()-2] << " == " << tp3 << std::endl << std::flush;
std::cout << " tp4: [" << (*GetLine())[GetLine()->count()-1] << " == " << tp4 << std::endl << std::flush;



		if (GetGrafport()->GetLineStyle() != LineStyle::INVISIBLE) {
			GetGrafport()->SetLineStyle(LineStyle::SOLID);
			apend1.Draw(GetGrafport(), &tp1, &tp2, &ep1);

std::cout << " apend1: [" << (*GetLine())[1] << " -> "
<< (*GetLine())[0] << "] -> " << ep1
<< std::endl << std::flush;

			apend2.Draw(GetGrafport(), &tp3, &tp4, &ep2);
std::cout << " apend2: [" << (*GetLine())[GetLine()->count()-2] << " -> "
<< (*GetLine())[GetLine()->count()-1] << "] -> " << ep2
<< std::endl << std::flush;

			GetGrafport()->SetLineStyle(GetLineStyle());


std::cout << "apend1=[" << *(*GetLine())[1] << "->"
	<< *(*GetLine())[0] << "] ==> " << ep1 << std::endl << std::flush;
std::cout << "apend2=[" << *(*GetLine())[GetLine()->count()-2] << "->"
	<< *(*GetLine())[GetLine()->count()-1] << "] ==> " << ep2 << std::endl << std::flush;
		}

		SetAnchors();


		if (IsCurved())
//			DrawBezier(&ep1, &ep2);
			DrawLine(&ep1, &ep2);
		else
			DrawLine(&ep1, &ep2);
	}

}

void APLine::DrawLine(const DPoint *ep1, const DPoint *ep2) /* const */ {

std::cout << "$$$ void APLine::DrawLine(" << *ep1 << "," <<  *ep2 << ")" << std::endl << std::flush;


//	delete [/* apline->count() */] p;


	unsigned u = GetLine()->count();
	if ( u < 2 || ! GetLine()->first() )
		return;
	DPoint *p = new DPoint[u];
	p[--u] = *ep1;
	while ( --u ) {
		GetLine()->next();
		p[u] = *GetLine()->cur();
	}
	p[0] = *ep2;
	GetGrafport()->DrawOpenPolygon(p, GetLine()->count());
	delete [/* GetLine()->count() */] p;


std::cout << " ENDOFFFF void APLine::DrawLine() " << std::endl << std::flush;
}







bool APLine::SetReferences(AssocList *al) {

std::cout << " bool APLine::SetReferences(AssocList *al) {" << std::endl << std::flush;

//
//	Line::SetReferences(al);
//
	Assoc *find, *assoc;
	find = new Assoc(GetFromShape());
	assoc = al->Get(find);
	delete find;
	if (check(assoc))
		SetFromShape((GShape *)assoc->copy);
	else {
		error("line %ld has no existing fromShape\n", GetId());
		SetFromShape((GShape *)0);
		return False;
	}
	if (!GetFromShape() || !GetFromShape()->IsShape()) {
		error("line %ld has no real shape as fromShape\n", GetId());
		SetFromShape(0);
		return False;
	}
	find = new Assoc(GetToShape());
	assoc = al->Get(find);
	delete find;
	if (check(assoc))
		SetToShape((GShape *)assoc->copy);
	else {
		error("line %ld has no existing toShape\n", GetId());
		SetToShape(0);
		return False;
	}
	if (!GetToShape() || !GetToShape()->IsShape()) {
		error("line %ld has no real shape as toShape\n", GetId());
		SetToShape(0);
		return False;
	}
	Point *l = (*GetLine())[0];
//	*l = GetFromShape()->GiveOrthoSnp(*l);
//	*l = ((LifeLine *)GetFromShape())->GiveAnchorSnp(*l);
//	l = (*GetLine())[GetLine()->count() - 1];
//	*l = GetToShape()->GiveOrthoSnp(*l);
//	*l = ((LifeLine *)GetToShape())->GiveAnchorSnp(*l);

	return True;
}

void APLine::CalcEndPoints() {

std::cout << "######  void APLine::CalcEndPoints() {" << std::endl << std::flush;
std::cout << " -chk-2- = " << (int) check(GetSubject()) << std::endl << std::flush;
std::cout << " GOING 2 	ReCalcEndPoints();" << std::endl << std::flush;
	ReCalcEndPoints();

}

bool APLine::CalcEndPoint(const Point *pt, unsigned int n) {

std::cout << " =!= APLine::CalcEndPoint([" << *pt << " ] ," << n << ")" << std::endl << std::flush;
	return True;
}


void APLine::ReCalcEndPoints() {

std::cout << "$$$  void APLine::ReCalcEndPoints() {" << std::endl << std::flush;
std::cout << " -chk-3- = " << (int) check(GetSubject()) << std::endl << std::flush;

	if (!check(GetFromShape()) || !check(GetToShape()))
		return;
	Point from, to, dummy;
	Point *firstPt, *lastPt;
//HZ	int code = orientation;
	int code = 1;
	int len = GetLine()->count();

	firstPt = (*GetLine())[0];
	lastPt = (*GetLine())[len-1];
std::cout << " <-- firstPt = " << *firstPt
	 << " <-- lastPt = " << *lastPt << " {" << len << "}" << std::endl << std::flush;
	if ((*GetLine())[1] == lastPt) {
		dummy = *(GetToShape()->GetPosition());
		to.x = dummy.x;
		to.y = lastPt->y;
	}
	else
		to = *(*GetLine())[1];
	if ((*GetLine())[len-2] == firstPt) {
		dummy = *(GetFromShape()->GetPosition());
		from.x = dummy.x;
		from.y = firstPt->y;
	}
	else
		from = *(*GetLine())[len-2];

std::cout << " <== from = " << from
	 << " <== to = " << to << "{" << len << "}" << std::endl << std::flush;
	if ((GetCount() == 1) || (GetFromShape() == GetToShape())) {
		if (len == 2) {
			if (GetFromShape()->IsLine() && !GetToShape()->IsLine()) {
				from = GetFromShape()->GiveOrthoSnp(to);
				to = GetToShape()->GiveSnp(from);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if (GetToShape()->IsLine() && !GetFromShape()->IsLine()) {
				to = GetToShape()->GiveOrthoSnp(from);
				from = GetFromShape()->GiveSnp(to);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if (GetFromShape()->IsLine() && GetToShape()->IsLine()) {
				Point p1 = GetFromShape()->GiveSnp(to);
				Point p2 = GetToShape()->GiveSnp(from);
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
			}
			else {
std::cout << " got HeRe " << std::endl << std::flush;
				GShape *s1 = GetFromShape();
				LifeLine *l1 = (LifeLine *) s1;
//				Point p1 = l1->GiveAnchorSnp(*firstPt, to);
				Point p1 = l1->GiveAnchorSnp(from, to);

//				Point p2 = ((LifeLine *)GetToShape())->GiveAnchorSnp(*lastPt, from);
				Point p2 = ((LifeLine *)GetToShape())->GiveAnchorSnp(to, from);
std::cout << "!!!firstPt [" << *firstPt << "] ==> [" << p1 << "]" << std::endl << std::flush;
std::cout << "!!!lastPt [" << *lastPt << "] ==> [" << p2 << "]" << std::endl << std::flush;
std::cout << "!!!to [" << to << "] ==> [" << p2 << "]" << std::endl << std::flush;
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
std::cout << " -1-> firstPt = " << *firstPt
	 << " -1-> lastPt = " << *lastPt << std::endl << std::flush;
			}
		}
		else {

std::cout << " len != 2 : {" << len << "}" << std::endl << std::flush;

//			Point p1 = GetFromShape()->GiveOrthoSnp(to);
//			Point p2 = GetToShape()->GiveOrthoSnp(from);
			/*Point p1 = ((LifeLine *)GetFromShape())->GiveAnchorSnp(*firstPt, to);
			Point p2 = ((LifeLine *)GetToShape())->GiveAnchorSnp(*lastPt, from);
			firstPt->Set(p1.x, p1.y);
			lastPt->Set(p2.x, p2.y);*/
	firstPt->Set((GetFromShape()->GetPosition())->x, firstPt->y);
			lastPt->Set((GetToShape()->GetPosition())->x, 	lastPt->y);

std::cout << " -2-> firstPt = " << *firstPt
	 << " -2-> lastPt = " << *lastPt << std::endl << std::flush;
		}
	}
	else {
		/*Point p1 = GetFromShape()->GiveSnp(to, GetOrder(), GetCount(), code);
		Point p2 = GetToShape()->GiveSnp(from, GetOrder(), GetCount(), code);
		firstPt->Set(p1.x, p1.y);
		lastPt->Set(p2.x, p2.y);*/

		firstPt->Set((GetFromShape()->GetPosition())->x, firstPt->y);
			lastPt->Set((GetToShape()->GetPosition())->x, lastPt->y);
std::cout << " -3-> firstPt = " << *firstPt
	 << " -3-> lastPt = " << *lastPt << std::endl << std::flush;
	}
}

void APLine::ReCalcEndPoints(List<Point *> *oline) {

std::cout << "$$$  void APLine::ReCalcEndPoints(oline) {" << std::endl << std::flush;

std::cout << " oline is " << std::endl << std::flush;
	for (oline->first(); !oline->done(); oline->next()) {
		Point *p1 = oline->cur();
std::cout << ">> Got oline *p1= " << *p1 << std::endl << std::flush;
	}
	if (!check(GetFromShape()) || !check(GetToShape()))
		return;
	Point from, to;
	Point *firstPt, *lastPt;
//HZ	int code = orientation;
	int code = 1;
	int len = oline->count();

	firstPt = (*oline)[0];
	lastPt = (*oline)[len-1];
std::cout << " <-- firstPt = " << *firstPt
	 << " <-- lastPt = " << *lastPt << std::endl << std::flush;
/*
	if ((*oline)[1] == lastPt)
		to = *(GetToShape()->GetPosition());
	else
*/
		to = *(*oline)[1];
/*
	if ((*oline)[len-2] == firstPt)
		from = *(GetFromShape()->GetPosition());
	else
*/
		from = *(*oline)[len-2];

std::cout << " <== from = " << from
	 << " <== to = " << to << std::endl << std::flush;
	if ((GetCount() == 1) || (GetFromShape() == GetToShape())) {
		if (len == 2) {
			if (GetFromShape()->IsLine() && !GetToShape()->IsLine()) {
				from = GetFromShape()->GiveOrthoSnp(to);
				to = GetToShape()->GiveSnp(from);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if (GetToShape()->IsLine() && !GetFromShape()->IsLine()) {
				to = GetToShape()->GiveOrthoSnp(from);
				from = GetFromShape()->GiveSnp(to);
				firstPt->Set(from.x, from.y);
				lastPt->Set(to.x, to.y);
				return;
			}
			else if (GetFromShape()->IsLine() && GetToShape()->IsLine()) {
				Point p1 = GetFromShape()->GiveSnp(to);
				Point p2 = GetToShape()->GiveSnp(from);
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
			}
			else {

				GShape *s1 = GetFromShape();
				LifeLine *l1 = (LifeLine *) s1;
				Point p1 = l1->GiveAnchorSnp(*firstPt, to);

				Point p2 = ((LifeLine *)GetToShape())->GiveAnchorSnp(*lastPt, from);
std::cout << "!!!firstPt [" << *firstPt << "] ==> [" << p1 << "]" << std::endl << std::flush;
std::cout << "!!!lastPt [" << *lastPt << "] ==> [" << p2 << "]" << std::endl << std::flush;
				firstPt->Set(p1.x, p1.y);
				lastPt->Set(p2.x, p2.y);
std::cout << " -1-> firstPt = " << *firstPt
	 << " -1-> lastPt = " << *lastPt << std::endl << std::flush;
			}
		}
		else {
			/*Point p1 = GetFromShape()->GiveOrthoSnp(to);
			Point p2 = GetToShape()->GiveOrthoSnp(from);
			firstPt->Set(p1.x, p1.y);
			lastPt->Set(p2.x, p2.y);*/

			firstPt->Set((GetFromShape()->GetPosition())->x, firstPt->y);
			lastPt->Set((GetToShape()->GetPosition())->x, lastPt->y);

std::cout << " -2-> firstPt = " << *firstPt
	 << " -2-> lastPt = " << *lastPt << std::endl << std::flush;
		}
	}
	else {
		/*Point p1 = GetFromShape()->GiveSnp(to, GetOrder(), GetCount(), code);
		Point p2 = GetToShape()->GiveSnp(from, GetOrder(), GetCount(), code);
		firstPt->Set(p1.x, p1.y);
		lastPt->Set(p2.x, p2.y);*/
firstPt->Set((GetFromShape()->GetPosition())->x, firstPt->y);
			lastPt->Set((GetToShape()->GetPosition())->x, lastPt->y);


std::cout << " -3-> firstPt = " << *firstPt
	 << " -3-> lastPt = " << *lastPt << std::endl << std::flush;
	}
}


