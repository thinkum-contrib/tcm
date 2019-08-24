////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "printerqueuedialog.h"
#include "printeroptions.h"
#include "mainwindow.h"
#include "promptdialog.h"
#include "messagedialog.h"
#include "link.h"
#include "mstring.h"
#include "system.h"
#include <Xm/XmAll.h>
#include <stdlib.h>

PrinterQueueDialog::PrinterQueueDialog(Widget p, MainWindow *w): 
		SelectionDialog(p) {
	SetAutoUnmanage(False);
	mainwindow = w;
	promptDialog = new PromptDialog(mainwindow->GetWidget());
	promptDialog->Initialize();
	printerOptions = mainwindow->GetPrinterOptions();
	queueCommand = "";
	defaultQueueCommand = "";
	removeCommand = "";
	defaultRemoveCommand = "";
}

void PrinterQueueDialog::CreateWidget() {
	// create the selection box dialog
	Arg al[10]; int ac = 0;
	XtSetArg(al[ac], XmNautoUnmanage, GetAutoUnmanage()); ac++;
	XtSetArg(al[ac], XmNdefaultButtonType, XmDIALOG_APPLY_BUTTON); ac++;
	XtSetArg(al[ac], XmNmustMatch, False); ac++;
	SetWidget(XmCreateSelectionDialog(GetParent(), (char *)GetClassName(), al, ac));
}

void PrinterQueueDialog::Configure() {
	SelectionDialog::Configure();
	const char *selection = 
		"Update refreshes, Remove cancels selected item and"
		" Dismiss deletes dialog.";
	SetSelectionLabel(selection);
	SetCancelButtonLabel("Dismiss");
	SetOKButtonLabel("Update");
	SetApplyButtonLabel("Remove");
	SetApplyCallback(RemoveCB, this);
	SetOKCallback(UpdateCB, this);
	SetCancelCallback(UnmanageCB, this);
	ManageHelpButton(False);
	SetEditable(False);
}

void PrinterQueueDialog::Update() {
	mainwindow->SetCursor(MouseCursor::WATCH);
	mainwindow->SetStatus("");
	// Check if printer queue command exists.
	if  (!System::FileExists(queueCommand.getstr())) {
		string txt = "The Unix program " + queueCommand + 
			     " cannot be found."; 
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))->
			Show("Error", &txt);
		error("Error: could not open %s\n", queueCommand.getstr());
		return;
	}
	// establish a link to Unix printer queue with the link class.
	// and place the strings from output into the selection box.
	Link l;
	char s[MAXNAME], s2[MAXNAME];
	if (!check(GetWidget()))
		return;
	char command[MAXNAME];
	string printerName = *printerOptions->GetPrinterName();
	System::GiveFile(queueCommand.getstr(), command);
	if (equal(command, "lpq"))
		sprintf(s2, "-P%s", printerName.getstr());
	else if (equal(command, "lpstat"))
		sprintf(s2, "-o %s", printerName.getstr());
	l.Open(queueCommand.getstr(), s2);
	// l.Read(s);  lose header line
	// XmListDeleteAllItems(GetList());
	DeleteAllItems();
	while (!l.Read(s)) {
		AddItem(s);
		// xs = CreateXmString(s);
		// XmListAddItem(GetList(), xs, 0);
		// XmStringFree(xs);
	}
	l.Close();
	XtManageChild(GetWidget());
	mainwindow->SetStatus("Update printer queue");
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

void PrinterQueueDialog::Remove(const char *procstr) {
	char s[MAXNAME];
	char rank[20], owner[64], job[20];
	char removeProg[MAXNAME];
	char queueProg[MAXNAME];
	if  (!System::FileExists(removeCommand.getstr())) {
		string txt = "The Unix program " + removeCommand +
			     " can not be found"; 
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))->
			Show("Error", &txt);
		error("Error: could not open %s\n", removeCommand.getstr());
	}
	// remove item
	System::GiveFile(removeCommand.getstr(), removeProg);
	System::GiveFile(queueCommand.getstr(), queueProg);
	// extract the job number from the line and remove that job number.
	bool succes = True;
	if (equal(queueProg, "lpq")) {
		if (sscanf(procstr, "%s%s%s", rank, owner, job) != 3)
			succes = False;
	}
	else if (equal(queueProg, "lpstat")) {
		if (sscanf(procstr, "%*[^-]-%s%s", job, owner) != 2)
			succes = False;
	}
	else
		succes = False;
	if (succes) {
		string printerName = *printerOptions->GetPrinterName();
		if (equal(removeProg, "lprm")) {
			sprintf(s, "%s -P%s %s 2>&1", 
				removeProg, printerName.getstr(), job);
		}
		else if (equal(removeProg, "cancel")) {
			sprintf(s, "%s %s-%s 2>&1", 
				removeProg, printerName.getstr(), job);
		}
		system(s);
		string txt = "try to remove job '";
		txt += job;
		txt += "'";
		mainwindow->SetStatus(&txt);
	}
	else
		mainwindow->SetStatus("nothing to be removed");
	// make selection string empty.
	SetTextString("");
	Update();
}

void PrinterQueueDialog::PrinterQueueCommand() {
	promptDialog->SetTitle("Printer queue command");
	promptDialog->SetSelectionLabel("Printer queue command:");
	promptDialog->SetTextString(&queueCommand);
	promptDialog->SetOKCallback(SetPrinterQueueCommandCB, this);
	promptDialog->SetDefaultValue(&defaultQueueCommand);
	promptDialog->Popup();
}

void PrinterQueueDialog::PrinterRemoveCommand() {
	promptDialog->SetTitle("Printer remove command");
	promptDialog->SetSelectionLabel("Printer remove command:");
	promptDialog->SetTextString(&removeCommand);
	promptDialog->SetOKCallback(SetPrinterRemoveCommandCB, this);
	promptDialog->SetDefaultValue(&defaultRemoveCommand);
	promptDialog->Popup();
}

void PrinterQueueDialog::SetPrinterQueueCommand(const string *s) {
	queueCommand = *s;
	string txt = "printer queue command is " + queueCommand;
	mainwindow->SetStatus(&txt);
}

void PrinterQueueDialog::SetPrinterRemoveCommand(const string *s) {
	removeCommand = *s;
	string txt = "printer remove command is " + removeCommand;
	mainwindow->SetStatus(&txt);
}

void PrinterQueueDialog::RemoveCB(Widget, XtPointer client_data, XtPointer cbs){
	XmSelectionBoxCallbackStruct *call_data = 
		(XmSelectionBoxCallbackStruct *)cbs;
	PrinterQueueDialog *p = (PrinterQueueDialog *)client_data;
	char *procstr;
	if (XmStringGetLtoR(call_data->value,XmFONTLIST_DEFAULT_TAG,&procstr)) {
		p->Remove(procstr);
		XtFree(procstr);
	}
}

void PrinterQueueDialog::UpdateCB(Widget, XtPointer client_data, XtPointer) {
	PrinterQueueDialog *p = (PrinterQueueDialog *)client_data;
	p->Update();
}

void PrinterQueueDialog::SetPrinterQueueCommandCB(Widget, XtPointer clientData,
		XtPointer) {
	PrinterQueueDialog *p = (PrinterQueueDialog *)clientData;
	PromptDialog *dialog = p->GetPromptDialog();
	string t;
	dialog->GetTextString(&t);
	p->SetPrinterQueueCommand(&t);
}

void PrinterQueueDialog::SetPrinterRemoveCommandCB(Widget, 
		XtPointer clientData, XtPointer) {
	PrinterQueueDialog *p = (PrinterQueueDialog *)clientData;
	PromptDialog *dialog = p->GetPromptDialog();
	string t;
	dialog->GetTextString(&t);
	p->SetPrinterRemoveCommand(&t);
}
