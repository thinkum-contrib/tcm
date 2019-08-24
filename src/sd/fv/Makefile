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
bidirectionaldataflow.o: bidirectionaldataflow.c bidirectionaldataflow.h \
  dataflow.h dfedge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
connectionend.o: connectionend.c connectionend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h erparse.h
connectionstart.o: connectionstart.c connectionstart.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h erparse.h
continuousdataflow.o: continuousdataflow.c continuousdataflow.h \
  dataflow.h dfedge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
continuouseventflow.o: continuouseventflow.c continuouseventflow.h \
  eventflow.h dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
controlleddatastream.o: controlleddatastream.c controlleddatastream.h \
  snnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
controlprocess.o: controlprocess.c controlprocess.h dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
dataflow.o: dataflow.c dataflow.h dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
dataprocess.o: dataprocess.c dataprocess.h dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
datastore.o: datastore.c datastore.h dfstore.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
datastream.o: datastream.c datastream.h snnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
dcfchecks.o: dcfchecks.c dcfchecks.h dfchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h controlprocess.h \
  dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h dataprocess.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
dcfdiagram.o: dcfdiagram.c dcfwindow.h dfwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h dcfviewer.h \
  dfviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h dcfstubs.h \
  dfstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h dcfchecks.h \
  dfchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  externalentity.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h datastore.h \
  dfstore.h eventstore.h dataprocess.h dfprocess.h controlprocess.h \
  splitmergenode.h bidirectionaldataflow.h dataflow.h dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  continuousdataflow.h continuouseventflow.h eventflow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/square.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/circle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/horizontalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h dcfdiagram.h \
  dfdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/togglelistdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/promptdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h
dcfeditor.o: dcfeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h dcfwindow.h \
  dfwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
dcfgraph.o: dcfgraph.c dcfgraph.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
dcfstubs.o: dcfstubs.c dcfstubs.h dfstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h dcfdiagram.h \
  dfdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h dcfviewer.h \
  dfviewer.h
dcfviewer.o: dcfviewer.c dcfwindow.h dfwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  dcfdiagram.h dfdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h dcfviewer.h \
  dfviewer.h
dcfwindow.o: dcfwindow.c dcfwindow.h dfwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dcfdiagram.h \
  dfdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h dcfviewer.h \
  dfviewer.h dcfgraph.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h dcfstubs.h \
  dfstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/HorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TopLabeledCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedTopLabeledCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedHorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleHeadedArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedDoubleHeadedArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Square.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm
dfchecks.o: dfchecks.c dfchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dataprocess.h \
  dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
dfdiagram.o: dfdiagram.c dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dfviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h dfwindow.h \
  dfstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h dfchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/replacedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/finddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/texteditdialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/textviewdialog.h \
  externalentity.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h dataprocess.h \
  dfprocess.h datastore.h dfstore.h splitmergenode.h \
  bidirectionaldataflow.h dataflow.h dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h dfdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/square.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/circle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/horizontalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h
dfedge.o: dfedge.c dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
dfeditor.o: dfeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h dfwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
dfgraph.o: dfgraph.c dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dataprocess.h \
  dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
dfnode.o: dfnode.c dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
dfprocess.o: dfprocess.c dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
dfstore.o: dfstore.c dfstore.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
dfstubs.o: dfstubs.c dfstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h dfdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h dfviewer.h
dfviewer.o: dfviewer.c dfviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h dataprocess.h \
  dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h dfwindow.h \
  dfdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h
dfwindow.o: dfwindow.c dfwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dfdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h dfviewer.h \
  dfstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/liteclue.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/HorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TopLabeledCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Square.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm
endc1arrow.o: endc1arrow.c endc1arrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h
eventflow.o: eventflow.c eventflow.h dfedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dataprocess.h \
  dfprocess.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
eventstore.o: eventstore.c eventstore.h dfstore.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dcfgraph.h \
  dfgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
externalentity.o: externalentity.c externalentity.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
snchecks.o: snchecks.c snchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
sndiagram.o: sndiagram.c snviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h snwindow.h \
  sngraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  snprocess.h snnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h snchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  datastream.h controlleddatastream.h statevector.h connectionstart.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h connectionend.h \
  startc1line.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  endc1arrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/leftlinecircle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h sndiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/circle.h
sneditor.o: sneditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h snwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
sngraph.o: sngraph.c sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
snnode.o: snnode.c snnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
snprocess.o: snprocess.c snprocess.h snnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
snviewer.o: snviewer.c snviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h snwindow.h
snwindow.o: snwindow.c snwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sndiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h snviewer.h \
  sngraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StartC1Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EndC1Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MediumCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MediumLeftLineCircle.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MediumDiamond.xbm
splitmergenode.o: splitmergenode.c splitmergenode.h dfnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dfgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
startc1line.o: startc1line.c startc1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h
statevector.o: statevector.c statevector.h snnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h sngraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
tcmfv.o: tcmfv.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h dcfwindow.h \
  dfwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h snwindow.h
