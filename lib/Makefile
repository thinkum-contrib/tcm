all:

config:

install:
	if test ! -d $(TCM_INSTALL_LIB) -o ! -d $(TCM_INSTALL_SHARE) -o ! -d $(CONFIG_INSTALL); then\
                mkdir -p $(TCM_INSTALL_SHARE);\
                mkdir -p $(CONFIG_INSTALL);\
                $(CHMOD) 755 $(TCM_INSTALL_SHARE) $(CONFIG_INSTALL); fi
	$(TCM_INSTALL_CMD) TCM banner.ps colorrgb.txt tcm.conf $(CONFIG_INSTALL)
	$(TCM_INSTALL_CMD) help $(TCM_INSTALL_SHARE)
	if test -f libglobal.so; then\
                mkdir -p $(TCM_INSTALL_LIB);\
		$(CHMOD) 755 $(TCM_INSTALL_LIB);\
		$(TCM_INSTALL_CMD) lib*.so $(TCM_INSTALL_LIB);\
	fi
clean:
	$(RM) lib*.so
	$(RM) lib*.a
	$(RM) help/CHANGELOG
	$(RM) help/COPYING

-include $(TCM_HOME)/src/Config.tmpl
