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
#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include "llist.h"
#include "point.h"
#include "messagedialog.h"
#include "drawwindow.h"
class TextViewDialog;
class TextEditDialog;
class FileSelectionDialog;
class FindDialog;
class ReplaceDialog;
class InputFile;
class OutputFile;
class Viewer;

/// (abstract) document class; generalization of diagram, tree, table, etc.
class Document {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// 
	Document(Config *c, EditWindow *d, Viewer *v); 
	///
	virtual ~Document();

	/// opens new document called untitled.'suffix'.
	void New(); 		

	/// popup file selector dialog for loading a file.
	virtual void Load();		

	/// same as load but old document remains unchanged.
	virtual void Append();	

	/// save document to file.
	void Save();

	/// popup file selector dialog for saving to a file.
	void SaveAs(); 		

	/// popup file selector dialog for saving selection to a file.
	void SaveSelectionAs();

	/// closes document (asks confirmation) and quits application.
	void Quit(); 		

	/// popup info dialog containing information about this document.
	void ShowDocInfo();	

	/// popup text edit dialog with document source from file.
	void ShowSource();
	/// save edited source back to file.
	void SaveSource();

	/// popup info dialog containing summary of contents of this document.
	virtual void ShowSummary(); 

	/// popup warning dialog containing soft constraint violations (syntactic)
	virtual void CheckDocument(); 

	/// popup dialog to model check a temporal logic property (semantic check)
        virtual void ModelCheckProperty(); 

       /// clear error trace

        virtual void ClearTrace();

	/// popup text edit dialog in which doc. annotation can be given.
	void Annotate();
				
	/// called from file selector dialog callbacks.
	void LoadSave(const string *file); 

	/// load document from file.
	virtual void DoLoad(const string *file);

	///
	void DoSaveAs(const string *file);
	///
	void DoSaveSelectionAs(const string *file);

	/// return format that was found in file that is read in.
	double GetLoadFormat() const {return loadFormat;}

	/// perform some document type specific initialization.
	virtual void Initialize();

	/// Checks if file is legal and opens new document with file as name.
	void NewFile(const string *file);

	/// Delete contents of the document.
	virtual void RemoveAll() = 0; 

	/// Checks if newname is legal, and if so, changes name of document.
	bool NewName(const string *newname);

	/// 
	void SetName(const string *newname) {name = *newname;}

	/// 
	const string *GetName() const {return &name;}

	/// 
	const string *GetDocType() const {return &docType;}

	/// 
	const string *GetSuffix() const {return &suffix;}

	///
	const string *GetToolName() const {return &toolName;}

	///
	const string *GetAuthor() const {return &author;}

	///
	const string *GetCreationTime() const {return &createdOn;}

	/// return whether doc.name is the default name.
	bool IsDefault();

	/// Checks if newdir is legal, and if so, changes current directory.
	void NewDir(const string *newdir);

	/// 
	void SetDir(const string *newdir) {dir = *newdir;}

	/// 
	const string *GetDir() const {return &dir;}

	/// Set dir from file selector.
	void SetFSDir();

	/// increases number of changes.
	void IncChanges(); 	

	/// decrease number of changes.
	void DecChanges();	

	/// 
	int GetChanges() const {return changes;}

	/// set inline edit (doc. type specific).
	virtual void SetInlineEdit(bool) {}

	///
	enum MoveType {UP, DOWN, LEFT, RIGHT, CENTER};

	/// move document in mainwindow.
	virtual void Move(MoveType) {}

	/// 
	bool IsModified() const {return changes > 0;} 
	/// 
	void SetModified(bool set) { if (set) changes=1; else changes=0;}
	///
	bool IsLoaded() const {return loaded;}

	/// ask user to confirm that a file may be overwritten
	bool MayWrite(const string *path); 

	/// set main window status message to msg.
	void SetStatus(const char *msg) {mainwindow->SetStatus(msg);}
	///
	void SetStatus(const string *msg) {mainwindow->SetStatus(msg);}

	/// set document annotation text to s.
	void SetAnnotation(const string *s);

	/// is the document hierarchic?
	bool IsHierarchic() const {return isHierarchic;}
	/// sets the hierarchic (editor mode) for the document
	virtual void SetHierarchic(bool set);
	/// is it allowed to switch to hierarchic mode? 
	virtual bool AllowHierarchic() const { return False; }

	/// find all strings.
	virtual void FindAll(const string *, bool, bool, bool)=0;

	/// find next string.
	virtual void FindNext(const string *, bool, bool, bool) =0;

	/// replace all strings.
	virtual void ReplaceAll(const string *, const string *, 
		bool, bool, bool)=0;

	/// replace next string.
	virtual void ReplaceNext(const string *, const string *, 
		bool, bool, bool)=0;

	/// issue a popup dialog for getting a search string.
	virtual void Find();

	/// issue a popup dialog for search and replace strings.
	virtual void Replace();

	/// update main window document text fields
	void UpdateWindow();

	/// 
	EditWindow *GetMainWindow() const {return mainwindow;}
	///
	Config *GetConfig() const {return config;}
	///
	Viewer *GetViewer() const {return viewer;}
	///
	InputFile *GetInputFile() const {return ifile;}
	///
	OutputFile *GetOutputFile() const {return ofile;}

	///
	TextEditDialog *GetSourceEditDialog() const {
		return sourceEditDialog;}
	///
	TextEditDialog *GetDocAnnotationDialog() const {
		return docAnnotationDialog;}
	///
	TextEditDialog *GetEltAnnotationDialog() const {
		return eltAnnotationDialog;}
	///
	FileSelectionDialog *GetFileSelectionDialog() const {
		return fileSelectionDialog;}
	///
	FindDialog *GetFindDialog() const {return findDialog;}

	///
	ReplaceDialog *GetReplaceDialog() const {return replaceDialog;}
protected:
	/// ...
	virtual void LoadEntries() = 0;
	/// ...
	virtual void SaveEntries()=0; 
	///
	bool IsAppending() const {return appending;}
	///
	bool IsSaveSelection() const {return saveSelection;}

	/// Set directory in all dialogs.
	virtual void UpdateDirectory(const string *s);

	///
	void ShowDialog(MessageDialog::DialogType t,
		const char *title, const char *text) const;
	///
	void ShowDialog(MessageDialog::DialogType t,
				const char *title, const string *text) const {
		ShowDialog(t, title, text->getstr());
	}

	/// Give results of Check Document in popup dialog.
	void ReportCheck(int errors, const string *msg);

	/// message string filled by Check Document.
	string chkbuf;		

private:
// attributes of current tool.
	/// 
	EditWindow *mainwindow;
	///
	Viewer *viewer;
	///
	Widget mwwidget;

	///
	TextEditDialog *sourceEditDialog;
	///
	TextEditDialog *docAnnotationDialog;
	///
	TextEditDialog *eltAnnotationDialog;
	///
	FileSelectionDialog *fileSelectionDialog;
	///
	TextViewDialog *checkDialog;
	///
	TextViewDialog *infoDialog;
	///
	FindDialog *findDialog;
	///
	ReplaceDialog *replaceDialog;

	///
	Config *config;

	///
	InputFile *ifile;
	///
	OutputFile *ofile;

	/// is document currently modified ?
	int changes;

	/// is document loaded or created.
	bool loaded;

	/// is document loaded (overwritten) or appended.
	bool appending;

	/// is selection saved or entire document;
	bool saveSelection;

	/// current tool.
	Toolkit::ToolType tool;

	/// current document suffix
	string suffix;

	/// login of person who runs tool.
	string login;

	/// name of the current tool.
	string toolName;

	/// current working directory.
	string dir;

	/// current version of file format (format that will be written).
	double fileFormat;

	///
	bool isHierarchic;
 
// attributes of document contents.
	/// current document name.
	string name; 	

	/// current document type.
	string docType;

	/// initial author of the document.
	string author; 	

	/// creation time and date.
	string createdOn;

// attributes of loaded document.
	/// file name from which document is loaded.
	string fileName; 

	/// file format of loaded document.
	double loadFormat; 	

	/// tool that wrote loaded document.
	string generatedFrom;

	/// writing time and date of loaded document.
	string writtenOn; 	

	/// login that wrote document to file.
	string writtenBy; 	

	/// document annotation text.
	string annotation;

	/// file in which document is saved.
	string saveName; 

	/// Create all popup dialog for document class.
	void CreateDialogs();

	/// function needed for loading document from file.
	bool AskSave();		

	/// ...
	bool Load(const string *file);

	/// ...
	bool LoadDocInfo();

	/// ...
	bool CheckDocInfo();

	///
	virtual bool LoadHeader();

	/// ...
	virtual bool LoadEditInfo() {return True;}

	/// ...
	virtual bool CheckEditInfo() {return True;}

	/// ...
	bool CheckFormat();

	/// ...
	bool CheckDocumentType();

protected:
	/// function needed for saving to file.
	bool Save(const string *file);

private:
	/// ...
	virtual void SaveDocInfo();

	/// ...
	virtual void SaveEditInfo();

	///
	void PrepareSaveDialog();
};
#endif
