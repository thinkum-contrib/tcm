//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente.
// Author: David Jansen (dnjansen@cs.utwente.nl).
//         Rik Eshuis (eshuis@cs.utwente.nl)
//         Jose Canete (canete@lsi.us.es)
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
#ifndef _SCDIAGRAM_H
#define _SCDIAGRAM_H

#include "diagram.h"
class SCGraph;
class SCWindow;
class SCViewer;
//class Transition;
//class InitialState;
#ifdef MODELCHECK
class ModelCheckDialog;
class SCDTransitionEdge;
class AbstractSequenceDiagram;
class ConcreteSequenceDiagram;
#endif
#include <stdio.h>

/// state transition diagram class
class SCDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TSCD} */
public:
	///
	SCDiagram(Config *, SCWindow *, SCViewer *, SCGraph *);
	///
	virtual ~SCDiagram();
	///
	virtual void Initialize();
	///
	Node *CreateNode();
	///
	Edge *CreateEdge(Subject *n1, Subject *n2);
	///
	NodeShape *CreateNodeShape(Node *node, int x, int y);
	///
	Line *CreateLine(Edge *edge, GShape *fromShape, 
		GShape *toShape, List<Point *> *line);
	///
	void UpdateNodeType(int n);
	///
	void UpdateEdgeType(int n);

	///
	void CheckDocument();
#ifdef MODELCHECK
	///
	/* virtual */ void ModelCheckProperty();
#endif

	///
	void ProvideFeedback(SCGraph *ah);

protected:
	///
	Thing *CreateThing(int classNr);
	///
	bool CheckEdgeConstraints(Subject *s1, Subject *s2);
	///
	bool CheckAndEdgeConstraints(Subject *s1, Subject *s2);

private:
#ifdef MODELCHECK
	///
	void DoModelCheckDocument(const string *internal,
		const string *formula, const string *clock);
	/// callback for model check document dialog
	static void ModelCheckDocumentOKCB(Widget, XtPointer,
							XtPointer);
	/// saves the current diagram in the model checker formal to *path.
	void SaveForModelChecker(const string *path, const string *internal,
		const string *clock, const string *formula);
	/// calls the model checker for a diagram saved in *path.
	bool ExecuteModelChecker(const string *path, const string *formula);

	/// computes the current step of firing transitions.
	List<SCDTransitionEdge *> ComputeMicroStep (SCGraph *gr, int state);

	/// Creates the abstract representation for a sequence diagram from
	/// NuSMV counterexample. This method should be called after the counterexample
	/// has been produced!
	AbstractSequenceDiagram * GenerateAbstractSequenceDiagram ();
        ///
        bool IsBroadcast (string event, List<SCDTransitionEdge *> step);
	/// Creates a possible layout from the abstract representation of the sequence diagram.
	ConcreteSequenceDiagram * GenerateConcreteSeqDiag (AbstractSequenceDiagram *asd);
	/// Generates the file with the sequence diagram.
	void GenerateSeqDiagFile (ConcreteSequenceDiagram *csd, const string *formula);
	///
	void GenerateGraphNodes (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateComments (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateGraphEdges (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateObjectBoxes (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateT4Lines (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateTextBoxes (ConcreteSequenceDiagram *csd, OutputFile *fp);
	///
	void GenerateNote (ConcreteSequenceDiagram *csd, OutputFile *fp, const string *formula);
	///
	void GenerateNoteBox (ConcreteSequenceDiagram *csd, OutputFile *fp);
	/// used for model checking
	ModelCheckDialog *promptDialog;
#endif
}; // end class SCDiagram


/*
 *
 * Classes for generating a Sequence Diagram. They should be moved to on a separate file.
 *
 *
 *
 */


class PairObjEv
{
 public:
  PairObjEv (int object, string event) : obj(object), ev(event) {}
  int GetObj () {return obj;}
  string GetEv () {return ev;}
  void PrintIt () {
  	std::cout << "(" << obj << "," << ev.getstr() << ")" << std::endl; }

 private:
  int obj;
  string ev;
};

class InteractionParticipant
{
 public:
  int GetNumberOfEvents () {return eventsToSend.count();}
  void AddPairObjEv (int object, string event);
  PairObjEv * GetPairObjEv (int i) {if (i<0 || i>static_cast<int>(eventsToSend.count()-1)) return NULL; else return eventsToSend[i];}
  void SetId (int i) {id= i;}
  int GetId () {return id;}
  void PrintIt ();
 private:
   List<PairObjEv *> eventsToSend;
   int id; //the id of the participant in the abstract sequence diagram

};

class InteractionRow
{
 public:

  InteractionParticipant * participants; //array [numObj] of InteractionParticipant

  InteractionRow (int n, int cs) : numObj(n), currentState(cs) {
      participants= new InteractionParticipant[numObj];
      for (int i=0; i< numObj; i++)
       	   participants[i].SetId(i);
  }
  int GetNumberOfParticipants () {return numObj;}
  int GetCurrentState () {return currentState;}
  void PrintIt ();
 private:
  int numObj;
  int currentState;
};



class AbstractSequenceDiagram
{
 public:
  List<InteractionRow *> rows;
  List<string> objNames;
  int numObjs;

  AbstractSequenceDiagram () : numObjs(0) {}

  void AddParticipant (string name) {objNames.add(name); numObjs++; }
  InteractionRow * AddRow (int cs); 

  void PrintIt ();
};



class ConcreteParticipant;

class StimulusInfo
{
 public:
  ConcreteParticipant *sender;
  ConcreteParticipant *receiver;
  string label;
  int logicalId; // logical id in the seq.diag.
  int shapeId; // shape id in the seq.diag.
  int y;  //the place of the stimulus in the temporal line
  bool isComment; //if True, this is a false stimulus, i.e. a comment: "stable" and "microstep"
};


class Stimulus
{
 public:
  bool isSender;
  StimulusInfo *info;
};


class ConcreteParticipant
{
 public:
  string name;
  int logicalId;
  int shapeId;
  int x, y;
  List<Stimulus *> anchors;
};



class ConcreteSequenceDiagram
{
  int counter;

 public:
  List<ConcreteParticipant *> participants;
  List<StimulusInfo *> stimuli;
  int lineLength; //end position of the lifelines

  ConcreteSequenceDiagram() : counter(1) {}

  int NextId () { counter++; return counter;}


};




#endif
