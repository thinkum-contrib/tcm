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
#ifndef _DIAGRAMVIEWER_H
#define _DIAGRAMVIEWER_H

#include "viewer.h"
#include "document.h"
#include "diagramwindow.h"
#include "shapeview.h"
#include "grid.h"
#include "lineend.h"
#include "nodealign.h"
class Buffer;
class LineEndDialog;
class NodeAlignmentDialog;
class NodeShapeDialog;

/// diagram viewer class, responsible for the contents of the drawing area.
class DiagramViewer: public Viewer {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// 
	DiagramViewer(Config *c, DiagramWindow *w); 
	///
	virtual ~DiagramViewer();
	///
	void Initialize();

	///
	void SetDiagram(Diagram *d) {diagram = d;}
	///
	Diagram *GetDiagram() const {return diagram;}
	///
	void SetGrafport(Grafport *g);
	///
	Buffer *GetBuffer() const {return buffer;}
	///
	Grid *GetGrid() const {return grid;}

	///
	int GetDefaultNodeType() const {return defaultNodeType;}
	///
	int GetDefaultEdgeType() const {return defaultEdgeType;}
	///
	int GetDefaultNodeShapeType() const {return defaultNodeShapeType;}
	///
	int GetDefaultLineType() const {return defaultLineType;}
	///
	bool IsDefaultCurve() const {return defaultCurve;}

	///
	void SetDefaultNodeType(int n) { defaultNodeType=n;}
	///
	void SetDefaultEdgeType(int n) { defaultEdgeType=n;}
	///
	void SetDefaultNodeShapeType(int n) {defaultNodeShapeType=n;}
	///
	void SetDefaultLineType(int n) {defaultLineType=n;}
	/// 
	void SetDefaultCurve(bool s) {defaultCurve=s;}

	///
	void SetShowIndexes(bool b) {showIndexes=b;}
	///
	bool IsShowIndexes() {return showIndexes;}

	///
	LineStyle::Type GetDefaultNodeLineStyle() const {
		return defaultNodeLineStyle;}
	///
	LineStyle::Type GetDefaultEdgeLineStyle() const {
		return defaultEdgeLineStyle;}
	///
	void SetDefaultNodeLineStyle(LineStyle::Type l) {
		defaultNodeLineStyle=l;}
	///
	void SetDefaultEdgeLineStyle(LineStyle::Type l) {
		defaultEdgeLineStyle=l;}

	///
        LineEnd::Type GetDefaultLineEnd1() { 
		return defaultLineEnd1;}
        ///
        LineEnd::Type GetDefaultLineEnd2() { 
		return defaultLineEnd2;}
        ///
        void SetDefaultLineEnd1(LineEnd::Type t) {
                defaultLineEnd1 = t; }
        ///
        void SetDefaultLineEnd2(LineEnd::Type t) {
                defaultLineEnd2 = t; }
                
	/// forwarding to grid object.
	virtual int Snap(int i) const {return grid->Snap(i);}
	///
	virtual void Snap(Point *p) {grid->Snap(p);}

	///
	void SetStatus(const char *msg) {GetMainWindow()->SetStatus(msg);}
	///
	void SetStatus(const string *msg) {GetMainWindow()->SetStatus(msg);}
	///
	void SetCursor(int cursor) {GetMainWindow()->SetCursor(cursor);}
	///
	void SetSizeCursor(int cursor) {GetMainWindow()->SetSizeCursor(cursor);}

	/// Draw all shapes of current view to grafport.
	virtual void Draw(); 	

	/// Erase all shapes of current view from grafport.
	virtual void Undraw(); 	

	/// Redraw everything including grid.
	void Redraw(); 

	/// return current view.
	ShapeView *GetCurView() const {return curView;}
	///
	void DeleteAllViews();
	///
	unsigned int NumberOfViews() const {return views->count();}
	///
	bool AddView(ShapeView *v);
	///
	void SetView(ShapeView *v);
	///
	void UpdateView(ShapeView *v);
	///
	bool HasView(const string *index);
	///
	bool HasView(ShapeView *v);
	///
	ShapeView *GetView(const string *index);

	/// Check all shapes in all views.
	void CheckShapes();

	/// write all shapes from all views to ofile.
	void WriteShapes(OutputFile *f); 

	/// write all selected shapes from current view to ofile.
	void WriteSelection(OutputFile *f); 

	/// perform the button1 functions (includes creating and moving shapes).
	void Select(int x, int y);

	/// Perform the 2nd button function: (de)selection.
	void Adjust(int x, int y);

	/// drag shapes and handles of line-segments.
	Command *Drag(int x, int y); 

	/// create an edge between nodes.
	Command *Connect(int x, int y); 

	/// change cursor to show the possible command (resize, move or edit).
	void MovingPointer(int x, int y);

	/// start textmode, or (if in textmode) handle key. (x,y) is position.
	void KeyTyped(int x, int y, int key);

	/// stop being in editing mode.
	void TextModeOff(); 

	/// deselect all shapes in all views in the viewer.
	void DeselectAll();

	/// return first shape from shapes having given subject (in any view).
	GShape *GetShape(Subject *subject);

	/// put in shapes all shapes from all views having given subject.
	void GetShapes(Subject *subject, List<GShape *> *shapes);

	/// Cut subjects/shapes cmd from current view to buffer.
	virtual void Cut();

	/// Copy subjects/shapes cmd from current view to buffer.
	virtual void Copy();

	/// Paste from buffer to current view and graph.
	virtual void Paste();

	/// Node shapes in selection are duplicated, pasted in current view.
	virtual void Duplicate(); 

	/// Align selection in current view according to given align type.
	virtual void AlignNodeShapes();

	/// Align selection in current view according to given align type.
	virtual void AlignNodes(NodeAlign::Type alignment); 

	/// Convert selected curves from/to selected segmented lines.
	virtual void UpdateCurve();

	/// Set/Unset the text underlining of the names of the selected shapes.
	virtual void UpdateTextUnderline();

	/// select all shapes having string s (sens case sensitive).
	virtual void FindAll(const string *s, bool sens, bool substr, 
		bool nameOnly);

	/// select next shape having string s, and set cursor before it.
	virtual void FindNext(const string *s, bool sens, bool substr, 
		bool nameOnly);

	/// replace string in next shape in current view.
	virtual void ReplaceNext(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly);

	/// replace all strings in current view.
	virtual void ReplaceAll(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly);

	/// edit annotation of first selected subject in current view.
	virtual void Annotate();

	/// Delete shapes (and event. subjects) from selection.
	virtual void DeleteShapes();

	/// All shapes (and subjects) are deleted from current view.
	virtual void DeleteAll();

	/// makes the size of selection shapes equal to size of the first.
	virtual void SameSize(); 

	/// move all shapes in current view according to move type.
	virtual void MoveAllShapes(Document::MoveType t);

	/// select all shapes in the current view.
	virtual void SelectAll();

	/// update text alignment of selection in current view.
	void UpdateTextAlignmentSelection(TextAlign::Type a);

	/// update text of textshape.
	void UpdateText(TextShape *t, const string *newtext, 
		const string *oldtext);

	/// update line width of selected shapes.
	void UpdateLineWidthSelection(unsigned i);

	/// update line style of selected shapes.
	void UpdateLineStyleSelection(LineStyle::Type s);

	/// update the fonts of selected shapes.
	void UpdateFontSelection(int family, int style, int size);

	/// update the colors of the lines of the selected shapes.
	void UpdateLineColorSelection(const string *color);

	/// update the colors of the texts of the selected shapes.
	void UpdateTextColorSelection(const string *color);

	/// update the fill colors of the selected shapes.
	void UpdateFillColorSelection(const string *color,
		FillStyle::Type f);

	/// calculate size of shapes in current view.
	void CalcSizeElements(Point &topLeft, Point &bottomRight);

	/// calc size of selection in current view.
	void CalcSizeSelection(Point &topLeft, Point &bottomRight);

	/// calculate covered area of shapes in grafport.
	void CalcSizeShapes(List<GShape *> *shapes, Point &topLeft, 
		Point &bottomRight);

	/// for each line connecting shape, position is propagated.
	void ShapePositionUpdate(GShape *shape);

	/// Update the duplication marks of shapes of given subjects.
	void UpdateDuplicationMarks(List<Subject *> *s);

	/// Update the duplication marks of shapes of given subject.
	void UpdateDuplicationMarks(Subject *s);

	/// shapes are moved delta and result is propagated to drawing area.
	void UpdateMoveShapes(List<GShape *> *shapes, const Point *delta);

	/// all shapes are moved delta (result not propagated).
	void MoveShapes(List<GShape *> *shapes, const Point *delta);

	/// convert selected node shapes to given code 
	virtual void UpdateNodeShapeType(int) {}

	/// convert selected node shapes.
	void ConvertNodeShapes();

	///
	virtual void DeleteSubjects();

	///
	void SetIndexes(bool b);
	///
	void Reindex(List<Node *> *nodes);

	///
	virtual void ZoomIn();
	///
	void ZoomOut();
	///
	void TopLevel();

	///
	LineEndDialog *GetLineEndDialog() {return lineEndDialog;}
	///
	void UpdateLineEnd();
	///
	void ShowDefaultLineEnd();
	///
	void UpdateLineEndSelection(LineEnd::Type e1, LineEnd::Type e2);

	///
	NodeAlignmentDialog *GetNodeAlignmentDialog() {return alignDialog;}
	///
	void ShowDefaultNodeAlignment();

	///
	NodeShapeDialog *GetNodeShapeDialog() {return nodeShapeDialog;}
	///
	void ShowDefaultNodeShape();

	/// Does any of the views have duplicates?
	bool HasDuplicates() const;

	/// recalculates all parents of all views.
	void RecalcAllParents(bool hierarchicDocument) const;

protected:
	///
	List<ShapeView *> *GetViews() const {return views;}

	/// error message because of empty selection.
	void EmptySelectionMessage();

	/// error message because there are no shapes.
	void EmptyShapesMessage();
private:
	/// The different views.
	List<ShapeView *> *views;

	/// The current view that is displayed.
	ShapeView *curView;

	/// buffer object for cut,copy and paste.
	Buffer *buffer; 	

	/// object for aligning shapes to a grid.
	Grid *grid; 		

	///
	Diagram *diagram;

	/// 
	int defaultNodeType;
	/// 
	int defaultNodeShapeType;
	/// 
	int defaultEdgeType;
	/// 
	int defaultLineType;
	/// 
	bool defaultCurve;

	///
	bool showIndexes;

	/// 
	LineStyle::Type defaultNodeLineStyle;
	/// 
	LineStyle::Type defaultEdgeLineStyle;
	///
	LineEnd::Type defaultLineEnd1;
	///
	LineEnd::Type defaultLineEnd2;

	///
	LineEndDialog *lineEndDialog;
	///
	NodeAlignmentDialog *alignDialog;
	///
	NodeShapeDialog *nodeShapeDialog;
 
	/// create a node in current view.
	void CreateNode(int x, int y); 

	/// if textshape at (x,y), edit it. 
	bool GoIntoTextMode(GShape *shape, int x, int y); 

	/// start editing textshape.
	bool TextMode(TextShape *); 
	
	/// if editing and text shape is hit: set edit cursor.
	void SetCursor(int x, int y);
};
#endif
