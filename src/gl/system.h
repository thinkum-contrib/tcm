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
#ifndef _SYSTEM_H 
#define _SYSTEM_H 
 
#include "bool.h"
class string;

/// Encapsulates some O.S. specific functions.
class System {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// set unix signal handler.
	static void SetSignalHandler();

	/// copies into host the hostname of the machine.
	static bool GetHostName(char* host);
	///
	static bool GetHostName(string* host);

	/// copies into login the loginname of the user.
	static bool GetLoginName(char* login);
	///
	static bool GetLoginName(string* login);

	/// copies in time the current machine time as a string.
	static bool GetTime(char* time);
	///
	static bool GetTime(string* time);

	/// returns a random number based on the time and the given number.
	static unsigned long GenerateId(unsigned long); 

	/// copies into printer the PRINTER environment variable.
	static bool GetPrinter(char* printer);
	///
	static bool GetPrinter(string* printer);

	/// retrieve current working directory.
	static bool GetCwd(char* dir);
	///
	static bool GetCwd(string* dir);
	
	/// retrieve home directory.
	static bool GetHome(char* home);
	///
	static bool GetHome(string* home);

	/// copies the tool home directory variable into home.
	static void GetToolkitHome(char* home); 
	///
	static void GetToolkitHome(string* home);

	/// copies the tool lib directory variable into lib.
	static void GetToolkitLib(char* lib);
	///
	static void GetToolkitLib(string* lib);

	/// copies the tool config directory variable into conf.
	static void GetToolkitConfig(char* conf);
	///
	static void GetToolkitConfig(string* conf);

	/// copies the tool share directory variable into share.
	static void GetToolkitShare(char* share);
	///
	static void GetToolkitShare(string* share);

	/// copies the tool help directory variable into help.
	static void GetToolkitHelp(char* help);
	///
	static void GetToolkitHelp(string* help);

	/// copies in dir and file the directory and file in the name 'path'.
	static void GiveFile(const char* path, char* dir, char* file);
	///
	static void GiveFile(const string* path, string* dir, string* file);

	/// copies in file the file in the name 'path'.
	static void GiveFile(const char* path, char* file); 
	///
	static void GiveFile(const string* path, string* file); 

	/// returns if file is regular (not directory, named pipe etc).
	static bool FileRegular(const char* file); 

	/// returns whether file exists
	static bool FileExists(const char* file);

	/// returns whether executable file exists
	static bool FileExecutable(const char* file);

	/// returns whether directory exists
	static bool DirExists(const char* dir);

	/// returns if there is command in a std dir, program becomes the path.
	static bool FindProgram(char* program, const char* command); 
	///
	static bool FindProgram(string* program, const char* command); 

	/// return true if desc is a 'num1'x'num2' string.
	static bool NxnParse(const char* desc, int &num1, int &num2); 
	
	/// return if argv contains arg. Index will be the position in argv.
	static bool FindArg(char** argv, int argc, const char* arg, int &index);

	/// send an email message (for instance for stats or bug reports).
	static void SendEmail(const char* recipient, const char* subject, 
		const char* program, const char* version, const char* text);

	/// default toolkit home directory.
	static const char TOOLKIT_HOME_DEFAULT[];

	/// Statistics message subject for logging.
	static const char TOOLKIT_STAT_HEADER[];
 
	/// Bug report message subject.
	static const char TOOLKIT_BUG_HEADER[];

	/// Variable name that contains the tool home directory.
	static const char TOOLKIT_HOME_VAR_NAME[];

	/// most common Unix directories for system wide available binaries.
	static const char* STD_SEARCH_DIRS[];

	/// send an email after crash
	static bool sendBugEmail;

	/// email address to send to.
	static char emailAddress[];

	/// the command name of the current program (argv[0]).
	static char currentProgram[];
protected:
	/// called when signal occurs.
	static void SignalHandler(int s);
};


 
#endif
