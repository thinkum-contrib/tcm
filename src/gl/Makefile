include ../Config.tmpl

CONFIG_FILE = tcm.conf

CFLAGS += -DCONFIG_INSTALL=\"$(CONFIG_INSTALL)\" -DTCM_INSTALL_DIR=\"$(TCM_INSTALL_DIR)\" -DTCM_INSTALL_LIB=\"$(TCM_INSTALL_LIB)\" -DTCM_INSTALL_SHARE=\"$(TCM_INSTALL_SHARE)\"
CFLAGS += -DCONFIG_FILE=\"$(CONFIG_FILE)\" -DHELP_DIR=\"$(TCM_INSTALL_SHARE)help/\"

OBJECTS=afont.o\
        assoclist.o\
	code.o\
	config.o\
	dpoint.o\
	file.o\
	fillstyle.o\
	inputfile.o\
	intersect.o\
	key.o\
	link.o\
	llist.o\
	linestyle.o\
	lstring.o\
	lvector.o\
        outputfile.o\
	pagesize.o\
	point.o\
	printeroptions.o\
	properties.o\
	readdirection.o\
	rectangle.o\
	sequence.o\
	side.o\
	system.o\
	textalign.o\
	toolkit.o\
	version.o

text2ps.o:
	$(Cc) $(SYSFLAGS) -c text2ps.c

text2ps$(EXEEXTENSION): text2ps.o
	$(Cc) text2ps.o -o $@ 
	$(CHMODPLUSX) $@
	$(MV) $@ $(BIN_DIR)

libglobal.a: $(OBJECTS)
	$(AR) $@ $(OBJECTS)
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libglobal.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(SHAREDFLAG) $(OBJECTS) -o $@
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(LIB_DIR)

clean: xclean

xclean::
	echo > instances.h

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
