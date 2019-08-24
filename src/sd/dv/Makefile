include ../../Config.tmpl
 
PARSER= cardconstraint.tab.o\
        cardconstraint.o

EROBJECTS = $(PARSER)\
	binaryrelationship.o\
	c1arrow.o\
	c2r2line.o\
	entitytype.o\
	erchecks.o\
	erdiagram.o\
	ergraph.o\
	erstubs.o\
	erview.o\
	erviewer.o\
	erwindow.o\
	function.o\
	isarelationship.o\
	relationshipnode.o\
	taxonomyjunction.o\
	updatereaddirectioncmd.o\
	valuetype.o

SSCROBJECTS = doubleclassbox.o\
	tripleclassbox.o\
        updateclassboxtypecmd.o
 
CROBJECTSX = classnode.o\
	componentfunction.o\
	crchecks.o\
	crdiagram.o\
	crgraph.o\
	crviewer.o\
	crwindow.o\
	modejunction.o

SESDOBJECTSX = ssdaggregationedge.o\
	ssdaggregationnode.o\
	ssdassociationlinkedge.o\
	ssdassociationnode.o\
	ssdbinaryassociationedge.o\
        ssdchecks.o\
        ssdclassnode.o\
        ssdcompositionedge.o\
	ssddoubleclassbox.o\
	ssddoubleobjectbox.o\
	ssdgeneralizationedge.o\
	ssdgeneralizationnode.o\
        ssdgraph.o\
	ssdobjectlinkedge.o\
	ssdobjectnode.o\
	ssdparticipantlinkedge.o\
	ssdr2line.o\
	ssdrcline.o\
	ssdsingleclassbox.o\
	ssdsingleobjectbox.o\
        ssdstubs.o\
	ssdtripleclassbox.o\
	ssdupdateclassboxtypecmd.o\
	ssdupdateclassboxpropertycmd.o\
        ssdviewer.o

SSDOBJECTSX = ssddiagram.o\
        ssdwindow.o

ESDOBJECTSX = esddiagram.o\
        esdwindow.o

UCDOBJECTSX=ucchecks.o\
	ucdactornode.o\
	ucdbinaryassociationedge.o\
	ucdboundarybox.o\
	ucdiagram.o\
	ucdgeneralizationedge.o\
	ucdsingleclassbox.o\
	ucdsystemnode.o \
	ucdusecasenode.o\
	ucgraph.o\
	ucupdateactortypecmd.o\
	ucviewer.o\
	ucwindow.o

CBDOBJECTSX=cbactor.o\
	c2r2mlistline.o\
	cbchecks.o\
	cbdiagram.o\
	cbgraph.o\
	cbdmessage.o\
	cbinteraction.o\
	cbclasslinkedge.o\
	cbobjectlinkedge.o\
	cbclassnode.o\
	cbsingleclassbox.o\
	ssdsingleclassbox.o\
		ssddoubleclassbox.o\
		ssdtripleclassbox.o\
		doubleclassbox.o\
		tripleclassbox.o\
	cbobjectnode.o\
	ucdsingleclassbox.o\
	ssdsingleobjectbox.o\
	cbupdateactortypecmd.o\
	ssdupdateclassboxpropertycmd.o\
	updatemessagedirectioncmd.o\
	cbstubs.o\
	cbviewer.o\
	cbwindow.o

SQDOBJECTSX=cbactor.o\
	sqchecks.o\
	sqdiagram.o\
	sqgraph.o\
	sqanchorlinkedge.o\
	cbdmessage.o\
	cbclassnode.o\
	lifeline.o\
	apline.o\
	createfoccmd.o\
	createl2ledgecmd.o\
	pullfoccmd.o\
	pullshapecmd.o\
	cbsingleclassbox.o\
	ssdsingleclassbox.o\
		ssddoubleclassbox.o\
		ssdtripleclassbox.o\
		doubleclassbox.o\
		tripleclassbox.o\
	sqobjectnode.o\
	ucdsingleclassbox.o\
	ssdsingleobjectbox.o\
	cbupdateactortypecmd.o\
	ssdupdateclassboxpropertycmd.o\
	sqstubs.o\
	sqviewer.o\
	sqwindow.o

CROBJECTS = $(EROBJECTS) $(SSCROBJECTS) $(CROBJECTSX)

ESDOBJECTS = $(EROBJECTS) $(SSCROBJECTS) $(SESDOBJECTSX) $(ESDOBJECTSX)

SSDOBJECTS = $(EROBJECTS) $(SSCROBJECTS) $(SESDOBJECTSX) $(SSDOBJECTSX)

UCDOBJECTS = $(EROBJECTS) $(UCDOBJECTSX)

CBDOBJECTS = $(EROBJECTS) $(CBDOBJECTSX)

SQDOBJECTS = $(EROBJECTS) $(SQDOBJECTSX)

DVOBJECTS = $(EROBJECTS) $(SSCROBJECTS) $(CROBJECTSX) $(CBDOBJECTSX) \
	$(SESDOBJECTSX) $(ESDOBJECTSX) $(SSDOBJECTSX) $(UCDOBJECTSX) \
	$(SQDOBJECTSX)

tcmdv$(EXEEXTENSION):  $(DVOBJECTS) tcmdv.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(DVOBJECTS) \
	$(LDFLAGS) -ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmdv.o -o $@ $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmdv.a: $(DVOBJECTS)
	$(AR) $@ $(DVOBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

terd$(EXEEXTENSION):   $(EROBJECTS) ereditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(EROBJECTS) ereditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tcrd$(EXEEXTENSION):   $(CROBJECTS) creditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(CROBJECTS) creditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tesd$(EXEEXTENSION):   $(ESDOBJECTS) esdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(ESDOBJECTS) esdeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tssd$(EXEEXTENSION):   $(SSDOBJECTS) ssdeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(SSDOBJECTS) ssdeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tucd$(EXEEXTENSION):   $(UCDOBJECTS) uceditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(UCDOBJECTS) uceditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tcbd$(EXEEXTENSION):   $(CBDOBJECTS) cbeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(CBDOBJECTS) cbeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tsqd$(EXEEXTENSION):   $(SQDOBJECTS) sqeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(SQDOBJECTS) sqeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	chmod a+rx $@
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
apline.o: apline.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoclist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/assoc.h lifeline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h apline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h sqobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h \
  sqanchorlinkedge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h
binaryrelationship.o: binaryrelationship.c binaryrelationship.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h erparse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
c1arrow.o: c1arrow.c c1arrow.h \
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
c2r2line.o: c2r2line.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h erviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  updatereaddirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
c2r2mlistline.o: c2r2mlistline.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h c2r2mlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4tlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  cbobjectlinkedge.h cbinteraction.h cbclasslinkedge.h cbdmessage.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h cbviewer.h \
  updatereaddirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  updatemessagedirectioncmd.h
cbactor.o: cbactor.c cbactor.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
cbchecks.o: cbchecks.c cbchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h
cbclasslinkedge.o: cbclasslinkedge.c cbclasslinkedge.h cbinteraction.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
cbclassnode.o: cbclassnode.c cbclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
cbdiagram.o: cbdiagram.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  cbsingleclassbox.h ssdsingleobjectbox.h c2r2mlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4tlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h cbclassnode.h \
  cbobjectnode.h ucdsingleclassbox.h cbactor.h cbclasslinkedge.h \
  cbinteraction.h binaryrelationship.h cbobjectlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h cbgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h cbwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h cbviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h cbchecks.h \
  erchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  cbdiagram.h erdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h cbdmessage.h
cbdmessage.o: cbdmessage.c cbdmessage.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
cbeditor.o: cbeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h cbwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
cbgraph.o: cbgraph.c cbgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
cbinteraction.o: cbinteraction.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbinteraction.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  cbdmessage.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h cbviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h
cbobjectlinkedge.o: cbobjectlinkedge.c cbobjectlinkedge.h cbinteraction.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
cbobjectnode.o: cbobjectnode.c cbobjectnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
cbsingleclassbox.o: cbsingleclassbox.c cbclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbsingleclassbox.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h
cbstubs.o: cbstubs.c cbstubs.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h cbviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h
cbupdateactortypecmd.o: cbupdateactortypecmd.c cbupdateactortypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
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
  ucdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h
cbviewer.o: cbviewer.c cbviewer.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h cbwindow.h \
  erwindow.h cbupdateactortypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  ssdupdateclassboxpropertycmd.h updatemessagedirectioncmd.h cbdmessage.h
cbwindow.o: cbwindow.c cbdiagram.h erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h cbviewer.h \
  cbgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h cbstubs.h \
  erstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h cbwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ActorBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ActorObjectBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ObjectBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/R2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickMan.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickManObject.xbm
classnode.o: classnode.c classnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h crgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
componentfunction.o: componentfunction.c componentfunction.h function.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h crgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
crchecks.o: crchecks.c crchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h crgraph.h ergraph.h \
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
crdiagram.o: crdiagram.c crgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h crwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h crviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h crchecks.h \
  erchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  doubleclassbox.h c1arrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  componentfunction.h function.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h isarelationship.h \
  modejunction.h taxonomyjunction.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h crdiagram.h \
  erdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h classnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h
createfoccmd.o: createfoccmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h createfoccmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h lifeline.h \
  sqobjectnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h
createl2ledgecmd.o: createl2ledgecmd.c \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  createl2ledgecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h sqviewer.h \
  erviewer.h
creditor.o: creditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h crwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
crgraph.o: crgraph.c crgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
crviewer.o: crviewer.c crwindow.h erwindow.h \
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
  updateclassboxtypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h crviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h
crwindow.o: crwindow.c crwindow.h erwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h crdiagram.h \
  erdiagram.h erviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h classnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h crviewer.h \
  crgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C1Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedC1Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Dot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/IsaArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TripleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleArrow.xbm
doubleclassbox.o: doubleclassbox.c doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
entitytype.o: entitytype.c entitytype.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
erchecks.o: erchecks.c erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  relationshipnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  binaryrelationship.h \
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
erdiagram.o: erdiagram.c ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h erview.h \
  erwindow.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h c1arrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h entitytype.h \
  relationshipnode.h valuetype.h taxonomyjunction.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h function.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  binaryrelationship.h isarelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/replacedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/finddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  erdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h
ereditor.o: ereditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h erwindow.h \
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
ergraph.o: ergraph.c ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
erstubs.o: erstubs.c erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h erdiagram.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mstring.h
erview.o: erview.c erview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h
erviewer.o: erviewer.c erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h erview.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  updatereaddirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
erwindow.o: erwindow.c erwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h erdiagram.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/config.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C1Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Dot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Diamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Ellipse.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/IsaArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleArrow.xbm
esddiagram.o: esddiagram.c ssdgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h esdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h ssdviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  ssdchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  ssddoubleclassbox.h doubleclassbox.h ssdsingleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssdsingleobjectbox.h ssddoubleobjectbox.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h ssdr2line.h \
  ssdrcline.h ssdbinaryassociationedge.h binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  ssdobjectlinkedge.h ssdparticipantlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  ssdgeneralizationedge.h isarelationship.h ssdassociationlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  ssdobjectnode.h ssdgeneralizationnode.h taxonomyjunction.h \
  ssdaggregationnode.h ssdassociationnode.h relationshipnode.h \
  ssdaggregationedge.h ssdcompositionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hexagon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h esddiagram.h \
  erdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
esdeditor.o: esdeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h esdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
esdwindow.o: esdwindow.c ssdstubs.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h esddiagram.h \
  erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h ssdviewer.h \
  ssdgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h esdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/CXRelationshipLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Diamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/WhiteDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm
function.o: function.c function.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h erparse.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
isarelationship.o: isarelationship.c isarelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
lifeline.o: lifeline.c lifeline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h sqobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/intersect.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h sqviewer.h \
  erviewer.h
modejunction.o: modejunction.c modejunction.h taxonomyjunction.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h crgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
pullfoccmd.o: pullfoccmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h pullfoccmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h lifeline.h \
  sqobjectnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h
pullshapecmd.o: pullshapecmd.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h pullshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h lifeline.h \
  sqobjectnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h
relationshipnode.o: relationshipnode.c relationshipnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h
sqanchorlinkedge.o: sqanchorlinkedge.c sqanchorlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h sqgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
sqchecks.o: sqchecks.c sqchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h
sqdiagram.o: sqdiagram.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  cbsingleclassbox.h ssdsingleobjectbox.h c2r2mlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4tlistline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h cbclassnode.h \
  apline.h sqobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h \
  ucdsingleclassbox.h lifeline.h cbactor.h cbclasslinkedge.h \
  cbinteraction.h binaryrelationship.h cbobjectlinkedge.h \
  sqanchorlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h sqgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h sqwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h sqviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h sqchecks.h \
  erchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  sqdiagram.h erdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h cbdmessage.h
sqeditor.o: sqeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h sqwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
sqgraph.o: sqgraph.c sqgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
sqobjectboxlifeline.o: sqobjectboxlifeline.c lifeline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
sqobjectnode.o: sqobjectnode.c sqobjectnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h sqgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
sqstubs.o: sqstubs.c sqstubs.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h sqviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h
sqviewer.o: sqviewer.c sqviewer.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h sqwindow.h \
  erwindow.h cbupdateactortypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  ssdupdateclassboxpropertycmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h apline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h lifeline.h \
  createfoccmd.h pullfoccmd.h pullshapecmd.h sqobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/anchorpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/createedgecmd.h \
  createl2ledgecmd.h sqanchorlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h
sqwindow.o: sqwindow.c sqdiagram.h erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h sqviewer.h \
  sqgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h sqstubs.h \
  erstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h sqwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ActorBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ActorObjectBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ObjectBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/R2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickMan.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickManObject.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/FOCBox.xbm
ssdaggregationedge.o: ssdaggregationedge.c ssdaggregationedge.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ssdaggregationnode.o: ssdaggregationnode.c ssdaggregationnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ssdassociationlinkedge.o: ssdassociationlinkedge.c \
  ssdassociationlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ssdassociationnode.o: ssdassociationnode.c ssdassociationnode.h \
  relationshipnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ssdbinaryassociationedge.o: ssdbinaryassociationedge.c \
  ssdbinaryassociationedge.h binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ssdchecks.o: ssdchecks.c ssdchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h
ssdclassnode.o: ssdclassnode.c ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ssdcompositionedge.o: ssdcompositionedge.c ssdcompositionedge.h \
  binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ssddiagram.o: ssddiagram.c ssdgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h ssdviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  ssdchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  ssddoubleclassbox.h doubleclassbox.h ssdsingleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssdsingleobjectbox.h ssddoubleobjectbox.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h ssdr2line.h \
  ssdrcline.h ssdbinaryassociationedge.h binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  ssdobjectlinkedge.h ssdparticipantlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  ssdgeneralizationedge.h isarelationship.h ssdassociationlinkedge.h \
  ssdaggregationedge.h ssdcompositionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  ssdobjectnode.h ssdgeneralizationnode.h taxonomyjunction.h \
  ssdaggregationnode.h ssdassociationnode.h relationshipnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hexagon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h ssddiagram.h \
  erdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
ssddoubleclassbox.o: ssddoubleclassbox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h
ssddoubleobjectbox.o: ssddoubleobjectbox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h ssdobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  ssddoubleobjectbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h
ssdeditor.o: ssdeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h ssdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
ssdgeneralizationedge.o: ssdgeneralizationedge.c ssdgeneralizationedge.h \
  isarelationship.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ssdgeneralizationnode.o: ssdgeneralizationnode.c ssdgeneralizationnode.h \
  taxonomyjunction.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ssdgraph.o: ssdgraph.c ssdgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
ssdobjectlinkedge.o: ssdobjectlinkedge.c ssdobjectlinkedge.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  ssddiagram.h erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h ssdviewer.h
ssdobjectnode.o: ssdobjectnode.c ssdobjectnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ssdparticipantlinkedge.o: ssdparticipantlinkedge.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  ssdparticipantlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
ssdr2line.o: ssdr2line.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  ssdobjectlinkedge.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h ssdr2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h erviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  updatereaddirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
ssdrcline.o: ssdrcline.c ssdrcline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
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
  ssdparticipantlinkedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/c1edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h
ssdsingleclassbox.o: ssdsingleclassbox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cbclassnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
ssdsingleobjectbox.o: ssdsingleobjectbox.c ssdsingleobjectbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
ssdstubs.o: ssdstubs.c ssdstubs.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h ssdviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h
ssdtripleclassbox.o: ssdtripleclassbox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssddoubleclassbox.h doubleclassbox.h ssdclassnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
ssdupdateclassboxpropertycmd.o: ssdupdateclassboxpropertycmd.c \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  ssdupdateclassboxpropertycmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
ssdupdateclassboxtypecmd.o: ssdupdateclassboxtypecmd.c \
  ssdupdateclassboxtypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
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
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  ssdsingleobjectbox.h ssddoubleobjectbox.h
ssdviewer.o: ssdviewer.c esdwindow.h erwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdwindow.h \
  ssdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ssddoubleclassbox.h doubleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  ssdtripleclassbox.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  ssdupdateclassboxtypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  ssdupdateclassboxpropertycmd.h ssdviewer.h erviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h
ssdwindow.o: ssdwindow.c ssdstubs.h erstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h ssddiagram.h \
  erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h ssdviewer.h \
  ssdgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h ssdwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Aggregation.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Composition.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Diamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DoubleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/WhiteDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ObjectBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ObjectDoubleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/R2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TripleBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/CXRelationshipLine.xbm
taxonomyjunction.o: taxonomyjunction.c taxonomyjunction.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
tcmdv.o: tcmdv.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h crwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ssdwindow.h \
  ucwindow.h esdwindow.h cbwindow.h sqwindow.h
tripleclassbox.o: tripleclassbox.c tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode2.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stringlistnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
ucchecks.o: ucchecks.c ucchecks.h erchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h
ucdactornode.o: ucdactornode.c ucgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ucdactornode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
ucdbinaryassociationedge.o: ucdbinaryassociationedge.c \
  ucdbinaryassociationedge.h binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ucgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ucdboundarybox.o: ucdboundarybox.c ucdboundarybox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h
ucdgeneralizationedge.o: ucdgeneralizationedge.c ucdgeneralizationedge.h \
  isarelationship.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ucgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
ucdiagram.o: ucdiagram.c ucgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h ucwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h ucviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h ucchecks.h \
  erchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  ucdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h c2r2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t4line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t2line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/t1line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h ucdactornode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  ucdusecasenode.h ucdbinaryassociationedge.h binaryrelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h ucdboundarybox.h \
  ucdgeneralizationedge.h isarelationship.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  ucdsystemnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h ucdiagram.h \
  erdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h
ucdsingleclassbox.o: ucdsingleclassbox.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  ucdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h
ucdsystemnode.o: ucdsystemnode.c ucdsystemnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ucgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ucdusecasenode.o: ucdusecasenode.c ucdusecasenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ucgraph.h \
  ergraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
uceditor.o: uceditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h ucwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
ucgraph.o: ucgraph.c ucgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
ucupdateactortypecmd.o: ucupdateactortypecmd.c ucupdateactortypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
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
  ucdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h
ucviewer.o: ucviewer.c ucwindow.h erwindow.h \
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
  ucdsingleclassbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/stickman.h \
  ucupdateactortypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h ucviewer.h \
  erviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h
ucwindow.o: ucwindow.c ucdiagram.h erdiagram.h erviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h ucviewer.h \
  ucgraph.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h ucwindow.h \
  erwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BoundaryBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/StickMan.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/C2Line.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Ellipse.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyOpenArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm
updateclassboxtypecmd.o: updateclassboxtypecmd.c updateclassboxtypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h tripleclassbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/triplebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/doublebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h doubleclassbox.h
updatemessagedirectioncmd.o: updatemessagedirectioncmd.c \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatemessagedirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h cbdmessage.h
updatereaddirectioncmd.o: updatereaddirectioncmd.c \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  updatereaddirectioncmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
valuetype.o: valuetype.c valuetype.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
