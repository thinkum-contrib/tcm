include ../Config.tmpl

CFLAGS += -DTCM_INSTALL_DIR=\"$(TCM_INSTALL_DIR)\"

OBJECTS=command.o\
	document.o\
	drawingarea.o\
	drawwindow.o\
	editstubs.o\
	editwindow.o\
	grid.o\
	inlineeditor.o\
        helper.o\
	printer.o\
	scaler.o\
	stringlist.o\
	viewer.o

STARTOBJECTS=helper.o\
	startupwindow.o\
	startup.o

libeditor.a: $(OBJECTS) 
	$(AR) $@ $(OBJECTS) 
	$(CHMODPLUSX) $@
	$(MV) $@ $(LIB_DIR)

libeditor.so: $(OBJECTS) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SHAREDFLAG) $(OBJECTS) -o $@
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(LIB_DIR)

tcm$(EXEEXTENSION): $(STARTOBJECTS)
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(STARTOBJECTS) -o $@ \
	$(LDFLAGS) -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
