////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "document.h"
#include "texteditdialog.h"
#include "fileselectiondialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "questiondialog.h"
#include "inputfile.h"
#include "outputfile.h"
#include "menu.h"
#include "system.h"
#include "version.h"
#include "config.h"
#include "viewer.h"
#include "editstubs.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

Document::Document(Config *c, EditWindow *e, Viewer *v) {
	mainwindow = e;
	config = c;
	viewer = v;
	mwwidget = mainwindow->GetWidget();
	ifile = new InputFile();
	ofile = new OutputFile();
	(void)System::GetCwd(&dir);
	changes = 0;
	loaded = False;
	appending = False;
	saveSelection = False;
	annotation = "";
	chkbuf = "";
	tool = (Toolkit::ToolType)e->GetTool();
	suffix = Toolkit::DOCUMENT_SUFFIXES[tool];
	(void)System::GetLoginName(&login);
	toolName = Toolkit::TOOL_NAMES[tool]; 
	toolName += "-version-";
	toolName += Version::TOOLKIT_VERSION;
	fileFormat = Version::FILE_FORMAT;
	name = Toolkit::DOCUMENT_DEFAULT + suffix;
	docType = Toolkit::DOCUMENT_TYPES[tool];
	author = login;
	(void)System::GetTime(&createdOn);
	fileName = "";
	loadFormat = 0;
	generatedFrom = ""; 
	writtenOn = ""; 
	writtenBy = ""; 
	saveName = "";
	SetHierarchic(False);
	CreateDialogs();
}

void Document::CreateDialogs() {
	sourceEditDialog = new TextEditDialog(mwwidget);
	sourceEditDialog->Initialize();
	sourceEditDialog->SetTitle("Document Source Editor");
	sourceEditDialog->SetCancelCallback(0, 0);
	sourceEditDialog->SetOKButtonLabel("Save");
	sourceEditDialog->SetOKCallback(EditStubs::DocumentSourceOKCB, this);
	sourceEditDialog->SetTextSize(12, 60);
	docAnnotationDialog = new TextEditDialog(mwwidget);
	docAnnotationDialog->Initialize();
	docAnnotationDialog->SetTitle("Document Annotation Editor");
	docAnnotationDialog->SetCancelCallback(0, 0);
	docAnnotationDialog->SetOKCallback(EditStubs::AnnotationOKCB, this);
	docAnnotationDialog->SetTextSize(12, 60);
	eltAnnotationDialog = new TextEditDialog(GetMainWindow()->GetWidget());
	eltAnnotationDialog->Initialize();
	eltAnnotationDialog->SetTitle("Annotation Editor");
	eltAnnotationDialog->SetCancelCallback(0, 0);
	eltAnnotationDialog->SetTextSize(12, 60);
	fileSelectionDialog = new FileSelectionDialog(mwwidget);
	fileSelectionDialog->Initialize();
	fileSelectionDialog->SetTitle("Document File Selector");
	fileSelectionDialog->SetCancelCallback(EditStubs::CancelFSCB, this);
	infoDialog = new TextViewDialog(mwwidget);
	infoDialog->Initialize();
	infoDialog->SetTextSize(23, 60);
	infoDialog->SetTitle("Document Info");
	checkDialog = new TextViewDialog(mwwidget);
	checkDialog->Initialize();
	checkDialog->SetTextSize(12, 72);
	checkDialog->SetTitle("Check Document");
	findDialog = new FindDialog(mwwidget);
	findDialog->Initialize();
	findDialog->SetOKCallback(EditStubs::FindNextCB, this);
	findDialog->SetApplyCallback(EditStubs::FindAllCB, this);
	findDialog->ManageSubstringToggle(True);
	findDialog->SetTitle("Find text");
	replaceDialog = new ReplaceDialog(mwwidget);
	replaceDialog->Initialize();
	replaceDialog->SetTitle("Replace text");
	replaceDialog->SetOKCallback(EditStubs::ReplaceFindCB, this);
	replaceDialog->SetReplaceCallback(EditStubs::ReplaceNextCB, this);
	replaceDialog->SetApplyCallback(EditStubs::ReplaceAllCB, this);
	replaceDialog->ManageSubstringToggle(True);
}

Document::~Document() {
	delete viewer;
	delete ifile;
	delete ofile;
	delete sourceEditDialog;
	delete docAnnotationDialog;
	delete eltAnnotationDialog;
	delete fileSelectionDialog;
}

void Document::UpdateWindow() {
	UpdateDirectory(&dir);
	mainwindow->SetModified(changes != 0);
	mainwindow->SetDocumentName(&name);
	mainwindow->SetDocumentType(&docType);
}

void Document::UpdateDirectory(const string *s) {
	mainwindow->SetDirName(s);
	sourceEditDialog->SetDirectory(s);
	docAnnotationDialog->SetDirectory(s);
	eltAnnotationDialog->SetDirectory(s);
	fileSelectionDialog->SetDirectory(s);
}

void Document::New() {
	SetStatus("action: new");
	if (changes != 0) {
		if (AskSave() == False)
			return;
	}
	string path = dir + Toolkit::DOCUMENT_DEFAULT + suffix;
	// delete document contents.
	RemoveAll(); 	
	NewFile(&path);
	Initialize();
	viewer->Refresh();
}


/* virtual */ void Document::Initialize() {
	SetHierarchic(False);
}


void Document::NewFile(const string *f) {
	string path = *f;
	if (!path.endsWith(suffix)) {
		string txt = "File name should have suffix '" + suffix + "'";
		if (mainwindow->IsDoMap()) {
			(new MessageDialog(mwwidget, MessageDialog::WARNING))->
				Show("Warning", &txt);
			SetStatus("");
		}
		else 
			std::cerr << txt << std::endl;

		// delete original suffix.
		path.setSuffix(suffix);
	}
	System::GiveFile(&path, &dir, &name); // get name from path.
	author = login;
	(void)System::GetTime(&createdOn);
	loaded = False;
	fileName = "";
	loadFormat = 0;
	generatedFrom = ""; 
	writtenOn = ""; 
	writtenBy = ""; 
	mainwindow->SetModified(False);
	mainwindow->SetDocumentName(&name);
	mainwindow->EnableDocumentSource(False);
	string txt = name + " [New Document]";
	SetStatus(&txt);
	annotation = "";
	changes = 0;
}

void Document::Load() {
	SetStatus("action: load");
	appending = False;
	string ext = "*" + suffix;
	fileSelectionDialog->SetTitle("Load document");
	fileSelectionDialog->ManageOptionMenu(False);
	fileSelectionDialog->SetExtension(&ext);
	fileSelectionDialog->SetOKCallback(EditStubs::LoadOKCB, this);
	fileSelectionDialog->SetDefaultFile("");
	fileSelectionDialog->Popup();
}

void Document::Append() {
	SetStatus("action: append");
	appending = True;
	string ext = "*" + suffix;
	fileSelectionDialog->SetTitle("Append document");
	fileSelectionDialog->SetExtension(&ext);
	fileSelectionDialog->SetOKCallback(EditStubs::LoadOKCB, this);
	fileSelectionDialog->SetDefaultFile("");
	fileSelectionDialog->Popup();
}

void Document::SetFSDir() {
	fileSelectionDialog->GetDirectory(&dir);
	UpdateDirectory(&dir);
}

void Document::LoadSave(const string *file) {
	if (changes != 0) {
		string tmp;    // make sure that the loaded
		System::GiveFile(file, &tmp); // file is not overwritten.
		if (tmp != name)
			if (AskSave() == False)
				return;
	}
	DoLoad(file);
}

void Document::DoLoad(const string *path) {
	mainwindow->SetCursor(MouseCursor::WATCH);
	if ((*path)[0] != '/')
		// make absolute path name.
		fileName = dir + *path;
	else
		fileName = *path;
	string suf;
	if (!fileName.getSuffix(suf))
		fileName.setSuffix(suffix);
	string txt = "loading from " + fileName;
	SetStatus(&txt);
	// is it an non-existent file ?
	if (!System::FileExists(fileName.getstr())) {
		NewFile(&fileName);
		mainwindow->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	if (Load(&fileName)) {
		changes = 0;
		mainwindow->SetDocumentName(&name);
		mainwindow->SetModified(False);
		if (appending)
			txt = name + " appended";
		else {
			loaded = True;
			txt = name + " loaded";
			mainwindow->EnableDocumentSource(True);
		}
		SetStatus(&txt);
	}
	else {
		loaded = False;
		if (appending)
			SetStatus("append document failed");
		else
			SetStatus("load document failed");
	}
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

bool Document::Load(const string *file) {
	// open file for reading.
	ifile->Open(file);
	if (!ifile->Good()) {
		string txt = "Can not open\n'" + *file + "'";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		ifile->Close();
		return False;
	}
	// Check if it is not a directory etc.
	if (!System::FileRegular(file->getstr())) {
		string txt = "'" + *file + "'\nis not a regular file";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		ifile->Close();
		return False;
	}
	if (!LoadHeader()) {
		ifile->Close();
		return False;
	}
	LoadEntries();
	ifile->Close();
	return True;
}

bool Document::LoadHeader() {
	// Check and load document info.
	if (appending) {
		if (!(CheckDocInfo() && 
		      viewer->Check(ifile, loadFormat) && 
		      CheckEditInfo()))
			return False;
	}
	else {  // we are loading
		if (!(LoadDocInfo() && viewer->Load(ifile, loadFormat) 
		    && LoadEditInfo()))
			return False;
	}
	return True;
}

bool Document::CheckDocInfo() {
	// Checks but does not actually read in the storage and document info;
	string val;
	// Check storage info and load file format (into loadFormat).
	if (!CheckFormat())
		;    // try to continue.
		// return False;
	if (loadFormat < 1.08) {
		if ( !ifile->ReadAttribute("Generator", &val) || 
			!ifile->ReadStringAttribute("Written", &val) || 
			!ifile->LookupChar('}'))
		return False;
	}
	else {
		if ( !ifile->ReadAttribute("GeneratedFrom", &val) || 
			!ifile->ReadAttribute("WrittenBy", &val) || 
			!ifile->ReadStringAttribute("WrittenOn", &val) || 
			!ifile->LookupChar('}'))
		return False;
	}
	// Check document info
	// dname = "Document" or "Diagram" (older versions).
	if (!ifile->ReadWord(&val) || 
	    ((val != "Diagram") && (val != "Document")) ||
	    !ifile->ReadWord(&val) || 
	    !ifile->LookupChar('{') ||
	    !CheckDocumentType())
		return False;
	if (!ifile->ReadAttribute("Name", &val))
		return False;
	if (!ifile->ReadAttribute("Author", &val))
		return False;
	if (loadFormat < 1.08) {
		if (!ifile->ReadStringAttribute("Created", &val))
			return False;
	}
	else {
		if (!ifile->ReadStringAttribute("CreatedOn", &val))
			return False;
	}
	if (loadFormat >= 1.09) {
		if (!ifile->ReadStringAttribute("Annotation", &val))
			return False;
	}
	if ( loadFormat >= 1.32 && Toolkit::HierarchicEditor(
						GetMainWindow()->GetTool()) ) {
		if ( ! ifile->ReadAttribute("Hierarchy", &val) )
			return False;
	}
	if (!ifile->LookupChar('}'))
		return False;
	return True;
}

bool Document::LoadDocInfo() {
	string val;
	// Load and Check storage info.
	if (!CheckFormat())
		return False;
	if (loadFormat < 1.08) {
		if (!ifile->ReadAttribute("Generator", &generatedFrom))
			return False;
		writtenBy = "?";
		if (!ifile->ReadStringAttribute("Written", &writtenOn))
			return False;
	}
	else {
		if (!ifile->ReadAttribute("GeneratedFrom", &generatedFrom))
			return False;
		if (!ifile->ReadAttribute("WrittenBy", &writtenBy))
			return False;
		if (!ifile->ReadStringAttribute("WrittenOn", &writtenOn))
			return False;
	}
	if (!ifile->LookupChar('}'))
		return False;
	// Load and Check document info.
	// dname = "Document" or "Diagram" (older versions).
	string dname;
	if (!ifile->ReadWord(&dname) || 
		((dname != "Diagram") && (dname != "Document")))
		return False;
	if (loadFormat < 1.20) // in past documents had an extra id.
		if (!ifile->ReadWord(&val))
			return False;
	if (!ifile->LookupChar('{') || !CheckDocumentType())
		return False;
	if (!ifile->ReadAttribute("Name", &name))
		return False;
	if (!ifile->ReadAttribute("Author", &author))
		return False;
	// file is copied or moved?
	string f;
	System::GiveFile(&fileName, &f);
	if (name != f && mainwindow->IsDoMap()) {
		string txt = "The file " + f + " contains the document named\n"
			+ name + " (apparently the file is moved or copied).\n"
			"Do you wish to set the file name as new document " 
			"name?";
		QuestionDialog q(mwwidget, False);
		q.Initialize();
		q.SetMessageString(&txt);
		q.SetTitle("file name as document name?");
		int answer = q.GetAnswer();
		if (answer == QuestionDialog::YES)
			NewName(&f);
	}
	if (loadFormat < 1.08) {
		if (!ifile->ReadStringAttribute("Created", &createdOn))
			return False;
	}
	else {
		if (!ifile->ReadStringAttribute("CreatedOn", &createdOn))
			return False;
	}
	if (loadFormat >= 1.09) {
		if (!ifile->ReadStringAttribute("Annotation", &annotation))
			return False;
	}
	if ( loadFormat >= 1.33 && Toolkit::HierarchicEditor(
						GetMainWindow()->GetTool()) ) {
		if ( ! ifile->ReadAttribute("Hierarchy", &val))
			return False;
		SetHierarchic(val %= "True");
	} else
		SetHierarchic(False);
	if (!ifile->LookupChar('}'))
		return False;
	if (!name.endsWith(suffix)) {
		// string txt = "File name should have suffix '" + suffix + "'";
		// ShowDialog(MessageDialog::WARNING, "Warning", &txt);
		name.setSuffix(suffix);
	}
	return True;
}

bool Document::CheckFormat() {
	string val = "Storage";
	// look for storage clause.
	if (!(ifile->LookupWord(&val) && ifile->LookupChar('{'))) {
		string txt = "This file does not contain a loadable document";
		ShowDialog(MessageDialog::ERROR, "File error", &txt);
		return False;
	}
	// Load file format number.
	if (!(ifile->ReadAttribute("Format", &val)))
		return False;
	loadFormat = val.todouble();
	// Check file format number.
	if (loadFormat < 1.0) {
		string txt = "I found an obsolete file format";
		ShowDialog(MessageDialog::ERROR, "File format error", &txt);
		loadFormat = fileFormat;
		return False;
	}
	else if (loadFormat > fileFormat) {
		string txt = "This file format is newer than the current";
		txt += "\nthis could give problems reading this document";
		ShowDialog(MessageDialog::WARNING, "File format warning", &txt);
		loadFormat = fileFormat;
		return True;
	}
	return True;
}

bool Document::CheckDocumentType() {
	string val;
	// Check document type.
	if (!(ifile->ReadStringAttribute("Type", &val)))
		return False;
	if (val != Toolkit::DOCUMENT_TYPES[tool])
		; 
		// error("Warning: trying to read a \"%s\" with %s\n", 
		// 	val.getstr(), Toolkit::TOOL_NAMES[tool]);
	return True;
}

void Document::Save() {
	SetStatus("action: save");
	if (IsDefault())
		SaveAs();
	else {
		saveName = dir + name;
		DoSaveAs(&saveName);
	}
}

void Document::PrepareSaveDialog() {
	saveName = dir;
	if (!IsDefault())
		saveName += name;
	string ext = "*" + suffix;
	fileSelectionDialog->ManageOptionMenu(False);
	fileSelectionDialog->SetExtension(&ext);
}

void Document::SaveAs() {
	SetStatus("action: save as");
	saveSelection = False;
	PrepareSaveDialog();
	fileSelectionDialog->SetTitle("Save document to file");
	fileSelectionDialog->SetOKCallback(EditStubs::SaveAsOKCB, this);
	fileSelectionDialog->SetDefaultFile(&saveName);
	fileSelectionDialog->Popup();
}

void Document::SaveSelectionAs() {
	SetStatus("action: save selection as");
	saveSelection = True;
	PrepareSaveDialog();
	fileSelectionDialog->SetTitle("Save selection to file");
	fileSelectionDialog->SetOKCallback(EditStubs::SaveAsOKCB, this);
	fileSelectionDialog->Popup();
}

void Document::DoSaveAs(const string *p) {
	string path = *p;
	mainwindow->SetCursor(MouseCursor::WATCH);
	if (System::FileExists(path.getstr()) &&
	    !System::FileRegular(path.getstr())) {
		string txt = "'" + path + "'\n is not a regular file";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		SetStatus("document is not saved");
		mainwindow->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	// make extension always .suffix
	if (!path.endsWith(suffix)) {
		path.setSuffix(suffix);
	}

	string file, directory;
	System::GiveFile(&path, &directory, &file);
	// not empty files.
	if (file == suffix)
		path = directory + '/' + Toolkit::DOCUMENT_DEFAULT + suffix;

	string txt = "saving to " + path;
	SetStatus(&txt);
	// Check if file already exists and the user _wants_ to overwrite it.
	if (!MayWrite(&path)) {
		SetStatus("document is not saved");
		mainwindow->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	// the chosen file name will be the document name.
	string oldName = name;
	if (file != name) {
		// check and give document new name.
		if (!NewName(&file)) {
			SetStatus("illegal name so document is not saved");
			mainwindow->SetCursor(MouseCursor::LEFT_PTR);
			return;
		}
	}
	saveName = path;
	if (Save(&saveName)) {
		txt = name + " saved";
		SetStatus(&txt);
	}
	else
		SetStatus("save document failed");

	if (saveSelection) {
		// restore old document name.
		name = oldName;	
		mainwindow->SetDocumentName(&name);
	}
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

bool Document::Save(const string *file) {
	// create or overwrite file
	ofile->Open(file);
	if (!ofile->Good()) {
		string txt = "'" + *file + 
			     "'\n can not be created or overwritten";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		ofile->Close();
		return False;
	}
	SaveDocInfo(); 	// write document info.
	viewer->Save(ofile); // write view options.
	SaveEditInfo(); // write editor defaults.
	SaveEntries();
	ofile->Close();// close file
	// reset changes counter of document when it is entirely saved.
	if (!saveSelection) {
		changes = 0;
		mainwindow->SetModified(False);
	}
	return True;
}

void Document::SaveDocInfo() {
	string val;
	// begin storage info
	(*ofile) << "Storage " << '\n';
	(*ofile) << "{\n";
	// write current format.
	// I do not trust operator<<(double).
	string x = fileFormat;
	(*ofile) << "\t{ " << "Format " << x << " }\n";
	// write name of tool.
	(*ofile) << "\t{ " << "GeneratedFrom " << toolName << " }\n";
	// write login name.
	(void)System::GetTime(&val);
	(*ofile) << "\t{ " << "WrittenBy " << login << " }\n";
	// write current time.
	(void)System::GetTime(&val);
	(*ofile) << "\t{ " << "WrittenOn " << '"' << val << '"' << " }\n";
	// end storage info
	(*ofile) << "}\n\n";
	// begin document info
	(*ofile) << "Document \n{\n"
	// write document type.
	            "\t{ Type \"" << docType << "\" }\n"
	// write document name.
	            "\t{ Name " << name << " }\n"
	// write document author.
	            "\t{ Author " << author << " }\n"
	// write document creation date.
	            "\t{ CreatedOn \"" << createdOn << "\" }\n"
	// write document annotation.
	            "\t{ Annotation \"" 
			<< annotation << "\" }\n";
	if ( Toolkit::HierarchicEditor(GetMainWindow()->GetTool()) ) {
		// write hierarchic document flag
		(*ofile) << "\t{ Hierarchy " <<
				(isHierarchic ? "True" : "False") << " }\n";
	}
	// end document info.
	(*ofile) << "}\n\n";
}

void Document::SaveEditInfo() { }

void Document::ShowSource() {
	SetStatus("action: show document source");
	sourceEditDialog->SetTitle(&fileName);
	sourceEditDialog->LoadFile(&fileName);
	sourceEditDialog->Popup();
	sourceEditDialog->SetStatus(&fileName);
}

void Document::SaveSource() {
	if (sourceEditDialog->SaveFile(&fileName))
		SetStatus("action: document source saved");
	else
		SetStatus("ok, did not save");
}

void Document::ShowDocInfo() {
	SetStatus("action: document info");
	string val;
	string temp = "Current tool info\n";
	temp += "---------------------\n";
	temp += "Tool: ";
	temp += toolName;
	temp += "\n";
	temp += "File format: ";
	temp += fileFormat;
	temp += "\n";
	temp += "Login: ";
	temp += login;
	temp += "\n";
	System::GetTime(&val);
	temp += "Current date: ";
	temp += val;
	temp += "\n";
	temp += "Directory: ";
	temp += dir;
	temp += "\n";
	temp += "Number of changes: ";
	temp += changes;
	temp += "\n";
	temp += "\n";
	temp += "Current document info\n";
	temp += "---------------------\n";
	temp += "Type: ";
	temp += docType;
	temp += "\n";
	temp += "Name: ";
	temp += name;
	temp += "\n";
	temp += "Author: ";
	temp += author;
	temp += "\n";
	temp += "Created on: ";
	temp += createdOn;
	temp += "\n";
	temp += "\n";
	temp += "Loaded file info\n";
	temp += "---------------------\n";
	if (loaded) {
		temp += "File name:";
		temp += fileName;
		temp += "\n";
		temp += "Loaded format: ";
		temp += loadFormat;
		temp += "\n";
		temp += "Generated from: ";
		temp += generatedFrom;
		temp += "\n";
		temp += "Written by: ";
		temp += writtenBy;
		temp += "\n";
		temp += "Written on: ";
		temp += writtenOn;
		temp += "\n";
	}
	else
		temp += "None: document is created by current tool\n";
	infoDialog->SetTextString(&temp);
	infoDialog->Popup();
}

void Document::ShowSummary() {
	SetStatus("action: document summary");
	ShowDialog(MessageDialog::INFORMATION, "Document summary", 
		"Nothing to summarize\n");
}

void Document::CheckDocument() {
	SetStatus("action: check document syntax");
	ShowDialog(MessageDialog::INFORMATION, "Check document syntax", 
		"There are no checks for this document type\n");
}

void Document::ModelCheckProperty() {
        SetStatus("action: model check property");           
        ShowDialog(MessageDialog::INFORMATION,
                "Model check property", 
                "There are no checks for this document type\n");
}

void Document::ClearTrace() {
        SetStatus("action: clear trace");
        ShowDialog(MessageDialog::INFORMATION,
                "Clear trace",
                "Not needed for this document type\n");
}

void Document::Annotate() {
	SetStatus("action: annotate document");
	string txt = "Annotation of " + name;
	docAnnotationDialog->SetTitle(&txt);
	docAnnotationDialog->SetTextString(&annotation);
	docAnnotationDialog->Popup();
	docAnnotationDialog->SetStatus(&txt);
}

void Document::Find() {
	SetStatus("action: find");
	findDialog->Popup();
}

void Document::Replace() {
	SetStatus("action: replace");
	replaceDialog->Popup();
}

void Document::SetAnnotation(const string *a) {
	annotation = *a;
	SetStatus("document annotation updated");
	IncChanges();
}

void Document::Quit() {
	SetStatus("action: quit");
	viewer->TextModeOff();
	int answer;
	if (changes > 0) {
		answer = AskSave();
		if (answer == False)
			return;
	}
	if (config->GetAskBeforeQuit()) {
		string txt = "Are you sure you want to quit ";
		txt += Toolkit::TOOL_NAMES[tool];
		txt += "?";
		QuestionDialog q(mwwidget, False);
		q.Initialize();
		q.SetTitle("Quit confirmation");
		q.SetMessageString(&txt);
		answer = q.GetAnswer();
		if (answer == QuestionDialog::NO)
			return;
	}
	// delete mainwindow and consequently the rest of the gang.
	mainwindow->Close();
}

bool Document::AskSave() {
	string txt = "Document '" + name + "' has been modified "
		"\nDo you want to save it first?";
	QuestionDialog q(mwwidget, True);
	q.Initialize();
	q.SetTitle("Document modified");
	q.SetMessageString(&txt);
	int answer = q.GetAnswer();
	if (answer == QuestionDialog::YES) {
		saveSelection = False;
		saveName = dir + name;
		if (!Save(&saveName))
			return False;
	}
	else if (answer == QuestionDialog::CANCEL)
		return False;
	return True;
}

bool Document::NewName(const string *n) {
	string newName = *n;
	bool error = False;
	string txt;

	// name has a suffix but not the required suffix then give error msg.
	string suf;
	if (newName.getSuffix(suf) && suf != suffix) {
		error = True;
		txt = "Document name should have suffix '" + suffix + "'";
	}
	// add suffix when necessary.
	if (!newName.endsWith(suffix))
		newName.setSuffix(suffix);

	// no empty names.
	if (newName == suffix)
		newName = Toolkit::DOCUMENT_DEFAULT + suffix;
	
	// Check for illegal chars.
	for (unsigned i=0; i<newName.length(); i++) {
		unsigned char c = (unsigned char) newName[i];
		if (c == '/' || c == '{' || c == '}' || c == '"') {
			error = True;
			string cs = (char) c;
			txt = "Document name should not contain the"
			      " character '" + cs + "'";
		}
		else if (!isprint(c)) {
			error = True;
			txt = "Document name should not contain"
			      " unprintable characters";
		}
		else if (isspace(c)) {
			error = True;
			txt = "Document name should not contain"
			      " white space characters";
		}
	}
	if (error) {
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		mainwindow->SetDocumentName(&name);
		SetStatus("document could not be renamed");
		return False;
	}
	mainwindow->SetDocumentName(&newName);
	if (name == newName)
		return True;
	name = newName;
	viewer->Refresh();	// refresh document header/footer (if any)
	txt = "document renamed to " + name;
	SetStatus(&txt);
	IncChanges();
	return True;
}

void Document::NewDir(const string *newdir) {
	if (!System::DirExists(newdir->getstr())) {
		string txt = *newdir + "\nis a non-existent directory";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		UpdateDirectory(&dir);
		SetStatus("change directory failed");
		return;
	}
	else {
		dir = *newdir;
		if (dir[dir.length()-1] != '/')
			dir += "/";
		UpdateDirectory(&dir);
		string txt = "change dir to " + dir;
		viewer->GetPrintFileSelectionDialog()->SetDirectory(&dir);
		SetStatus(&txt);
	}
}

bool Document::IsDefault() {
	string t = Toolkit::DOCUMENT_DEFAULT;
	return (name.startsWith(t) != 0);
}

void Document::IncChanges() {
	mainwindow->SetModified(0 != ++changes);
}

void Document::DecChanges() {
	mainwindow->SetModified(0 != --changes);
}

bool Document::MayWrite(const string *path) {
	if (System::FileExists(path->getstr())) {
		string txt = "'" + *path + 
			"'\nalready exists. Do you want to overwrite it ?";
		QuestionDialog q(mwwidget, False);
		q.Initialize();
		q.SetTitle("Question");
		q.SetMessageString(&txt);
		int answer = q.GetAnswer();
		if (answer == QuestionDialog::NO)
			return False;
	}
	return True;
}

void Document::ReportCheck(int errors, const string *msg) {
	SetStatus("action: report check document results");
	if (errors != 0) {
		string text = *msg;
		// get rid of carr. returns in text labels.
		text.replace('\r', ' ');
		checkDialog->SetTextString(&text);
		checkDialog->Popup();
	}
	else
		ShowDialog(MessageDialog::INFORMATION, "Check document",
			"No violations found\n");
}
 

void Document::ShowDialog(MessageDialog::DialogType t, const char *title, 
			  const char *text) const {
	if (!mainwindow->IsDoMap()) {
		// mainwindow is not mapped, print to stderr.
		std::cerr << title << ": " << text << std::endl;
		return;
	}
	MessageDialog *d = new MessageDialog(mwwidget, t);
	d->Initialize();
	d->SetTitle(title);
#ifdef LINUX
	// I dont know why but otherwise I got crashes.
	d->Manage();
#endif
	d->SetMessageString(text);
	d->Popup();
}


void Document::SetHierarchic(bool set) {
	isHierarchic = AllowHierarchic() ? set : False;
}
