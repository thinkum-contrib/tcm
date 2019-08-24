include ../../Config.tmpl
 
GTOBJECTS = textedge.o\
	textnode.o\
	textroot.o\
	trdiagram.o\
	trgraph.o\
	trview.o\
	trviewer.o\
	trwindow.o
 
FDOBJECTS = $(GTOBJECTS)\
	fddiagram.o\
	fdviewer.o\
	fdwindow.o

TROBJECTS = $(FDOBJECTS)
 
tcmtr$(EXEEXTENSION):  $(TROBJECTS) tcmtr.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TROBJECTS) \
	-ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmtr.o -o $@ $(LDFLAGS) $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmtr.a: $(TROBJECTS)
	$(AR) $@ $(TROBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

tgtt$(EXEEXTENSION):   $(GTOBJECTS) gteditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(GTOBJECTS) gteditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tfrt$(EXEEXTENSION):   $(FDOBJECTS) fdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(FDOBJECTS) fdeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
