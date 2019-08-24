	///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
#include "toolkit.h"

const char Toolkit::TOOLKIT_NAME[] = "TCM";

// Window titles for the different tools.
const char *Toolkit::TOOL_TITLES[] = {
	"Tool for Generic Diagrams",
	"Tool for Entity Relationship Diagrams (classic)",
	"Tool for Class Relationship Diagrams",
	"Tool for State Transition Diagrams (Mealy)",
	"Tool for Process Structure Diagrams (JSD)",
	"Tool for Recursive Process Graphs",
	"Tool for Data Flow Diagrams",
	"Tool for Data and Event Flow Diagrams",
	"Tool for System Network Diagrams (JSD)",
	"Tool for Generic Tables",
	"Tool for Transaction Decomposition Tables",
	"Tool for Transaction Use Tables",
	"Tool for Function Entity type Tables",
	"Tool for Generic Textual Trees",
	"Tool for Function Refinement Trees",
	"Tool for Text",
	"Tool for Color-X Static Object Diagrams",
	"Tool for Color-X Event Diagrams",
	"Tool for Static Structure Diagrams",
	"Tool for Collaboration Diagrams",
	"Tool for Sequence Diagrams",
	"Tool for Component Diagrams",
	"Tool for Deployment Diagrams",
	"Tool for Use Case Diagrams",
	"Tool for StateChart Diagrams",
	"Tool for Activity Diagrams",
	"Tool for Entity Relationship Diagrams",
	0};

const char Toolkit::STARTUP_TOOL_NAME[] = "TCM";

const char *Toolkit::TOOL_NAMES[] = {
	"TGD",
	"TERD",
	"TCRD",
	"TSTD",
	"TPSD",
	"TRPG",
	"TDFD",
	"TEFD",
	"TSND",
	"TGT",
	"TTDT",
	"TTUT",
	"TFET",
	"TGTT",
	"TFRT",
	"TT",
	"CSOD",
	"CED",
	"TSSD",
	"TCBD",
	"TSQD",
	"TCPD",
	"TDPD",
	"TUCD",
	"TSCD",
	"TATD",
	"TESD",
	0};
 
const char *Toolkit::EXECUTABLE_NAMES[] = {
	"tgd",
	"terd",
	"tcrd",
	"tstd",
	"tpsd",
	"trpg",
	"tdfd",
	"tefd",
	"tsnd",
	"tgt",
	"ttdt",
	"ttut",
	"tfet",
	"tgtt",
	"tfrt",
	"tt",
	"csod",
	"ced",
	"tssd",
	"tcbd",
	"tsqd",
	"tcpd",
	"tdpd",
	"tucd",
	"tscd",
	"tatd",
	"tesd",
	0};
 

const char *Toolkit::DOCUMENT_SUFFIXES[] = { 
	".gd", 
	".erd", 
	".crd", 
	".std", 
	".psd", 
	".rpg", 
	".dfd", 
	".efd", 
	".snd", 
	".gt", 
	".tdt", 
	".tut", 
	".fet", 
	".gtt", 
	".frt", 
	".sillysuffixx", 
	".csod", 
	".ced", 
	".ssd",
	".cbd",
	".sqd",
	".cpd",
	".dpd",
	".ucd",
	".scd",
	".atd",
	".esd",
	0};

const char *Toolkit::DOCUMENT_TYPES[] = {
	"Generic Diagram",
	"Entity Relationship Diagram (classic)",
	"Class Relationship Diagram (obsolete)",
	"State Transition Diagram (Mealy)",
	"Process Structure Diagram (JSD)",
	"Recursive Process Graph",
	"Data Flow Diagram (subset of TEFD)",
	"Data and Event Flow Diagram",
	"System Network Diagram (JSD)",
	"Generic Table",
	"Transaction Decomposition Table",
	"Transaction Use Table",
	"Function Entity type Table",
	"Generic Textual Tree",
	"Function Refinement Tree",
	"Text",
	"COLOR-X Static Object Diagram",
	"COLOR-X Event Diagram",
	"Static Structure Diagram",
	"Collaboration Diagram",
	"Sequence Diagram",
	"Component Diagram",
	"Deployment Diagram",
	"Use Case Diagram",
	"Statechart Diagram",
	"Activity Diagram",
	"Entity Relationship Diagram",
	0};
 
const char Toolkit::DOCUMENT_DEFAULT[] = "untitled";

const char *Toolkit::DOCUMENT_TYPES_INFO[] = {
	"This tool is for arbitrary graphs and does not perform \
semantic checks.",
	"This tool is for classic entity relationship diagrams (ERDs). \
New users are advised to use TESD.",
	"This tool is for class-relationship diagrams (CRDs). \
New users are advised to use TSSD.",
	"This tool is for state transition diagrams, \
using the Mealy convention.",
	"This tool is for process structure diagrams (PSDs), \
that are used in the Jackson System Development method (JSD).",
	"This tool is for recursive process graphs (RPGs), \
also called life cycle diagrams.",
	"This tool is for data flow diagrams (DFDs). \
This tool is a subset of TEFD.",
	"This tool is for data and event flow diagrams.",
	"This tool is for system network diagrams (SNDs) \
that are used in the Jackson System Development method (JSD).",
	"This tool is for generic tables and does not perform \
semantic checks.",
	"This tool is for transaction decomposition tables. \
See 'introduction to TTDT' in the help menu of TTDT.",
	"This tool is for transaction use tables. \
See 'introduction to TTUT' in the help menu of TTUT.",
	"This tool is for function entity type tables. \
See 'introduction to TFET' in the help menu of TFET.",
	"This tool is for generic trees in which all nodes are \
text labels and which does not perform semantic checks.",
	"This tool is for function refinement trees.",
	"Text",
	"COLOR-X Static Object Diagram",
	"COLOR-X Event Diagram",
	"This tool is for UML static structure diagrams (SSDs)",
	"Tool for UML Collaboration Diagrams.", // TCBD
	"Tool for UML Sequence Diagrams",		// TSQD
	"Tool for UML Component Diagrams.", // TCPD
	"Tool for UML Deployment Diagrams.",		// TDPD
	"This tool is for UML use-case diagrams.",	// TUCD
	"This tool is for UML (and Stat	emate) state charts.",		// TSCD
	"This tool is for UML activity diagrams.",	// TATD
	"This tool is for entity relationship diagrams (ERDs)", // TESD
	0};


bool Toolkit::TableEditor(int tool) {
	return (tool == GT || tool == FET || tool == TDT || tool == TUT);
}

bool Toolkit::DiagramEditor(int tool) {
	return (!TableEditor(tool) && !TextEditor(tool));
}

bool Toolkit::TreeEditor(int tool) {
	return (tool == GTT || tool == FDT);
}

bool Toolkit::GenericEditor(int tool) {
	return (tool == GD || tool == GT || tool == GTT);
}

bool Toolkit::HierarchicEditor(int tool) {
	return tool==ERD||tool==CRD ||tool==GD ||
		tool==DFD||tool==EFD||tool==STD|| SCD == tool ||
		tool==SSD||
		tool==ESD /* || TreeEditor(tool) */;
}

bool Toolkit::TextEditor(int tool) {
	return (tool == T);
}

bool Toolkit::EditorWithoutCurves(int tool) {
	return !(DiagramEditor(tool) && tool != PSD && !TreeEditor(tool));
}

bool Toolkit::EditorWithoutDuplicates(int tool) {
	return ! DiagramEditor(tool) || tool == PSD || SCD == tool
		|| TreeEditor(tool);
}

bool Toolkit::EditorWithInterEdgeConnections(int tool) {
	return (DiagramEditor(tool) && (tool == GD || tool == SSD || tool == ESD));
}

bool Toolkit::EditorWithModelChecker(int tool) {
        return STD == tool || SCD == tool || ATD == tool ;
}
