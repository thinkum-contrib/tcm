////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl),
// David N. Jansen (dnjansen@cs.utwente.nl)
// Rik Eshuis (eshuis@cs.utwente.nl)
// Jose Canete (canete@lsi.us.es)
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
#include "scgraph.h"
#include "scwindow.h"
#include "textbox.h"
#include "comment.h"
#include "commentlink.h"
#include "scdiagram.h"
#include "roundedbox.h"
#include "scdandstatebox.h"
#include "scdorstate.h"
#include "scdandstate.h"
#include "scdandedge.h"
#include "scdtransitionedge.h"
#include "scdandline.h"
#include "blackdot.h"
#include "bullseye.h"
#include "minidiamond.h"
#include "solidhorizontalbar.h"
#include "solidverticalbar.h"
#include "note.h"
#include "notebox.h"
#include "scddefaultstate.h"
#include "scdfinalstate.h"
#include "scddecisionstate.h"
#include "scdsynchronizationstate.h"
#include "scviewer.h"

#ifdef MODELCHECK
#include "modelcheckdialog.h"
//#include "scdsmv.h"
#include <ctype.h>
#endif

#include "outputfile.h"

#include "adsmcoutputparse.h"
#include "adsedgelabelparse.h"

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

SCDiagram::SCDiagram(Config *c, SCWindow *d, SCViewer *v, SCGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
//	GetReplaceDialog()->ManageNameOnlyToggle(True);
//	scChecks = new SCChecks(this,g);
#ifdef MODELCHECK
	promptDialog = new ModelCheckDialog(GetMainWindow()->GetWidget());
	promptDialog->Initialize();
#endif
}


SCDiagram::~SCDiagram() {
#ifdef MODELCHECK
	delete promptDialog;
#endif
//	delete scChecks;
}


/* virtual */ void SCDiagram::Initialize() {
	Diagram::Initialize();
	SetHierarchic(True);
}


Thing *SCDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	SCGraph *sg = (SCGraph *)GetGraph();
	Thing *thing = 0;
	switch ( classNr ) {
	// view
	case Code::VIEW:
		thing = new ShapeView(GetDiagramViewer());
		break;

	// node shapes
	case Code::ROUNDED_BOX:
		thing = new RoundedBox(v, g, 0, 0);
		break;
	case Code::SCD_AND_STATE_BOX:
		thing = new SCDAndStateBox(v, g, 0, 0);
		break;
	case Code::TEXT_BOX:
		thing = new TextBox(v, g, 0, 0); 
		break;
	case Code::BLACK_DOT:
		thing = new BlackDot(v, g, 0, 0);
		break;
	case Code::BULLS_EYE:
		thing = new BullsEye(v, g, 0, 0);
		break;
	case Code::MINI_DIAMOND:
		thing = new MiniDiamond(v, g, 0, 0);
		break;
	case Code::SOLID_HORIZONTAL_BAR:
		thing = new SolidHorizontalBar(v, g, 0, 0);
		break;
	case Code::SOLID_VERTICAL_BAR:
		thing = new SolidVerticalBar(v, g, 0, 0);
		break;
	case Code::NOTE_BOX:
		thing = new NoteBox(v, g, 0, 0);
		break;

	// lines
	case Code::LINE:
		thing = new Line(v, g, 0, 0, 0);
		break;
//	case Code::ARROW:
//		Line *line = new Line(v, g, 0, 0, 0);
//		line->SetEnd1(LineEnd::EMPTY);
//		line->SetEnd2(LineEnd::FILLED_ARROW);
//		thing = line;
//		break;
	case Code::SCD_AND_LINE:
		thing = new SCDAndLine(v, g, 0, 0);
		break;

	// nodes
	case Code::SCD_AND_STATE:
		thing = new SCDAndState(sg);
		break;
	case Code::SCD_DECISION_STATE:
		thing = new SCDDecisionState(sg);
		break;
	case Code::SCD_DEFAULT_STATE:
		thing = new SCDDefaultState(sg);
		break;
	case Code::SCD_FINAL_STATE:
		thing = new SCDFinalState(sg);
		break;
	case Code::SCD_OR_STATE:
		thing = new SCDOrState(sg);
		break;
	case Code::SCD_SYNCHRONIZATION_STATE:
		thing = new SCDSynchronizationState(sg);
		break;
	case Code::COMMENT:
		thing = new Comment(sg);
		break;
	case Code::NOTE:
		thing = new Note(sg);
		break;

	// edges
	case Code::SCD_TRANSITION_EDGE:
		thing = new SCDTransitionEdge(sg, 0, 0);
		break;
	case Code::SCD_AND_EDGE:
		thing = new SCDAndEdge(sg, 0, 0);
		break;
	case Code::COMMENT_LINK:
		thing = new CommentLink(sg, 0, 0);
		break;
	default:
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	}
	return thing;
}


Node *SCDiagram::CreateNode() {
	Node *node = 0;
	SCGraph *sg = (SCGraph *)GetGraph();
	switch ( GetNodeType() ) {
	case Code::SCD_AND_STATE:
		node = new SCDAndState(sg);
		break;
	case Code::SCD_DECISION_STATE:
		node = new SCDDecisionState(sg);
		break;
	case Code::SCD_DEFAULT_STATE:
		node = new SCDDefaultState(sg);
		break;
	case Code::SCD_FINAL_STATE:
		node = new SCDFinalState(sg);
		break;
	case Code::SCD_OR_STATE:
		node = new SCDOrState(sg);
		break;
	case Code::SCD_SYNCHRONIZATION_STATE:
		node = new SCDSynchronizationState(sg);
		break;
	case Code::COMMENT:
		node = new Comment(sg);
		break;
	case Code::NOTE:
		node = new Note(sg);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	}
	return node;
}


Edge *SCDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if ( ! CheckEdgeConstraints(subj1, subj2) )
		return 0;
	Edge *edge = 0;
	SCGraph *sg = (SCGraph *)GetGraph();
	switch ( GetEdgeType() ) {
	case Code::SCD_TRANSITION_EDGE:
		edge = new SCDTransitionEdge(sg, subj1, subj2);
		break;
	case Code::SCD_AND_EDGE:
		if ( ! CheckAndEdgeConstraints(subj1, subj2) )
			return 0;
		edge = new SCDAndEdge(sg, subj1, subj2);
		break;
	case Code::COMMENT_LINK:
		edge = new CommentLink(sg, subj1, subj2);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	}
	return edge;
}


NodeShape *SCDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	switch ( GetNodeShapeType() ) {
	case Code::ROUNDED_BOX:
		shape = new RoundedBox(v, g, x, y);
		break;
	case Code::SCD_AND_STATE_BOX:
		shape = new SCDAndStateBox(v, g, x, y);
		break;
	case Code::TEXT_BOX:
		shape = new TextBox(v, g, x, y);
		break;
	case Code::NOTE_BOX:
		shape = new NoteBox(v, g, x, y);
		break;
	case Code::BLACK_DOT:
		shape = new BlackDot(v, g, x, y);
		break;
	case Code::BULLS_EYE:
		shape = new BullsEye(v, g, x, y);
		break;
	case Code::MINI_DIAMOND:
		shape = new MiniDiamond(v, g, x, y);
		break;
	case Code::SOLID_HORIZONTAL_BAR:
		shape = new SolidHorizontalBar(v, g, x, y);
		break;
	case Code::SOLID_VERTICAL_BAR:
		shape = new SolidVerticalBar(v, g, x, y);
		break;
	default:
		error("%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);
	}
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}


Line *SCDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Line *line = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
//	*((*l)[0]) = *(from->GetPosition());
//	*((*l)[l->count()-1]) = *(to->GetPosition());
	switch ( GetLineType() ) {
	case Code::LINE:
		line = new Line(v, g, from, to, l, IsCurve());
		break;
	case Code::SCD_AND_LINE:
		line = new SCDAndLine(v, g, from, l, IsCurve());
		break;
	default:
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	}

	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
//		line->SetEnd1(GetLineEnd1());
                line->SetEnd2(GetLineEnd2());
	}
	return line;
}


void SCDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::SCD_OR_STATE);
		SetNodeShapeType(Code::ROUNDED_BOX);
		break;
	case 2: SetNodeType(Code::SCD_AND_STATE);
		SetNodeShapeType(Code::SCD_AND_STATE_BOX);
		break;
	case 3: SetNodeType(Code::SCD_DEFAULT_STATE);
		SetNodeShapeType(Code::BLACK_DOT);
		break;
	case 4:	SetNodeType(Code::SCD_FINAL_STATE);
		SetNodeShapeType(Code::BULLS_EYE);
		break;
	case 5: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	case 6:	SetNodeType(Code::SCD_DECISION_STATE);
		SetNodeShapeType(Code::MINI_DIAMOND);
		break;
	case 7:	SetNodeType(Code::SCD_SYNCHRONIZATION_STATE);
		SetNodeShapeType(Code::SOLID_HORIZONTAL_BAR);
		break;
	case 8:	SetNodeType(Code::SCD_SYNCHRONIZATION_STATE);
		SetNodeShapeType(Code::SOLID_VERTICAL_BAR);
		break;
	case 9: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		break;

	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}


void SCDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::SCD_TRANSITION_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
//		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 2: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
//		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 3: SetEdgeType(Code::SCD_AND_EDGE);
		SetLineType(Code::SCD_AND_LINE);
		SetEdgeLineStyle(LineStyle::DASHED);
//		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}


bool SCDiagram::CheckAndEdgeConstraints(Subject *subj1, Subject *subj2) {
	if ( subj1->GetClassType() != Code::SCD_AND_STATE ) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"An and-line must begin at an and-state");
		return False;
	}
	if ( subj1 != subj2 ) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"An and-line must begin and end at the same state");
		return False;
	}

// ----> Hier toevoegen: check that an and-edge lies inside its and-shape.

	return True;
}



bool SCDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False;
	return True;
}


//bool SCDiagram::SetEvent(Transition *t, const string *s) {
//	List<GShape *> shapes;
//	GetDiagramViewer()->GetShapes(t, &shapes);
//	Subject::NameErrType n = t->SetEvent(s);
//	if (n == Subject::OK) {
//		if (shapes.first())
//			do
//				((TransitionArrow *)shapes.cur())->UpdateEvent(s);
//			while (shapes.next());
//		else {
//			error("%s, line %d: shape does not exist\n", 
//					__FILE__, __LINE__);
//			return False;
//		}
//		return True;
//	}
//	else if (n == Subject::IMPOSSIBLE_NAME) {
//		string msg = "'" + *s + "' wrong syntax\n for an event string";
//		ShowDialog(MessageDialog::ERROR, "Error", &msg);
//		return False;
//	}
//	else if (n == Subject::DOUBLE_EDGE) {
//		string msg = "there is already a transition with\n"
//			"event string '" + *s + "' between this pair of states";
//		ShowDialog(MessageDialog::ERROR, "Error", &msg);
//		return False;
//	}
//	else {
//		error("%s, line %d: case not handled\n", __FILE__, __LINE__);
//	}
//	return True;
//}


//bool SCDiagram::SetAction(Subject *t, const string *s, unsigned nr) {
//	List<GShape *> shapes;
//	GetDiagramViewer()->GetShapes(t, &shapes);
//	unsigned m = nr;
//	// split string in different one line strings.
//	string ss(*s);
//	char *str = (char *)ss.getstr();
//	char empty[2] = "";
//	char *x = strtok(str, "\r");
//	if (x == 0)
//		x = empty;
//	while (x != 0) {
//		string *ns = new string(x);
//		bool update = True;
//		Subject::NameErrType result;
//		if (m == nr) {
//			if (t->IsEdge())
//				result = ((Transition *)t)->SetAction(ns, m, True);
//			else
//				result = ((InitialState *)t)->SetAction(ns, m, True);
//		}
//		else {
//			if (t->IsEdge())
//				result = ((Transition *)t)->SetAction(ns, m, False);
//			else
//				result = ((InitialState *)t)->SetAction(ns, m, False);
//			update = False;
//		}
//		if (result != Subject::OK) {
//			string msg;
//			if (result == Subject::HAS_ACTION)
//				msg = "transition already has an action '" + *ns + "'";
//			else
//				msg = "'" + *ns + "' wrong syntax\n for an action string";
//			ShowDialog(MessageDialog::ERROR, "Error", &msg);
//			// make actions empty.
//			*ns = "";
//			if (!update) {
//				for (shapes.first(); !shapes.done(); shapes.next()) {
//					if (t->IsEdge())
//						((TransitionArrow *)shapes.cur())->
//							UpdateAction(ns, m, update);
//					else
//						((InitialStateBox *)shapes.cur())->
//							UpdateAction(ns, m, update);
//				}
//			} 
//			delete ns;
//			return False;
//		}
//		// update the shapes.
//		if (shapes.first())
//			do {
//				if (t->IsEdge())
//					((TransitionArrow *)shapes.cur())->
//						UpdateAction(ns, m, update);
//				else
//					((InitialStateBox *)shapes.cur())->
//						UpdateAction(ns, m, update);
//			} while (shapes.next());
//		else {
//			error("%s, line %d: shape does not exist\n", 
//					__FILE__, __LINE__);
//			return False;
//		}
//		m++;
//		x = strtok(0, "\r");
//		delete ns;
//	}
//	return True;
//}


//InitialState *SCDiagram::FindInitialState(Subject *state) {
//	if (state->GetClassType() == Code::INITIAL_STATE)
//		return (InitialState *)state;
//	List<Subject *> initStates;
//	GetGraph()->GetNodes(&initStates, Code::INITIAL_STATE);
//	for (initStates.first(); !initStates.done(); initStates.next()) {
//		InitialState *init = (InitialState *)initStates.cur();
//		if (GetGraph()->UndirectedPathExists(init, state))
//			return init;
//	} 
//	return 0;
//}


void SCDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
//	total += scChecks->CheckNamelessNodes(Code::INITIAL_STATE, chkbuf);
//	total += scChecks->CheckNamelessNodes(Code::STATE, chkbuf);
//	total += scChecks->CheckNamelessNodes(Code::DECISION_POINT, chkbuf);
//	total += scChecks->CheckDoubleNodes(Code::STATE, chkbuf);
//	total += scChecks->CheckDoubleNodes(Code::DECISION_POINT, chkbuf);
//	total += scChecks->CheckDoubleEvents(chkbuf);
//	total += scChecks->CheckEmptyEvents(chkbuf);
//	total += scChecks->CheckEmptyActions(chkbuf);
//	total += scChecks->CheckNoActions(chkbuf);
//	total += scChecks->CheckCountEdgesFrom(Code::DECISION_POINT, 
//		Code::TRANSITION, 2, INT_MAX, False, False, chkbuf);
//	int sub = scChecks->CheckNodeCount(1, Code::INITIAL_STATE, chkbuf);
//	total += sub;
//	if (sub == 0) {
//		total += scChecks->CheckReachability(
//			Code::INITIAL_STATE, Code::STATE, False, chkbuf);
//		total += scChecks->CheckReachability(
//			Code::INITIAL_STATE, Code::DECISION_POINT, False, chkbuf);
//	}
	ReportCheck(total, &chkbuf);
}


#ifdef MODELCHECK
void SCDiagram::ModelCheckProperty() {
	SetStatus("action: model check document semantics");
	promptDialog->SetTitle("Model check document semantics");
	promptDialog->SetOKCallback(ModelCheckDocumentOKCB, this);
	promptDialog->Popup();
}


/* static */ void SCDiagram::ModelCheckDocumentOKCB(Widget,
		XtPointer clientData, XtPointer)
{
	SCDiagram *scd = (SCDiagram *)clientData;
	string formula, internal, clock;
	scd->promptDialog->GetFormulaString(&formula);
	scd->promptDialog->GetInternString(&internal);
	scd->promptDialog->GetClockString(&clock);
	scd->DoModelCheckDocument(&internal, &formula, &clock);
}


//void SCDiagram::DoModelCheckDocument(const string *internal,
//			const string *formula, const string *clock)
//{
//	SetStatus("action: model check document semantics");
//	GetMainWindow()->SetCursor(MouseCursor::WATCH);
//	string tmpModel;
//tmpModel = "model";
////	GetViewer()->GetPrinter()->MakeTmpFile(&tmpModel);
//	tmpModel += ".smv";
//std::cerr << "Temporary model file: " << tmpModel.getstr() << "\n";
//
//	SaveForModelChecker(&tmpModel, internal, clock, formula);
//	bool ok = ExecuteModelChecker(&tmpModel, formula);
//	GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
////	unlink(tmpModel.getstr());
//	if ( ! ok )
//		SetStatus("model checking aborted");
//	else
//		SetStatus("model checking completed");
//	return;
//}


void SCDiagram::DoModelCheckDocument(const string *internal,
			const string *formula, const string *clock)
{
	SetStatus("action: model check document semantics");
	GetMainWindow()->SetCursor(MouseCursor::WATCH);
	string tmpModel;
	tmpModel = "model";
//	GetViewer()->GetPrinter()->MakeTmpFile(&tmpModel);
	tmpModel += ".smv";
	std::cout << "Temporary model file: " << tmpModel.getstr() << '\n';

	OutputFile *ofile2= new OutputFile();
        ofile2->Open(&tmpModel);
	SCGraph *scg=(SCGraph *)this->GetGraph();
        scg->WriteNuSMV(ofile2,True);
	string f=*formula;
	(*ofile2) << "\nSPEC\n" << f<< "\n";
        ofile2->Close();
        
	//	SaveForModelChecker(&tmpModel, internal, clock, formula);
	//	bool ok = ExecuteModelChecker(&tmpModel, formula);

	GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);




//	unlink(tmpModel.getstr());
	//	if ( ! ok )
	//		SetStatus("model checking aborted");
	//	else
	//		SetStatus("model checking completed");




  char output[6];
  strcpy(output,"XXXXXX");
  (void)mktemp(output); // replaces the six X's with a string that can be used to create a unique file name 
 
  string command = "NuSMV model.smv > ";
  string outputfile= output;
  outputfile += ".out";

  command = command + outputfile;
  std::cout << "Executing command\t" << command;
  system(command.getstr()); // do the actual model checking
  std::cout.flush();
  std::cerr.flush();


  // parse the model checker's output
  ::adsmcoutputin=fopen(outputfile.getstr(),"r");
  ::mctraceindex=0;
  ::statecounter=0;
  ::sourceindex=0;
  ::targetindex=0;
  ::enabledindex=0;
  ::eventIndex=0;
  for (int i=0; i<2000; i++) ::isStable[i]= 0;

  bool b=adsmcoutputparse(); 
  if (b) {
    error("I couldn't parse the model checker's output\n"); 
    return ;
  }
  
  string mctxt;
  if (!mcfeedback) {
    mctxt="The requirement is satisfied\n";
    ShowDialog(MessageDialog::MESSAGE, "Notice", &mctxt);
  }
  else{
    mctxt="The requirement is not satisfied; see the counter example\n";
    ShowDialog(MessageDialog::MESSAGE, "Notice", &mctxt);
    AbstractSequenceDiagram *asd= GenerateAbstractSequenceDiagram();
    ConcreteSequenceDiagram *csd= GenerateConcreteSeqDiag(asd);
    GenerateSeqDiagFile(csd, formula);    
  }

  GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
  unlink(output); // cleanup buf
  //  unlink(req);
  //  unlink(buf); // cleanup if wanted	

  return;
}

void SCDiagram::SaveForModelChecker(const string *path, const string *internal,
			const string * clock, const string *formula) {
	/* Split internal into a list of strings */
	List<string> intevent;
	if ( internal ) {
		const char *cp = internal->getstr();
		while ( *cp ) {
			while ( *cp && isspace(*cp) )
				++cp;
			if ( ! *cp )
				break;
			const char *ep = cp;
			if ( '[' == *cp ) {
				while ( *++ep )
					if ( ']' == *ep ) {
						++ep;
						break;
					}
			} else
				while ( *++ep && ! isspace(*ep) && '[' != *ep )
					;
			string event;
			event.add(cp, ep - cp);
			intevent.add(event);
			cp = ep;
		}
	}

	//	SCDSMV s(GetGraph());
	//	s.WriteSMV(path->getstr(), &intevent, formula);
}


bool SCDiagram::ExecuteModelChecker(const string *path, const string *formula) {
	return False;
}



List<SCDTransitionEdge *> SCDiagram::ComputeMicroStep (SCGraph *gr, int state)
{
  /* This function takes the graph and the number of a state in the NuSMV counterexample trace. It computes the
     transitions to be fired from state to state+1, i.e., the transitions in the microstep.
     Please note that the states are numbered from 0 to ::statecounter-1.
  */


  // state refers to an state of the Kripke structure

  
  
  List<SCDTransitionEdge *> enabledTrans, step;
  List<Subject *> hedges;
  int i;
  int nextState;
  int st;
  int ev;
  int aux;
  int ntrans;
  bool found;
  bool fired;




  if (state >=0 && state < ::statecounter){

    nextState= state +1;

    
    i=0;


    while ((i<(::enabledindex))&&(enabledstatenumber[i]<state))
           i++;
    if (enabledstatenumber[i]>state) // if there is no enabled transition in the specified state of the Kripke Structure (KS)
      return step; //empty

    // Now enabledhyperedge[i] (and possibly some of its followers) is an enabled transition in KS state.
    // We collect all the corresponding SCDTransitionEdge objects in the list "enabledTrans",
    // using the information contained in enabledhyperedge (which come from the NuSMV output).

    gr->GetEdges(&hedges);


    for (int k=i; k<(::enabledindex) && enabledstatenumber[k]==state; k++){
       for (hedges.first();!hedges.done();hedges.next()){
	if ((int)hedges.cur()->GetId()==enabledhyperedge[k]){	
	    enabledTrans.add((SCDTransitionEdge *)hedges.cur()); // the enabled hyperedges in "state"
	    break; // hyperedge found, so abort loop
	}
      }
    }

    // Now enabledTrans contains all the enabled transitions in the specified state.

    ntrans= enabledTrans.count();

      
    for (int et=0; et< ntrans; et++){  //for each enabled transition et

          // We will infer if the transition is taken as in Chan's paper:
	  //  - in the next state, its target is set to one
	  //  - in the next state, the possible action event is set to one
 
          // First we look for the states which are true in the next state.
          // Remember that in targetname we have all the states which are true in the trace.
          found= False;
	  st=0;
	  while (st < targetindex && !found)
	    if (targetstatenumber[st]==nextState)
	      found= True;
	    else
	      st++;
	  // Now in targetname[st] (and possibly, in some of its followers) we have a state that will been entered in the next state
	  // of the KS.
	  // We check if the target state of et is in the set of states which will been entered in the next state.
	  found= False;
	  while (st < targetindex && targetstatenumber[st]==nextState && !found)
	    if (strcmp(targetname[st], enabledTrans[et]->GetSubject2()->GetName()->getstr())==0)
	      found= True;
	    else
	      st++;
	  
	  if (found){
	    if (enabledTrans[et]->GetSendEvent()==NULL) // the transition hasn't send event
	      fired= True;
	    else { // et has send event
	            
	      // Now we have to check that the possible action event of et is sent in the next state.
	      found= False;
	      ev= 0;
	      while (ev < eventIndex && !found)
	        if (occurredEventStates[ev]==nextState)
		  found= True;
	        else
		  ev++;

	      // Now in occurredEvents[ev] (and possibly, in the followers) we have an event which will occur in the next state of the KS.
	      // We check that the send event of et is in the set of occurred events in the next state of the KS.
	      found= False;
	      while (ev < eventIndex && occurredEventStates[ev]==nextState && !found)
		if (strcmp(occurredEvents[ev], enabledTrans[et]->GetSendEvent()->GetName().getstr())==0)
		  found= True;
	        else
		  ev++;
	      
	      fired= found;

	    }
	  }
	  else
	    fired= False;
	  
	  
	  if (fired) //then we add the transition to the step
	    step.add (enabledTrans[et]);
    }

  }
  return step;
} 




AbstractSequenceDiagram * SCDiagram::GenerateAbstractSequenceDiagram ()
{

  AbstractSequenceDiagram *asd;
  int currentState; // current state of the Kripke structure
  int formerState; // state of the Kripke structure where the last processed event was produced
  int ev; // counter for events
  InteractionRow * row;
  SCGraph *theGraph;
  Prop *prop;
  string str;
  List<SCDTransitionEdge *> step;

  
  theGraph= (SCGraph *)GetGraph();


  asd= new AbstractSequenceDiagram;
  str= "Environment";
  asd->AddParticipant(str);
  str= "System";
  asd->AddParticipant(str);

  
  formerState= -1;
  
  for (ev=0; ev<eventIndex; ev++){
    
    // First let's see if ev is really an event (note that it can also be stable (from stable = 1),
    // events (from events = 1), and so on. If it is an event, it will be in the property list of the graph
    // and will have an appropiate type.
    prop= theGraph->EventInPropl(occurredEvents[ev]);
    if (prop && (prop->GetType()==::EV_FROM_ENV ||
                 prop->GetType()==::EV_TO_ENV ||
                 prop->GetType()==::EV_INT)){ //ok, it is an event!
        currentState= ::occurredEventStates[ev];
        if (formerState != currentState) //we need a new row!
	    row= asd->AddRow(currentState); //add a new row with the correct number of columns; it also returns the row
        
        // row is the current row in which we have to include the event
        if (prop->GetType()==::EV_FROM_ENV)
	    row->participants[0].AddPairObjEv(1,prop->GetName());
        else if (prop->GetType()==::EV_TO_ENV)
	    row->participants[1].AddPairObjEv(0,prop->GetName());
        else{ //EV_INT
	    row->participants[1].AddPairObjEv(1, prop->GetName());
	    step= ComputeMicroStep (theGraph, currentState-1); //computes the fired transitions from
	    // the KR states currentState-1 to currentState.
	    // With this, we get the transitions that have been fired. The event ev must be in the
	    // action part of some transition in the set. We have to check if it is EV_INT_BC in that
	    // transition.
	    if (IsBroadcast (prop->GetName(), step))
	      row->participants[1].AddPairObjEv(0, prop->GetName());	    
        }
	formerState= currentState;
    }
  }  

  return asd;


}


bool SCDiagram::IsBroadcast (string event, List<SCDTransitionEdge *> step)
{
  bool found= false;
  int i= 0;
  Prop *prop;

  while (i< step.count() && !found){
    if (step[i]->GetSendEvent()){ //it has send event
      prop= step[i]->GetSendEvent();
      if (prop->GetName()==event && prop->GetType()==::EV_INT_BC)
	found= true;
      else
	i++;
    }
    else
      i++;
  }

  return found;
}





ConcreteSequenceDiagram * SCDiagram::GenerateConcreteSeqDiag (AbstractSequenceDiagram *asd)
{
  ConcreteSequenceDiagram *csd;
  ConcreteParticipant *cp;
  InteractionRow *row;
  InteractionParticipant *ip;
  PairObjEv *pair;
  StimulusInfo *sinf;
  Stimulus *stim1;
  Stimulus *stim2;
  int stimY;
  int formerState, currentState;

  string microstep= "-----------------microstep-----------------";
  string stable=    "------------------stable-------------------";
  

  int i, j, k, ev;
  bool found;

  if (asd==NULL) return NULL;

  csd= new ConcreteSequenceDiagram;

  
  
  // First we create all the ConcreteParticipants, in the same order as in AbstractSequenceDiagram.
  // note that this is just the trivial ordering, but it is possible also to have other layouts (different orderings
  // of the participants).
  for (i=0; i< asd->numObjs; i++){
    cp= new ConcreteParticipant();
    cp->name= asd->objNames[i];
    cp->logicalId= csd->NextId();
    cp->shapeId= csd->NextId();
    cp->y= 50; //we set all the objects to a height of 50
    cp->x= 120+i*280; //this way every object will be horizontally separated by 280 units from its neighbours.
    csd->participants.add (cp);
  }
  
  // Now we travel across all the happened events.
  // We create StimulusInfo objects for the list of stimuli, and
  // we attach those stimuli to the concrete participants created
  // above.
  for (i=0; i< asd->rows.count(); i++){
    
    if (i==0){
      // A microstep begins in the diagram. We add the proper comment.
      // Note that it's simulating a false message from the first participant
      // to the last one. This way the comment extends over all the objects.
      // Note that we do not add the stimuli in the anchor lists of the objects,
      // as it is not an anchor.
      sinf= new StimulusInfo();
      sinf->sender= csd->participants[0];
      sinf->receiver= csd->participants[csd->participants.count()-1];
      sinf->label= stable;
      sinf->logicalId= csd->NextId();
      sinf->shapeId= csd->NextId();
      stimY= 110; // initial position in the temporal line
      sinf->y= stimY;
      sinf->isComment= True;
      csd->stimuli.add (sinf);
    }

    row= asd->rows[i];
 
    if (i==0)
      formerState= currentState= row->GetCurrentState();
    else{
      formerState= currentState;
      currentState= row->GetCurrentState();
    }


    found= False;
    k= formerState+1;
    while (k<=currentState && !found){
      if (::isStable[k])
	found= True;
      else
	k++;
    }
   
    if (found){
        sinf= new StimulusInfo();
        sinf->sender= csd->participants[0];
        sinf->receiver= csd->participants[csd->participants.count()-1];
        sinf->label= stable;
        sinf->logicalId= csd->NextId();
        sinf->shapeId= csd->NextId();
        stimY+=50;
        sinf->y= stimY;
        sinf->isComment= True;
        csd->stimuli.add (sinf);
    }


    for (j=0; j< asd->numObjs; j++){
      ip= &(row->participants[j]);
      for (ev=0; ev< ip->GetNumberOfEvents(); ev++){
	pair= ip->GetPairObjEv (ev);
	sinf= new StimulusInfo();
	sinf->sender= csd->participants[j];
	sinf->receiver= csd->participants[pair->GetObj()];
	sinf->label= pair->GetEv();
	sinf->logicalId= csd->NextId();
	sinf->shapeId= csd->NextId();
	stimY+=50;
	sinf->y= stimY;
	sinf->isComment= False;
	
	stim1= new Stimulus();
	stim2= new Stimulus();
	stim1->isSender= True;
	stim2->isSender= False;
	stim1->info= sinf;
	stim2->info= sinf;
	
	csd->participants[j]->anchors.add (stim1); //Sender
	if (j!=pair->GetObj()) // if it is not an event to self
	    csd->participants[pair->GetObj()]->anchors.add (stim2); //Receiver

	csd->stimuli.add (sinf);
      } //end of loop in ev
    } //end of loop in j

    // We add a new comment to mark the end of the microstep or the stability of the system.
    sinf= new StimulusInfo();
    sinf->sender= csd->participants[0];
    sinf->receiver= csd->participants[csd->participants.count()-1];
    sinf->label= microstep;
    sinf->logicalId= csd->NextId();
    sinf->shapeId= csd->NextId();
    stimY+=50;
    sinf->y= stimY;
    sinf->isComment= True;
    csd->stimuli.add (sinf);
  } //end of loop in i

  if (::isStable[::statecounter-1]){ //The system finishes stable
    sinf= new StimulusInfo();
    sinf->sender= csd->participants[0];
    sinf->receiver= csd->participants[csd->participants.count()-1];
    sinf->label= stable;
    sinf->logicalId= csd->NextId();
    sinf->shapeId= csd->NextId();
    stimY+=50;
    sinf->y= stimY;
    sinf->isComment= True;
    csd->stimuli.add (sinf);
  }

  csd->lineLength= stimY+50;


  return csd;
}



void SCDiagram::GenerateSeqDiagFile (ConcreteSequenceDiagram *csd, const string *formula)
{
  
  string filen= "cntex.sqd";
  OutputFile *fp;


  if (csd==NULL) return;

  fp= new OutputFile();
  fp->Open (&filen);

  (*fp) << "Storage\n";
  (*fp) << "{\n";
  (*fp) << "\t{ Format 1.32 }\n";
  (*fp) << "\t{ GeneratedFrom TSCD-version-2.10a }\n";
  (*fp) << "\t{ WrittenBy tcm }\n";
  (*fp) << "\t{ WrittenOn \"Sat Jul  6 17:16:35 2002\" }\n";
  (*fp) << "\t}\n\n";
  (*fp) << "Document\n";
  (*fp) << "{\n";
  (*fp) << "\t{ Type \"Sequence Diagram\" }\n";
  (*fp) << "\t{ Name cntex.sqd }\n";
  (*fp) << "\t{ Author tcm }\n";
  (*fp) << "\t{ CreatedOn \"Sat Jul  6 14:14:12 2002\" }\n";
  (*fp) << "\t{ Annotation \"\" }\n";
  (*fp) << "}\n\n";
  (*fp) << "Page\n";
  (*fp) << "{\n";
  (*fp) << "\t{ PageOrientation Portrait }\n";
  (*fp) << "\t{ PageSize A4 }\n";
  (*fp) << "\t{ ShowHeaders False }\n";
  (*fp) << "\t{ ShowFooters False }\n";
  (*fp) << "\t{ ShowNumbers False }\n";
  (*fp) << "}\n\n";
  (*fp) << "Scale\n";
  (*fp) << "{\n";
  (*fp) << "\t{ ScaleValue 1 }\n";
  (*fp) << "}\n\n";
  (*fp) << "# GRAPH NODES\n\n";

  GenerateGraphNodes (csd, fp);
  GenerateComments (csd, fp);
  GenerateNote (csd, fp, formula);
  GenerateGraphEdges (csd, fp);


  (*fp) << "# VIEWS AND GRAPHICAL SHAPES\n";
  (*fp) << "\n";
  (*fp) << "View 1\n";
  (*fp) << "{\n";
  (*fp) << "\t{ Index \"0\" }\n";
  (*fp) << "\t{ Parent 0 }\n";
  (*fp) << "}\n\n";

  GenerateObjectBoxes (csd, fp);
  GenerateT4Lines (csd, fp);
  GenerateTextBoxes (csd, fp);
  GenerateNoteBox (csd, fp);


  fp->Close();

}



void SCDiagram::GenerateGraphNodes (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  int i, j;
  ConcreteParticipant *cp;



  if (csd==NULL || fp==NULL) return;

 
  for (i=0; i< csd->participants.count(); i++){
    cp= csd->participants[i];
    (*fp) << "CBDObjectNode " << cp->logicalId << "\n";
    (*fp) << "{\n";
    (*fp) << "\t{ Name \"" << cp->name << "\" }\n";
    (*fp) << "\t{ Annotation \"\" }\n";
    (*fp) << "\t{ Parent 0 }\n";
    (*fp) << "\t{ Index \"\" }\n";
    (*fp) << "\t{ Stereotype \"<< - >>\" }\n";
    (*fp) << "\t{ Properties \"{ - }\" }\n";
    (*fp) << "\t{ Anchors " << cp->anchors.count() << " }\n"; //it's OK also for 0
    for (j=0; j< cp->anchors.count(); j++){
      (*fp) << "\t{ Anchor " << cp->anchors[j]->info->y << " ";
      if (cp->anchors[j]->isSender)
	(*fp) << cp->logicalId; // it puts its own number
      else
	(*fp) << cp->anchors[j]->info->sender->logicalId;
      
      (*fp) << " }\n";
    }
    (*fp) << "}\n";
  }

}



void SCDiagram::GenerateComments (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  int i;
  StimulusInfo *sinf;

  if (csd==NULL || fp==NULL) return;


  // We travel across the stimuli and issue a "Comment" section in the file every
  // time we find a stimuli with a True isComment attribute.

  for (i=0; i< csd->stimuli.count(); i++){
    if (csd->stimuli[i]->isComment){
      sinf= csd->stimuli[i];
      (*fp) << "Comment " << sinf->logicalId << "\n";
      (*fp) << "{\n";
      (*fp) << "\t{ Name \"" << sinf->label << "\" }\n";
      (*fp) << "\t{ Annotation \"\" }\n";
      (*fp) << "\t{ Parent 0 }\n";
      (*fp) << "\t{ Index \"\" }\n";
      (*fp) << "}\n\n";
    }
  }

}



void SCDiagram::GenerateGraphEdges (ConcreteSequenceDiagram *csd, OutputFile *fp)
{

  int i;
  StimulusInfo *sinf;


  if (csd==NULL || fp==NULL) return;

  (*fp) << "# GRAPH EDGES\n\n";


  for (i=0; i< csd->stimuli.count(); i++){
    if (!csd->stimuli[i]->isComment){ //then it is a real stimulus
      sinf= csd->stimuli[i];
      (*fp) << "CBDObjectLinkEdge " << sinf->logicalId << "\n";
      (*fp) << "{\n";
      (*fp) << "\t{ Name \"" << sinf->label << "\" }\n";
      (*fp) << "\t{ Annotation \"\" }\n";
      (*fp) << "\t{ Parent 0 }\n";
      (*fp) << "\t{ Subject1 " << sinf->sender->logicalId << " }\n";
      (*fp) << "\t{ Subject2 " << sinf->receiver->logicalId << " }\n";
      (*fp) << "\t{ Anchor1 " << sinf->y << " " << sinf->sender->shapeId << " }\n";
      (*fp) << "\t{ Anchor2 " << sinf->y << " " << sinf->receiver->shapeId << " }\n";
      (*fp) << "}\n\n";
    }
  }

}



void SCDiagram::GenerateObjectBoxes (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  int i, len;
  ConcreteParticipant *cp;

  if (csd==NULL || fp==NULL) return;

  for (i=0; i< csd->participants.count(); i++){
    cp= csd->participants[i];
    (*fp) << "SSDSingleObjectBox " << cp->shapeId << "\n";
    (*fp) << "{\n";
    (*fp) << "\t{ View 1 }\n";
    (*fp) << "\t{ Subject " << cp->logicalId << " }\n";
    (*fp) << "\t{ Position " << cp->x << " " << cp->y << " }\n";
    (*fp) << "\t{ Size 80 40 }\n";
    (*fp) << "\t{ Color \"black\" }\n";
    (*fp) << "\t{ LineWidth 1 }\n";
    (*fp) << "\t{ LineStyle Solid }\n";
    (*fp) << "\t{ FillStyle Unfilled }\n";
    (*fp) << "\t{ FillColor \"white\" }\n";
    (*fp) << "\t{ FixedName False }\n";
    (*fp) << "\t{ Font \"-*-helvetica-medium-r-normal--10*\" }\n";
    (*fp) << "\t{ TextAlignment Center }\n";
    (*fp) << "\t{ TextColor \"black\" }\n";
    (*fp) << "\t{ NameUnderlined True }\n";

    /* We need to know how long will be the lifeline of each object. We have chosen that 
       all the objects have the same length.
    */
    (*fp) << "\t{ EndPosition " << cp->x << " " << csd->lineLength << " }\n";
    (*fp) << "\t{ Destructive 0 }\n";
    (*fp) << "}\n\n";
  }


}



void SCDiagram::GenerateT4Lines (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  int i;
  StimulusInfo *sinf;
  int min;


  if (csd==NULL || fp==NULL) return;


  for (i=0; i< csd->stimuli.count(); i++){
    sinf= csd->stimuli[i];
    if (!sinf->isComment){
      (*fp) << "T4Line " << sinf->shapeId << "\n";
      (*fp) << "{\n";
      (*fp) << "\t{ View 1 }\n";
      (*fp) << "\t{ Subject " << sinf->logicalId << " }\n";
      (*fp) << "\t{ FromShape " << sinf->sender->shapeId << " }\n";
      (*fp) << "\t{ ToShape " << sinf->receiver->shapeId << " }\n";
      (*fp) << "\t{ Curved False }\n";
      (*fp) << "\t{ End1 Empty }\n";
      (*fp) << "\t{ End2 FilledArrow }\n";
      if (sinf->sender==sinf->receiver){ // event to self
	// This kind of arrow consists of 4 points.
	(*fp) << "\t{ Points 4 }\n";
	(*fp) << "\t{ Point " << sinf->sender->x << " " << sinf->y << " }\n";
	(*fp) << "\t{ Point " << (sinf->sender->x+20) << " " << sinf->y << " }\n";
	(*fp) << "\t{ Point " << (sinf->sender->x+20) << " " << (sinf->y+10) << " }\n";
	(*fp) << "\t{ Point " << sinf->sender->x << " " << (sinf->y+10) << " }\n";
      }
      else{ //event between two different participants
	(*fp) << "\t{ Points 2 }\n";
	(*fp) << "\t{ Point " << sinf->sender->x << " " << sinf->y << " }\n";
	(*fp) << "\t{ Point " << sinf->receiver->x << " " << sinf->y << " }\n";
      }
      // The position of the name is fixed to 140 units from the smallest X of both objects
      // and 10 units from the Y, unless it is an event to self. In that case, the offset is 20.
      if (sinf->sender->x < sinf->receiver->x)
	min= sinf->sender->x;
      else
	min= sinf->receiver->x;
	
      if (sinf->sender==sinf->receiver)
	 (*fp) << "\t{ NamePosition " << (min+20) << " " << (sinf->y-10) << " }\n";
      else
         (*fp) << "\t{ NamePosition " << (min+140) << " " << (sinf->y-10) << " }\n";
      (*fp) << "\t{ Color \"black\" }\n";
      (*fp) << "\t{ LineWidth 1 }\n";
      (*fp) << "\t{ LineStyle Solid }\n";
      (*fp) << "\t{ FixedName False }\n";
      (*fp) << "\t{ Font \"-*-helvetica-medium-r-normal--10*\" }\n";
      (*fp) << "\t{ TextAlignment Center }\n";
      (*fp) << "\t{ TextColor \"black\" }\n";
      (*fp) << "\t{ NameUnderlined False }\n";
      (*fp) << "}\n\n";
    }
  }

}


void SCDiagram::GenerateTextBoxes (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  int i;
  StimulusInfo *sinf;

  if (csd==NULL || fp==NULL) return;

  for (i=0; i< csd->stimuli.count(); i++){
    sinf= csd->stimuli[i];
    if (sinf->isComment){
      (*fp) << "TextBox " << sinf->shapeId << "\n";
      (*fp) << "{\n";
      (*fp) << "\t{ View 1 }\n";
      (*fp) << "\t{ Subject " << sinf->logicalId << " }\n";
      (*fp) << "\t{ Position " << (sinf->sender->x+140) << " " << sinf->y << " }\n";
      (*fp) << "\t{ Size 20 20 }";
      (*fp) << "\t{ Color \"black\" }\n";
      (*fp) << "\t{ LineWidth 1 }\n";
      (*fp) << "\t{ LineStyle Invisible }\n";
      (*fp) << "\t{ FillStyle Unfilled }\n";
      (*fp) << "\t{ FillColor \"white\" }\n";
      (*fp) << "\t{ FixedName False }\n";
      (*fp) << "\t{ Font \"-*-helvetica-medium-r-normal--10*\" }\n";
      (*fp) << "\t{ TextAlignment Center }\n";
      (*fp) << "\t{ TextColor \"black\" }\n";
      (*fp) << "\t{ NameUnderlined False }\n";
      (*fp) << "}\n\n";
     }
  }

}



void SCDiagram::GenerateNote (ConcreteSequenceDiagram *csd, OutputFile *fp, const string *formula)
{
  if (csd==NULL || fp==NULL || formula==NULL) return;

  (*fp) << "Note " << csd->NextId() << "\n";
  (*fp) << "{\n";
  (*fp) << "\t{ Name \"Counterexample for\\r" << *formula << "\" }\n";
  (*fp) << "\t{ Annotation \"\" }\n";
  (*fp) << "\t{ Parent 0 }\n";
  (*fp) << "\t{ Index \"\" }\n";
  (*fp) << "}\n\n";
}



void SCDiagram::GenerateNoteBox (ConcreteSequenceDiagram *csd, OutputFile *fp)
{
  if (csd==NULL || fp==NULL) return;

  int id= csd->NextId();
  int posx= csd->participants[csd->participants.count()-1]->x;
  int posy= csd->participants[csd->participants.count()-1]->y;

  (*fp) << "NoteBox " << id << "\n";
  (*fp) << "{\n";
  (*fp) << "\t{ View 1 }\n";
  (*fp) << "\t{ Subject " << (id-1) << " }\n";
  (*fp) << "\t{ Position " << (posx+160) << " " << posy << " }\n";
  (*fp) << "\t{ Size 170 82 }\n"; //Enhacement: calculate the size based on the characters of the formula.
  (*fp) << "\t{ Color \"black\" }\n";
  (*fp) << "\t{ LineWidth 1 }\n";
  (*fp) << "\t{ LineStyle Solid }\n";
  (*fp) << "\t{ FillStyle Unfilled }\n";
  (*fp) << "\t{ FillColor \"white\" }\n";
  (*fp) << "\t{ FixedName False }\n";
  (*fp) << "\t{ Font \"-*-helvetica-medium-r-normal--10*\" }\n";
  (*fp) << "\t{ TextAlignment Center }\n";
  (*fp) << "\t{ TextColor \"black\" }\n";
  (*fp) << "\t{ NameUnderlined False }\n";
  (*fp) << "}\n\n";
}

void InteractionParticipant::AddPairObjEv (int object, string event)
{
  PairObjEv *newPair= new PairObjEv (object, event);
  eventsToSend.add (newPair);
}



void InteractionParticipant::PrintIt ()
{
  std::cout << "Participant:" << std::endl;
  for (int i=0; i< eventsToSend.count(); i++)
    eventsToSend[i]->PrintIt();
  std::cout << std::endl;

}

void InteractionRow::PrintIt ()
{
  for (int i=0; i< numObj; i++)
    participants[i].PrintIt();

  std::cout << std::endl;

}

void AbstractSequenceDiagram::PrintIt ()
{
  for (int t=0; t< rows.count(); t++){
    std::cout << "Time " << std::endl;
    rows[t]->PrintIt();
  }
}


InteractionRow * AbstractSequenceDiagram::AddRow (int cs)
{
  InteractionRow *ir= new InteractionRow (numObjs, cs);
  rows.add (ir);
  return ir;
}
 

#endif


//bool SCDiagram::SetText(TextShape *t, const string *s) {
//	const string *description = t->GetDescription();
//	Subject *subj = t->GetParent()->GetSubject();
//	if (*description == "Event")
//		return SetEvent((Transition *)subj, s);
//	else if (*description == "Action")
//		return SetAction(subj, s, t->GetSequence());
//	else 
//		return Diagram::SetText(t, s);
//}
