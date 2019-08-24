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
#include "system.h"
#include "util.h"
#include "lstring.h"
#include "version.h"
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(AIX)
#include <time.h>
#else
#include <sys/time.h>
#if defined(LINUX)
#include <time.h>
#endif
#endif
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#if !defined(__GNUC__)
#include <sysent.h>
#endif

const char System::TOOLKIT_STAT_HEADER[] = "TCM-STAT";

const char System::TOOLKIT_BUG_HEADER[] = "TCM-BUG";

const char System::TOOLKIT_HOME_VAR_NAME[] = "TCM_HOME";

const char System::TOOLKIT_HOME_DEFAULT[] = "/home/tcm";

bool System::sendBugEmail = False;
char System::emailAddress[MAXNAME] = "tcm@cs.utwente.nl";
char System::currentProgram[MAXNAME] = "";

#if defined(BSD)
	extern "C" int GetHostName(char *host, int namelen);
#else
	#include <sys/utsname.h>
#endif
// extern int uname(struct utsname *name);

// most common Unix directories for system wide available binaries.
const char *System::STD_SEARCH_DIRS[] =
	{"./", "/bin/", "/usr/bin/", "/usr/local/bin/", 
	 "/usr/local/tcm/bin/", "/home/tcm/bin/", "/usr/bin/X11/", 
	 "/usr/ucb/", "/usr/sbin/", "/usr/X11/bin/", "/usr/openwin/bin/", 
	 "/opt/tcm/bin/", "/usr/local/X11/bin/", "/usr/local/bin/X11/",
	 "/usr/openwin/contrib/bin/", "/Window/X11/bin/",
	 "/Window/X11/contrib/bin/", 0};

#if defined(LINUX) || defined(AIX) || defined(HPUX) || defined(OSF1) || defined(BSD) || defined(__CYGWIN__)
typedef void (*SIG_PF)(int);
#endif

bool System::GetHostName(char *host) {
#if defined(BSD)
	char buf[MAXNAME];
	if (gethostname(buf, MAXNAME-1) == 0) {
		strncpy(host, buf, MAXNAME-1);
		return 1;
	}
#else
	struct utsname name;
	if (uname(&name)) {
		strncpy(host, name.nodename, MAXNAME-1);
		return 1; 
	}
#endif
	return 0;
}

bool System::GetLoginName(char *login) {
	static bool newError = True;
	if (login == 0)
		return 0;
	static struct passwd *myentry = 0;
	static struct passwd pwdentry;
	if (myentry == 0)
		myentry = getpwuid(geteuid());
	if (myentry != 0) {
		memcpy (&pwdentry, myentry, sizeof (struct passwd));
		myentry = &pwdentry;
	}
	if (myentry) {
		strcpy(login, pwdentry.pw_name);
	}
	else {
		if (newError) {
			error("Warning: uid %d has no passwd entry\n", 
				geteuid());
			newError = False;
		}
		strcpy(login, "nobody");
	}
	return 1;
}

bool System::GetTime(char *time) {
	struct timeval tp;
#ifdef BSD
	struct timezone tzp;
	gettimeofday(&tp, &tzp);
#else
	gettimeofday(&tp, 0);
#endif
	time_t secs = tp.tv_sec;
		// ctime puts the time in a 26 char time string.
	strcpy(time, ctime(&secs));
		// remove newline at end of string.
	if (time != 0)
		time[24] = '\0';
	return (time == 0);
}

bool System::GetPrinter(char *printer) {
	char *p = getenv("PRINTER");
	if (!p || equal(p, "")) {
		// error("Warning: PRINTER variable not set \n");
		return False;
	}
	strcpy(printer, p);
	return True;
}


bool System::GetCwd(char *dir) {
	// current directory has to be found.
#ifdef BSD
	if (!getwd(dir)) {
#else
	if (!getcwd(dir, MAXNAME-1)) {
#endif
		strcpy(dir, "");
		return False;
	}
	strcat(dir, "/");
	return True;
}
 
bool System::GetHome(char *home) {
	char *p = getenv("HOME");
	if (!p || equal(p, ""))
		return False;
	strncpy(home, p, MAXNAME-1);
	strcat(home, "/");
	return True;
}

void System::GetToolkitHome(char *home) {
	char *p = getenv(TOOLKIT_HOME_VAR_NAME);
	if (!p || equal(p, "")) {
		// try first TCM_HOME for compatibility.
		char *p2 = getenv("TCM_HOME");
		if (p2 && !equal(p2, "")) {
			strncpy(home, p2, MAXNAME-1);
		}
		else {
			const char tmp[]=TCM_INSTALL_DIR;
			strcpy(home, tmp);
		}
	}
	else
		strncpy(home, p, MAXNAME-1);
}

void System::GetToolkitLib(char *lib) {
	char *p = getenv("TCM_LIB");
	if (!p || equal(p, "")) {
		// try TCM_HOME/lib for compatibility.
		char *p2 = getenv("TCM_HOME");
		if (p2 && !equal(p2, "")) {
			strncpy(lib, p2, MAXNAME-1);
			strcat(lib, "/lib/");
		}
		else {
			const char tmp[]=TCM_INSTALL_LIB;
			strcpy(lib, tmp);
		}
	}
	else
		strncpy(lib, p, MAXNAME-1);
}

void System::GetToolkitConfig(char *conf) {
	char *p = getenv("TCM_CONFIG");
	if (!p || equal(p, "")) {
		// try TCM_HOME/lib for compatibility.
		char *p2 = getenv("TCM_HOME");
		if (p2 && !equal(p2, "")) {
			strncpy(conf, p2, MAXNAME-1);
			strcat(conf, "/lib/");
		}
		else {
			const char tmp[]=CONFIG_INSTALL;
			strcpy(conf, tmp);
		}
	}
	else
		strncpy(conf, p, MAXNAME-1);
}

void System::GetToolkitShare(char *share) {
	char *p = getenv("TCM_SHARE");
	if (!p || equal(p, "")) {
		// try TCM_HOME/lib for compatibility.
		char *p2 = getenv("TCM_HOME");
		if (p2 && !equal(p2, "")) {
			strncpy(share, p2, MAXNAME-1);
			strcat(share, "/lib/");
		}
		else {
			const char tmp[]=TCM_INSTALL_SHARE;
			strcpy(share, tmp);
		}
	}
	else
		strncpy(share, p, MAXNAME-1);
}

void System::GetToolkitHelp(char *help) {
	char *p = getenv("TCM_HELP");
	if (!p || equal(p, "")) {
		// try TCM_HOME/lib for compatibility.
		char *p2 = getenv("TCM_HOME");
		if (p2 && !equal(p2, "")) {
			strncpy(help, p2, MAXNAME-1);
			strcat(help, "/lib/help/");
		}
		else {
			const char tmp[]=HELP_DIR;
			strcpy(help, tmp);
		}
	}
	else
		strncpy(help, p, MAXNAME-1);
}

unsigned long System::GenerateId(unsigned long s) {
	long id = abs ((long)time((time_t *)0) - ((time_t)s));
	srand48(id);
	id = lrand48();
	return id;
}

void System::GiveFile(const char *path, char *dir, char *file) {
	const char *p = strrchr(path, '/');
	if (p == 0) {
		strcpy(dir, "");
		strncpy(file, path, MAXNAME-1);
	}
	else {
		strncpy(file, ++p, MAXNAME-1);
		int len = strlen(path)-strlen(p);
		strncpy(dir, path, len);
		dir[len] = '\0';
	}
}

void System::GiveFile(const char *path, char *file) {
	const char *p = strrchr(path, '/');
	if (p == 0)
		strncpy(file, path, MAXNAME-1);
	else
		strncpy(file, ++p, MAXNAME-1);
}

bool System::FileRegular(const char *file) {
	struct stat status;
	if (stat(file, &status) != 0)
		return False;
	return S_ISREG(status.st_mode);
}

bool System::FileExecutable(const char *file) {
	struct stat status;
	if (stat(file, &status) == 0) {
		mode_t mode =  status.st_mode;
		if (mode & S_IXOTH)
			return True;
	}
	return False;
}

bool System::FileExists(const char *path) {
	struct stat status;
	return (stat(path, &status) == 0);
}

bool System::DirExists(const char *dir) { 
	struct stat status;
	if (stat(dir, &status) != 0)
		return False;
	return S_ISDIR(status.st_mode);
}

bool System::FindProgram(char *program, const char *command) {
//	strcpy(program, "");
//	// first try this:
//	char *t = getenv(TOOLKIT_HOME_VAR_NAME);
//	if (!t || equal(t,"")) {
//		t = getenv("TCM_HOME");
//		if (!t || equal(t,""))
//			return False;
//	}
	const char *t = TCM_INSTALL_DIR;
	strcpy(program, t);
	strcat(program, "/bin/");
	strcat(program, command);
	if (FileExecutable(program)) {
		return True;
	}
	// try some common directories.
	for (const char **p = &STD_SEARCH_DIRS[0]; *p; p++) {
		strcpy(program, *p);
		strcat(program, command);
		if (FileExecutable(program)) {
			return True;
		}
	}
	return False;
}

bool System::NxnParse(const char *parsestring, int &num1, int &num2) {
	char description[MAXNAME];
	strcpy(description, parsestring);
	char *p = description;
	while (*p != 'x')
		p++;
	if (!*p) {
		error("parse %s: no x found\n", parsestring);
		return False;
	}
	*p = '\0';
	num1 = atoi(description);
	if (num1 <= 0) {
		error("parse %s: no num1 found\n", parsestring);
		return False;
	}
	num2 = atoi(++p);
	if (num2 <= 0) {
		error("parse %s: no num2 found\n", parsestring);
		return False;
	}
	return True;
}

bool System::FindArg(char **argv, int argc, const char *arg, int &index) {
	for (int i=0; i<argc; i++) {
		if (equal(argv[i], arg)) {
			index = i;
			return True;
		}
	}
	return False;
}

void System::SignalHandler(int s) {
	char bug[MAXNAME];
	switch(s) {
#ifdef SIGINT
	case SIGINT: error("Interrupt caught: use 'Quit' to quit\n");
			(void) signal (SIGINT, (SIG_PF)SignalHandler);
			return; // continue
#endif
#ifdef SIGQUIT
	case SIGQUIT: error("SIGQUIT caught: use 'Quit' to quit\n");
			(void) signal (SIGQUIT, (SIG_PF)SignalHandler);
			return; // continue
#endif
#ifdef SIGPIPE
	case SIGPIPE: 
			error("Warning: Broken Pipe\n");
			(void) signal (SIGPIPE, (SIG_PF)SignalHandler);
			return; // continue
#endif
#ifdef SIGTRAP
	case SIGTRAP: 
			strcpy(bug, "Trace/breakpoint Trap");
			break;
#endif
#ifdef SIGABRT
	case SIGABRT: 
			strcpy(bug, "Abort Signal");
			break;
#endif
#ifdef SIGBUS
	case SIGBUS: 
			strcpy(bug, "Bus Error");
			break;
#endif
#ifdef SIGSEGV
	case SIGSEGV: 
			strcpy(bug, "Segmentation Fault");
			break;
#endif
#ifdef SIGSYS
	case SIGSYS: 
			strcpy(bug, "Bad System Call");
			break;
#endif
#ifdef SIGFPE
	case SIGFPE: 
			strcpy(bug, "Arithmetic Exception");
			break;
#endif
#ifdef SIGILL
	case SIGILL: 
			strcpy(bug, "Illegal Instruction");
			break;
#endif
	default:
			error("signal %d caught, trying to ignore it\n", s);
			(void) signal (s, (SIG_PF)SignalHandler);
			return;
	}
	if (sendBugEmail)
		SendEmail(emailAddress, TOOLKIT_BUG_HEADER, currentProgram, 
		  	Version::TOOLKIT_VERSION, bug);
	std::cerr << bug << " occurred." << std::endl;
	std::cerr << "Please send a bug report to " << emailAddress << std::endl; 
	exit(1);
}

void System::SetSignalHandler() {
// #ifdef SIGINT
//	(void) signal (SIGINT, (SIG_PF)SignalHandler);
// #endif
#ifdef SIGQUIT
	(void) signal (SIGQUIT, (SIG_PF)SignalHandler);
#endif
#ifdef SIGTRAP
	(void) signal (SIGTRAP, (SIG_PF)SignalHandler);
#endif
#ifdef SIGABRT
	(void) signal (SIGABRT, (SIG_PF)SignalHandler);
#endif
#ifdef SIGBUS
	(void) signal (SIGBUS, (SIG_PF)SignalHandler);
#endif
#ifdef SIGSEGV
	(void) signal (SIGSEGV, (SIG_PF)SignalHandler);
#endif
#ifdef SIGSYS
	(void) signal (SIGSYS, (SIG_PF)SignalHandler);
#endif
#ifdef SIGILL
	(void) signal (SIGILL, (SIG_PF)SignalHandler);
#endif
#ifdef SIGFPE
	(void) signal (SIGFPE, (SIG_PF)SignalHandler);
#endif
#ifdef SIGPIPE
	(void) signal (SIGPIPE, (SIG_PF)SignalHandler);
#endif
}

 
void System::SendEmail(const char *recipient, const char *subject, 
		const char *program,
	const char *version, const char *text) {

	char info[MAXNAME];
	char mailProg[MAXNAME];
	char buf[MAXNAME];
#if defined(SOLARIS) || defined(IRIX)
	const char *MailCommand = "mailx";
	const char *MailCommand2 = "mail";
#else
	const char *MailCommand = "mail";
	const char *MailCommand2 = "mailx";
#endif
	sprintf(buf, " %s %s ", program, version);
	strcpy(info, subject);
	strcat(info, buf);
#ifdef LINUX
	strcat(info, "linux");
#elif SOLARIS
	#ifdef __i386
		strcat(info, "solaris x86");
	#else
		strcat(info, "solaris sparc");
	#endif
#elif SUNOS
	strcat(info, "sunos");
#elif HPUX
	strcat(info, "hp-ux");
#elif IRIX
	strcat(info, "irix");
#endif
	if (!System::FindProgram(mailProg, MailCommand)) {
		if (!System::FindProgram(mailProg, MailCommand2))
			return;
	}
	// construct mail command
	sprintf(buf, "/bin/echo %s | %s -s \"%s\" %s &",
			text, mailProg, info, recipient);
#ifdef DEBUG
	error("executing %s\n", buf);
#endif
	// execute the command
	int status = system(buf);
	// Check for errors
	if (status)
		error("notice: sending email to %s did not succeed\n", 
			recipient);
}

bool System::GetCwd(string *dir) {
	char tmp[MAXNAME];
	bool b = GetCwd(tmp);
	if (b) *dir = tmp;
	return b;
}
 
bool System::GetHostName(string *hn) {
	char tmp[MAXNAME];
	bool b = GetHostName(tmp);
	if (b) *hn = tmp;
	return b;
}
 
bool System::GetLoginName(string *ln) {
	char tmp[MAXNAME];
	bool b = GetLoginName(tmp);
	if (b) *ln = tmp;
	return b;
}

bool System::GetTime(string *tm) {
	char tmp[MAXNAME];
	bool b = GetTime(tmp);
	if (b) *tm = tmp;
	return b;
}
 
bool System::GetPrinter(string *printer) {
	char tmp[MAXNAME];
	bool b = GetPrinter(tmp);
	if (b) *printer = tmp;
	return b;
}

bool System::GetHome(string *home) {
	char tmp[MAXNAME];
	bool b = GetHome(tmp);
	if (b) *home = tmp;
	return b;
}

void System::GetToolkitHome(string *home) {
	char tmp[MAXNAME];
	GetToolkitHome(tmp);
	*home = tmp;
}

void System::GetToolkitLib(string *lib) {
	char tmp[MAXNAME];
	GetToolkitLib(tmp);
	*lib = tmp;
}

void System::GetToolkitConfig(string *conf) {
	char tmp[MAXNAME];
	GetToolkitConfig(tmp);
	*conf = tmp;
}

void System::GetToolkitShare(string *share) {
	char tmp[MAXNAME];
	GetToolkitShare(tmp);
	*share = tmp;
}

void System::GetToolkitHelp(string *help) {
	char tmp[MAXNAME];
	GetToolkitHelp(tmp);
	*help = tmp;
}

void System::GiveFile(const string *path, string *dir, string *file) {
	char t1[MAXNAME];
	char t2[MAXNAME];
	GiveFile(path->getstr(), t1, t2);
	*dir = t1;
	*file = t2;
}

void System::GiveFile(const string *path, string *file) {
	char t1[MAXNAME];
	GiveFile(path->getstr(), t1);
	*file = t1;
}

bool System::FindProgram(string *program, const char *command) {
	char t1[MAXNAME];
	bool b = FindProgram(t1, command);
	*program = t1;
	return b;
}
