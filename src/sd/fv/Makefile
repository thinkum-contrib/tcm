include ../../Config.tmpl

PARSER = cardconstraint.tab.o\
	cardconstraint.o

DFOBJECTS = bidirectionaldataflow.o\
	dataflow.o\
	dataprocess.o\
	datastore.o\
	dfchecks.o\
	dfdiagram.o\
	dfedge.o\
	dfgraph.o\
	dfnode.o\
	dfprocess.o\
	dfstore.o\
	dfstubs.o\
	dfviewer.o\
	dfwindow.o\
	externalentity.o\
	splitmergenode.o
 
DCFOBJECTS = $(DFOBJECTS)\
	dcfchecks.o\
	dcfdiagram.o\
	dcfgraph.o\
	dcfstubs.o\
	dcfviewer.o\
	dcfwindow.o\
	continuousdataflow.o\
	continuouseventflow.o\
	controlprocess.o\
	eventflow.o\
	eventstore.o
 
SNOBJECTS = connectionend.o\
	connectionstart.o\
	controlleddatastream.o\
	datastream.o\
	endc1arrow.o\
	snchecks.o\
	sndiagram.o\
	sngraph.o\
	snnode.o\
	snprocess.o\
	snviewer.o\
	snwindow.o\
	statevector.o\
	startc1line.o

FVOBJECTS = $(DCFOBJECTS) $(SNOBJECTS)

tcmfv$(EXEEXTENSION):  $(FVOBJECTS) tcmfv.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(FVOBJECTS) \
	-ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmfv.o -o $@ $(LDFLAGS) $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmfv.a: $(FVOBJECTS)
	$(AR) $@ $(FVOBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

tdfd$(EXEEXTENSION):   $(DFOBJECTS) dfeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(DFOBJECTS) dfeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tsnd$(EXEEXTENSION):   $(SNOBJECTS) $(PARSER) sneditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(SNOBJECTS) $(PARSER) sneditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tefd$(EXEEXTENSION):  $(DCFOBJECTS) dcfeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(DCFOBJECTS) dcfeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

cardconstraint.tab.c: cardconstraint.y cardconstraint.l
	$(YACC) --debug -p cardconstraint -d cardconstraint.y
	$(LEX) -Pcardconstraint -ocardconstraint.c cardconstraint.l
cardconstraint.tab.h: cardconstraint.y cardconstraint.l
	$(YACC) --debug -p cardconstraint -d cardconstraint.y
	$(LEX) -Pcardconstraint -ocardconstraint.c cardconstraint.l
cardconstraint.c: cardconstraint.l cardconstraint.y
	$(LEX) -Pcardconstraint -ocardconstraint.c cardconstraint.l
cardconstraint.o:
	$(Cc) -c cardconstraint.c
cardconstraint.tab.o: cardconstraint.tab.h
	$(Cc) -c cardconstraint.tab.c

clean: xclean

xclean::
	$(RM) cardconstraint.c cardconstraint.tab.*

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
