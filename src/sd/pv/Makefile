include ../../Config.tmpl
 
CPOBJECTS = cpdcomponentnode.o\
	cpdinterfacenode.o\
	cpddependencyedge.o\
	cpdrealizationedge.o\
	dpdresourcenode.o\
	dpdcommunicationedge.o\
	cpdiagram.o\
	cpgraph.o\
	cpviewer.o\
	cpwindow.o

DPOBJECTS = dpdiagram.o\
	dpwindow.o

PVOBJECTS = $(CPOBJECTS) $(DPOBJECTS)

tcmpv$(EXEEXTENSION):  $(PVOBJECTS) tcmpvo
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(PVOBJECTS) \
	-ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmpv.o -o $@ $(LDFLAGS) $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmpv.a: $(PVOBJECTS)
	$(AR) $@ $(PVOBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

tcpd$(EXEEXTENSION):   $(CPOBJECTS) cpeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(CPOBJECTS) cpeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tdpd$(EXEEXTENSION):   $(PVOBJECTS) dpeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(PVOBJECTS) dpeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

clean: xclean

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
