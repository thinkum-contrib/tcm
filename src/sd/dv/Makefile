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
