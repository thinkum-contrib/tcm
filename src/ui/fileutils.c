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
#include "fileutils.h"
#include "system.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "questiondialog.h"
#include "printeroptions.h"
#include "application.h"
#include "config.h"

bool FileUtils::Load(Widget widget, const char *file, string *text) {
	FILE *fd;
	char buf[MAXNAME+1];
	if (!System::FileExists(file)) {
		sprintf(buf, "File %s does not exist", file);
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", buf);
		return False;
	}
	else if (!System::FileRegular(file)) {
		sprintf(buf, "File %s is not a regular file", file);
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", buf);
		return False;
	}
	else if ((fd = fopen(file, "r")) == 0) {
		sprintf(buf, "Cannot read file %s", file);
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", buf);
		return False;
	}
	int cnt;
	while ((cnt = fread(buf, sizeof(char), MAXNAME, fd)) > 0) {
		buf[cnt] = '\0';
		*text += buf;
	}
	fclose(fd);
	return True;
}
	
bool FileUtils::Save(Widget widget, const char *file, const string *text) {
	FILE *fd;
	char buf[MAXNAME];
	if (System::FileExists(file) && !System::FileRegular(file)) {
		sprintf(buf, "File %s is not a regular file", file);
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", buf);
		return False;
	}
	if (System::FileExists(file)) {
		QuestionDialog q(widget, False);
		q.Initialize();
		q.SetTitle("Question");
		sprintf(buf, "File %s exists\n do you want to overwrite?",file);
		q.SetMessageString(buf);
		int answer = q.GetAnswer();
		if (answer == QuestionDialog::NO)
			return False;
	}
	if ((fd = fopen(file, "w")) == 0) {
		sprintf(buf, "Cannot write file %s", file);
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", buf);
		return False;
	}
	fprintf(fd,"%s", text->getstr());
	fclose(fd);
	return True;
}

bool FileUtils::PrintingOK(Widget widget, const char *jobName) {
	PrinterOptions *printerOptions = theApplication->GetPrinterOptions();
	string name = *printerOptions->GetPrinterName();
	string txt = "Do you want to print ";
	txt += jobName;
	txt += "\nto PostScript printer ";
	txt += name;
	txt += "?";
	QuestionDialog q(widget, False);
	q.Initialize();
	q.SetTitle("Print confirmation");
	q.SetMessageString(&txt);
	return (q.GetAnswer() == QuestionDialog::YES);
}

bool FileUtils::Print(Widget widget, const char *file, 
		const char *jobName, const char *filter) {
	bool result = True;
	char command[MAXNAME];
	char job[MAXNAME];
	if (equal(jobName, ""))
		strcpy(job, "Untitled");
	else
		strcpy(job, jobName);

	char buf[MAXNAME];
	command[0]= '\0';
	PrinterOptions *printerOptions = theApplication->GetPrinterOptions();
	string name = *printerOptions->GetPrinterName();
	int copies = printerOptions->GetPrintCopies();
	int bannerPage = printerOptions->GetPrintBannerPage();
	string printBanner = "";
	string printCommand = *printerOptions->GetPrintCommand();
	// print it
	if (name != "") {
		if  (!System::FileExists(printCommand.getstr())) {
			string txt = "The Unix command " + printCommand + 
				     " is not installed"; 
			(new MessageDialog(widget, MessageDialog::ERROR))->
				Show("Error", &txt);
			error("Error: could not open %s\n", 
				printCommand.getstr());
			result = False;
		}
		else {
			System::GiveFile(printCommand.getstr(), buf);
			// construct print command
			if (equal(buf, "lpr")) {
				if (bannerPage != Config::DEF_BANNER)
					printBanner = "-h";
			    	if (equal(filter, ""))
					sprintf(command, 
				  "%s -P%s -#%d -J%s %s <%s 2>&1 | cat >/dev/null",
				    	printCommand.getstr(), name.getstr(), 
					copies, job, printBanner.getstr(), file);
			    	else
					sprintf(command, 
				    	"%s <%s | %s -P%s -#%d -J%s %s 2>&1 "
					"| cat >/dev/null",
				    	filter, file, printCommand.getstr(), 
					name.getstr(), copies, job,
					printBanner.getstr());
			}
			else if (equal(buf, "lp")) {
				if (bannerPage != Config::DEF_BANNER)
					printBanner = "-o nobanner";
				if (equal(filter, ""))
					sprintf(command, 
				    	"%s -d %s -n %d -t %s %s <%s 2>&1 "
					"| cat >/dev/null",
				    	printCommand.getstr(), name.getstr(), 
					copies, job, printBanner.getstr(), file);
			    	else
					sprintf(command, 
					"%s < %s | %s -d %s -n %d -t %s %s 2>&1 "
					"| cat >/dev/null",
					filter, file, printCommand.getstr(), 
					name.getstr(), copies, job,
					printBanner.getstr());
			}
			else {
				if (equal(filter, ""))
					sprintf(command, 
					"%s <%s 2>&1 | cat >/dev/null", 
					printCommand.getstr(), file);
			    	else
					sprintf(command, 
					"%s < %s | %s 2>&1 | cat >/dev/null", 
					filter, file, printCommand.getstr());
			}
			int status = system(command);
			// Check for errors
			if (status) {
				(new MessageDialog(widget, 
					MessageDialog::ERROR))->
					Show("Error", 
					"Printing did not succeed");
				error("print error, print status = %d \n", 
					status);
				result = False;
			}
		}
	} 
	else {
		(new MessageDialog(widget, MessageDialog::ERROR))->
			Show("Error", "The printer name is not set");
		result = False;
	}
	// remove it.
	unlink(file);
	return result;
}
