////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
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
#include "atdactionstatenode.h"
#include "atddecisionstatenode.h"
#include "atdfinalstatenode.h"
#include "atdwaitstatenode.h"
#include "atdinitialstatenode.h"
#include "atdsynchronizationnode.h"
#include "atdtransitionedge.h"
#include "emptynode.h"
#include "blackdot.h"
#include "bullseye.h"
#include "note.h"
#include "notebox.h"
#include "roundedbox.h"
#include "ellipsedbox.h"
#include "solidhorizontalbar.h"
#include "solidverticalbar.h"
#include "minidiamond.h"
#include "line.h"
#include "textbox.h"
#include "comment.h"
#include "commentlink.h"
#include "atchecks.h"
#include "atdiagram.h"
#include "atgraph.h"
#include "atviewer.h"
#include "atwindow.h"

#include "system.h"  
#include "adshypergraph.h"
#include "adssemantics.h"                                           /*new*/
#include "adseliminatepseudostatenodes.h"
#include "adspropertyvaluation.h"
#include "adsproperty.h"
#include "temporalpropertydialog.h"
#include "outputfile.h"
#include "inputfile.h"
#include "adsmcoutputparse.h"
#include "adsltlformulaparse.h"
//#include "adsmcoutput.tab.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>


const int ATDiagram::DOT_WIDTH = 8;
 
ATDiagram::ATDiagram(Config *c, ATWindow *d, ATViewer *v, ATGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	atChecks = new ATChecks(this,g);
}

ATDiagram::~ATDiagram() {
	delete atChecks;
}

Thing *ATDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	ATGraph *cg = (ATGraph *)GetGraph();
	Thing *thing = 0;

	if (classNr == Code::ELLIPSED_BOX)
		thing = new EllipsedBox(v, g, 0, 0); 
	else if (classNr == Code::ROUNDED_BOX)
		thing = new RoundedBox(v, g, 0, 0); 
	else if (classNr == Code::MINI_DIAMOND)
		thing = new MiniDiamond(v, g, 0, 0); 
	else if (classNr == Code::BLACK_DOT)
		thing = new BlackDot(v, g, 0, 0); 
	else if (classNr == Code::BULLS_EYE)
		thing = new BullsEye(v, g, 0, 0); 
	else if (classNr == Code::SOLID_HORIZONTAL_BAR)
                thing = new SolidHorizontalBar(v, g, 0, 0);
	else if (classNr == Code::SOLID_VERTICAL_BAR)
                thing = new SolidVerticalBar(v, g, 0, 0);
	else if (classNr == Code::NOTE_BOX)
                thing = new NoteBox(v, g, 0, 0);
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 

	else if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer()); 

	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);
	// old line (arrow) types...
	else if (classNr == Code::ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		thing = line;
	}

	else if (classNr==Code::INITIAL_STATE || classNr == Code::ATD_INITIAL_STATE_NODE)
		thing = new ATDInitialStateNode(cg);
	else if (classNr == Code::ATD_ACTION_STATE_NODE)
		thing = new ATDActionStateNode(cg);
	else if (classNr == Code::ATD_WAIT_STATE_NODE)
		thing = new ATDWaitStateNode(cg);
	else if (classNr == Code::ATD_DECISION_STATE_NODE)
		thing = new ATDDecisionStateNode(cg);
	else if (classNr == Code::ATD_SYNCHRONIZATION_NODE)
		thing = new ATDSynchronizationNode(cg);
	else if (classNr==Code::FINAL_STATE || classNr == Code::ATD_FINAL_STATE_NODE)
		thing = new ATDFinalStateNode(cg);
	else if (classNr == Code::NOTE)
		thing = new Note(cg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(cg);

	// edges
	else if (classNr==Code::TRANSITION || classNr == Code::ATD_TRANSITION_EDGE)
		thing = new ATDTransitionEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);

	else {
		error("%s, line %d: impl error: " "wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
		return 0;
	}
	if (thing != 0 && HasIndexShape(thing->GetClassType()))
		((NodeShape *)thing)->SetFixedIndexLabel(False);

	return thing;
}

Node *ATDiagram::CreateNode(){
	Node *node = 0;
	ATGraph *g = (ATGraph *)GetGraph();
	if (GetNodeType() == Code::ATD_INITIAL_STATE_NODE)
		node = new ATDInitialStateNode(g);
	else if (GetNodeType() == Code::ATD_ACTION_STATE_NODE)
		node = new ATDActionStateNode(g);
	else if (GetNodeType() == Code::ATD_WAIT_STATE_NODE)
		node = new ATDWaitStateNode(g);
	else if (GetNodeType() == Code::ATD_DECISION_STATE_NODE)
		node = new ATDDecisionStateNode(g);
	else if (GetNodeType() == Code::ATD_SYNCHRONIZATION_NODE)
		node = new ATDSynchronizationNode(g);
	else if (GetNodeType() == Code::ATD_FINAL_STATE_NODE)
		node = new ATDFinalStateNode(g);
	else if (GetNodeType() == Code::NOTE)
		node = new Note(g);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(g);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *ATDiagram::CreateEdge(Subject *node1, Subject *node2){
	// Check possible connections (node-node-edge matrix).
	if (!CheckConnection(node1, node2))
		return 0; 
	if ((GetEdgeType() == Code::ATD_TRANSITION_EDGE) &&
	    (node1->GetClassType() == Code::ATD_DECISION_STATE_NODE) && 
	    (node1 == node2)) {
		ShowDialog(MessageDialog::ERROR, "Error",
			       "This is not a valid transition");
		return 0;
	}
	Edge *edge = 0;
	ATGraph *g = (ATGraph *)GetGraph();
	if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, node1, node2);
	else if (GetEdgeType() == Code::ATD_TRANSITION_EDGE)
		edge = new ATDTransitionEdge(g, node1, node2);

	else 
		error( "%s, line %d: impl error: "
			" unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *ATDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	int t = GetNodeShapeType();
	if (t == Code::ELLIPSED_BOX)
		shape = new EllipsedBox(v, g, x, y);
	else if (t == Code::ROUNDED_BOX)
		shape = new RoundedBox(v, g, x, y);
	else if (t == Code::MINI_DIAMOND)
		shape = new MiniDiamond(v, g, x, y);
	else if (t == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else if (t == Code::BLACK_DOT)
		shape = new BlackDot(v, g, x, y);
	else if (t == Code::BULLS_EYE)
		shape = new BullsEye(v, g, x, y);
	else if (t == Code::SOLID_HORIZONTAL_BAR)
                shape = new SolidHorizontalBar(v, g, x, y);
	else if (t == Code::SOLID_VERTICAL_BAR)
                shape = new SolidVerticalBar(v, g, x, y);
	else if (t == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else {
		error( "%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);
	}
	if (check(shape)) {
		if (HasIndexShape(t))
			shape->SetFixedIndexLabel(False);
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *ATDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	int t = GetLineType();
	if (t == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error( "%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());
	}
	return line;
}

void ATDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::ATD_ACTION_STATE_NODE);
		SetNodeShapeType(Code::ELLIPSED_BOX);
		break;
	case 2: SetNodeType(Code::ATD_DECISION_STATE_NODE);
		SetNodeShapeType(Code::MINI_DIAMOND);
		break;
	case 3: SetNodeType(Code::ATD_SYNCHRONIZATION_NODE);
		SetNodeShapeType(Code::SOLID_HORIZONTAL_BAR);
		break;
	case 4: SetNodeType(Code::ATD_INITIAL_STATE_NODE);
                SetNodeShapeType(Code::BLACK_DOT);
                break;
	case 5: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		SetNodeLineStyle(LineStyle::INVISIBLE);
		break;
	case 6: SetNodeType(Code::ATD_WAIT_STATE_NODE);
		SetNodeShapeType(Code::ROUNDED_BOX);
		break;
	case 7: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		break;
	case 8: SetNodeType(Code::ATD_SYNCHRONIZATION_NODE);
		SetNodeShapeType(Code::SOLID_VERTICAL_BAR);
		break;
	case 9: SetNodeType(Code::ATD_FINAL_STATE_NODE);
		SetNodeShapeType(Code::BULLS_EYE);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void ATDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::ATD_TRANSITION_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 2: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool ATDiagram::HasIndexNode(int code) {
	return (code == Code::ATD_ACTION_STATE_NODE ||
		code == Code::ATD_WAIT_STATE_NODE ||
		code == Code::ATD_DECISION_STATE_NODE);
}

bool ATDiagram::HasIndexShape(int code) {
	return (code==Code::ROUNDED_BOX ||
		code==Code::ELLIPSED_BOX ||
		code==Code::DIAMOND ||
		code==Code::NOTE_BOX);
}

void ATDiagram::CheckDocument() {
	chkbuf = "";
	unsigned errors = 0;
	errors += atChecks->CheckNodeCount(1, Code::ATD_INITIAL_STATE_NODE, chkbuf);
	errors += atChecks->CheckNodeCount(1, Code::ATD_FINAL_STATE_NODE, chkbuf);
	if (errors == 0)    // only useful with 1 INITIAL && 1 FINAL state
		errors += atChecks->CheckUnreachableStates(chkbuf);
	errors += atChecks->CheckNodeCount(1, INT_MAX, Code::ATD_ACTION_STATE_NODE, chkbuf);

	errors += atChecks->CheckNamelessNodes(Code::ATD_ACTION_STATE_NODE, chkbuf);
	errors += atChecks->CheckNamelessNodes(Code::ATD_WAIT_STATE_NODE, chkbuf);


	errors += atChecks->CheckCountEdgesFrom(Code::ATD_SYNCHRONIZATION_NODE, 
		Code::ATD_TRANSITION_EDGE, 2, INT_MAX, False, False, chkbuf);

	ReportCheck(errors, &chkbuf);
}




void ATDiagram::ModelCheckProperty() {

	int status = system("which NuSMV > /dev/null 2>/dev/null");
	if (status) {
		string URL = "http://www.cs.utwente.nl/~tcm/tatd.html"; // RIK: AANPASSEN
		string txt = "Model checker NuSMV cannot be found.";
		txt += "\n\nPlease check your PATH or the URL below for more information:";
		txt += "\n\n" + URL;
		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::INFORMATION))->
			Show("Notice", &txt);
	}
	else {
        	SetStatus("action: model check property");
		tpd = new TPDialog(GetMainWindow()->GetWidget());
		tpd->Initialize();
		tpd->SetTitle("Model check property");
		tpd->SetOKCallback(&ModelCheckPropertyOKCB, this);
        	tpd->ManageSubstringToggle(True);
		tpd->ManageNameOnlyToggle(True);
		tpd->Popup();
	}
}


extern string replace(string s); // defined in adscks


void ATDiagram::ModelCheckPropertyOKCB(Widget w, XtPointer clientData, XtPointer) {
  ATDiagram *atd = (ATDiagram *)clientData;
  XtUnmanageChild(w);
  string fbuf;
  atd->GetTPDialog()->GetTextString(&fbuf);
  atd->DoModelCheckProperty(&fbuf, atd->GetTPDialog()->SensitiveOn(), atd->GetTPDialog()->SubstringOn(), atd->GetTPDialog()->NameOnlyOn() );
}

void ATDiagram::DoModelCheckProperty(const string *p, bool symbolic, bool reduction, bool sf) {
  // fill initial and final for the parser
  // initial and final are state predicates that characterise when a configuration is initial and when it is
  // final. The meaning of final depends upon the model being checked.


  GetMainWindow()->SetCursor(MouseCursor::WATCH);

  ADSHyperGraph *ah;
  ah=new ADSHyperGraph();    
  if (!ComputeHyperGraph(ah)) return;


  ::initial = (char *) malloc (strlen("I___INITIAL>0")+1); 
  strcpy(::initial,"I___INITIAL>0");

  string str=*p;
  str.replace('\r','_');


  // parse the property
  ::isfinal=0;
  ::identifier_count=0;
  ::isltl=1; // set to zero if ctl formula
  YY_BUFFER_STATE y = ::adsltlformula_scan_string(str.getstr());
  strcpy(::adsltlformula_constraint, "");
  bool b = !adsltlformulaparse();
  adsltlformula_delete_buffer(y);
  if (!b) {
    error("I cannot parse this property\n");
    return;
  }

  if (reduction){
    List <ADSVar *> varused; // ASSUMPTION: only boolean variables are used, so no integer expressions (what about nodes)
    List <Node *> nodeused;
    for (int i=0;i<identifier_count;i++){
      ADSVar *v=new ADSVar(identifier[i],::PROP);
      ADSVar *v_old= ah->FindSimilarVar(v);
      if (v_old){ // v occurs as variable in hypergraph ah
	varused.add(v_old);
      }
      
      string iname=identifier[i];
      Node *n= (ah->FindNode(iname));
      if (n){
	nodeused.add(n);
      }
    }
    if (::isfinal){
      List <Subject *> finalnodes;
      ah->GetFinalNodes(&finalnodes);
      for (finalnodes.first();!finalnodes.done();finalnodes.next()){
	nodeused.add((Node*)finalnodes.cur());
      }      
    }
    ah->RemoveLocalVariables(&varused);
    ah->RemoveNodes(nodeused,varused,reduction);
  }

  string sfinal=ah->ComputeFinalPredicate();
  string property=::ltlprop;
  property.replace("FINAL",sfinal);
    
 
  char buf[100]; // temporary filename for activity graph model
  strcpy(buf,"XXXXXX");
  (void)mkstemp(buf);
  string bufstr(buf);
  char req[100]; // temporarly filename for LTL property
  strcpy(req,"XXXXXX");
  (void)mkstemp(req);
  strcat(req,".req");
  FILE *ftemp;  // temporarly file for LTL property
  ftemp=fopen(req,"w");
  fprintf(ftemp,"%s",property.getstr()); // put the property in the temp file
  fclose(ftemp);
  string reqstr(req);


  ADSCks *ac= NULL; 

  OutputFile *ofile2= new OutputFile();
  ofile2->Open(&bufstr);
  if (symbolic) {
    ah->WriteNuSMV(ofile2,sf);
  }
  else{
    ac= new ADSCks(ah); 
    ComputeCKS(ah,ac,reduction);
    ac->WriteSMVFile(ofile2,sf);
  }

  if (::isltl){
    (*ofile2) << "\n\nLTLSPEC\n";
  }  
  else{
    (*ofile2) << "\n\nSPEC\n";
  }
  (*ofile2) << property << "\n\n";
  ofile2->Close(); 

  // Next start the model checking
  SetStatus("Model checking...");
  char output[6];
  strcpy(output,"XXXXXX");
  (void)mkstemp(output);
  
  string command = "NuSMV " + bufstr + " > " + output;
  system(command.getstr()); // do the actual model checking
  

  // parse the model checker's output
  ::adsmcoutputin=fopen(output,"r");
  ::mctraceindex=0;
  ::statecounter=0;
  ::sourceindex=0;
  ::targetindex=0;
  ::enabledindex=0;
  b=adsmcoutputparse(); 
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
    if (symbolic) ProvideFeedback(ah);
    else ProvideFeedback(ac);
  }

  GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
  unlink(output); // cleanup buf
  unlink(req); // cleanup 
  unlink(buf); // cleanup 
}


void ATDiagram::GeneralCheck() {
        SetStatus("action: general check");
	DoGeneralCheck();
	SetStatus("general check done");
}


void ATDiagram::DoGeneralCheck(){
  GetMainWindow()->SetCursor(MouseCursor::WATCH);

  ADSHyperGraph *ah;
  ah=new ADSHyperGraph();    
  if (!ComputeHyperGraph(ah)) return;

  // check that every run leads to a final state
  string constraint="F G ";
  string finalstr = ah->ComputeFinalPredicate();
  constraint += finalstr;

  char buf[100]; // temporary filename for activity graph model
  strcpy(buf,"XXXXXX");
  (void)mkstemp(buf);
  strcat(buf,".tlv");
  string bufstr(buf);

  char req[100]; // temporarly filename for LTL property
  strcpy(req,"XXXXXX");
  (void)mkstemp(req);
  strcat(req,".req");
  FILE *ftemp;  // temporarly file for LTL property
  ftemp=fopen(req,"w");
  fprintf(ftemp,"%s",constraint.getstr()); // put the property in the temp file
  fclose(ftemp);
  string reqstr(req);


  ADSCks *ac;
  ac= new ADSCks(ah);
  ComputeCKS(ah,ac,False);

 
  OutputFile *ofile2= new OutputFile();
  ofile2->Open(&bufstr);
  ac->WriteSMVFile(ofile2,True);
  (*ofile2) << "\n\nLTLSPEC\n";
  (*ofile2) << constraint << "\n\n";
  ofile2->Close();
  // Next start the model checking
  SetStatus("Model checking...");
  char output[6];
  strcpy(output,"XXXXXX");
  (void)mkstemp(output);
  

  string command = "NuSMV " + bufstr + " > " + output;
  system(command.getstr()); // do the actual model checking
  

  // parse the model checker's output
  ::adsmcoutputin=fopen(output,"r");
  ::mctraceindex=0;
  ::statecounter=0;
  ::sourceindex=0;
  ::targetindex=0;
  ::enabledindex=0;
  bool b=adsmcoutputparse();
  
  if (b) {
    error("I couldn't parse the model checker's output\n"); 
    return ;
  }

  unlink(output); // cleanup
  unlink(req); // cleanup
  unlink(buf); // cleanup
  
  string mctxt;
  if (mcfeedback){
    mctxt="Not every run leads to a final state node;see the counter example\n";
    ShowDialog(MessageDialog::MESSAGE, "Notice", &mctxt);	  
    ProvideFeedback(ac);
  }


  // Now check for dead nodes and transitions

  string nodead = ah->DeadEdgesNodesConstraints();

  ofile2->Open(&bufstr);
  ac->WriteSMVFile(ofile2,False);	
  (*ofile2) << "\nSPEC\n" << nodead << "\n\n"; 
  ofile2->Close();

  command = "NuSMV ";
  command +=  bufstr + " > " + output;
  system(command.getstr()); // do the actual model checking
  
  // parse the model checker's output
  ::adsmcoutputin=fopen(output,"r");
  ::mctraceindex=0;
  ::statecounter=0;
  ::sourceindex=0;
  ::targetindex=0;
  ::enabledindex=0;
  b=adsmcoutputparse(); 
  if (b) {
    error("I couldn't parse the model checker's output\n"); 
    return ;
  }

  List <Subject *> ahnodes;
  ah->GetNodes(&ahnodes);
  string deadnodes;
  for (ahnodes.first();!ahnodes.done();ahnodes.next()){
    if ((ahnodes.cur()->GetClassType()==Code::NOTE)|| (ahnodes.cur()->GetClassType()==Code::COMMENT)) continue;
    if (ah->GetBound(ahnodes.cur())==0){
      string nodename= *ahnodes.cur()->GetName();
      deadnodes+= "\n" + nodename ;
    }
  }
  
  if ((!mcfeedback) && (!deadnodes.length())) {
    mctxt="The general requirement is satisfied:\n\tEvery run leads to final state nodes\n\tThere are no dead nodes\n\tThere are no dead transitions\n";
    ShowDialog(MessageDialog::MESSAGE, "Notice", &mctxt);
  }
  else{
    if (!deadnodes.length()) // are there dead nodes?
      mctxt="There are some dead transitions: see feedback.\n";
    else
      mctxt="There are some dead nodes and perhaps transitions:\nNode(s)\n\t" +deadnodes +"\n\nis/are dead.\n" + "See also the feedback.\n";
    ShowDialog(MessageDialog::MESSAGE, "Notice", &mctxt);	  
    if (mcfeedback) ProvideFeedback(ac);
    
  }


  unlink(output); // cleanup
  unlink(req); // cleanup 
  unlink(buf); // cleanup 


  GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
  SetStatus("Model checking done");
  return ;
  
}


// the feedback is stored in ::mctrace
void ATDiagram::ProvideFeedback(ADSCks *ac){
  List <Subject *> ls;

  // color all nodes gray
  this->GetGraph()->GetNodes(&ls);
  for (ls.first();!ls.done();ls.next()){
    GShape *gs= GetDiagramViewer()->GetShape(ls.cur()); // find the corresponding shape to color it red
    if ((gs->GetClassType()==Code::SOLID_HORIZONTAL_BAR) || (gs->GetClassType()==Code::SOLID_VERTICAL_BAR)) {
	  ((NodeShape *)gs)->UpdateFillColor(new string("gray"));
    }
    ((NodeShape *)gs)->UpdateColor(new string("gray"));
    gs->GetName()->UpdateColor(new string("gray"));
  }

  // color all edges gray
  ls.empty();
  this->GetGraph()->GetEdges(&ls);
  for (ls.first();!ls.done();ls.next()){
    GShape *gs= GetDiagramViewer()->GetShape(ls.cur()); // find the corresponding shape to color it red
    ((NodeShape *)gs)->UpdateColor(new string("gray"));
    gs->GetName()->UpdateColor(new string("gray"));
  }

  // color initial node red
  ls.empty();
  this->GetGraph()->GetNodes(&ls,Code::ATD_INITIAL_STATE_NODE); // get all the initial nodes (ideally one, but I do not check this here)
  for (ls.first();!ls.done();ls.next()){
    GShape *gs= GetDiagramViewer()->GetShape(ls.cur()); // find the corresponding shape to color it red
    if (gs->GetClassType()==Code::BLACK_DOT){ // just to be sure...
      ((NodeShape *)gs)->UpdateColor(new string("red"));
    }
  }
  
  List <ADSTransition *> amtransition;
  ac->GetEdges((List <Subject *> *)&amtransition);
  for (amtransition.first();!amtransition.done();amtransition.next()){
    int sourcenum=((ADSValuation *)amtransition.cur()->GetSubject1())->GetNumber(); // get value of c___counter in source state of amtransition.cur()
    bool foundsource=False;
    int i;
    for (i=0;i<(::mctraceindex);i++){
      if (mctrace[i]==sourcenum){ // mctrace[i] is source of transition
	foundsource=True;
	break;
      }
    }
    if (!foundsource) continue; // amtransition.cur() is not part of the trace
    int targetnum=((ADSValuation *)amtransition.cur()->GetSubject2())->GetNumber();
    bool foundtarget=False;
    int j;
    for (j=i+1;j<(::mctraceindex);j++){
      if (mctrace[j]==targetnum){// mctrace[j] is target of transition
	foundtarget=True;
	break;
      }
	  }
    if (!foundtarget) continue;// amtransition.cur() is not part of the trace

    // amtransition.cur() is part of the error trace, so it should be highlighted
    
    Bag <ADSHyperEdge *> step;
    amtransition.cur()->GetStep(step); // the step taken in the current transition (possibly empty)
    List <ADSHyperEdge *> steplist;
    step.GetSet(&steplist);
    for (steplist.first();!steplist.done();steplist.next()){ 
      List <Subject *> simpleedges; 
      steplist.cur()->GetEdges(&simpleedges);
      for (simpleedges.first();!simpleedges.done();simpleedges.next()){
	GShape *gs= GetDiagramViewer()->GetShape(simpleedges.cur());	       
	gs->UpdateColor(new string("blue"));
	gs->GetName()->UpdateColor(new string("blue"));	      	      
	gs=GetDiagramViewer()->GetShape(((Edge *)simpleedges.cur())->GetSubject2()); // only the target needs to be high-lighted, the source has already been highlighted, since it is the target of another transition.
	if ((gs->GetClassType()==Code::SOLID_HORIZONTAL_BAR) || (gs->GetClassType()==Code::SOLID_VERTICAL_BAR)) {
	  ((NodeShape *)gs)->UpdateFillColor(new string("red"));
	}
	gs->UpdateColor(new string("red"));	     
	gs->GetName()->UpdateColor(new string("red"));
      }
    }
  }
}

//extern string replace(string s); // defined in adscks

// 
void ATDiagram::ProvideFeedback(ADSHyperGraph *ah){
  List <Subject *> ls;
  this->GetGraph()->GetNodes(&ls,Code::ATD_INITIAL_STATE_NODE); // get all the initial nodes (ideally one, but I do not check this here)
  for (ls.first();!ls.done();ls.next()){
    GShape *gs= GetDiagramViewer()->GetShape(ls.cur()); // find the corresponding shape to color it red
    if (gs->GetClassType()==Code::BLACK_DOT){ // just to be sure...
      ((NodeShape *)gs)->UpdateColor(new string("red"));
    }
  }
  
  List <Subject *> nodes;
  this->GetGraph()->GetNodes(&nodes);

  List <Subject *> hedges;
  ah->GetHyperEdges(&hedges);
  for (int j=0;j<(::statecounter-1);j++){ // j counts the current state of the error trace
    int i=0;
    while ((i<(::enabledindex))&&(enabledstatenumber[i]<j)) i++;
    if (enabledstatenumber[i]>j) continue;
    List <ADSHyperEdge *> step;
    for (int k=i;k<(::enabledindex) && enabledstatenumber[k]==j ;k++){
      for (hedges.first();!hedges.done();hedges.next()){
	if ((int)hedges.cur()->GetId()==enabledhyperedge[k]){	  
	  step.add((ADSHyperEdge *)hedges.cur()); // the enabled hyperedges in state j	 
	  break; // hyperedge found, so abort loop
	}
      }
    }  
    int steplen=step.count();
    bool taken[100]; // taken[i] iff step[i] is taken
    for (int sl1=0;sl1<steplen;sl1++){
      List <ADSHyperEdge *> conflict;
      step[sl1]->GetConflict(&conflict);
      if (!conflict.count()) taken[sl1]=True;
      // if an enabled hyperedge is taken, then in the next state j+1 its source is set to zero and its target is set to one
      taken[sl1]=True;
      for (conflict.first();!conflict.done();conflict.next()){
	if (step.contains(conflict.cur())){

	  int nextstateindex=0;
	  List <Subject *> target; // all the nodes set to one in state j+1
	  nextstateindex=0;
	  while ((nextstateindex<(::targetindex))&&(::targetstatenumber[nextstateindex  ]<=j)) nextstateindex++   ;
	  
	  for (;(nextstateindex<(::targetindex)) && (::targetstatenumber[nextstateindex]==j+1);nextstateindex++){
	    string s=::targetname[nextstateindex];
	    for (nodes.first();!nodes.done();nodes.next()){
	      string nodename= *(nodes.cur()->GetName()); 	       	      
	      if (replace(nodename)==s){ // targetname[i] is a node
		target.add(nodes.cur());
	      }
	    }    
	  }
	  
	  bool FoundHE=False;
	  taken[sl1]=True;
	  List <Subject *> *target1=step[sl1]->GetSubject2();
	  List <Subject *> *target2=conflict.cur()->GetSubject2();
	  for (target1->first();!target1->done();target1->next()){
	    if ((!target2->contains(target1->cur())) &&(target.contains(target1->cur()))){ // target1->cur() uniquely identifies step[sl1]; step[sl1] is taken
	      taken[sl1]=True;
	      FoundHE=True; 	      
	    }
	  }

	  for (target2->first();!target2->done();target2->next()){
	    if ((!target1->contains(target2->cur())) && (target.contains(target2->cur()))){ // conflict.cur() is taken
	      if (FoundHE){ 
		error("Two conflicting edges seem to be taken....\n");
	      } 
	      taken[sl1]=False; 	      
	    }
	  }
	}
      }				  
    } // end of steplent     
    bool showingstep=False;
    for (int sl1=0;sl1<steplen;sl1++){
      showingstep=showingstep || taken[sl1];
      if (taken[sl1]) {	
	List <Subject *> simpleedges; 
	step[sl1]->GetEdges(&simpleedges);
	for (simpleedges.first();!simpleedges.done();simpleedges.next()){
	  GShape *gs= GetDiagramViewer()->GetShape(simpleedges.cur());	       
	  gs->UpdateColor(new string("blue"));	      	      
	  gs=GetDiagramViewer()->GetShape(((Edge *)simpleedges.cur())->GetSubject2()); // only the target needs to be high-lighted, the source has already been highlighted, since it is the target of another transition.
	  if ((gs->GetClassType()==Code::SOLID_HORIZONTAL_BAR) || (gs->GetClassType()==Code::SOLID_VERTICAL_BAR)) {
	    ((NodeShape *)gs)->UpdateFillColor(new string("red"));
	  }
	  gs->UpdateColor(new string("red"));	     
	}
      }
    }
    if ((!showingstep) && (steplen)){
      error ("I could not show a step!\n");
    }
  }
}






bool ATDiagram::ComputeHyperGraph(ADSHyperGraph *ah){
  bool b;
  Elim el; // functional class that maps graph into hypergraph
  //  if (am) delete am; // commented since otherwise a segmentation fault occurs
  SetStatus("computing hypergraph");
  Graph *g=(ATGraph *)this->GetGraph();
  b=el.EliminatePseudoStateNodes(g,ah); // the actual elimination
  ah->Initialise(); // compute conflicts between activities
  SetStatus("hypergraph file computed");
  return b;
}

void ATDiagram::ComputeCKS(ADSHyperGraph *ah, ADSCks *ac, bool reduction){
  ADSSem adssem; // functional class that maps hypergraph to kripke structure
  // if (cl) delete cl;
  if (!ah) return;
  adssem.ComputeCKS(ah,ac,reduction); // the actual semantics
}
  

// the following procedure does not work yet
//void ATDiagram::ComputeImpCKS(ADSHyperGraph *ah, ADSCks *ac){
//  ADSSem adssem; // functional class that maps hypergraph to kripke structure
//  // if (cl) delete cl;
//  if (!ah) return;
//  //  adssem.ComputeImpCKS(ah,ac); // the actual semantics
//}
  


// make nodes and edges black
void ATDiagram::ClearTrace() {  
  List <Subject *> nodes; 
  this->GetGraph()->GetNodes(&nodes,Code::ATD_INITIAL_STATE_NODE);
  for (nodes.first();!nodes.done();nodes.next()){
      GShape *gs= GetDiagramViewer()->GetShape(nodes.cur()); 
      ((NodeShape *)gs)->UpdateColor(new string("black"));
  }
  List <Subject *> simpleedges; 
  this->GetGraph()->GetEdges(&simpleedges);
  for (simpleedges.first();!simpleedges.done();simpleedges.next()){
    GShape *gs= GetDiagramViewer()->GetShape(simpleedges.cur());	       
    gs->UpdateColor(new string("black"));
    gs->GetName()->UpdateColor(new string("black"));	      	      
    gs=GetDiagramViewer()->GetShape(((Edge *)simpleedges.cur())->GetSubject2()); // only the target needs to be high-lighted, the source has already been highlighted, since it is the target of another transition.
    if ((gs->GetClassType()==Code::SOLID_HORIZONTAL_BAR) || (gs->GetClassType()==Code::SOLID_VERTICAL_BAR)) {
      ((NodeShape *)gs)->UpdateFillColor(new string("black"));
    }
    gs->UpdateColor(new string("black"));	     
    gs->GetName()->UpdateColor(new string("black"));
  }
}





