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
	$(RM) instances.h
	touch instances.h 

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
afont.o: afont.c afont.h lstring.h bool.h
assoclist.o: assoclist.c assoclist.h llist.h element.h bool.h assoc.h
code.o: code.c code.h typename.h util.h error.h
config.o: config.c config.h llist.h element.h bool.h lstring.h point.h \
  linestyle.h textalign.h pagesize.h afont.h util.h error.h inputfile.h \
  file.h system.h
dpoint.o: dpoint.c dpoint.h point.h bool.h
file.o: file.c file.h bool.h lstring.h
fillstyle.o: fillstyle.c fillstyle.h lstring.h
inputfile.o: inputfile.c inputfile.h file.h bool.h lstring.h error.h
intersect.o: intersect.c intersect.h point.h bool.h util.h error.h
key.o: key.c key.h bool.h
linestyle.o: linestyle.c linestyle.h lstring.h
link.o: link.c link.h
llist.o: llist.c llist.h element.h bool.h instances.h
lstring.o: lstring.c lstring.h util.h error.h
lvector.o: lvector.c lvector.h bool.h llist.h element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h code.h typename.h \
  lstring.h
outputfile.o: outputfile.c outputfile.h file.h bool.h lstring.h point.h \
  util.h error.h
pagesize.o: pagesize.c pagesize.h lstring.h
point.o: point.c point.h bool.h
printeroptions.o: printeroptions.c printeroptions.h lstring.h bool.h \
  config.h llist.h element.h point.h linestyle.h textalign.h pagesize.h \
  util.h error.h
properties.o: properties.c properties.h property.h lstring.h bool.h \
  llist.h element.h inputfile.h file.h outputfile.h point.h
readdirection.o: readdirection.c readdirection.h lstring.h
rectangle.o: rectangle.c rectangle.h point.h bool.h
sequence.o: sequence.c sequence.h
side.o: side.c side.h lstring.h
system.o: system.c system.h bool.h util.h error.h lstring.h version.h
text2ps.o: text2ps.c
textalign.o: textalign.c textalign.h lstring.h
toolkit.o: toolkit.c toolkit.h bool.h
Vector.o: Vector.c Vector.h bool.h llist.h element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h code.h typename.h \
  lstring.h
version.o: version.c version.h
