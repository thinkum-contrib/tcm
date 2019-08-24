////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by
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
#include "code.h"
#include "util.h"

TypeName Code::typeNames[] = {
	// general node shape types
	{BOX, "Box"},
	{SQUARE, "Square"},
	{DOUBLE_BOX, "DoubleBox"},
	{TRIPLE_BOX, "TripleBox"},
	{UR_LABELED_BOX, "URLabeledBox"},
	{ARROW_BOX, "ArrowBox"},
	{TEXT_BOX, "TextBox"},
	{ARROW_TEXT_BOX, "ArrowTextBox"},
	{ELLIPSE, "Ellipse"},
	{CIRCLE, "Circle"},
	{BLACK_DOT, "BlackDot"},
	{WHITE_DOT, "WhiteDot"},
	{ELLIPSIS, "Ellipsis"},
	{BULLS_EYE, "BullsEye"},
	{MINI_ARROW_ELLIPSE, "MiniArrowEllipse"},
	{LEFT_LINE_CIRCLE, "LeftLineCircle"},
	{ROUNDED_BOX, "RoundedBox"},
	{ELLIPSED_BOX, "EllipsedBox"},
	{DIAMOND, "Diamond"},
	{HORIZONTAL_BAR, "HorizontalBar"},
	{VERTICAL_BAR, "VerticalBar"},
	{TRIANGLE, "Triangle"},
	{HEXAGON, "Hexagon"},
	{MINI_BOX, "MiniBox"},
	{MINI_ELLIPSE, "MiniEllipse"},
	{MINI_DIAMOND, "MiniDiamond"},
	{MINI_TRIANGLE, "MiniTriangle"},
	{NOTE_BOX, "NoteBox"},
	{SOLID_HORIZONTAL_BAR, "SolidHorizontalBar"},
	{SOLID_VERTICAL_BAR, "SolidVerticalBar"},
	{STICKMAN, "StickMan"},
	{BUILDING_BLOCK, "BuildingBlock"},
	{CUBE, "Cube"},
	{FOLDER, "Folder"},
	{SUB_FOLDER, "SubFolder"},
	{DISK, "Disk"},

	// line types
	{LINE, "Line"},
	{FLASH_ARROW, "FlashArrow"},
	{T1_LINE, "T1Line"},
	{T2_LINE, "T2Line"},
	{T4_LINE, "T4Line"},
	{T4_TLIST_LINE, "T4TListLine"},
	{TRANSITION_ARROW, "TransitionArrow"},
	{C2R2_LINE, "C2R2Line"},
	{C2R2_MLIST_LINE, "C2R2MListLine"},
 
	// used in older file formats.
	{ARROW, "Arrow"},
	{T1_ARROW, "T1Arrow"},
	{DOUBLE_ARROW, "DoubleArrow"},
	{DOUBLE_HEADED_ARROW, "DoubleHeadedArrow"},

	// node types
	{COMMENT, "Comment"},
	{GENERIC_NODE, "GenericNode"},
	{NOTE, "Note"},
	{EMPTY_NODE, "EmptyNode"},
	{ENTITY_TYPE, "EntityType"},
	{VALUE_TYPE, "ValueType"},
	{TAXONOMY_JUNCTION, "TaxonomyJunction"},
	{RELATIONSHIP_NODE, "RelationshipNode"},
	{SUBJECT_AREA, "SubjectArea"},
	{CLASS_NODE, "ClassNode"},
	{MODE_JUNCTION, "ModeJunction"},
	{DATA_PROCESS, "DataProcess"},
	{DATA_STORE, "DataStore"},
	{EVENT_STORE, "EventStore"},
	{EXTERNAL_ENTITY, "ExternalEntity"},
	{SPLIT_MERGE_NODE, "SplitMergeNode"},
	{CONTROL_PROCESS, "ControlProcess"},
	{PS_PROCESS, "PSProcess"},
	{DATA_STREAM, "DataStream"},
	{STATE_VECTOR, "StateVector"},
	{CONTROLLED_DATA_STREAM, "ControlledDataStream"},
	{SN_PROCESS, "SNProcess"},
	{STATE, "State"},
	{INITIAL_STATE, "InitialState"},
	{DECISION_POINT, "DecisionPoint"},
	{PROCESS_GRAPH_NODE, "ProcessGraphNode"},
	{PROCESS_GRAPH_ROOT, "ProcessGraphRoot"},
	{TEXT_ROOT, "TextRoot"},
	{TEXT_NODE, "TextNode"},
	{FINAL_STATE, "FinalState"},

	// edge types
	{GENERIC_EDGE, "GenericEdge"},
	{COMMENT_LINK, "CommentLink"},
	{EMPTY_EDGE, "EmptyEdge"},
	{TEXT_EDGE, "TextEdge"},
	{BINARY_RELATIONSHIP, "BinaryRelationship"},
	{FUNCTION, "Function"},
	{ISA_RELATIONSHIP, "IsaRelationship"},
	{COMPONENT_FUNCTION, "ComponentFunction"},
	{DATA_FLOW, "DataFlow"},
	{BIDIRECTIONAL_DATA_FLOW, "BidirectionalDataFlow"},
	{CONTINUOUS_DATA_FLOW, "ContinuousDataFlow"},
	{EVENT_FLOW, "EventFlow"},
	{CONTINUOUS_EVENT_FLOW, "ContinuousEventFlow"},
	{CONNECTION_START, "ConnectionStart"},
	{CONNECTION_END, "ConnectionEnd"},
	{TRANSITION, "Transition"},
	{EVENT, "Event"},

	// le view
	{VIEW, "View"},

	// UML node types
	{SSD_CLASS_NODE, "SSDClassNode"},
	{SSD_OBJECT_NODE, "SSDObjectNode"},
	{SSD_ASSOCIATION_NODE, "SSDAssociationNode"},
	{SSD_GENERALIZATION_NODE, "SSDGeneralizationNode"},
	{SSD_AGGREGATION_NODE, "SSDAggregationNode"},
	{UCD_ACTOR_NODE, "UCDActorNode"},
	{UCD_USE_CASE_NODE, "UCDUseCaseNode"},
	{UCD_SYSTEM_NODE, "UCDSystemNode"},
	{ATD_SYNCHRONIZATION_NODE, "ATDSynchronizationNode"},
	{ATD_ACTION_STATE_NODE, "ATDActionStateNode"},
	{ATD_WAIT_STATE_NODE, "ATDWaitStateNode"},
	{ATD_DECISION_STATE_NODE, "ATDDecisionStateNode"},
	{ATD_INITIAL_STATE_NODE, "ATDInitialStateNode"},
	{ATD_FINAL_STATE_NODE, "ATDFinalStateNode"},
	{CPD_COMPONENT_NODE, "CPDComponentNode"},
	{CPD_INTERFACE_NODE, "CPDInterfaceNode"},
	{DPD_RESOURCE_NODE, "DPDResourceNode"},
	{CBD_ACTOR_NODE, "CBDActorNode"},
	{CBD_CLASS_NODE, "CBDClassNode"},
	{CBD_OBJECT_NODE, "CBDObjectNode"},
	{SCD_AND_STATE, "SCDAndState"},
	{SCD_DECISION_STATE, "SCDDecisionState"},
	{SCD_DEFAULT_STATE, "SDCDefaultState"},
	{SCD_FINAL_STATE, "SCDFinalState"},
	{SCD_OR_STATE, "SCDOrState"},
	{SCD_SYNCHRONIZATION_STATE, "SCDSynchronizationState"},

	// UML edge types
	{SSD_BINARY_ASSOCIATION_EDGE, "SSDBinaryAssociationEdge"},
	{SSD_GENERALIZATION_EDGE, "SSDGeneralizationEdge"},
	{SSD_OBJECT_LINK_EDGE, "SSDObjectLinkEdge"},
	{SSD_PARTICIPANT_LINK_EDGE, "SSDParticipantLinkEdge"},
	{SSD_ASSOCIATION_LINK_EDGE, "SSDAssociationLinkEdge"},
	{SSD_AGGREGATION_EDGE, "SSDAggregationEdge"},
	{SSD_COMPOSITION_EDGE, "SSDCompositionEdge"},
	{UCD_BINARY_ASSOCIATION_EDGE, "UCDBinaryAssociationEdge"},
	{UCD_GENERALIZATION_EDGE, "UCDGeneralizationEdge"},
	{ATD_TRANSITION_EDGE, "ATDTransitionEdge"},
	{CPD_REALIZATION_EDGE, "CPDRealizationEdge"},
	{CPD_DEPENDENCY_EDGE, "CPDDependencyEdge"},
	{DPD_COMMUNICATION_EDGE, "DPDCommunicationEdge"},
	{CBD_CLASS_LINK_EDGE, "CBDClassLinkEdge"},
	{CBD_OBJECT_LINK_EDGE, "CBDObjectLinkEdge"},
	{SCD_TRANSITION_EDGE, "SCDTransitionEdge"},
	{SCD_AND_EDGE, "SCDAndEdge"},

	// UML specific shape types
	{SSD_SINGLE_OBJECT_BOX, "SSDSingleObjectBox"},
	{SSD_DOUBLE_OBJECT_BOX, "SSDDoubleObjectBox"},
	{SSD_SINGLE_CLASS_BOX, "SSDSingleClassBox"},
	{SSD_DOUBLE_CLASS_BOX, "SSDDoubleClassBox"},
	{SSD_TRIPLE_CLASS_BOX, "SSDTripleClassBox"},
	{SSD_RCLINE, "SSDRCLine"},
	{SSD_R2LINE, "SSDR2Line"},
	{UCD_SINGLE_CLASS_BOX, "UCDSingleClassBox"},
	{UCD_BOUNDARY_BOX, "UCDBoundaryBox"},
	{CBD_SINGLE_CLASS_BOX, "CBDSingleClassBox"},
	{CBD_SINGLE_OBJECT_BOX, "CBDSingleObjectBox"},
	{SCD_AND_STATE_BOX, "SCDAndStateBox"},
	{SCD_AND_LINE, "SCDAndLine"},
	{OBJECT_STICKMAN, "ObjectStickMan"},
	{ACTOR_CLASS_BOX, "ActorClassBox"},
	{ACTOR_OBJECT_BOX, "ActorObjectBox"},
	{GD_BOUNDARY_SHAPE, "GDBoundaryShape"},
	{GD_CONTROLLER_SHAPE, "GDControllerShape"},
	{GD_ENTITY_SHAPE, "GDEntityShape"},

	// CSOD Types
	{CSO_CLASS_BOX, "CSO_ClassBox"},
	{CSO_OBJECT_BOX, "CSO_ObjectBox"},
	{CSO_CLASS, "CSO_Class"},
	{CSO_OBJECT, "CSO_Object"},
	{CSO_RELATIONSHIP, "CSO_Relationship"},
	{CSO_PARTICIPANT, "CSO_Participant"},
	{CSO_JUNCTION, "CSO_Junction"},
	{CSO_INSTANTIATION, "CSO_Instantiation"},
	{CSO_POSSESSION, "CSO_Possession"},
	{CSO_SUBCLASSES, "CSO_Subclasses"},
	{CSO_AGGREGATION, "CSO_Aggregation"},
	{CSO_GENERALIZATION, "CSO_Generalization"},
	{CSO_CONSTRAINT_EDGE, "CSO_ConstraintEdge"},

	// CED Types
	{CE_MUST_EVENT_NODE, "CE_MustEventNode"},
	{CE_NEC_EVENT_NODE, "CE_NecEventNode"},
	{CE_PERMIT_EVENT_NODE, "CE_PermitEventNode"},
	{CE_START_NODE, "CE_StartNode"},
	{CE_FINAL_NODE, "CE_FinalNode"},
	{CE_EVENT_EDGE, "CE_EventEdge"},
	{CE_NONEVENT_EDGE, "CE_NonEventEdge"},


	// Conversions for older file formats
	// in the past we had "Dashed" shape types (how inconvenient)
	{BOX, "DashedBox"},
	{CIRCLE, "DashedCircle"},
	{CIRCLE, "DashedTCircle"},
	{DIAMOND, "DashedDiamond"},
	{ELLIPSE, "DashedEllipse"},
	{MINI_ELLIPSE, "DashedDot"},
	{HEXAGON, "DashedHexagon"},
	{HORIZONTAL_BAR, "DashedHorizontalBar"},
	{ROUNDED_BOX, "DashedRoundedBox"},
	{TRIANGLE, "DashedTriangle"},
	{LINE, "DashedLine"},
	{ARROW, "DashedArrow"},
	{T1_ARROW, "DashedC1Line"},
	{T1_ARROW, "DashedC1Arrow"},
	{DOUBLE_ARROW, "DashedDoubleArrow"},
	{DOUBLE_HEADED_ARROW, "DashedDoubleHeadedArrow"},

	// old node shape type names
	{BULLS_EYE, "BlackDotEllipse"},
	{CIRCLE, "TCircle"},
	{CIRCLE, "TopLabeledCircle"},
	{MINI_ELLIPSE, "Dot"},
	{MINI_TRIANGLE, "BlackMiniTriangle"},
	{HORIZONTAL_BAR, "Bar"},
	{LEFT_LINE_CIRCLE, "LLCircle"},
	{UR_LABELED_BOX, "URBox"},

	// old line type names
	{ARROW, "PredefinedArrow"},
	{LINE, "PredefinedLine"},
	{T1_ARROW, "C1Arrow"},
	{T1_ARROW, "C1Line"},
	{T1_ARROW, "EndC1Arrow"},
	{T1_LINE, "StartC1Line"},
	{T4_LINE, "C2Line"},
	{TRANSITION_ARROW, "HLineArrow"},

	// old node type names
	{CLASS_NODE, "ObjectClass"},
	{DATA_PROCESS, "DataTransformation"},
	{PS_PROCESS, "Process"},
	{RELATIONSHIP_NODE, "Relationship"},

	// old edge type names
	{BIDIRECTIONAL_DATA_FLOW, "BiDataFlow"},
	{BINARY_RELATIONSHIP, "BinaryAssociation"},
	{BINARY_RELATIONSHIP, "ManyManyRelationship"},
	{COMMENT_LINK, "NoteBoxPath"},
	{COMMENT_LINK, "NoteBoxLink"},

	// old UML type names
	{SSD_OBJECT_NODE, "ObjectNode"},
	{SSD_AGGREGATION_NODE, "AggregationJunction"},
	{UCD_SYSTEM_NODE, "UCSystem"},
	{UCD_ACTOR_NODE, "Actor"},
	{UCD_USE_CASE_NODE, "UseCase"},
	{ATD_ACTION_STATE_NODE, "ActionState"},
	{ATD_WAIT_STATE_NODE, "InactiveState"},
	{ATD_DECISION_STATE_NODE, "DecisionState"},
	{ATD_SYNCHRONIZATION_NODE, "Synchronization"},
	{SSD_ASSOCIATION_LINK_EDGE, "AssociationPath"},
	{SSD_OBJECT_LINK_EDGE, "ObjectLink"},
	{SSD_ASSOCIATION_LINK_EDGE, "AssociationLink"},
	{SSD_PARTICIPANT_LINK_EDGE, "ParticipantLink"},
	{SSD_AGGREGATION_EDGE, "Aggregation"},
	{SSD_COMPOSITION_EDGE, "Composition"},
	{SSD_SINGLE_OBJECT_BOX, "ObjectBox"},
	{SSD_DOUBLE_OBJECT_BOX, "ObjectDoubleBox"},
	{UCD_SINGLE_CLASS_BOX, "UCSingleClassBox"},
	{UCD_BOUNDARY_BOX, "UCBoundaryBox"},
	{0, ""} 
};


const char *Code::GetName(int code) {
	TypeName *n = &typeNames[0];
	while (n->code != 0) {
		if (n->code == code)
			return n->name;
		n++;
	}
	return 0;
}

int Code::GetCode(const char *name) {
	TypeName *n = &typeNames[0];
	while (n->code != 0) {
		if (equal(name, n->name))
			return n->code;
		n++;
	}
	return 0;
}

int Code::GetIndex(int code, const int codelist[]) {
	int i = 0;
	while (codelist[i] != 0) {
		if (codelist[i] == code)
			return i+1;
		else
			i++;
	}
	return 0;
}
