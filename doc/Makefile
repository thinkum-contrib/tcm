SUBDIRS = docxx userdoc techdoc classdoc

TCM_COMPILE_DIR=$(shell pwd)/..
TEXINPUTS=.:$(TCM_COMPILE_DIR)/doc/docsrc/texstyles

ifndef TCM_INSTALL_DOC
	TCM_INSTALL_DOC=$(TCM_INSTALL_DIR)/doc/
endif

config:

all:
	@echo making $@ for $(TCM_PLATFORM)...
	for dir in $(SUBDIRS); do \
                (cd docsrc/$${dir}; \
                 ${MAKE} -k TCM_COMPILE_DIR='$(TCM_COMPILE_DIR)' \
			    TCM_VERSION='$(TCM_VERSION)' \
			    TEXINPUTS='$(TEXINPUTS)' $@); done
	@echo done making $@ for $(TCM_PLATFORM)

clean:
	if test -d docsrc; then\
                for dir in $(SUBDIRS); do \
                        (cd docsrc/$${dir}; \
                        ${MAKE} $@); done; \
                $(RM) usersguide/*; \
                $(RM) developersguide/*; \
                $(RM) sourcecode/*; \
                $(RM) *.pdf *.ps.gz; fi \
 

install:
	if test ! -d $(TCM_INSTALL_DOC); then\
		mkdir -p $(TCM_INSTALL_DOC);\
		chmod 755 $(TCM_INSTALL_DOC);\
		mkdir -p $(TCM_INSTALL_DOC)/usersguide;\
		chmod 755 $(TCM_INSTALL_DOC)/usersguide; fi
	chmod 644 index.html usersguide/*.*
	$(TCM_INSTALL_CMD) usersguide*.pdf.gz usersguide*.ps.gz index.html \
			usersguide.html wishlist $(TCM_INSTALL_DOC)
	$(TCM_INSTALL_CMD) usersguide/*.html usersguide/*.gif \
			usersguide/*.css $(TCM_INSTALL_DOC)/usersguide


docxx classdoc techdoc userdoc:
	(cd docsrc/$@; \
	${MAKE} -k TCM_COMPILE_DIR='$(TCM_COMPILE_DIR)' \
			    TCM_VERSION='$(TCM_VERSION)' \
			    TEXINPUTS='$(TEXINPUTS)' all)
