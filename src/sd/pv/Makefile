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
cpdcomponentnode.o: cpdcomponentnode.c cpdcomponentnode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
cpddependencyedge.o: cpddependencyedge.c cpddependencyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
cpdiagram.o: cpdiagram.c cpddependencyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  cpdrealizationedge.h cpdcomponentnode.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/node.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/hypergraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cpdinterfacenode.h \
  dpdresourcenode.h dpdcommunicationedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/note.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/comment.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/notebox.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/solidhorizontalbar.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/buildingblock.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/cube.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/miniellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/ellipse.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/line.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/lineend.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/commentlink.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/emptyedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/textbox.h cpdiagram.h \
  cpviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h cpwindow.h
cpdinterfacenode.o: cpdinterfacenode.c cpdinterfacenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
cpdrealizationedge.o: cpdrealizationedge.c cpdrealizationedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
cpeditor.o: cpeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h cpwindow.h \
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
cpgraph.o: cpgraph.c cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h
cpviewer.o: cpviewer.c cpviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/nodealign.h cpwindow.h
cpwindow.o: cpwindow.c cpwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cpdiagram.h \
  cpviewer.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BuildingBlock.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Dot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm
dpdcommunicationedge.o: dpdcommunicationedge.c dpdcommunicationedge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/edge.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/subject.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/thing.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/code.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/typename.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h
dpdiagram.o: dpdiagram.c dpdiagram.h cpdiagram.h cpviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h dpwindow.h \
  cpwindow.h
dpdresourcenode.o: dpdresourcenode.c dpdresourcenode.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h
dpeditor.o: dpeditor.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h dpwindow.h \
  cpwindow.h /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
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
dpwindow.o: dpwindow.c dpwindow.h cpwindow.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dpdiagram.h \
  cpdiagram.h cpviewer.h \
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
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagram.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/sequence.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/grafport.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/rectangle.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/xfont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/afont.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/color.h cpgraph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/graph.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menu.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/menuitem.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editstubs.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/BuildingBlock.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Comment.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Cube.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/Dot.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/NoteBox.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/EmptyLine.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DashedArrow.xbm \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/bitmaps/DottedLine.xbm
tcmpv.o: tcmpv.c \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/application.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mwidget.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/component.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/bool.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/lstring.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/llist.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/element.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/util.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/error.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/system.h cpwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/dg/diagramwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/bitmap.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/editwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mainwindow.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ui/mousecursor.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/toolkit.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/ed/drawingarea.h \
  /users/corbita/tcm/tcm2.20-TSQD-orion/src/gl/point.h dpwindow.h
