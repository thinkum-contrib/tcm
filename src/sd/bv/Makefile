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
