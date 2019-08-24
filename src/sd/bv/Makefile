include ../../Config.tmpl
 
PSOBJECTS = pschecks.o\
	psdiagram.o\
	psgraph.o\
	psprocess.o\
	psstubs.o\
	psviewer.o\
	pswindow.o\
	urlabeledbox.o
 
STOBJECTS = decisionpoint.o\
	draghlinecmd.o\
	dragstlabelcmd.o\
	initialstate.o\
	initialstatebox.o\
	state.o\
	stchecks.o\
	stdiagram.o\
	stgraph.o\
	stnode.o\
	stviewer.o\
	stwindow.o\
	transition.o\
	transitionarrow.o

# uncomment the next lines to include experimental translation to model checkers
#STOBJECTS += eventset.o\
#	klocation.o\
#	kronos.o\
#	ptrset.o\
#	ktransition.o\
#	relevantset.o\
#	smv.o
#CFLAGS += -DMODELCHECK

SCOBJECTS = $(PARSER)\
	adsclock.o\
	adsclockconstraint.o\
	adsproperty.o\
	adsvariable.o\
	scchecks.o\
	scdandedge.o\
	scdandline.o\
	scdandstate.o\
	scdandstatebox.o\
	scdcreateandlinecmd.o\
	scddecisionstate.o\
	scddefaultstate.o\
	scdfinalstate.o\
	scdiagram.o\
	scdorstate.o\
	scdsynchronizationstate.o\
	scdtransitionedge.o\
	scgraph.o\
	scnode.o\
	scviewer.o\
	scwindow.o

RPOBJECTS = event.o\
	processgraphnode.o\
	processgraphroot.o\
	rpdiagram.o\
	rpgraph.o\
	rpupdatenodeshapetypecmd.o\
	rpviewer.o\
	rpwindow.o

PARSER = adsedgelabel.tab.o\
        adsedgelabel.o\
        adsedgelabelevaluation.tab.o\
        adsedgelabelevaluation.o\
        adsmcoutput.tab.o\
        adsmcoutput.o\
	adsltlformula.tab.o\
	adsltlformula.o

ATOBJECTS = $(PARSER)\
	atchecks.o \
	atdactionstatenode.o \
	atddecisionstatenode.o \
	atdfinalstatenode.o \
	atdwaitstatenode.o \
	atdinitialstatenode.o \
	atdsynchronizationnode.o \
	atdtransitionedge.o \
	atdiagram.o\
	atgraph.o\
	atviewer.o\
	atupdatenodeshapetypecmd.o\
	atwindow.o\
	adsactivity.o\
	adscks.o\
	adsclock.o\
	adsclockconstraint.o\
	adsclockmanager.o\
	adseliminatepseudostatenodes.o\
	adshyperedge.o\
	adshypergraph.o\
	adsproperty.o\
	adspropertyvaluation.o\
	adssemantics.o\
	adstransition.o\
	adsvaluation.o\
	adsvariable.o\
	bag.o

BVOBJECTS = $(STOBJECTS) $(SCOBJECTS) $(PSOBJECTS) $(RPOBJECTS) $(ATOBJECTS)
 
tcmbv$(EXEEXTENSION):  $(BVOBJECTS) tcmbv.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(BVOBJECTS) \
	-ldiagram -leditor -lguix $(LIB_DIR)/libglobal.a \
	tcmbv.o -o $@ $(LDFLAGS) $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

libtcmbv.a: $(BVOBJECTS)
	$(AR) $@ $(BVOBJECTS)
	$(CHMODPLUSX) $@
	$(RANLIB) $@
	$(MV) $@ $(LIB_DIR)

tpsd$(EXEEXTENSION):   $(PSOBJECTS) pseditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(PSOBJECTS) pseditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tstd$(EXEEXTENSION):   $(STOBJECTS) steditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(STOBJECTS) steditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tscd$(EXEEXTENSION):   $(SCOBJECTS) sceditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(SCOBJECTS) sceditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

trpg$(EXEEXTENSION):   $(RPOBJECTS) rpeditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(RPOBJECTS) rpeditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

tatd$(EXEEXTENSION):   $(ATOBJECTS) ateditor.o
	$(PURIFY) $(CC) $(CFLAGS) $(CPPFLAGS) $(ATOBJECTS) ateditor.o -o $@ \
	$(LDFLAGS) -ldiagram -leditor -lgui -lglobal $(LDLIBS)
	$(CHMODPLUSX) $@
	$(STRIP) $@
	$(MV) $@ $(BIN_DIR)

adsedgelabel.tab.c: adsedgelabel.y adsedgelabel.l
	$(YACC) -p adsedgelabel -d adsedgelabel.y
	$(LEX) -Padsedgelabel -oadsedgelabel.c adsedgelabel.l
adsedgelabel.tab.h: adsedgelabel.y adsedgelabel.l
	$(YACC) -p adsedgelabel -d adsedgelabel.y
	$(LEX) -Padsedgelabel -oadsedgelabel.c adsedgelabel.l
adsedgelabel.c: adsedgelabel.l adsedgelabel.y
	$(LEX) -Padsedgelabel -oadsedgelabel.c adsedgelabel.l
adsedgelabel.o:
	$(Cc) -c adsedgelabel.c
adsedgelabel.tab.o: adsedgelabel.tab.h
	$(Cc) -c adsedgelabel.tab.c


adsedgelabelevaluation.tab.c: adsedgelabelevaluation.y adsedgelabelevaluation.l
	$(YACC) --debug -p adsedgelabelevaluation -d adsedgelabelevaluation.y
	$(LEX) -Padsedgelabelevaluation -oadsedgelabelevaluation.c adsedgelabelevaluation.l
adsedgelabelevaluation.tab.h: adsedgelabelevaluation.y adsedgelabelevaluation.l
	$(YACC) --debug -p adsedgelabelevaluation -d adsedgelabelevaluation.y
	$(LEX) -Padsedgelabelevaluation -oadsedgelabelevaluation.c adsedgelabelevaluation.l
adsedgelabelevaluation.c: adsedgelabelevaluation.l adsedgelabelevaluation.y
	$(LEX) -Padsedgelabelevaluation -oadsedgelabelevaluation.c adsedgelabelevaluation.l
adsedgelabelevaluation.o:
	$(Cc) -c adsedgelabelevaluation.c
adsedgelabelevaluation.tab.o: adsedgelabelevaluation.tab.h
	$(Cc) -c adsedgelabelevaluation.tab.c
 
adsmcoutput.tab.c: adsmcoutput.y adsmcoutput.l
	$(YACC) -p adsmcoutput -d adsmcoutput.y
	$(LEX) -Padsmcoutput -oadsmcoutput.c adsmcoutput.l
adsmcoutput.tab.h: adsmcoutput.y adsmcoutput.l
	$(YACC) -p adsmcoutput -d adsmcoutput.y
	$(LEX) -Padsmcoutput -oadsmcoutput.c adsmcoutput.l
adsmcoutput.c: adsmcoutput.l adsmcoutput.y
	$(LEX) -Padsmcoutput -oadsmcoutput.c adsmcoutput.l
adsmcoutput.o:
	$(Cc) -c adsmcoutput.c
adsmcoutput.tab.o: adsmcoutput.tab.h
	$(Cc) -c adsmcoutput.tab.c

adsltlformula.tab.c: adsltlformula.y adsltlformula.l
	$(YACC) -p adsltlformula -d adsltlformula.y
	$(LEX) -Padsltlformula -oadsltlformula.c adsltlformula.l
adsltlformula.tab.h: adsltlformula.y adsltlformula.l
	$(YACC) -p adsltlformula -d adsltlformula.y
	$(LEX) -Padsltlformula -oadsltlformula.c adsltlformula.l
adsltlformula.c: adsltlformula.l adsltlformula.y
	$(LEX) -Padsltlformula -oadsltlformula.c adsltlformula.l
adsltlformula.o:
	$(Cc) -c adsltlformula.c
adsltlformula.tab.o: adsltlformula.tab.h
	$(Cc) -c adsltlformula.tab.c
 

clean: xclean

xclean::
	$(RM) adsedgelabel.c adsedgelabel.tab.*
	$(RM) adsedgelabelevaluation.c adsedgelabelevaluation.tab.*
	$(RM) adsmcoutput.c adsmcoutput.tab.*
	$(RM) adsltlformula.c adsltlformula.tab.*

depend: xdepend

undepend: xundepend

# DO NOT DELETE THIS LINE -- make depend depends on it.
adsactivity.o: adsactivity.c adsactivity.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsvariable.h \
  adspropertytype.h
adscks.o: adscks.c adsclockmanager.h adsclock.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  adspropertytype.h adsvariable.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h adscks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h hashlist.h \
  adsvaluation.h atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h adsactivity.h \
  adstransition.h adshypergraph.h adspropertyvaluation.h
adsclock.o: adsclock.c adsclock.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  adspropertytype.h adsvariable.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  /usr/include/stdio.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
adsclockconstraint.o: adsclockconstraint.c adsclockconstraint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h adsproperty.h \
  ../../gl/bool.h ../../gl/lstring.h adspropertytype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adsclock.h \
  adsvariable.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /usr/include/stdio.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
adsclockmanager.o: adsclockmanager.c adsclockmanager.h adsclock.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  adspropertytype.h adsvariable.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /usr/include/stdio.h
adseliminatepseudostatenodes.o: adseliminatepseudostatenodes.c \
  atddecisionstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atdiagram.h \
  atviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  adseliminatepseudostatenodes.h adshypergraph.h bag.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  atdtransitionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  ../../dg/hyperedge.h adsclock.h adsvariable.h adsedgelabelparse.h \
  adsclocktypes.h adspropertyvaluation.h
adshyperedge.o: adshyperedge.c adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adshypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h bag.h \
  adsvariable.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h
adshypergraph.o: adshypergraph.c adshypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h adsactivity.h \
  adsvariable.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h adsclock.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h adssemantics.h \
  atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h adscks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h hashlist.h \
  adsclockmanager.h atdtransitionedge.h adsvaluation.h adstransition.h
adsproperty.o: adsproperty.c adsproperty.h ../../gl/bool.h \
  ../../gl/lstring.h adspropertytype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h adsvariable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
adspropertyvaluation.o: adspropertyvaluation.c adspropertyvaluation.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h adsproperty.h \
  ../../gl/bool.h ../../gl/lstring.h adspropertytype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
adssemantics.o: adssemantics.c adsactivity.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h adssemantics.h \
  atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h adshypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h bag.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adscks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h hashlist.h \
  adsclockmanager.h adsclock.h adsvariable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h atdtransitionedge.h \
  adsvaluation.h atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h adstransition.h \
  initialstate.h state.h stnode.h adspropertyvaluation.h \
  adsedgelabelevaluationparse.h
adstransition.o: adstransition.c adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adstransition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h bag.h \
  adsvaluation.h atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h adsactivity.h \
  adscks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  hashlist.h adsclockmanager.h adsclock.h adsvariable.h atdiagram.h \
  atviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  adspropertyvaluation.h
adsvaluation.o: adsvaluation.c adsvaluation.h atdactionstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsactivity.h \
  bag.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adscks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h hashlist.h \
  adsclockmanager.h adsclock.h adsvariable.h atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  adspropertyvaluation.h adshypergraph.h
adsvariable.o: adsvariable.c adsvariable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  adspropertytype.h /usr/include/stdio.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
atchecks.o: atchecks.c atchecks.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h transition.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h initialstate.h \
  state.h stnode.h
atdactionstatenode.o: atdactionstatenode.c atdactionstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsactivity.h \
  atgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
atddecisionstatenode.o: atddecisionstatenode.c atddecisionstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
atdfinalstatenode.o: atdfinalstatenode.c atdfinalstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
atdiagram.o: atdiagram.c atdactionstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsactivity.h \
  atddecisionstatenode.h atdfinalstatenode.h atdwaitstatenode.h \
  atdinitialstatenode.h atdsynchronizationnode.h atdtransitionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptynode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/bullseye.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/roundedbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipsedbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidhorizontalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidverticalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/minidiamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h atchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h atwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h adshypergraph.h \
  bag.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adssemantics.h adscks.h hashlist.h adsclockmanager.h \
  adsclock.h adsvariable.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h adsvaluation.h \
  adstransition.h adseliminatepseudostatenodes.h adspropertyvaluation.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/temporalpropertydialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  adsmcoutputparse.h adsltlformulaparse.h
atdinitialstatenode.o: atdinitialstatenode.c atdinitialstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
atdsynchronizationnode.o: atdsynchronizationnode.c \
  atdsynchronizationnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
atdtransitionedge.o: atdtransitionedge.c atdtransitionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
atdwaitstatenode.o: atdwaitstatenode.c atdwaitstatenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
ateditor.o: ateditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h atwindow.h \
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
atgraph.o: atgraph.c atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
atupdatenodeshapetypecmd.o: atupdatenodeshapetypecmd.c \
  atupdatenodeshapetypecmd.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidhorizontalbar.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidverticalbar.h
atviewer.o: atviewer.c atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h atwindow.h \
  atupdatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
atwindow.o: atwindow.c atwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atdiagram.h \
  atviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h atgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MiniDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidHorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidVerticalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BullsEye.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/RoundedBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EllipsedBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm
bag.o: bag.c bag.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h ../../dg/subject.h atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsactivity.h
decisionpoint.o: decisionpoint.c decisionpoint.h stnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
draghlinecmd.o: draghlinecmd.c \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h transitionarrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h stviewer.h \
  draghlinecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
dragstlabelcmd.o: dragstlabelcmd.c transitionarrow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h initialstatebox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  dragstlabelcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragtextshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h
event.o: event.c event.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h rpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
eventset.o: eventset.c eventset.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h
hashlist.o: hashlist.c hashlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h adsvaluation.h \
  atdactionstatenode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h adsactivity.h \
  bag.h adshyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hyperedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h adscks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h adsclockmanager.h \
  adsclock.h adsvariable.h atdiagram.h atviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h adstransition.h
initialstatebox.o: initialstatebox.c \
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
  initialstatebox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h initialstate.h \
  state.h stnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
initialstate.o: initialstate.c initialstate.h state.h stnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/stringlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
klocation.o: klocation.c klocation.h stnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lvector.h ptrset.h \
  relevantset.h eventset.h ktransition.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h
kronos.o: kronos.c kronos.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h stdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h klocation.h \
  stnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lvector.h ptrset.h \
  relevantset.h eventset.h ktransition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h initialstate.h \
  state.h
ktransition.o: ktransition.c ktransition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lvector.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h klocation.h \
  stnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h ptrset.h \
  relevantset.h eventset.h
processgraphnode.o: processgraphnode.c processgraphnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h rpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
processgraphroot.o: processgraphroot.c processgraphroot.h \
  processgraphnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h rpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h
pschecks.o: pschecks.c pschecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
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
  psprocess.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
psdiagram.o: psdiagram.c psgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h psviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h pswindow.h \
  pschecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h psprocess.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  urlabeledbox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h psdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
pseditor.o: pseditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h pswindow.h \
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
psgraph.o: psgraph.c psgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
psprocess.o: psprocess.c psprocess.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h psgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h
psstubs.o: psstubs.c psstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h psdiagram.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h psviewer.h
psviewer.o: psviewer.c psviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h psdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h urlabeledbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h psprocess.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h pswindow.h
pswindow.o: pswindow.c pswindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h psdiagram.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h psviewer.h \
  psstubs.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h psgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Box.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm
ptrset.o: ptrset.c ptrset.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h ktransition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lvector.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h klocation.h \
  stnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h relevantset.h \
  eventset.h
relevantset.o: relevantset.c relevantset.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h eventset.h
rpdiagram.o: rpdiagram.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/replacedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/finddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h event.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  processgraphroot.h processgraphnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h rpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h rpviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/linestyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h rpwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniarrowellipse.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/roundedbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h rpdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h
rpeditor.o: rpeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h rpwindow.h \
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
rpgraph.o: rpgraph.c rpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  processgraphroot.h processgraphnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
rpupdatenodeshapetypecmd.o: rpupdatenodeshapetypecmd.c \
  rpupdatenodeshapetypecmd.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/roundedbox.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h rpdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h
rpviewer.o: rpviewer.c rpviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h rpwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  rpupdatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatenodeshapetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/updatetypecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h
rpwindow.o: rpwindow.c rpwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h rpdiagram.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h rpviewer.h \
  rpgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Dot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MiniArrowEllipse.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/RoundedBox.xbm
scchecks.o: scchecks.c scchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h
scdandedge.o: scdandedge.c scdandedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
scdandline.o: scdandline.c scdandline.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h
scdandstatebox.o: scdandstatebox.c scdandstatebox.h \
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
scdandstate.o: scdandstate.c scdandstate.h scnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scdcreateandlinecmd.o: scdcreateandlinecmd.c scdcreateandlinecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/createedgecmd.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h
scddecisionstate.o: scddecisionstate.c scddecisionstate.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scddefaultstate.o: scddefaultstate.c scddefaultstate.h scnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scdfinalstate.o: scdfinalstate.c scdfinalstate.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scdiagram.o: scdiagram.c scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h scwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/fillstyle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/dpoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h scdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/document.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/messagedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/dialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/viewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/scaler.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapeview.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/grid.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/roundedbox.h \
  scdandstatebox.h scdorstate.h scnode.h scdandstate.h scdandedge.h \
  scdtransitionedge.h adsclockconstraint.h adsproperty.h ../../gl/bool.h \
  ../../gl/lstring.h adspropertytype.h scdandline.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/blackdot.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/bullseye.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/minidiamond.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidhorizontalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidverticalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
  scddefaultstate.h scdfinalstate.h scddecisionstate.h \
  scdsynchronizationstate.h scviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h adsmcoutputparse.h \
  adsedgelabelparse.h adsclocktypes.h
scdorstate.o: scdorstate.c scdorstate.h scnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scdsynchronizationstate.o: scdsynchronizationstate.c \
  scdsynchronizationstate.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scdtransitionedge.o: scdtransitionedge.c scdtransitionedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  adsclockconstraint.h adsproperty.h ../../gl/bool.h ../../gl/lstring.h \
  adspropertytype.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h scnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
sceditor.o: sceditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h scwindow.h \
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
scgraph.o: scgraph.c scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
scnode.o: scnode.c scnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
scviewer.o: scviewer.c scwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/sizeshapebordercmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/sizeshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  scdcreateandlinecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/createedgecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h
scwindow.o: scwindow.c scwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h scviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h scdiagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h scgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/RoundedBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/AndStateBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BlackDot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BullsEye.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/MiniDiamond.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidHorizontalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/SolidVerticalBar.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Arrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedEmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm
smv.o: smv.c smv.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h initialstate.h \
  state.h stnode.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
state.o: state.c state.h stnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
stchecks.o: stchecks.c stchecks.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h transition.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h initialstate.h \
  state.h stnode.h
stdiagram.o: stdiagram.c stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h stviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h stwindow.h \
  stchecks.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramchecks.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/replacedialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/finddialog.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/selectiondialog.h \
  initialstate.h state.h stnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  decisionpoint.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hexagon.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  transitionarrow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  initialstatebox.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/box.h \
  stdiagram.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/printer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/pagesize.h
steditor.o: steditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h stwindow.h \
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
stgraph.o: stgraph.c stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
stnode.o: stnode.c stnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
stviewer.o: stviewer.c stwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h stviewer.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/selectareacmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/command.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/sizeshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polypoint.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/draghandlecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragshapecmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragshapescmd.h \
  dragstlabelcmd.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/dragtextshapecmd.h \
  draghlinecmd.h transitionarrow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodeshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shapetype.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/polygon.h
stwindow.o: stwindow.c stwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h stdiagram.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h stviewer.h \
  stgraph.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/LongBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/ArrowBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/TransitionArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Hexagon.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm
tcmbv.o: tcmbv.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h stwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h atwindow.h \
  pswindow.h rpwindow.h
transitionarrow.o: transitionarrow.c \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  transitionarrow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/gshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textshape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/textalign.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/shape.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/readdirection.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h
transition.o: transition.c transition.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h stgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/inputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/file.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/outputfile.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/stringlist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h
urlabeledbox.o: urlabeledbox.c urlabeledbox.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h psprocess.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h
