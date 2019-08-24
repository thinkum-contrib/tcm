////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
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

#include "lifeline.h"
#include "inputfile.h"
#include "outputfile.h"
#include "subject.h"
#include "grafport.h"
#include "sqobjectnode.h"
#include "shapetype.h"
#include "polypoint.h"
#include "intersect.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "sqviewer.h"
#include <limits.h>

const int LifeLine::LIFELINE_WIDTH = 80;
const int LifeLine::LIFELINE_HEIGHT = 40;

const ShapeType LifeLine::llType(Code::BOX,
	LIFELINE_WIDTH, LIFELINE_HEIGHT, 0.0, 0.0,
	&Polygon::Box, &Polygon::Box1, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &Polygon::Box);

LifeLine::LifeLine(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &llType)
{
    GetName()->SetUnderlined(True);
	endPosition.x = GetPosition()->x;
	endPosition.y = GetPosition()->y + 400;

	destructive = False;	//init
}

LifeLine::LifeLine(const NodeShape &c)
	:NodeShape(c, &llType)
{
        GetName()->SetUnderlined(True);
}




void LifeLine::WriteMembers(OutputFile *ofile) {
	NodeShape::WriteMembers(ofile);
	(*ofile) << "\t{ EndPosition " << endPosition  << " }\n";
	(*ofile) << "\t{ Destructive " << (int) destructive << " }\n";
}

bool LifeLine::ReadMembers(InputFile *ifile, double format) {
std::cout << "a" << std::endl << std::flush;
	if (!NodeShape::ReadMembers(ifile, format))
		return False;
std::cout << "b" << std::endl << std::flush;
	if (format >= 1.32) {	//HZ : AnchorNode patch
std::cout << "eP" << std::endl << std::flush;
		string val1, val2;
		if (!ifile->ReadAttribute2("EndPosition", &val1, &val2)) {
std::cout << "Wrong EndPos: " << std::endl << std::flush;
			return False;
		}
std::cout << "Got EndPos [" << val1 << ", " << val2 << "]" << std::endl << std::flush;
		endPosition.x = val1.toint();
		endPosition.y = val2.toint();



		string val;
		if (!ifile->ReadAttribute("Destructive", &val))	{
std::cout << "Wrong DESTR: " << std::endl << std::flush;
			return False;
		}
std::cout << "Got DESTR = " << val << std::endl << std::flush;
		destructive = (val1 %= "True");
	}



	return True;
}



void LifeLine::DrawOutLine(double x, double y, double w, double h) {
std::cout << " !!! void LifeLine::DrawOutLine(" << x << ", " << y << ", " << w
<< ", " << h << ")" << std::endl << std::flush;

std::cout << " GetPosition = " << *GetPosition() << std::endl << std::flush; 
std::cout << " GetHeight = " << GetHeight() << std::endl << std::flush; 
std::cout << " EndPosition = " << endPosition << std::endl << std::flush; 

	NodeShape::DrawOutLine(x, y, w, h);


	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawLine((double) x, (double) (y + h/2),
							(double) x, (double) endPosition.y);	
	GetGrafport()->SetLineStyle(LineStyle::SOLID);

}



void LifeLine::DrawOutLine(const Point *center, double t) {
std::cout << " !TTT! void LifeLine::DrawOutLine(" << *center 
<< ", T=" << t << ")" << std::endl << std::flush;
	DrawOutLine(center->x, center->y,
				GetWidth(), GetHeight());

	GetGrafport()->SetLineStyle(LineStyle::SOLID);
//Z	GetGrafport()->DrawLine((double) endPosition.x, (double) endPosition.y,
//Z											(double) endPosition.x, t);	
	GetGrafport()->SetLineStyle(LineStyle::DASHED);

}


void LifeLine::DrawOutLineTail(const Point *center, double t) {
std::cout << " !T__tail__T! void LifeLine::DrawOutLineTail(" << *center 
<< ", T=" << t << ")" << std::endl << std::flush;

	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawLine((double) center->x, (double) center->y,
											(double) endPosition.x, t);	
	GetGrafport()->SetLineStyle(LineStyle::DASHED);

}




void LifeLine::DrawOutLineFOC(double startFOC, double endFOC) {
std::cout << " !T__FOC__T! void LifeLine::DrawOutLineFOC(" << startFOC
<< "-->" << endFOC << ")" << std::endl << std::flush;

	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawRectangle( (double) GetPosition()->x - 5, startFOC, 10, endFOC - startFOC );
	GetGrafport()->SetLineStyle(LineStyle::DASHED);
}

void LifeLine::DrawShape() {
std::cout << " void LifeLine::DrawShape() {"
<< GetPosition()->y << " -d- " << endPosition.y
<< std::endl << std::flush;

	if (GetPosition()->x != endPosition.x) {
		endPosition.x = GetPosition()->x;
	}

	NodeShape::DrawShape();
std::cout << " GetPosition = " << *GetPosition() << std::endl << std::flush;
std::cout << " GetHeight = " << GetHeight() << std::endl << std::flush;


std::cout << " EndPosition = " << endPosition << std::endl << std::flush;

	//AleisterMod 20
	/*if (check(GetSubject() &&
		  GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {*/

std::cout << "GetSubject()->GetId()  = " << GetSubject()->GetId()
//<< " GetName.getstr=" << *GetSubject()->GetName()->getstr()
<< std::endl << std::flush;

std::cout << "NrAnchors =" << ((SQObjectNode *)GetSubject())->NrAnchors() << std::endl << std::flush;

		List<Point *> *apoints;
		DPoint *prev = new DPoint ((double) GetPosition()->x,
								(double) (GetPosition()->y + GetHeight()/2) );
		apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

std::cout << "NrAnchors2 =" << apoints->count() << std::endl << std::flush;


		for(apoints->first(); !apoints->done(); apoints->next()) {
			Point *ap = apoints->cur();
			Point p = *apoints->cur();
std::cout << "*ap=" << *ap << " p=" << p << std::endl << std::flush;

			switch (p.y) {
				case 2:
					std::cout << " Start FOC : " << p << std::endl << std::flush;
					GetGrafport()->SetLineStyle(LineStyle::DASHED);
					GetGrafport()->DrawLine(prev->x, prev->y,
											(double) prev->x, (double) p.x);
					prev->y = p.x;
					break;
				case 3:
					std::cout << " End FOC : " << p << std::endl << std::flush;
					GetGrafport()->SetLineStyle(LineStyle::SOLID);
//					GetGrafport()->DrawLine((double) prev->x, (double) prev->y,
//											(double) prev->x, (double) p.x);
					GetGrafport()->DrawRectangle( (double) prev->x - 5,
												  (double) prev->y,
												  10,
												  (double) p.x - prev->y );

					prev->y = p.x;
					break;
				default:
					std::cout << " ignored : " << p << std::endl << std::flush;
					break;
			}
		}


		if (prev->y != endPosition.y) {
std::cout << "Finishing " << std::endl << std::flush;
			GetGrafport()->SetLineStyle(LineStyle::DASHED);
			GetGrafport()->DrawLine((double) prev->x, (double) prev->y,
									(double) endPosition.x,
									(double) endPosition.y);
		}

	//AleisterMod 20
	/*}*/


std::cout << " going 2 DrawDuplicate? " << IsDuplicate() << std::endl << std::flush;
	if (IsDuplicate())
		DrawDuplicate();

//	GetGrafport()->SetLineStyle(LineStyle::DASHED);
//	GetGrafport()->DrawLine((double) GetPosition()->x,
//					(double) (GetPosition()->y + GetHeight()/2),
//							(double) endPosition.x, (double) endPosition.y);
//	GetGrafport()->SetLineStyle(LineStyle::SOLID);

}


void LifeLine::UndrawShape() {
std::cout << " void LifeLine::UndrawShape() {"
<< GetPosition()->y << " -u- " << endPosition.y
<< std::endl << std::flush;
	DrawShape();
}




/* virtual */ Point LifeLine::GiveSnp(Point to) const {
std::cout << "___ Point LifeLine::GiveSnp([" << to << "]) ep="
<< endPosition.x << std::endl << std::flush;

	Point p1 = NodeShape::GiveSnp(to);
//	return p1;

	Point p2 = to;
	if (p2.x != endPosition.x)
		p2.x = endPosition.x;

std::cout << " p1 = " << p1 << " => p2 = " << p2 << std::endl << std::flush;
	return p2;

}

// Begin Aleister7
bool LifeLine::IsOverlappingAnotherFOC(int prevStartFOC,
					int prevEndFOC,
					int startFOC, int endFOC) {
	if (check(GetSubject() &&
		  GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {
		List<Point *> *apoints;
		apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

		bool in_FOC = False;

		for(apoints->first(); !apoints->done(); apoints->next()) {
			Point *ap = apoints->cur();

			if(ap->y == 2) {
				// FOC
				if(ap->x != prevStartFOC) {
					if(ap->x >= startFOC &&
					   ap->x <= endFOC) {
						in_FOC = True;
					}
				}
			} else {
			if(ap->y == 3) {
				// FOC
				if (ap->x != prevEndFOC) {
					if(ap->x <= endFOC &&
					   ap->x >= startFOC) {
						in_FOC = True;
					}
				}
			}
			}
		}

		return (in_FOC);
	}

	return False;
}
// End Aleister7

bool LifeLine::PtInFOCblock(int x, int y) const {
std::cout << " bool LifeLine::PtInFOCblock(" << x << "," << y << ") @["
<< *GetPosition() << "]" << std::endl << std::flush;

	Rectangle rect(GetPosition()->x - 5,
					GetPosition()->y + GetHeight()/2,
					10,
					endPosition.y - (GetPosition()->y + GetHeight()/2));
	if (rect.Inside(x, y)) {
		std::cout << "PtInFOCblock: inside rect (" << std::endl << std::flush;


		if (check(GetSubject() &&
		  	GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {



std::cout << "_F_GetSubject()->GetId()  = " << GetSubject()->GetId()
//<< " GetName.getstr=" << *GetSubject()->GetName()->getstr()
<< std::endl << std::flush;

std::cout << "_F_NrAnchors =" << ((SQObjectNode *)GetSubject())->NrAnchors() << std::endl << std::flush;

			List<Point *> *apoints;
			DPoint *prev = new DPoint ((double) GetPosition()->x,
									(double) (GetPosition()->y + GetHeight()/2) );
			apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

std::cout << "_F_NrAnchors2 =" << apoints->count() << std::endl << std::flush;

			int start_FOC = INT_MAX;
			int end_FOC = 0;
			bool in_FOC = False;

			for(apoints->first(); !apoints->done(); apoints->next()) {
				Point *ap = apoints->cur();
				Point p = *apoints->cur();
std::cout << "FOC*ap=" << *ap << " p=" << p << std::endl << std::flush;

				if (!in_FOC) {
					switch (p.y) {
						case 2:
							std::cout << "_F_Start FOC : " << p << std::endl << std::flush;
							start_FOC = p.x;
							break;
						case 3:
							std::cout << "_F_End FOC : " << p << std::endl << std::flush;
							if (y >= start_FOC && y <= p.x) {
std::cout << " Point [" << x << ", " << y << "] in FOC! " << std::endl << std::flush;
								in_FOC = True;
								end_FOC = p.x;
							}
							else
								start_FOC = INT_MAX;		//reset
							break;
						default:
							std::cout << "_F_ignored : " << p << std::endl << std::flush;
							break;
					}
				}
			}


std::cout << "--F---> PtInFOCblok: in_FOC=" << in_FOC << "[" << start_FOC << "->"
<< end_FOC <<"]" << std::endl << std::flush;

			return (in_FOC);
		}

		return False;
	}
	else {
		std::cout << "PtInFOCBlock: NOT inside rect " << std::endl << std::flush;
		return False;
	}
}


bool LifeLine::PtInFOCblock(int x, int y, int *start, int *end) const {
std::cout << " bool LifeLine::PtInFOCblock(" << x << "," << y << ", start, end ) @["
<< *GetPosition() << "]" << std::endl << std::flush;

	Rectangle rect(GetPosition()->x - 5,
					GetPosition()->y + GetHeight()/2,
					10,
					endPosition.y - (GetPosition()->y + GetHeight()/2));
	if (rect.Inside(x, y)) {
		std::cout << "_R_PtInFOCblock: inside rect (" << std::endl << std::flush; 


		if (check(GetSubject() &&
		  	GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {
		  	


std::cout << "_R_GetSubject()->GetId()  = " << GetSubject()->GetId()  
//<< " GetName.getstr=" << *GetSubject()->GetName()->getstr()
<< std::endl << std::flush; 

std::cout << "_R_NrAnchors =" << ((SQObjectNode *)GetSubject())->NrAnchors() << std::endl << std::flush; 

			List<Point *> *apoints;
			DPoint *prev = new DPoint ((double) GetPosition()->x,
									(double) (GetPosition()->y + GetHeight()/2) );
			apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

std::cout << "_R_NrAnchors2 =" << apoints->count() << std::endl << std::flush; 

			int start_FOC = INT_MAX;
			int end_FOC = 0;
			bool in_FOC = False;

			for(apoints->first(); !apoints->done(); apoints->next()) {
				Point *ap = apoints->cur();
				Point p = *apoints->cur();
std::cout << "_R_FOC*ap=" << *ap << " p=" << p << std::endl << std::flush;

				if (!in_FOC) {
					switch (p.y) {
						case 2:
							std::cout << "_R_Start FOC : " << p << std::endl << std::flush; 
							start_FOC = p.x;
							break;
						case 3:
							std::cout << "_R_End FOC : " << p << std::endl << std::flush; 
							if (y >= start_FOC && y <= p.x) {
std::cout << "_R_ Point [" << x << ", " << y << "] in FOC! " << std::endl << std::flush;
								in_FOC = True;
								end_FOC = p.x;
							}
							else
								start_FOC = INT_MAX;		//reset
							break;
						default:
							std::cout << "_R_ignored : " << p << std::endl << std::flush; 
							break;
					}
				}
			}


std::cout << "--R---> PtInFOCblok: in_FOC=" << in_FOC << "[" << start_FOC << "->" 
<< end_FOC <<"]" << std::endl << std::flush; 
			*start = start_FOC;
			*end = end_FOC;
			return (in_FOC);
		}

		return False;
	}
	else {
		std::cout << "_R_PtInFOCBlock: NOT inside rect " << std::endl << std::flush;
		return False;
	}
}


bool LifeLine::PtInFOCarea(int x, int y) const {
std::cout << " bool LifeLine::PtInFOCarea(" << x << "," << y << ") @[" 
<< *GetPosition() << "]" << std::endl << std::flush;

	Rectangle rect(GetPosition()->x - 5,
					GetPosition()->y + GetHeight()/2,
					10,
					endPosition.y - (GetPosition()->y + GetHeight()/2));
	if (rect.Inside(x, y)) {
		std::cout << "PtInFOCarea: inside rect (" << std::endl << std::flush; 
		return True;
	} else {
		std::cout << "PtInFOCarea: NOT inside rect " << std::endl << std::flush; 
		return False;
	}
//	return (rect.Inside(x, y));
}


bool LifeLine::IsOverlappingFOC(int startFOC, int endFOC) const {
std::cout << " bool LifeLine::IsOverlappingFOC(" << startFOC << ", " << endFOC << ")" << std::endl << std::flush;

		if (check(GetSubject() &&
		  	GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {



std::cout << "_O_GetSubject()->GetId()  = " << GetSubject()->GetId()
//<< " GetName.getstr=" << *GetSubject()->GetName()->getstr()
<< std::endl << std::flush;

std::cout << "_O_NrAnchors =" << ((SQObjectNode *)GetSubject())->NrAnchors() << std::endl << std::flush;

			List<Point *> *apoints;
			apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

std::cout << "_O_NrAnchors2 =" << apoints->count() << std::endl << std::flush;

			bool in_FOC = False;

			for(apoints->first(); !apoints->done(); apoints->next()) {
				Point *ap = apoints->cur();
				Point p = *apoints->cur();
std::cout << "_O_FOC*ap=" << *ap << " p=" << p << std::endl << std::flush;

				if ( (ap->x > startFOC) && (ap->x < endFOC) ) {		//excluding borders
std::cout << " #### GOT IT: [" << startFOC << " <- " << ap->x << " -> " << endFOC << "]" << std::endl << std::flush;
					in_FOC = True;
				}
			}

std::cout << "--O--> IsOverlappingFOC(" << startFOC << ", " << endFOC << ") ==> " << in_FOC << std::endl << std::flush;

			return (in_FOC);
		}

std::cout << " NOT A Code::CBD_OBJECT_NODE ??? " << std::endl << std::flush;
		return False;
}



/* virtual */ Point LifeLine::GiveAnchorSnp(Point ap, Point to) const {
std::cout << " Point LifeLine::GiveAnchorSnp([" << ap << "], ->[" << to << "] <" 
<< GetPosition()->x << "> )" << std::endl << std::flush;


	Point ref = ap;
	Point p1 = ap;
std::cout << " ap=" << ap << " - ref =" << ref << std::endl << std::flush; 

	if (ref.x != GetPosition()->x) {
std::cout << "DIFF in X: " << ref.x << " <-> " << GetPosition()->x << std::endl << std::flush; 
		ref.x = GetPosition()->x;
	}

	if (PtInFOCblock(ap.x, ap.y))
		p1 = Intersect::BoxIntersects(ap, to, 10, 10);
	else
		p1 = Intersect::BoxIntersects(ref, to, 1, 1);

std::cout << " p1 = " << p1 << std::endl << std::flush; 
	return p1;

}



/* virtual */ Point LifeLine::GiveSnp(Point to, int order, int count,
	int &) /* const */
{
std::cout << "Point LifeLine::GiveSnp([" << to << "], " <<  order 
	<< ", {" << count << "})" << std::endl << std::flush; 

	int dum = 4;
	int *dumm = &dum;
	int *dummy = new int(3);

std::cout << "dum=" << dum << " *dumm=" << *dumm << "*dummy=" << *dummy << std::endl << std::flush;

	Point p1 = NodeShape::GiveSnp(to, order, count, dum ) ;
	Point p2 = NodeShape::GiveSnp(to, order, count, *dumm ) ;
std::cout << " p1 = " << p1 << std::endl << std::flush; 
	return p1;

}


Point LifeLine::GiveOrthoSnp(double dx, double dy, double hs, double vs,
		double tw, double th) const {
std::cout << "$$$ Point LifeLine::GiveOrthoSnp(" << dx << "," << dy << "," 
<< hs << "," << vs << "," << tw << "," << th 
<< std::endl << std::flush; 
	Point *np = new Point (333, 333);
std::cout << " new Poitn ==> " << *np << std::endl << std::flush; 
	return *np;
}



Point LifeLine::GiveOrthoSnp(Point p) const {
std::cout << "$$$ Point LifeLine::GiveOrthoSnp(" << p << ") ep="
<< endPosition.x 
<< std::endl <<std::flush; 
	Point dummy = endPosition;
	dummy.y = 300;
	Point np = GiveAnchorSnp(dummy, p);
std::cout << " GiveAnchorSnp : " << np << " ==> " << p << std::endl << std::flush; 
	return np;
}



TextShape *LifeLine::ChooseTextShape(int x, int y) {

std::cout << "TextShape *LifeLine::ChooseTextShape(" << x << "," << y <<") "
<< std::endl << std::flush;

std::cout << " GetPosition = " << *GetPosition() << std::endl << std::flush; 
std::cout << " GetHeight = " << GetHeight() << std::endl << std::flush; 
std::cout << " EndPosition = " << endPosition << std::endl << std::flush; 
std::cout << " CalcBottomRight = " << GetShapeType()->CalcBottomRight().GetXHorizScaled() << std::endl << std::flush; 

	Rectangle rect2(GetPosition()->x - 5,
					GetPosition()->y + GetHeight()/2,
					10,
					endPosition.y - (GetPosition()->y + GetHeight()/2));

	return NodeShape::ChooseTextShape(x, y);
}




bool LifeLine::ContainsPt(int x, int y) {
std::cout << "****** bool LifeLine::ContainsPt(" << x << "," << y << ")" << std::endl << std::flush;
std::cout << " CONNECT CHECK: IsInConnectMode()="
	<< ((SQViewer *)GetViewer())->IsInConnectMode() << std::endl << std::flush;
std::cout << " prevPos=" << prevPosition << " pos= " << *GetPosition() <<std::endl<<std::flush;


//	bool thisInFOCblock = False; 	//default init

//A	((SQViewer *)GetViewer())->SetInFOCblock(False);	//default init

	Rectangle rect(GetPosition()->x - 11,
					GetPosition()->y + GetHeight()/2,
					22,
					endPosition.y - (GetPosition()->y + GetHeight()/2));
	if (rect.Inside(x, y)) {
		std::cout << ">>> inside rect (" << std::endl << std::flush; 


		if (check(GetSubject() &&
		  	GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) {
		  	


std::cout << "__GetSubject()->GetId()  = " << GetSubject()->GetId()  
//<< " GetName.getstr=" << *GetSubject()->GetName()->getstr()
<< std::endl << std::flush; 

std::cout << "__NrAnchors =" << ((SQObjectNode *)GetSubject())->NrAnchors() << std::endl << std::flush; 

			List<Point *> *apoints;
//			DPoint *prev = new DPoint ((double) GetPosition()->x,
//									(double) (GetPosition()->y + GetHeight()/2) );
			apoints = ((SQObjectNode *)GetSubject())->GetAnchors();

std::cout << "__NrAnchors2 =" << apoints->count() << std::endl << std::flush; 

			int start_FOC = INT_MAX;
			int end_FOC = 0;
			bool in_FOC = False;

			for(apoints->first(); !apoints->done(); apoints->next()) {
				Point *ap = apoints->cur();
				Point p = *apoints->cur();
std::cout << "*ap=" << *ap << " p=" << p << std::endl << std::flush;

				if (!in_FOC) {
					switch (p.y) {
						case 2:
							std::cout << "__Start FOC : " << p << std::endl << std::flush; 
							start_FOC = p.x;
							break;
						case 3:
							std::cout << "__End FOC : " << p << std::endl << std::flush; 
							if (y >= start_FOC && y <= p.x) {
std::cout << " Point [" << x << ", " << y << "] in FOC! " << std::endl << std::flush; 
								in_FOC = True;
								end_FOC = p.x;
							}
							else
								start_FOC = INT_MAX;		//reset
							break;
						default:
							std::cout << "__ignored : " << p << std::endl << std::flush;
							break;
					}
				}
			}


std::cout << " in_FOC=" << in_FOC << "[" << start_FOC << "->" 
<< end_FOC <<"]" << std::endl << std::flush; 
//std::cout << " GNT=" << GetNodeType() << std::endl << std::flush; 
//std::cout << " GdNT=" << GetDefaultNodeType() << std::endl << std::flush; 

			if (in_FOC) {
				//UndrawSelect();

//A				((SQViewer *)GetViewer())->SetInFOCblock(True);

/* ****** *******

				Point old_tl = *GetTopLeft();
std::cout << " old_tl=[" << old_tl << "]" << std::endl << std::flush; 

				prevPosition = *GetPosition();


				int prevWidth = GetWidth();
				int prevHeight = GetHeight();
				SetWidth (10);
				SetHeight (end_FOC - start_FOC);

//				SetXHorizScaled(0.0);


				Point *p1 = new Point ( GetPosition()->x, 
										start_FOC + (end_FOC - start_FOC)/2 );
				SetPosition (p1);
std::cout << " new_tl=[" << *GetTopLeft() << "]" << std::endl << std::flush; 

				DrawSelect();

std::cout << "done SetPositionHandles();" << std::endl << std::flush; 


				SetWidth (prevWidth);
				SetHeight (prevHeight);
				SetPosition ( &prevPosition);		//reset 
* ****** ******* */

			}
			else {
//A				((SQViewer *)GetViewer())->SetInFOCblock(False);

std::cout << " this not in_FOC block " << std::endl << std::flush; 
std::cout << "IsInFOCmode()=" << ((SQViewer *)GetViewer())->IsInFOCmode() 
<< "  IsInFOCblock()=" << ((SQViewer *)GetViewer())->IsInFOCblock() 
<< std::endl << std::flush;


/* *****************

				if (((SQViewer *)GetViewer())->IsInFOCmode()) {
std::cout << " inFOCmode: CREATE FOC here " << std::endl << std::flush; 					


		UndrawShape();

		((SQObjectNode *)GetSubject())->InsertAnchor(y-20,2);
		((SQObjectNode *)GetSubject())->InsertAnchor(y+20,3);
//		((SQObjectNode *)GetSubject())->SortAnchors();

		DrawShape();


				}
***************** */



			}


		}


std::cout << ">>> ### INSIDE rect: returning True" << std::endl << std::flush; 
		return True;
	}
	else {
		std::cout << ">>> NOT inside rect " << std::endl << std::flush; 
		std::cout << ">> IsInConnectMode()=" << ((SQViewer *)GetViewer())->IsInConnectMode() << std::endl << std::flush; 

		if ( ((SQViewer *)GetViewer())->IsInConnectMode() ) {
			bool b1 = NodeShape::ContainsPt(x,y);
std::cout << ">>> ### NOT INSIDE rect && IsInConnectMode: checking NS:ContainsPt: " << b1  << std::endl << std::flush;
			if (b1) {
std::cout << " >>> ### NodeShape::ContainPt True. Set invalidConnect" << std::endl << std::flush; 
				((SQViewer *)GetViewer())->SetInvalidConnect(True);
			}

std::cout << " >>> ### RETURNING" << b1  << std::endl << std::flush; 

			return (b1);
//			return (NodeShape::ContainsPt(x,y));
//			return 0;
		} else {

			bool b2 = NodeShape::ContainsPt(x,y);
std::cout << ">>> $$$ NOT INSIDE rect && $$$$ NOT IsInConnectMode: returning NS:ContainsPt: " << b2 << std::endl << std::flush; 
			return (b2);
//			return (NodeShape::ContainsPt(x,y));
		}
	}
}


/* virtual */ void LifeLine::SetPositionHandles() {
std::cout << " void LifeLine::SetPositionHandles() {" << std::endl << std::flush; 
	// Positions of the handles:
	//   0----5----1
	//   |         |
	//   6         7
	//   |         |
	//   3----4----2
	const Point *pos = GetPosition();
	DPoint tl, br;
	GetShapeType()->CalcTopLeft().CalcPoint(&tl,
		pos->x - HANDLE_WIDTH * 0.5, pos->y - HANDLE_WIDTH * 0.5,
		GetWidth(), GetHeight(), GetName()->GetStringWidth(),
		GetName()->GetStringHeight());
	GetShapeType()->CalcBottomRight().CalcPoint(&br,
		pos->x - HANDLE_WIDTH * 0.5, pos->y - HANDLE_WIDTH * 0.5,
		GetWidth(), GetHeight(), GetName()->GetStringWidth(),
		GetName()->GetStringHeight());
	handles[0].Set(int(0.5 + tl.x), int(0.5 + tl.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[1].Set(int(0.5 + br.x), int(0.5 + tl.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[2].Set(int(0.5 + br.x), int(0.5 + br.y), HANDLE_WIDTH, HANDLE_WIDTH);
	handles[3].Set(int(0.5 + tl.x), int(0.5 + br.y), HANDLE_WIDTH, HANDLE_WIDTH);
//	handles[4].SetPosition(int(0.5 - HANDLE_WIDTH * 0.5 + pos->x), int(0.5 + br.y));
	handles[4].SetPosition(int(0.5 - HANDLE_WIDTH * 0.5 + pos->x), int(0.5 + endPosition.y));
	handles[5].SetPosition(int(0.5 - HANDLE_WIDTH * 0.5 + pos->x), int(0.5 + tl.y));
	if ( ! IsResizable() || GetShapeType()->HasFixedHeight() ) {
		handles[4].width = handles[5].width =
		handles[4].height = handles[5].height = 0;
	} else {
		handles[4].width = handles[5].width = HANDLE_WIDTH;
		handles[4].height = handles[5].height = HANDLE_WIDTH;
	}
	handles[6].SetPosition(int(0.5 + tl.x), int(0.5 - HANDLE_WIDTH * 0.5 + pos->y));
	handles[7].SetPosition(int(0.5 + br.x), int(0.5 - HANDLE_WIDTH * 0.5 + pos->y));
	if ( ! IsResizable() || GetShapeType()->HasFixedWidth() ) {
		handles[6].width = handles[7].width =
		handles[6].height = handles[7].height = 0;
	} else {
		handles[6].width = handles[7].width = HANDLE_WIDTH;
		handles[6].height = handles[7].height = HANDLE_WIDTH;
	}
	SetNrHandles(8);
}


/* virtual */ void LifeLine::SnapPosition() {
std::cout << " /* virtual */ void LifeLine::SnapPosition() {" << std::endl << std::flush; 
	NodeShape::SnapPosition();
}

/* virtual */ void LifeLine::SetPosition(const Point *pos, bool snap) {
std::cout << "@@@ void LifeLine::SetPosition(" << *pos << ", " << snap << ") {" << std::endl << std::flush;

	NodeShape::SetPosition(pos, snap);
}

/* *****
	if ( check(GetView()) &&
	 	 (check(GetSubject() && GetSubject()->GetClassType()==Code::CBD_OBJECT_NODE)) ) {

		if ( (GetView()->Snap(pos->y) + GetHeight()/2) >
				((SQObjectNode *)GetSubject())->GetMinAnchor() ) {
std::cout << "@@@@@@@@@@@@@@@@@@@@2 INVALID position... " << (GetView()->Snap(pos->y) + GetHeight()/2) << " >>> "
<< ((SQObjectNode *)GetSubject())->GetMinAnchor() << std::endl << std::flush;
std::cout << " *GetPosition() = " << *GetPosition() << std::endl << std::flush;
			return;
		} else
			NodeShape::SetPosition(pos, snap);
	} else {
std::cout << " %%%%%%%%% INVALID CHECKS " << std::endl << std::flush;
//	NodeShape::SetPosition(pos, snap);
	}
}

* ***** */
//???????????????????????????????????????????
void LifeLine::UndrawHandles(){
	UndrawSelect();
}
//???????????????????????????????????????????

