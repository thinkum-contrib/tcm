# This Makefile requires GNU make (gmake).

SHELL=/bin/sh

# change this if you want to install it in a different place
ifndef $(TCM_INSTALL_DIR)
	TCM_INSTALL_DIR=$TCM_HOME
endif

# the current version.
TCM_VERSION=2.20

# just a guess (flags should indicate recursiveness, permission
# keeping and links should stay links).
TCM_INSTALL_CMD = /bin/cp -fpr


ifndef TCM_INSTALL_LIB
	TCM_INSTALL_LIB=$(TCM_INSTALL_DIR)/lib/
endif

ifndef CONFIG_INSTALL
	CONFIG_INSTALL=$(TCM_INSTALL_LIB)
endif

ifndef TCM_INSTALL_DOC
	TCM_INSTALL_DOC=$(TCM_INSTALL_DIR)/doc/
endif

ifndef TCM_INSTALL_SHARE
	TCM_INSTALL_SHARE=$(TCM_INSTALL_LIB)
endif

ifndef TCM_INSTALL_MAN
	TCM_INSTALL_MAN=$(TCM_INSTALL_DIR)/man/
endif

MFLAGS += TCM_INSTALL_DIR='$(TCM_INSTALL_DIR)' TCM_INSTALL_LIB='$(TCM_INSTALL_LIB)' CONFIG_INSTALL='$(CONFIG_INSTALL)' TCM_INSTALL_DOC='$(TCM_INSTALL_DOC)' TCM_COMPILER='$(TCM_COMPILER)' TCM_INSTALL_CMD='$(TCM_INSTALL_CMD)' TCM_HOME='$(TCM_COMPILE_DIR)' TCM_INSTALL_SHARE='$(TCM_INSTALL_SHARE)'

UNAME=$(shell uname -s | sed -e 's/_NT.*//g')

ifeq ($(UNAME),IRIX64)
    UNAME = IRIX
endif

ifeq ($(UNAME),IRIX)
    TCM_PLATFORM = irix
    TCM_COMPILER = gcc
endif
ifeq ($(UNAME),Linux)
    TCM_PLATFORM = linux
    TCM_COMPILER = gcc
    TCM_INSTALL_CMD = /bin/cp -af
endif
ifeq ($(UNAME),HP-UX)
    TCM_PLATFORM = hpux
    TCM_COMPILER = gcc
endif
ifeq ($(UNAME),AIX)
    TCM_PLATFORM = aix
    TCM_COMPILER = gcc
    # TCM_COMPILER = xlc
endif
ifeq ($(UNAME),OSF1)
    TCM_PLATFORM = osf1
    TCM_COMPILER = gcc
endif
ifeq ($(UNAME),FreeBSD)
    TCM_PLATFORM = freebsd
    TCM_COMPILER = gcc
    TCM_INSTALL_CMD = /bin/cp -Rp
endif
ifeq ($(UNAME),SunOS)
    TCM_PLATFORM = solaris
    TCM_COMPILER = suncc
    TCM_INSTALL_CMD = /usr/bin/cp -fpr
    # TCM_PLATFORM = solaris.gcc
    # TCM_COMPILER = gcc
endif
ifeq ($(UNAME),CYGWIN)
    TCM_PLATFORM = CYGWIN
    TCM_COMPILER = gcc
    TCM_INSTALL_CMD = /bin/cp -dRf
endif

TCM_COMPILE_DIR=$(shell pwd)
TCM_HOME=$(TCM_COMPILE_DIR)
SUBDIRS = bin lib src doc

config:
	@echo making $@ for $(TCM_PLATFORM)...
	(cd ./src; rm -f ./Config.tmpl)
	(cd ./src; ln -s Config.tmpl_$(TCM_PLATFORM) Config.tmpl) 
	(cd ./src; rm -f ./Makefile)
	(cd ./src; ln -s Makefile.$(TCM_COMPILER) Makefile) 
	(cd ./src; touch ./gl/instances.h) 
	(cd ./lib/help; ln -s ../../CHANGELOG .) 
	(cd ./lib/help; ln -s ../../COPYING .) 
	@echo done making $@ for $(TCM_PLATFORM)
	@echo PLEASE CHECK FIRST THE SETTINGS IN src/Config.tmpl!
	@echo after that you can do the following: 
	@echo make depend: for making file dependencies
	@echo make execs: for making the binaries
	@echo make install: for copying the binaries and the files\
	       that they need to $(TCM_INSTALL_DIR)
	@echo \(this installation directory can be changed in $(TCM_HOME)/Makefile\)
	@echo make all: to do all this in one run
	@echo make clean: to remove all binaries, object and temporary files.

all: config depend execs install

execs:
	(cd ./src; ${MAKE} $(MFLAGS) all)

docs:
	(cd ./doc; ${MAKE} TCM_VERSION='$(TCM_VERSION)' all)

depend:
	(cd ./src; ${MAKE} TCM_HOME='$(TCM_COMPILE_DIR)' depend)

undepend:
	(cd ./src; ${MAKE} TCM_HOME='$(TCM_COMPILE_DIR)' undepend)

clean:
	@echo making $@...
	for dir in $(SUBDIRS); do \
                (cd $${dir}; ${MAKE} TCM_HOME='$(TCM_COMPILE_DIR)' $@); done
	@echo done making $@...

install:
	@echo making $@...
	if test ! -d $(TCM_INSTALL_DIR); then\
                mkdir -p $(TCM_INSTALL_DIR);\
                $(CHMOD) 755 $(TCM_INSTALL_DIR); fi
	$(TCM_INSTALL_CMD) README CHANGELOG COPYING FILEMAP \
			INSTALL_ README.cygwin INSTALL.cygwin man $(TCM_INSTALL_DIR)
	if test ! -d $(TCM_INSTALL_MAN); then\
		mkdir -p $(TCM_INSTALL_MAN);\
		$(CHMOD) 755 $(TCM_INSTALL_MAN); fi
	$(TCM_INSTALL_CMD) man/* $(TCM_INSTALL_MAN)
	for dir in $(SUBDIRS); do \
		(cd $${dir}; ${MAKE} $(MFLAGS) $@); done
	@echo done making $@...

-include $(TCM_HOME)/src/Config.tmpl
