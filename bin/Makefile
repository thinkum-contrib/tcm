TCM_INSTALL_BIN=$(TCM_INSTALL_DIR)/bin

all:

config:

install:
	@if test $(TCM_COMPILER) = gcc; then\
		TCM_HOME=$(TCM_HOME) ./linkx; fi
	if test ! -d $(TCM_INSTALL_BIN); then\
                mkdir -p $(TCM_INSTALL_BIN);\
                $(CHMOD) 755 $(TCM_INSTALL_BIN); \
		fi
	$(TCM_INSTALL_CMD) psf t* $(TCM_INSTALL_BIN)

clean:
	$(RM) t* c*

-include $(TCM_HOME)/src/Config.tmpl
