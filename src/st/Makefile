include ../Config.tmpl

TDOBJECTS =     tdtable.o tdwindow.o tdviewer.o
 
TUOBJECTS =     tutable.o tuwindow.o tuviewer.o
 
FEOBJECTS =     fetable.o fewindow.o feviewer.o
 
TBOBJECTS = $(TDOBJECTS) $(TUOBJECTS) $(FEOBJECTS)

tcmt$(EXEEXTENSION):   $(TBOBJECTS) tcmt.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TBOBJECTS) tcmt.o \
	$(LIB_DIR)/libtable.a $(LIB_DIR)/libeditor.a $(LIB_DIR)/libgui.a \
         -o $@ $(LDFLAGS) $(LIB_DIR)/libglobal.a $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tgt$(EXEEXTENSION):    $(OBJECTS) tableeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) tableeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

ttdt$(EXEEXTENSION):   $(TDOBJECTS) tdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TDOBJECTS) tdeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

ttut$(EXEEXTENSION):   $(TUOBJECTS) tueditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(TUOBJECTS) tueditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tfet$(EXEEXTENSION):   $(FEOBJECTS) feeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(FEOBJECTS) feeditor.o -o $@ \
	$(LDFLAGS) -ltable -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
